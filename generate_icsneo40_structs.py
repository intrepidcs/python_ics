# run before: clang-format --style=mozilla -i include\ics\icsnVC40.h
import re
import os.path
from collections import OrderedDict
import sys
from subprocess import run, PIPE
from enum import Enum, auto
import random
import ctypes

debug_print = False

__unique_numbers = []
def get_unique_number():
    "Returns a unique integer"
    global __unique_numbers
    random.seed(1234)
    while True:
        value = random.randint(0, 65535)
        if value not in __unique_numbers:
            __unique_numbers.append(value)
            return value


class DataType(Enum):
    Unknown = auto()
    Union = auto()
    Struct = auto()
    Enum = auto()

class CVariable(object):
    name = ""
    data_type = None
    array_length = None
    bitfield_size = False
    is_enum = False
    enum_value = None

    def __init__(self, name, data_type, array_length, bitfield_size, enum_value=None):
        self.name = name
        self.data_type = data_type
        self.array_length = array_length
        self.bitfield_size = bitfield_size
        self.enum_value = enum_value
        self.is_enum = bool(self.enum_value)
    
    def __repr__(self):
        return f'<{self.__class__.__name__} {self.name} {self.data_type} @ {hex(id(self))}>'

    def to_ordered_dict(self):
        od = OrderedDict()
        od['name'] = self.name
        od['data_type'] = self.data_type
        od['array_length'] = self.array_length
        od['bitfield_size'] = self.bitfield_size
        od['is_enum'] = self.is_enum
        od['enum_value'] = self.enum_value
        return od

class CEnum(CVariable):
    def __init__(self, name, value):
        super().__init__(name, "int", 0, 0, value)


class CObject(object):
    def __init__(self):
        self.data_type = DataType.Unknown
        self.is_anonymous = False
        self.packing = None
        self.preferred_name = ""
        self.names = []
        # list of CObject and CObjectMember
        self.members = []
        self.enum_last_value = None

    def __repr__(self):
        if self.names:
            name = self.names[-1]
        else:
            name = 'Anon'
        
        if self.data_type == DataType.Struct:
            t_name = 'Struct'
        elif self.data_type == DataType.Union:
            t_name = 'Union'
        elif self.data_type == DataType.Enum:
            t_name = 'Enum'
        else:
            t_name = 'Unknown'

        return f'<{self.__class__.__name__} {name} {t_name} {len(self.members)} members @ {hex(id(self))}>'
    
    def to_ordered_dict(self):
        od = OrderedDict()
        if self.data_type == DataType.Struct:
            t_name = 'Struct'
        elif self.data_type == DataType.Union:
            t_name = 'Union'
        elif self.data_type == DataType.Enum:
            t_name = 'Enum'
        else:
            t_name = 'Unknown'

        od['names'] = self.names
        od['data_type'] = t_name
        od['packing'] = self.packing
        od['is_anonymous'] = self.is_anonymous
        od['members'] = []
        for member in self.members:
            od['members'].append(member.to_ordered_dict())
        return od

    def assign_preferred_name(self, is_embedded=False):
        """This assigns a name to the object if we are nameless and anonymous, safe to call multiple times."""
        self.preferred_name = get_preferred_struct_name(self.names)
        if self.is_anonymous and not self.preferred_name:
            self.preferred_name = f"Nameless{get_unique_number()}"
        if self.preferred_name and not is_embedded:
            self.preferred_name = convert_to_snake_case(self.preferred_name)
        

def is_line_start_of_object(line):
    "Returns True if we are a c object (enum, struct, union)"
    def find_whole_word(w):
        return re.compile(r'\b({0})\b'.format(w), flags=re.IGNORECASE).search
    
    object_names = ('enum', 'struct', 'union')
    is_start = [x for x in object_names if find_whole_word(x)(line) != None]
    return bool(is_start)

# This contains all the objects that don't pass convert_to_ctype_object
NON_CTYPE_OBJ_NAMES = []
# This contains a list of every object we collected
ALL_C_OBJECTS = []

