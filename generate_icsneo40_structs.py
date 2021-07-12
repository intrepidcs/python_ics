# run before: clang-format --style=mozilla -i include\ics\icsnVC40.h
import re
import os.path
from collections import OrderedDict
import sys
from subprocess import run, PIPE
from enum import Enum, auto

debug_print = True

class DataType(Enum):
    Unknown = auto()
    UnionAnnonomous = auto()
    Union = auto()
    StructAnnonomous = auto()
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
        self.names = []
        # list of CObject and CObjectMember
        self.members = []

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

def is_line_start_of_object(line):
    "Returns True if we are a c object (enum, struct, union)"
    object_names = ('enum', 'struct', 'union')
    is_start = [x for x in object_names if x in line]
    return bool(is_start)

def parse_object(f, pos=-1):
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
        # Grab the object name
        name = re.sub('typedef|struct|enum|union|\{|\s*', '', line)
        new_obj.is_anonymous = not bool(name)
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
                    embedded_object = parse_object(f)
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
        return new_obj
    finally:
        if pos != -1:
            f.seek(pos)
    raise RuntimeError("parse_object(): Failure. This is a bug and we shouldn't be here!")



def parse_struct_member(buffered_line):
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
        data_name_index = words.index(":")-1

        try:
            bitwise_length = int(
                re.search('\d*', words[words.index(":")+1]).group(0))
        except Exception as ex:
            if debug_print:
                print("EXCEPTION:", ex)
            bitwise_length = 0
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


def get_preferred_struct_name(name, struct_names):
    # Expects a dictionary object from get_struct_names()
    r = re.compile("^[sS].*")
    r_underscore = re.compile("^(?![_]).*")
    r_end_t = re.compile("^.*(_[tT])$")
    for k, v in struct_names.items():
        names = []
        names.append(k)
        names += v
        if not name in names:
            continue  # not the correct structure
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
        if k == name:
            return v[0]
        if name in names:
            return v[v.index(name)]
    raise ValueError("name '{}' is not part of struct_names".format(name))


