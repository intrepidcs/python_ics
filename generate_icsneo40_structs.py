import re

debug_print = False


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
    buffered_line = re.sub("\s*\[", "[", ' '.join(buffered_line.split()))
    
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
    if ':' in words:
        # we are a bitfield ;(
        data_name_index = words.index(":")-1
        
        try:
            bitwise_length = int(re.search('\d*', words[words.index(":")+1]).group(0))
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
    # DEBUG: ['uint8_t', 'MACAddress[6];']
    # print("DEBUG:", words, buffered_line)
    
    
    
    # remove stuff that shouldn't be in the name
    data_name = re.sub('{|{|}|\s*', '', data_name)
    data_type = re.sub('union|{|{|}', '', data_type)
    data_type = data_type.strip()
    if not data_type:
        data_name = ''
    
    return re.sub('\[.*\]|;', '', data_name), data_type, array_length, bitwise_length

def get_struct_name_from_header(line):
    struct_name = re.sub('typedef|struct|\s*', '', line) #line.split('struct ')[-1]
    if not struct_name: # == 'typedef struct':
        anonomous_struct = True
        struct_name = 'Anonomous'
    else:
        anonomous_struct = False
    return struct_name, anonomous_struct
    
def generate_ctype_struct_pyfile_from_dict(name, data, path='.'):
    def get_data_type_list(data, unknown_only=False):
        types = {}
        for name, values in data['members'].items():
            print("DEBUG: ", name, values)
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
                    types[convert_to_snake_case(values[0])] = None
        return types.keys()
        
    def convert_to_snake_case(name):
        s1 = re.sub('(.)([A-Z][a-z]+)', r'\1_\2', name)
        s2 = re.sub('([a-z0-9])([A-Z])', r'\1_\2', s1).lower()
        return re.sub(r'(_)\1{1,}', '_', s2)
    
    def convert_to_ctype_object(data_type):
        if data_type == 'unsigned':
            data_type = 'uint32_t'
        elif data_type == 'void*':
            data_type = 'void_p'
        # Try to convert to ctypes type
        try:
            import ctypes
            eval("ctypes.c_{}".format(re.sub('_t', '', data_type)))
            type = 'ctypes.c_' + re.sub('_t', '', data_type)
            return type
        except:
            return None
            """
            if isinstance(values, dict):
                type = name
            else:
                type = values[0]
            """
            
    def write_struct(class_name, data, f):
        # Class definition
        f.write('class {}(ctypes.Structure):\n'.format(class_name))
        # Structure pack size
        try:
            pack_size = data['pack']
            if pack_size != 0:
                f.write("    _pack_ = {}\n".format(pack_size))
        except KeyError:
            pass
        f.write('    _fields_ = [\n')
        # write the fields
        for name, values in data['members'].items():
            if isinstance(values, dict):
                # TODO: this is an inner struct
                pass #continue
            
            # expand the values
            if not isinstance(values, dict):
                data_type, array_length, bitwise_length, last_comment = values
            else:
                data_type = 'nope'
                array_length = 0
                bitwise_length = 0
                last_comment = ''
            
            # Try to convert to ctypes type
            type = convert_to_ctype_object(data_type)
            if not type and isinstance(values, dict):
                # type is a nested struct we will generate another class for
                type = name
            elif not type:
                type = convert_to_snake_case(values[0])
            
            # make the comment a python comment
            if last_comment:
                last_comment = "# " + last_comment
            
            if bitwise_length > 0:
                f.write("        ('{}', {}, {}), {}\n".format(name, type, bitwise_length, last_comment))
            elif array_length > 0:
                f.write("        ('{}', {} * {}), {}\n".format(name, type, array_length, last_comment))
            else:
                f.write("        ('{}', {}), {}\n".format(name, type, last_comment))
                
        f.write('    ]\n\n')
    
        f.write("# Extra names go here:\n")
        for name in data['names']:
            if name == class_name:
                continue
            f.write('{} = {}\n'.format(name, class_name))
        f.write("# End of extra names\n")
        f.write('\n')
        
    fixed_name = convert_to_snake_case(name)
    
    with open('{}/object_{}.py'.format(path, fixed_name), 'w+') as f:
        f.write('# This file was auto generated; Do not modify, if you value your sanity!')
        f.write('import ctypes\n')
        f.write('\n')
        for type in get_data_type_list(data, True):
            f.write("from object_{} import {}\n".format(type, type))
        f.write('\n')
        for name, values in data['members'].items():
            if isinstance(values, dict):
                # This is an inner struct
                try:
                    f.write('# {}\n'.format(name))
                    write_struct(name, values, f)
                except:
                    print('VALUES: ', values)
                    raise
        write_struct(fixed_name, data, f)
        
    