def get_object_from_name(name):
    global ALL_C_OBJECTS
    for obj in ALL_C_OBJECTS:
        if name in obj.preferred_name or name in obj.names:
            return obj
    return None

def parse_object(f, pos=-1, pack_size=None, is_embedded=False):
    """
    takes a file object and returns a class with the object data.
    if pos is -1, don't reset position when finished
    """
    start_pos = f.tell()
    opening_bracket_count = 0
    opening_bracket_count = 0
    try:
        # Read the first line and make sure we have a C Object
        line = f.readline()
        if not line:
            raise RuntimeError("Reached end of file when we shouldn't have!")
        # Remove new lines
        line = line.strip()
        if not is_line_start_of_object(line):
            raise RuntimeError("Current line is not the declaration of a C Object (enum/struct/union)")
        # Lets start parsing the lines for our C Object
        new_obj = CObject()
        new_obj.packing = pack_size
        # Grab the object name
        name = re.sub('typedef|struct|enum|union|\{|\s*', '', line)
        # Only append the name if its not anonymous
        if name:
            new_obj.names.append(name)
        # Determine the type of object
        if 'struct' in line:
            new_obj.data_type = DataType.Struct
        elif 'union' in line:
            new_obj.data_type = DataType.Union
        elif 'enum' in line:
            new_obj.data_type = DataType.Enum
        else:
            new_obj.data_type = DataType.Unknown
        # Time to parse the rest of the object
        last_pos = f.tell()
        line = f.readline()
        finished = False
        while line:
            try:
                # Remove new lines
                line = line.strip()
                if not line:
                    continue
                # Parse any embedded objects
                if is_line_start_of_object(line):
                    f.seek(last_pos)
                    embedded_object = parse_object(f, -1, pack_size, True)
                    new_obj.members.append(embedded_object)
                    continue
                opening_bracket_count += line.count('{')
                opening_bracket_count -= line.count('}')
                # Determine if we are at the end of the struct
                if opening_bracket_count == 0 and re.match('}.*;', line):
                    extra_names = ''.join(line.split()).strip('};').split(',')
                    try:
                        # Remove dangling empty string
                        extra_names.remove('')
                    except ValueError:
                        pass
                    if extra_names:
                        new_obj.names.extend(extra_names)
                    # We are finally done
                    finished = True
                    break
                # Nothing to do with this line anymore
                if re.match('.*{.*', line):
                    continue
                # Parse the member
                if new_obj.data_type == DataType.Enum:
                    member = CEnum(*parse_enum_member(line))
                elif new_obj.data_type == DataType.Struct:
                    member = CVariable(*parse_struct_member(line))
                elif new_obj.data_type == DataType.Union:
                    member = CVariable(*parse_struct_member(line))
                new_obj.members.append(member)
            finally:
                # Grab the position before we read the next line
                if not finished:
                    last_pos = f.tell()
                    line = f.readline()
        new_obj.is_anonymous = not bool(new_obj.names)
        new_obj.assign_preferred_name(is_embedded)
        # Append the objects to a global list for parsing later
        global ALL_C_OBJECTS
        ALL_C_OBJECTS.append(new_obj)
        return new_obj
    finally:
        if pos != -1:
            f.seek(pos)
    raise RuntimeError("parse_object(): Failure. This is a bug and we shouldn't be here!")