def generate_ctype_struct_pyfile_from_dict(name, data, struct_data, path='.', is_enum=False):
    def get_data_type_list(data, unknown_only=False):
        types = OrderedDict()
        all_struct_names = get_struct_names(struct_data)
        if not 'members' in data:
            # We are probably an upper level before members here
            for k, v in data.items():
                for subtype in get_data_type_list(v, unknown_only):
                    types[subtype] = None
        else:
            for name, values in data['members'].items():
                #print("DEBUG: ", name, values)
                # Check for nested structs
                if isinstance(values, dict):
                    for subtype in get_data_type_list(values, unknown_only):
                        types[subtype] = None
                else:
                    ctypes_type = convert_to_ctype_object(values[0])
                    if ctypes_type:
                        if not unknown_only:
                            types[values[0]] = None
                    else:
                        try:
                            data_type = get_preferred_struct_name(
                                values[0], all_struct_names)
                            types[convert_to_snake_case(data_type)] = None
                        except ValueError as ex:
                            # We must be an enum or something...
                            # if debug_print:
                            #print("Unknown datatype {}:".format(values[0]), ex)
                            types[convert_to_snake_case(values[0])] = None

                        #types[convert_to_snake_case(values[0])] = None
        return types.keys()

    def convert_to_snake_case(name):
        # return name
        s1 = re.sub('(.)([A-Z][a-z]+)', r'\1_\2', name)
        s2 = re.sub('([a-z0-9])([A-Z])', r'\1_\2', s1).lower()
        return re.sub(r'(_)\1{1,}', '_', s2)

    def convert_to_ctype_object(data_type):
        if data_type == 'unsigned':
            data_type = 'uint32_t'
        elif data_type == 'void *' or data_type == 'void*':
            data_type = 'void_p'
        elif data_type == 'unsigned char':
            data_type = 'ubyte'
        elif data_type == 'unsigned long':
            data_type = 'ulong'
        elif data_type == 'unsigned short':
            data_type = 'ushort'
        elif data_type == 'descIdType':
            data_type = 'int16_t'
        elif data_type == 'e_device_settings_type':
            data_type == 'int32_t'

        #print("DEBUG:", data_type)
        is_pointer = '*' in data_type
        # Try to convert to ctypes type
        try:
            import ctypes
            eval("ctypes.c_{}".format(re.sub('_t*|\**', '', data_type)))
            type = 'ctypes.c_' + re.sub('_t*|\**', '', data_type)
            if is_pointer:
                type = 'ctypes.POINTER({})'.format(type)
                #print("DEBUG: POINTER TYPE:", type)
            return type
        except Exception as ex:
            #print("EXCEPTION", ex)
            return None
            """
            if isinstance(values, dict):
                type = name
            else:
                type = values[0]
            """

    def write_enum(class_name, data, f):
        f.write('from enum import IntEnum\n\n')

        f.write('class {}(IntEnum):\n'.format(class_name))
        f.write('    """A ctypes-compatible IntEnum superclass."""\n')
        f.write('    @classmethod\n')
        f.write('    def from_param(cls, obj):\n')
        f.write('        return int(obj)\n')
        f.write('\n')
        for name, values in data['members'].items():
            f.write('    {} = {}\n'.format(name, values[0]))
        f.write('\n\n')
        f.write("# Extra names go here:\n")
        for name in data['names']:
            if name == class_name:
                continue
            f.write('{} = {}\n'.format(re.sub('^\*', '', name), class_name))
        f.write("# End of extra names\n")
        f.write('\n')

    def write_struct(class_name, data, f, struct_data, parent_object_name):
        if is_enum:
            write_enum(class_name, data, f)
            return

        # Class definition
        if 'union' in data:
            if data['union']:
                f.write('class {}(ctypes.Union):\n'.format(class_name))
            else:
                f.write('class {}(ctypes.Structure):\n'.format(class_name))
        else:
            f.write('class {}(ctypes.Structure):\n'.format(class_name))

        # Structure pack size
        try:
            pack_size = data['pack']
            if pack_size != 0:
                f.write("    _pack_ = {}\n".format(pack_size))
        except KeyError:
            pass
        try:
            # Grab all the anonymous names here
            anonymous_objects = []
            for name, values in data['members'].items():
                if 'anonymous' in values and values['anonymous'] == True:
                    anonymous_objects.append(name)
            if len(anonymous_objects):
                object_str_list = ', '.join([f'"{c}"' for c in anonymous_objects])
                f.write(f"    _anonymous_ = ({object_str_list},)\n")
        except KeyError:
            pass
        f.write('    _fields_ = [\n')
        # write the fields
        for name, values in data['members'].items():
            if isinstance(values, dict):
                # This is an inner struct
                pass

            # expand the values
            if not isinstance(values, dict):
                data_type, array_length, bitwise_length, last_comment = values
                # print(values)
            else:
                data_type = 'nope'
                array_length = 0
                bitwise_length = 0
                last_comment = ''

            # Try to convert to ctypes type
            dtype = convert_to_ctype_object(data_type)
            if not dtype and isinstance(values, dict):
                # type is a nested struct we will generate another class for
                data_types = get_data_type_list(data, True)
                dtype = name
            elif not dtype:
                try:
                    preferred_name = get_preferred_struct_name(
                        values[0], get_struct_names(struct_data))
                    dtype = convert_to_snake_case(preferred_name)
                except ValueError as ex:
                    # We must be an enum
                    dtype = convert_to_snake_case(values[0])
                    print("WARNING: UNKNOWN TYPE:", dtype,
                          "Defaulting to ctypes.c_int type...")
                    # We have no way of telling if this is an enum and there is only one right now
                    # so we are going to be lazy here and just default to c_int... (e_device_settings)
                    dtype = 'ctypes.c_int'

            # make the comment a python comment
            if last_comment:
                last_comment = "# " + last_comment

            if bitwise_length > 0:
                f.write("        ('{}', {}, {}), {}\n".format(
                    name, dtype, bitwise_length, last_comment))
            elif array_length > 0:
                f.write("        ('{}', {} * {}), {}\n".format(name,
                                                               dtype, array_length, last_comment))
            else:
                f.write("        ('{}', {}), {}\n".format(
                    name, dtype, last_comment))

        f.write('    ]\n\n')

        f.write("# Extra names go here:\n")
        for name in data['names']:
            if name == class_name:
                continue
            f.write('{} = {}\n'.format(re.sub('^\*', '', name), class_name))
        f.write("# End of extra names\n")
        f.write('\n')

    fixed_name = convert_to_snake_case(name)

    fname = '{}.py'.format(fixed_name)
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
        f.write(
            '# This file was auto generated; Do not modify, if you value your sanity!\n')
        f.write('import ctypes\n')
        f.write('\n')
        if is_enum:
            write_struct(fixed_name, data, f, struct_data, '')
        else:
            all_data_types = get_data_type_list(struct_data, True)
            data_types = get_data_type_list(data, True)
            if len(data_types):
                f.write('try: # {}\n'.format(len(data_types)))
                for type in data_types:
                    if not type in all_data_types:
                        f.write("# ")
                        print("WARNING: data_type import will fail:", type)
                    f.write("    from {} import {}\n".format(type, type))
                f.write('except:\n')
                for type in data_types:
                    f.write(
                        "    from ics.structures.{} import {}\n".format(type, type))
                f.write('\n')
            def write_inner_structs_or_unions(fixed_name, data, struct_data, f, parent_object_name):
                if not 'members' in data:
                    return
                for name, values in data['members'].items():
                    if isinstance(values, dict) and 'members' in values:
                        # This is an inner struct/union
                        # Recursively write anything deeper inside
                        write_inner_structs_or_unions(fixed_name, values, struct_data, f, name)
                        try:
                            f.write('# {}\n'.format(name))
                            write_struct(name, values, f, struct_data, fixed_name)
                        except:
                            print('VALUES: ', values)
                            raise
            write_inner_structs_or_unions(fixed_name, data, struct_data, f, fixed_name)
            write_struct(fixed_name, data, f, struct_data, fixed_name)
    return fname, fname_with_path


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
                    elif re.match('#pragma.*pack.*.*push.*', line):
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
                    obj = parse_object(f)
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