def parse_header_file(filename='include/ics/icsnVC40.h'):
     # key = struct name, value = dict
    struct_data = {}
    line_count = 0
    with open(filename, 'r') as f:
        inside_struct = False
        inside_comment = False
        opening_bracket_count = 0
        struct_name = 'None'
        anonomous_struct = False
        buffered_line = ''
        struct_data_member = {}
        last_comment = ''
        inside_inner_union = False
        inside_inner_struct = False
        inner_anonomous_struct = False
        inner_struct_data_member = {}
        inner_struct_name = ''
        inner_struct_data = {}
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
                    pack_size = 0
                elif re.match('#pragma.*pack.*.*push.*', line):
                    pack_size = int(re.search('\d{1,}', line).group(0))
                    if debug_print:
                        print("PACK SIZE:", pack_size)
                elif re.match('#define.*', line) and len(line.split(' ')) == 3 and not '\\' in line and not 'sizeof' in line:
                    # preprocessor define that can be used as a number in array sizes...
                    # we are going to hack the variable into the module's globals so we can eval() it later
                    words = line.split(' ')
                    if debug_print:
                        print("ADDING {} to globals with value of {}".format(words[1], words[2]))
                    globals()[words[1]] = eval(words[2])
                    
                continue
            # we stripped out a lot of stuff, if nothing left we are done
            #if not line:
            #    continue
            # Finally determine if we are inside a struct and get the name
            if 'struct' in line and not inside_struct:
                inside_struct = True
                opening_bracket_count = line.count('{')
                struct_name, anonomous_struct = get_struct_name_from_header(line)
                if debug_print:
                    print('------- {} ---------------------------------'.format(struct_name))
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
                    if anonomous_struct:
                        struct_name = extra_names[0]
                    if struct_name not in struct_data:
                        struct_data[struct_name] = {}
                    struct_data[struct_name]['names'] = extra_names
                    if 'members' not in struct_data[struct_name]:
                        struct_data[struct_name]['members'] = {}
                    struct_data[struct_name]['members'].update(struct_data_member)
                    struct_data[struct_name]['pack'] = pack_size
                    struct_data_member = {}
                    if inner_struct_data:
                        struct_data[struct_name]['members'].update(inner_struct_data)
                        inner_struct_data = {}
                    if debug_print:
                        print('------- Extra Names: {} -------------------------\n'.format(' '.join(extra_names)))
                    continue
                # inner struct
                if 'struct' in line:
                    inside_inner_struct = True
                    inner_struct_name, inner_anonomous_struct = get_struct_name_from_header(line)
                    continue
                if inside_inner_struct:
                    if re.match('}.*;', line):
                        # We are at the end of the inner struct
                        inside_inner_struct = False
                        inner_extra_names = ''.join(line.split()).strip('};').split(',')
                        if inner_anonomous_struct and inner_extra_names[0]:
                            inner_struct_name = inner_extra_names[0]
                        
                        if inner_anonomous_struct and not inner_extra_names[0]:
                            inner_struct_data.update(inner_struct_data_member)
                        else:
                            inner_struct_data[inner_struct_name] = {}
                            inner_struct_data[inner_struct_name]['names'] = inner_extra_names
                            inner_struct_data[inner_struct_name]['members'] = inner_struct_data_member
                            inner_struct_data[inner_struct_name]['pack'] = pack_size
                        inner_struct_data_member = {}
                        inner_struct_name = ''
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
                data_name, data_type, array_length, bitwise_length = parse_struct_member(buffered_line)
                if bitwise_length:
                    last_comment = '[Bitfield] ' + last_comment
                if data_name:
                    if inside_inner_struct:
                        inner_struct_data_member[data_name] = [data_type, array_length, bitwise_length, last_comment]
                    else: #if data_name not in struct_data_member:
                        struct_data_member[data_name] = [data_type, array_length, bitwise_length, last_comment]
                    #struct_data_member[re.sub('\[.*\]|;', '', member_name)] = [member_data_type, re.search('\[.*\]', member_name) is not None, last_comment]
                
                    #print('{}'.format(int(inside_struct)), opening_bracket_count, line)
                    if debug_print:
                        print('{:04d} {} {} {}'.format(line_count, int(inside_comment), int(inside_struct), int(inside_inner_struct)), opening_bracket_count, buffered_line, inner_struct_name)
                buffered_line = ''
    return struct_data

if __name__ == '__main__':
    import pprint
    
    struct_data = parse_header_file()
    # print the data to stdout
    pp = pprint.PrettyPrinter(indent=1, width=140)
    pp.pprint(struct_data)
    
    # print all datatypes
    if False:
        data_types = []
        for key in struct_data.keys():
            for value in struct_data[key]['members'].values():
                if isinstance(value, dict):
                    #for sub_value in value.values():
                    #    print(sub_value)
                    #    data_types.append(sub_value[0])
                    pass
                else:
                    data_types.append(value[0])
        #print(data_types)
        print(sorted(list(dict.fromkeys(data_types))))

    import json
    j = json.dumps(struct_data, indent=4, sort_keys=True)
    with open('test_json.txt', 'w+') as f:
        f.write(j)
    
    for name in struct_data:
        generate_ctype_struct_pyfile_from_dict(re.sub('^_', '', name), struct_data[name], 'test_gen')
    #generate_ctype_struct_pyfile_from_dict('SCyanSettings', struct_data['_SCyanSettings'])
    #generate_ctype_struct_pyfile_from_dict('stCM_ISO157652_TxMessage', struct_data['_stCM_ISO157652_TxMessage'])
        