def parse_struct_member(buffered_line):
    # unsigned : 31;
    # unsigned char bIPV6_Address[16];
    # unsigned asdf[12];
    # unsigned : 15;
    # unsigned test : 1;
    # uint8_t test;
    # uint8_t test2[12];
    # STRUCT_TYPE asdf;
    # unsigned char test
    #        [16]; // why not make something defined like this?
    # uint8_t data[4 * 1024]; /* The data */

    # remove all unneeded whitespace
    #print("DEBUG BEFORE:", buffered_line)
    # if len(buffered_line.split('\n')):
    #    new_buffered_line = ''
    #    for line in buffered_line.split('\n'):
    #        new_buffered_line += re.sub('{|union|}|;', '', line) + '\n'
    #    buffered_line = new_buffered_line
    buffered_line = re.sub("\s*\[", "[", ' '.join(buffered_line.split()))
    #print("DEBUG AFTER:", buffered_line)

    # Figure out if we are an array type and get the array length
    array_subsection = re.search('\[.*\]', buffered_line)
    is_array = array_subsection is not None
    if is_array:
        array_length = int(eval(array_subsection.group(0).strip('[]')))
    else:
        array_length = 0
    # Remove the array portion
    buffered_line = re.sub('\[.*\]', '', buffered_line)
    # split up the remaining
    words = buffered_line.split()
    if not len(words):
        return None, '', 0, 0  # data_type, array_length, bitwise_length
    if ':' in words:
        # we are a bitfield ;(
        try:
            bitwise_length = int(
                re.search('\d*', words[words.index(":")+1]).group(0))
        except Exception as ex:
            if debug_print:
                print("EXCEPTION:", ex)
            bitwise_length = 0
        # see if we get a valid ctype object before : to check for things like "unsigned : 31;"
        pre_colon_text = ' '.join(words[:words.index(":")])
        check_data_type = convert_to_ctype_object(pre_colon_text)
        if check_data_type:
            data_name = ''
            data_type = pre_colon_text
        else:
            data_name_index = words.index(":")-1
            data_name = words[data_name_index]
            data_type = ' '.join(words[0:data_name_index])
    else:
        bitwise_length = 0
        data_name = words[-1]
        data_type = ' '.join(words[0:len(words)-1])
        if data_name.startswith('*'):
            data_type += ' *'
            data_name = data_name.lstrip('*')
    # DEBUG: ['uint8_t', 'MACAddress[6];']
    # print("DEBUG:", words, buffered_line)

    # remove stuff that shouldn't be in the name
    data_name = re.sub('{|{|}|\s*', '', data_name)
    data_type = re.sub('union|{|{|}', '', data_type)
    data_type = data_type.strip()
    if not data_type:
        data_name = ''

    return re.sub('\[.*\]|;', '', data_name), data_type, array_length, bitwise_length


def parse_enum_member(buffered_line):
    # VARIABLE_NAME,
    # VARIABLE_NAME = 0,

    # remove all unneeded whitespace
    buffered_line = re.sub("\s*\[", "[", ' '.join(buffered_line.split()))

    if '=' in buffered_line:
        name = buffered_line.split('=')[0]
        value = buffered_line.split('=')[1]
        value = re.sub('{|{|}|,|\s*', '', value)
        try:
            value = int(value)
        except ValueError as ex:
            if '0X' in value.upper():
                value = int(value, 16)
            elif '0B' in value.upper():
                value = int(value, 2)
    else:
        name = re.sub(',', '', buffered_line)
        value = None
    return name, value


def get_struct_name_from_header(line):
    # line.split('struct ')[-1]
    struct_name = re.sub('typedef|struct|enum|union|\{|\s*', '', line)
    if not struct_name:  # == 'typedef struct':
        anonymous_struct = True
        struct_name = 'anonymous'
    elif '{' == struct_name:
        anonymous_struct = True
        struct_name = 'anonymous'
    else:
        anonymous_struct = False
    return struct_name, anonymous_struct


def get_struct_names(data):
    names = OrderedDict()
    # Pack all the names into dictionary
    # key = the "key" in the data
    # values = list of other names
    for name in data.keys():
        if name in ('names', 'pack'):
            continue
        if 'names' in data[name]:
            names[name] = data[name]['names']
        else:
            names[name] = [name, ]
    return names

