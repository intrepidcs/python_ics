# run before: clang-format --style=mozilla -i include\ics\icsnVC40.h
import re
import os.path
from collections import OrderedDict
import sys
from subprocess import run, PIPE
from enum import Enum, auto

debug_print = False

class DataType(Enum):
    UnionAnnonomous = auto()
    Union = auto()
    StructAnnonomous = auto()
    Struct = auto()

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
    processed_fname = "icsnVC40_processed.h"
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
    # key = struct name, value = dict
    struct_data = OrderedDict()
    line_count = 0
    with open(filename, 'r') as f:
        inside_enum = False
        enum_name = ''
        enum_data = OrderedDict()
        enum_data_member = OrderedDict()
        anonymous_enum = False
        inside_struct = False
        struct_is_union = False
        inside_comment = False
        opening_bracket_count = 0
        struct_name = 'None'
        anonymous_struct = False
        buffered_line = ''
        struct_data_member = OrderedDict()
        last_comment = ''
        inside_inner_union = False
        inner_union_data_member = OrderedDict()
        inner_union_name = ''
        inner_anonymous_union = False
        #inner_union_data = OrderedDict()
        inside_inner_struct = False
        inner_anonymous_struct = False
        inner_struct_data_member = OrderedDict()
        inner_struct_name = ''
        #inner_struct_data = OrderedDict()
        inner_struct_inside_anonymous_union = False
        inner_union_has_structs = False
        pushed_last_pack_size = False
        inner_anonymous_data_member = OrderedDict()
        anonymous_struct_index = 0
        anonymous_union_index = 0


        pack_size = 0
        for line in f:
            line_count += 1
            # Remove any single line comments
            try:
                line, last_comment = line.split('//')
                #last_comment = last_comment.split()
                last_comment = ' '.join(last_comment.split())
                if debug_print:
                    print("COMMENT:", last_comment)
            except Exception as ex:
                line = line.split('//')[0]
                last_comment = ''
            line = re.sub('\/\*.*\*\/', '', line)
            # Handle C style comments /* comment */
            if inside_comment and '*/' in line:
                inside_comment = False
                # remove everything left inside the comment
                line = re.sub('.*\*\/', '', line)
            elif inside_comment:
                continue
            if not inside_comment and '/*' in line:
                inside_comment = True
                line = line.split('/*')[0]
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
            # we stripped out a lot of stuff, if nothing left we are done
            # if not line:
            #    continue
            # we need to parse enums first since they are used in structures
            if 'enum' in line and not inside_enum:
                inside_enum = True
                opening_bracket_count = line.count('{')
                enum_name, anonymous_enum = get_struct_name_from_header(line)
                if debug_print:
                    print(
                        '------- ENUM {} ---------------------------------'.format(enum_name))
                continue
            elif inside_enum:
                opening_bracket_count += line.count('{')
                opening_bracket_count -= line.count('}')
                if line == '{':
                    continue
                if opening_bracket_count == 0 and re.match('}.*;', line):
                    inside_enum = False
                    extra_names = ''.join(line.split()).strip('};').split(',')
                    if anonymous_enum and not extra_names[0]:
                        enum_data_member = OrderedDict()
                        continue  # we don't care about this one
                    elif anonymous_enum and extra_names:
                        enum_name = extra_names[0]
                    if enum_name not in enum_data:
                        enum_data[enum_name] = OrderedDict()
                    if not enum_name:
                        enum_data_member = OrderedDict()
                        continue  # we don't care about this one
                    enum_data[enum_name]['members'] = enum_data_member
                    enum_data_member = OrderedDict()
                    if extra_names:
                        enum_data[enum_name]['names'] = extra_names
                    # We need to update enum values that weren't specified.
                    # C/C++ standard states no value = increment
                    # initial value starts at 0
                    last_value = -1
                    for k, v in enum_data[enum_name]['members'].items():
                        if not v[0]:
                            last_value += 1
                            enum_data[enum_name]['members'][k][0] = last_value
                        else:
                            last_value = int(v[0])
                    if debug_print:
                        print(
                            '------- Extra ENUM Names: {} -------------------------\n'.format(' '.join(extra_names)))
                    continue

                name, value = parse_enum_member(line)
                if name:
                    enum_data_member[name] = [value, last_comment]
                if debug_print:
                    print('{:04d} {} {} {} line: "{}" enum_name: "{}" enum_type: "{}"'.format(line_count, int(
                        inside_comment), int(inside_enum), opening_bracket_count, line, name, value))
                continue

            # Finally determine if we are inside a struct and get the name
            if ('struct' in line or 'union' in line) and not inside_struct:
                inside_struct = True
                struct_is_union = 'union' in line
                opening_bracket_count = line.count('{')
                struct_name, anonymous_struct = get_struct_name_from_header(
                    line)
                if debug_print:
                    print(
                        '------- {} ---------------------------------'.format(struct_name))
                continue
            # Hey we are finally inside ;)
            if inside_struct:
                opening_bracket_count += line.count('{')
                opening_bracket_count -= line.count('}')
                # Determine if we are at the end of the struct
                if opening_bracket_count == 0 and re.match('}.*;', line):
                    inside_struct = False
                    # We are at the end of the struct
                    extra_names = ''.join(line.split()).strip('};').split(',')
                    if anonymous_struct:
                        struct_name = extra_names[0]
                    if struct_name not in struct_data:
                        struct_data[struct_name] = OrderedDict()
                    struct_data[struct_name]['names'] = extra_names
                    if 'members' not in struct_data[struct_name]:
                        struct_data[struct_name]['members'] = OrderedDict()
                    struct_data[struct_name]['members'].update(
                        struct_data_member)
                    struct_data[struct_name]['pack'] = pack_size
                    struct_data[struct_name]['union'] = struct_is_union
                    struct_data_member = OrderedDict()
                    """
                    if inner_struct_data and not inner_union_has_structs:
                        struct_data[struct_name]['members'].update(inner_struct_data)
                        inner_struct_data = OrderedDict()
                    if inner_union_data:
                        struct_data[struct_name]['members'].update(inner_union_data)
                        inner_union_data = OrderedDict()
                    """
                    inner_union_has_structs = False
                    if debug_print:
                        print(
                            '------- Extra Names: {} -------------------------\n'.format(' '.join(extra_names)))
                    continue
                # inner struct
                if re.match(r'\bstruct\b', line):  # 'struct' in line:
                    inside_inner_struct = True
                    inner_struct_name, inner_anonymous_struct = get_struct_name_from_header(
                        line)
                    if inner_anonymous_struct:
                        last_inner_datatype = DataType.StructAnnonomous
                    else:
                        last_inner_datatype = DataType.Struct
                    continue
                if inside_inner_struct and inside_inner_union:
                    # This is a special case, we can't apply the member until we are done parsing the object.
                    if re.match('}.*;', line):
                        # We are at the end of the inner struct/union
                        inner_extra_names = ''.join(
                            line.split()).strip('};').split(',')
                        # Inner Struct
                        if last_inner_datatype in (DataType.StructAnnonomous, DataType.Struct):
                            inside_inner_struct = False
                            if inner_anonymous_struct and inner_extra_names[0]:
                                inner_struct_name = inner_extra_names[0]
                                last_inner_datatype = DataType.Struct
                                inner_anonymous_struct = False
                            if inner_anonymous_struct and not inner_extra_names[0]:
                                inner_union_data_member.update(inner_anonymous_data_member)
                            else:
                                inner_union_data_member[inner_struct_name] = OrderedDict()
                                inner_union_data_member[inner_struct_name]['names'] = inner_extra_names
                                inner_union_data_member[inner_struct_name]['members'] = inner_anonymous_data_member
                                inner_union_data_member[inner_struct_name]['pack'] = pack_size
                                inner_union_data_member[inner_struct_name]['union'] = False
                                inner_union_data_member[inner_struct_name]['anonymous'] = inner_anonymous_struct
                                inner_struct_name = ''
                        elif last_inner_datatype in (DataType.UnionAnnonomous, DataType.Union):
                            inside_inner_union = False
                            if inner_anonymous_union and inner_extra_names[0]:
                                inner_union_name = inner_extra_names[0]
                                last_inner_datatype = DataType.Union
                                inner_anonymous_union = False
                            if inner_anonymous_union and not inner_extra_names[0]:
                                inner_struct_data_member.update(inner_anonymous_data_member)
                            else:
                                inner_struct_data_member[inner_union_name] = OrderedDict()
                                inner_struct_data_member[inner_union_name]['names'] = inner_extra_names
                                inner_struct_data_member[inner_union_name]['members'] = inner_anonymous_data_member
                                inner_struct_data_member[inner_union_name]['pack'] = pack_size
                                inner_struct_data_member[inner_union_name]['union'] = True
                                inner_struct_data_member[inner_union_name]['anonymous'] = inner_anonymous_union
                                inner_union_name = ''
                        inner_anonymous_data_member = OrderedDict()
                        continue
                if inside_inner_struct:
                    if re.match('}.*;', line):
                        # We are at the end of the inner struct
                        inside_inner_struct = False
                        inner_extra_names = ''.join(
                            line.split()).strip('};').split(',')
                        if inner_anonymous_struct and inner_extra_names[0]:
                            inner_struct_name = inner_extra_names[0]
                            last_inner_datatype = DataType.Struct
                        if not inner_extra_names[0]:
                            inner_extra_names[0] = f'_U{anonymous_struct_index}'
                            anonymous_struct_index += 1
                        inner_struct_data = OrderedDict()
                        inner_struct_data[inner_struct_name] = OrderedDict()
                        inner_struct_data[inner_struct_name]['names'] = inner_extra_names
                        inner_struct_data[inner_struct_name]['members'] = inner_struct_data_member
                        inner_struct_data[inner_struct_name]['pack'] = pack_size
                        inner_struct_data[inner_struct_name]['union'] = False
                        inner_struct_data[inner_struct_name]['anonymous'] = inner_anonymous_struct
                        struct_data_member.update(inner_struct_data)

                        inner_struct_data_member = OrderedDict()
                        inner_struct_name = ''
                        continue
                # inner union
                if re.match(r'\bunion\b', line):  # 'struct' in line:
                    inner_union_has_structs = inside_inner_struct
                    inside_inner_union = True
                    inner_union_name, inner_anonymous_union = get_struct_name_from_header(
                        line)
                    if inner_anonymous_union:
                        last_inner_datatype = DataType.UnionAnnonomous
                    else:
                        last_inner_datatype = DataType.Union
                    continue
                if inside_inner_union:
                    if re.match('}.*;', line):
                        # We are at the end of the inner union
                        inside_inner_union = False
                        inner_extra_names = ''.join(
                            line.split()).strip('};').split(',')
                        if not inner_extra_names[0]:
                            inner_extra_names[0] = f'_U{anonymous_union_index}'
                            anonymous_union_index += 1
                        inner_union_name = inner_extra_names[0]
                        last_inner_datatype = DataType.Union
                        inner_union_data = OrderedDict()
                        inner_union_data[inner_union_name] = OrderedDict()
                        inner_union_data[inner_union_name]['names'] = inner_extra_names
                        inner_union_data[inner_union_name]['members'] = inner_union_data_member
                        inner_union_data[inner_union_name]['pack'] = pack_size
                        inner_union_data[inner_union_name]['union'] = True
                        inner_union_data[inner_union_name]['anonymous'] = inner_anonymous_union
                        struct_data_member.update(inner_union_data)

                        inner_union_data_member = OrderedDict()
                        inner_union_name = ''
                        if inner_union_has_structs and inner_anonymous_union:
                            inner_struct_inside_anonymous_union = True
                        continue
                # some lines are spaced out between multiple lines for no reason, lets merge them here and parse on the next loop around
                # make sure the newline is still in there since the for loop removes it
                buffered_line += '\n' + line
                if not ';' in buffered_line:
                    continue
                # remove newlines and extra whitespace
                buffered_line = buffered_line.strip()
                # remove empty lines with just a semi-colon
                if buffered_line == ';':
                    buffered_line = ''
                    continue
                data_name, data_type, array_length, bitwise_length = parse_struct_member(
                    buffered_line)
                if bitwise_length:
                    last_comment = '[Bitfield] ' + last_comment
                if data_name:
                    if inside_inner_union and inside_inner_struct:
                        # This is a special case here - When we are inside an inner union and inner struct
                        # we don't know if they are anonymous yet and no idea where to place them yet.
                        inner_anonymous_data_member[data_name] = [
                            data_type, array_length, bitwise_length, last_comment]
                    elif inside_inner_union:
                        inner_union_data_member[data_name] = [
                            data_type, array_length, bitwise_length, last_comment]
                    elif inside_inner_struct:
                        inner_struct_data_member[data_name] = [
                            data_type, array_length, bitwise_length, last_comment]
                    else:  # if data_name not in struct_data_member:
                        struct_data_member[data_name] = [
                            data_type, array_length, bitwise_length, last_comment]
                    #struct_data_member[re.sub('\[.*\]|;', '', member_name)] = [member_data_type, re.search('\[.*\]', member_name) is not None, last_comment]

                    #print('{}'.format(int(inside_struct)), opening_bracket_count, line)
                if debug_print:
                    print('{:04d} {} {} {} {} line: "{}" inner_struct_name: "{}" data_name: "{}" data_type: "{}"'.format(line_count, int(
                        inside_comment), int(inside_struct), int(inside_inner_struct), opening_bracket_count, line, inner_struct_name, data_name, data_type))
                buffered_line = ''
    return struct_data, enum_data


def generate():
    import shutil
    import json
    filename = 'include/ics/icsnVC40.h'
    filename = format_file(filename)
    struct_data, enum_data = parse_header_file(filename)
    # print the data to stdout
    if debug_print:
        import pprint
        pp = pprint.PrettyPrinter(indent=1, width=140)
        pp.pprint(struct_data)
        pp.pprint(enum_data)

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
    with open('icsnVC40.h.json', 'w+') as f:
        f.write(j)
    j = json.dumps(enum_data, indent=4, sort_keys=False)
    with open('icsnVC40.h.enums.json', 'w+') as f:
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
    generate()