def generate(filename):
    import shutil
    import json
    import os
    basename = os.path.basename(filename)
    filename = format_file(filename)
    c_objects, enum_objects = parse_header_file(filename)
    # print the data to stdout
    if debug_print:
        import pprint
        pp = pprint.PrettyPrinter(indent=1, width=140)
        for c_object in c_objects:
            pp.pprint(c_object.to_ordered_dict())
        for enum_object in enum_objects:
            pp.pprint(enum_object.to_ordered_dict())

    # print all datatypes
    if False:
        data_types = []
        for key in struct_data.keys():
            for value in struct_data[key]['members'].values():
                if isinstance(value, dict):
                    # for sub_value in value.values():
                    #    print(sub_value)
                    #    data_types.append(sub_value[0])
                    pass
                else:
                    data_types.append(value[0])
        # print(data_types)
        print(sorted(list(dict.fromkeys(data_types))))
    # make the json file
    j = json.dumps(struct_data, indent=4, sort_keys=False)
    with open(f'{basename}.json', 'w+') as f:
        f.write(j)
    j = json.dumps(enum_data, indent=4, sort_keys=False)
    with open(f'{basename}.enums.json', 'w+') as f:
        f.write(j)
    # generate the python files
    output_dir = './ics/structures'
    print(f"Removing {output_dir}...")
    try:
        shutil.rmtree(output_dir)
    except FileNotFoundError:
        pass
    ignore_names = ['__fsid_t', 'NeoDevice', 'neo_device', 'NeoDeviceEx', 'neo_device_ex', 'icsSpyMessage', 'icsSpyMessageJ1850', 'ics_spy_message', 'ics_spy_message_j1850'] 
    file_names = []
    prefered_names = []
    for name in struct_data:
        prefered_name = get_preferred_struct_name(
            name, get_struct_names(struct_data))
        if name in ignore_names or prefered_name in ignore_names:
            continue
        #file_name, file_path = generate_ctype_struct_pyfile_from_dict(re.sub('^_', '', name), struct_data[name], struct_data, output_dir)
        file_name, file_path = generate_ctype_struct_pyfile_from_dict(
            prefered_name, struct_data[name], struct_data, output_dir)
        print("Generated {}...".format(file_name))
        file_names.append(file_name)
        prefered_names.append(prefered_name)
    # enums
    for name in enum_data:
        prefered_name = get_preferred_struct_name(
            name, get_struct_names(enum_data))
        #file_name, file_path = generate_ctype_struct_pyfile_from_dict(re.sub('^_', '', name), struct_data[name], struct_data, output_dir)
        file_name, file_path = generate_ctype_struct_pyfile_from_dict(
            prefered_name, enum_data[name], enum_data, output_dir, True)
        file_names.append(file_name)

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