def get_preferred_struct_name(_names):
    # Remove the reference
    names = _names[:]
    r = re.compile("^[sS].*")
    r_underscore = re.compile("^(?![_]).*")
    r_end_t = re.compile("^.*(_[tT])$")
    # Remove all instances of _t at end unless that is all we have
    setting_structures_with_t = list(filter(r_end_t.match, names))
    if len(setting_structures_with_t):
        if len(setting_structures_with_t) != len(names):
            for name in setting_structures_with_t:
                names.remove(name)
    # Find any that start with 'S' and prefer that
    setting_structures = list(filter(r.match, names))
    if setting_structures:
        return setting_structures[0]
    # Find any that don't start with _ and prefer that
    setting_structures = list(filter(r_underscore.match, names))
    if setting_structures:
        return setting_structures[0]
    try:
        return names[0]
    except IndexError as _:
        # We didn't find any names to deal with...
        return None


def convert_to_snake_case(name):
    # return name
    s1 = re.sub('(.)([A-Z][a-z]+)', r'\1_\2', name)
    s2 = re.sub('([a-z0-9])([A-Z])', r'\1_\2', s1).lower()
    return re.sub(r'(_)\1{1,}', '_', s2)

def convert_to_ctype_object(data_type):
    ctype_types = {
        "c_bool": ("_Bool", "bool"),
        "c_char": ("char",),
        "c_wchar": ("wchar_t",),
        "c_byte": (),
        "c_ubyte": ("unsigned char",),
        "c_short": ("short",),
        "c_ushort": ("unsigned short",),
        "c_int": ("int",),
        "c_uint": ("unsigned", "unsigned int",),
        "c_long": ("long",),
        "c_ulong": ("unsigned long",),
        "c_longlong": ("__int64", "long long",),
        "c_ulonglong": ("unsigned __int64", "unsigned long long",),
        "c_size_t": ("size_t",),
        "c_ssize_t": ("ssize_t", "Py_ssize_t",),
        "c_float": ("float",),
        "c_double": ("double",),
        "c_void_p": ("void*", "void *",),
    }
    # Add all the intX_t types
    for d in [8, 16, 32, 64]:
        ctype_types[f'c_int{d}'] = (f'int{d}_t',)
        ctype_types[f'c_uint{d}'] = (f'uint{d}_t',)
    
    # This is dirty but we don't parse typedefs...
    ctype_types["c_uint16"] = ctype_types["c_uint16"] + ("descIdType",)

    is_pointer = '*' in data_type and not 'void' in data_type
    for ctype_type, c_types in ctype_types.items():
        for c_type in c_types:
            if is_pointer:
                data_type = data_type.replace('*', '')
            if c_type == data_type:
                try:
                    t = f"ctypes.{ctype_type}"
                    eval(t)
                    if is_pointer:
                        t = f'ctypes.POINTER({t})'
                    return t
                except AttributeError as ex:
                    return None 
    return None

def format_file(filename):
    import os
    processed_fname = os.path.basename(filename)
    name, ext = os.path.splitext(processed_fname)
    processed_fname = f'{name}_processed{ext}'
    #processed_fname = "icsnVC40_processed.h"
    # Run it through the preprocessor
    # clang -E -P .\include\ics\icsnVC40.h -o output.h
    result = run(["clang", "-E", "-P", filename, "-o", processed_fname], stdout=PIPE, stderr=PIPE)
    result.check_returncode()

    # Format the file
    result = run(["clang-format", "-i", "--style",
                  "{BasedOnStyle: Mozilla, ColumnLimit: '200'}", processed_fname], stdout=PIPE, stderr=PIPE)
    result.check_returncode()

    return processed_fname

