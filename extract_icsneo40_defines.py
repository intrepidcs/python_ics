#!/usr/bin/env python
from __future__ import print_function
import os.path

use_internal = False
if os.path.isfile('include/ics/icsnVC40Internal.h'):
    use_internal = True
    print("Using Internal Header!")

boiler_plate = """
//
// WARNING: This file was auto generated and should not be modified directly!
// Any changes here will be overwritten!
//
"""

#write the header file first
with open('include/setup_module_auto_defines.h', 'w') as f:
    print("#ifndef __SETUP_MODULE_AUTO_DEFINES_H__", file=f)
    print("#define __SETUP_MODULE_AUTO_DEFINES_H__", file=f)
    if use_internal:
        print("\n#ifndef _USE_INTERNAL_HEADER_\n#define _USE_INTERNAL_HEADER_\n#endif\n", file=f)
    print('#include <Python.h>', file=f)
    print("\nint setup_module_auto_defines(PyObject * module);\n", file=f)
    print("#endif // __SETUP_MODULE_AUTO_DEFINES_H__", file=f)

ignores = ('(', '#endif', '#define', 'icscm_', 'GCC_MODIFIER', 'VS_MODIFIER', '{', 'ICSNVC40_H', 'ICSNVC40INTERNAL__H_', 'SYellowSettings_SIZE')
use_enums = True
with open('src/setup_module_auto_defines.cpp', 'w') as f:
    print(boiler_plate, file=f)
    # Include the header files needed for the defines
    print("#include <Python.h>\n#include \"ics/icsnVC40.h\"", file=f)
    if use_internal:
        print("#include \"ics/icsnVC40Internal.h\"", file=f)

    print("int setup_module_auto_defines(PyObject * module)\n{", file=f)
    print("\tint result = 0;\n", file=f)
    # Let's get to work here!
    for header_file in ('include/ics/icsnVC40.h', 'include/ics/icsnVC40Internal.h'):
        if not os.path.isfile(header_file) and 'Internal' in header_file:
            # Ignore this file
            continue
        with open(header_file, 'r') as fname:
            if 'icsnVC40Internal' in header_file:
                print("\n#ifdef _USE_INTERNAL_HEADER_ /* ALL THESE DEFINES ARE SPECIFIED IN THE INTERNAL HEADER */\n", file=f)
            inside_enum = False
            inside_comment = False
            for line in fname:
                if line.startswith('//'):
                    continue
                if inside_enum and '}' in line:
                    inside_enum = False
                    if use_enums:
                        print('\t// end of enum - ', line, file=f)
                    continue
                elif inside_comment and '*/' in line:
                    inside_comment = False
                    continue
                elif inside_enum and not '{' in line:
                    sline = line.split()
                    if not sline:
                        continue
                    if any(x in sline[0] for x in ignores):
                        continue
                    if use_enums:
                        if ',' in sline[0]:
                            # This removes anything after the comma as we don't need it
                            sline[0] = sline[0].split(',')[0]
                        print('\tresult += PyModule_AddIntMacro(module, %s);' % sline[0].replace(',', ''), file=f)
                    continue
                if '#define' in line:
                    sline = line.split()
                    #print('\t\t' + str(sline))
                    if any(x in sline[1] for x in ignores):
                        continue
                    print('\tresult += PyModule_AddIntMacro(module, %s);' % sline[1], file=f)
                elif '/*' in line:
                    inside_comment = True
                    continue
                elif 'enum' in line:
                    inside_enum = True
                    if use_enums:
                        print('\t// enum', file=f)
                    if '{' in line and '};' in line:
                        # Special Case here
                        sline = "".join(line[line.find("{")+1:line.find("}")].split()).split(',')
                        # Remove =X assignments if present.
                        sline = [x.split('=')[0] for x in sline]
                        for e in sline:
                            print('\tresult += PyModule_AddIntMacro(module, %s);' % e, file=f)
                        inside_enum = False
                    continue
            if 'icsnVC40Internal' in header_file:
                print("\n#endif // _USE_INTERNAL_HEADER_\n", file=f)

    print("\n\treturn result == 0 ? 1 : 0;\n}", file=f)