def parse_header_file(filename):
    with open(filename, 'r') as f:
        pack_size = 0
        line_count = 0
        last_pos = f.tell()
        c_objects = []
        enum_objects = []
        pushed_last_pack_size = False
        line = f.readline()
        while line:
            try:
                # Remove newlines
                line = line.strip()
                line_count += 1
                # Remove all unneeded whitespace
                line = ' '.join(line.split())
                # Remove preprocessor statements
                if line.startswith("#"):
                    # get the pack size
                    if re.match('#pragma.*pack.*.*pop.*', line):
                        if pushed_last_pack_size:
                            pack_size = last_pack_size
                            pushed_last_pack_size = False
                        else:
                            pack_size = 0
                    elif re.match('#pragma.*pack.*.*push.*', line) or re.match('#pragma.*pack\(\d\)', line):
                        try:
                            pack_size = int(re.search('\d{1,}', line).group(0))
                        except AttributeError:
                            if not 'push' in line:
                                raise
                            pushed_last_pack_size = True
                            last_pack_size = pack_size
                            pack_size = 0
                        if debug_print:
                            print("PACK SIZE:", pack_size)
                    elif re.match('#define.*', line) and len(line.split(' ')) == 3 and not '\\' in line and not 'sizeof' in line:
                        # preprocessor define that can be used as a number in array sizes...
                        # we are going to hack the variable into the module's globals so we can eval() it later
                        words = line.split(' ')
                        if debug_print:
                            print("ADDING {} to globals with value of {}".format(
                                words[1], words[2]))
                        globals()[words[1]] = eval(words[2])
                    continue
                # Process the object
                if is_line_start_of_object(line):
                    pos = f.tell()
                    f.seek(last_pos)
                    obj = parse_object(f, -1, pack_size)
                    if obj.data_type == DataType.Struct:
                        obj.packing = pack_size
                    if obj.data_type == DataType.Enum:
                        enum_objects.append(obj)
                    else:
                        c_objects.append(obj)
            finally:
                last_pos = f.tell()
                line = f.readline()
        return c_objects, enum_objects

def generate(filename='include/ics/icsnVC40.h'):
    import shutil
    import json
    import os
    basename = os.path.basename(filename)
    filename = format_file(filename)
    c_objects, enum_objects = parse_header_file(filename)
    # make the json file
    c_objects_converted = []
    enum_objects_converted = []
    for c_object in c_objects:
        c_objects_converted.append(c_object.to_ordered_dict())
    for enum_object in enum_objects:
        enum_objects_converted.append(enum_object.to_ordered_dict())
    j = json.dumps(c_objects_converted, indent=4, sort_keys=False)
    with open(f'{basename}.json', 'w+') as f:
        f.write(j)
    j = json.dumps(enum_objects_converted, indent=4, sort_keys=False)
    with open(f'{basename}.enums.json', 'w+') as f:
        f.write(j)
    # generate the python files
    output_dir = './ics/structures'
    print(f"Removing {output_dir}...")
    try:
        shutil.rmtree(output_dir)
    except FileNotFoundError:
        pass
    ignore_names = [
        '__fsid_t', '__darwin_pthread_handler_rec', '_mbstate_t',
        '_opaque_pthread_attr_t', '_opaque_pthread_cond_t', '_opaque_pthread_condattr_t',
        '_opaque_pthread_mutex_t', '_opaque_pthread_mutexattr_t', '_opaque_pthread_once_t',
        '_opaque_pthread_rwlock_t', '_opaque_pthread_rwlockattr_t', '_opaque_pthread_t',
        'NeoDevice', 'neo_device', 'NeoDeviceEx', 'neo_device_ex',
        'icsSpyMessage', 'icsSpyMessageJ1850', 'ics_spy_message', 'ics_spy_message_j1850']
    file_names = []
    prefered_names = []
    all_objects = c_objects + enum_objects
    print(f"Generating python files objects...")
    ignored_enum_count = 0
    for c_object in all_objects:
        # TODO: Bypass all anonymous enums
        if c_object.data_type == DataType.Enum:
            if c_object.is_anonymous:
                ignored_enum_count += 1
                continue
        # Bypass all the ignore_names above
        names = c_object.names
        names.append(c_object.preferred_name)
        if set(names) & set(ignore_names):
            continue
        # Generate the python file for the c_object
        file_name, file_path = generate_pyfile(c_object, output_dir)
        if debug_print:
            print(file_name, file_path)
        file_names.append(file_name)
    
    # Verify we don't have any unknown data types here
    global NON_CTYPE_OBJ_NAMES
    global ALL_C_OBJECTS 
    errors = False
    for obj_name in NON_CTYPE_OBJ_NAMES:
        obj = get_object_from_name(obj_name)
        if not obj:
            print(f"Warning: Not a valid object: {obj_name}")
            errors = False
    if errors:
        raise RuntimeError("Failed to parse all objects properly")
    else:
        print(f"Generated all python {len(all_objects)-ignored_enum_count} files.")

    # Generate __init__.py and add all the modules to __all__
    with open(os.path.join(output_dir, '__init__.py'), 'w+') as f:
        f.write("__all__ = [\n")
        for file_name in file_names:
            fname = re.sub('(\.py)', '', file_name)
            r = re.compile('(' + fname + ')')
            if list(filter(r.match, ignore_names)):
                #print("IGNORING:", fname)
                continue
            f.write('    "')
            f.write(fname)
            f.write('",\n')
        f.write("]\n")
    # write a hidden_import python file for pyinstaller
    with open('./ics/hiddenimports.py', 'w+') as f:
        f.write('hidden_imports = [\n')
        for file_name in file_names:
            fname = re.sub('(\.py)', '', file_name)
            r = re.compile('(' + fname + ')')
            if list(filter(r.match, ignore_names)):
                #print("IGNORING:", fname)
                continue
            f.write(f'    "ics.structures.{fname}",\n')
        f.write(']\n\n')

    # Verify We can at least import all of the modules - quick check to make sure parser worked.
    # TODO: This is broke
    """
    sys.path.insert(0, output_dir)
    for file_name in file_names:
        import_line = "from ics.structures import {}".format(
            re.sub('(\.py)', '', file_name))
        try:
            print("Importing / Verifying {}...".format(file_name))
            exec(import_line)
        except Exception as ex:
            print("ERROR: ", ex, 'IMPORT LINE:', import_line)
    """
    print("Done.")

def _write_c_object(f, c_object):
    # Write the header
    if c_object.data_type == DataType.Struct:
        f.write(f'class {c_object.preferred_name}(ctypes.Structure):\n')
    elif c_object.data_type == DataType.Union:
        f.write(f'class {c_object.preferred_name}(ctypes.Union):\n')
    elif c_object.data_type == DataType.Enum:
        f.write(f'class {c_object.preferred_name}(enum.IntEnum):\n')
        f.write('    """A ctypes-compatible IntEnum superclass."""\n')
        f.write('    @classmethod\n')
        f.write('    def from_param(cls, obj):\n')
        f.write('        return int(obj)\n')
        f.write('\n')
    else:
        raise ValueError("CObject is not of a known data type!")
    
    # Write the rest of the header for structs/unions
    if c_object.data_type in (DataType.Struct, DataType.Union):
        # Setup the packing
        if c_object.packing:
            f.write(f'    _pack_ = {c_object.packing}\n')
        # Grab all the anonymous names
        anonymous_names = []
        for member in c_object.members:
            if isinstance(member, CObject) and member.is_anonymous:
                anonymous_names.append(member.preferred_name)
        if anonymous_names:
            f.write(f'    _anonymous_  = {str(tuple(anonymous_names))}\n')
        f.write(f'    _fields_ = [\n')
    
    # Write the members
    for member in c_object.members:
        if c_object.data_type == DataType.Enum:
            enum_value = member.enum_value
            if enum_value == None:
                if c_object.enum_last_value != None:
                    enum_value = 'enum.auto()'
                    c_object.enum_last_value += 1
                else:
                    # https://docs.python.org/3/library/enum.html#enum.auto
                    # By default, the initial value starts at 1.
                    c_object.enum_last_value = 0
                    enum_value = '0'
            elif c_object.enum_last_value == None:
                c_object.enum_last_value = 0
            f.write(f'    {member.name} = {enum_value}\n')
        else:
            # Struct/Union
            def _write_member(f, member, is_struct_or_union=False):
                # Get the ctypes data type
                if not is_struct_or_union:
                    data_type = convert_to_ctype_object(member.data_type)
                    # If we aren't a valid ctypes data type we are probably a struct
                    if not data_type:
                        #print(f"Warning: Couldn't find a valid ctype type for '{member.data_type}' in '{member.name}'")
                        global NON_CTYPE_OBJ_NAMES
                        NON_CTYPE_OBJ_NAMES.append(member.data_type)
                        data_type = member.data_type
                    obj = get_object_from_name(member.data_type)
                    if obj and obj.data_type == DataType.Enum:
                        # C enum types can be char, unsigned, signed but seem to default to
                        # 4 byte integer on most systems (even 64-bit)
                        # This is a potential hole but nothing we can do here
                        data_type = 'ctypes.c_int32'
                else:
                    data_type = member.data_type
                if member.bitfield_size:
                    f.write(f"        ('{member.name}', {data_type}, {member.bitfield_size}),\n")
                elif member.array_length:
                    f.write(f"        ('{member.name}', {data_type} * {member.array_length}),\n")
                else:
                    f.write(f"        ('{member.name}', {data_type}),\n")

            if isinstance(member, CVariable):
                _write_member(f, member, False)
            elif isinstance(member, CObject):
                _name = member.preferred_name
                _created_member = CVariable(_name, _name, 0, 0)
                _write_member(f, _created_member, True)
    
    # Finalize the _fields_ attribute and extra names
    if c_object.data_type in (DataType.Struct, DataType.Union):
        f.write(f'    ]\n')
    # Extra names here
    f.write('\n\n')
    for name in c_object.names:
        # Ignore the actual object name
        if name == c_object.preferred_name:
            continue
        f.write('{} = {}\n'.format(re.sub('^\*', '', name), c_object.preferred_name))
    f.write('\n')

def generate_pyfile(c_object, path):
    #name = get_preferred_struct_name(c_object.names)
    #c_object.preferred_name = convert_to_snake_case(name)
    # Make the fname and the path
    fname = f'{c_object.preferred_name}.py'
    fname_with_path = os.path.normpath(os.path.join(path, fname))
    # create the needed directories
    if not os.path.exists(os.path.split(fname_with_path)[0]):
        try:
            os.makedirs(os.path.split(fname_with_path)[0])
        except OSError as ex:
            import errno
            if ex.errno != errno.EEXIST:
                # Race condition handler, if someone else makes a directory after we check if exists
                raise
    with open(fname_with_path, 'w+') as f:
        # Write the boiler plate code
        f.write(
            '# This file was auto generated; Do not modify, if you value your sanity!\n')
        f.write('import ctypes\n')
        f.write('import enum\n')
        f.write('\n')
        # Generate all the imports
        def get_c_object_imports(c_object):
            import_names = []
            for member in c_object.members:
                # If CVariable and not a datatype then its a custom struct/union
                if isinstance(member, CVariable):
                    is_ctype_type = bool(convert_to_ctype_object(member.data_type))
                    if not is_ctype_type:
                        # Attempt to get the preferred name here.
                        obj = get_object_from_name(member.data_type)
                        if obj:
                            actual_data_type = obj.preferred_name
                        else:
                            actual_data_type = member.data_type
                        import_names.append(convert_to_snake_case(actual_data_type))
                elif isinstance(member, CObject):
                    import_names.extend(get_c_object_imports(member))
            # anonymous/nameless objects put an empty string in the list, lets remove it here
            import_names = [name for name in import_names if name]
            return sorted(set(import_names))
        
        import_names = get_c_object_imports(c_object)
        for import_name in (import_names):
            f.write(f"from ics.structures.{import_name} import *\n")
        f.write('\n\n')

        def _generate_inner_objects(f, c_object):
            for member in c_object.members:
                if isinstance(member, CObject):
                    _generate_inner_objects(f, member)
                    _write_c_object(f, member) 
        # generate all the inner objects
        _generate_inner_objects(f, c_object)
        # Finally write our main object
        _write_c_object(f, c_object)
    return fname, fname_with_path

if __name__ == '__main__':
    import sys
    import os
    try:
        filename = sys.argv[1]
        filename = os.path.normpath(filename)
        print(f"Parsing '{filename}'...")
    except IndexError as _:
        filename = 'include/ics/icsnVC40.h' 
    generate(filename)