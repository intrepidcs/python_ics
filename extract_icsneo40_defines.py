#!/usr/bin/env python
from __future__ import print_function
import os.path
import re
from subprocess import run, PIPE
import pathlib
import shutil

# Shamelessly stolen from generate_icsneo40_structs.py
# At some point this entire file should probably be collasped into the other


def format_file(filename, preprocessor=False):
    import os

    processed_fname = os.path.basename(filename)
    name, ext = os.path.splitext(processed_fname)
    processed_fname = f"{name}_processed{ext}"
    # processed_fname = "icsnVC40_processed.h"
    # Run it through the preprocessor
    # clang -E -P .\include\ics\icsnVC40.h -o output.h
    if preprocessor:
        result = run(["clang", "-E", "-P", filename, "-o", processed_fname], stdout=PIPE, stderr=PIPE)
        result.check_returncode()
    else:
        original_path = pathlib.Path(filename)
        new_path = pathlib.Path(processed_fname)
        shutil.copy(str(original_path), str(new_path))

    # Format the file
    result = run(
        ["clang-format", "-i", "--style", "{BasedOnStyle: Mozilla, ColumnLimit: '200'}", processed_fname],
        stdout=PIPE,
        stderr=PIPE,
    )
    result.check_returncode()

    return processed_fname


def extract():
    use_internal = False
    if os.path.isfile("include/ics/icsnVC40Internal.h"):
        use_internal = True
        print("Using Internal Header!")

    boiler_plate = """
//
// WARNING: This file was auto generated and should not be modified directly!
// Any changes here will be overwritten!
//
"""

    # write the header file first
    with open("include/setup_module_auto_defines.h", "w") as f:
        print("#ifndef __SETUP_MODULE_AUTO_DEFINES_H__", file=f)
        print("#define __SETUP_MODULE_AUTO_DEFINES_H__", file=f)
        if use_internal:
            print("\n#ifndef _USE_INTERNAL_HEADER_\n#define _USE_INTERNAL_HEADER_\n#endif\n", file=f)
        print("#include <Python.h>", file=f)
        print("\nint setup_module_auto_defines(PyObject * module);\n", file=f)
        print("#endif // __SETUP_MODULE_AUTO_DEFINES_H__", file=f)

    ignores = (
        "(",
        "#endif",
        "#define",
        "icscm_",
        "GCC_MODIFIER",
        "VS_MODIFIER",
        "{",
        "ICSNVC40_H",
        "ICSNVC40INTERNAL__H_",
        "SYellowSettings_SIZE",
        "IS_64BIT_SYSTEM",
    )
    use_enums = True
    with open("src/setup_module_auto_defines.cpp", "w") as f:
        print(boiler_plate, file=f)
        # Include the header files needed for the defines
        
        print('#include "setup_module_auto_defines.h"\n#include <Python.h>\n#pragma warning(push, 0)\n#include "ics/icsnVC40.h"\n#pragma warning(pop)', file=f)
        if use_internal:
            print('#pragma warning(push, 0)\n#include "ics/icsnVC40Internal.h"\n#pragma warning(pop)', file=f)

        print("\nint setup_module_auto_defines(PyObject * module)\n{", file=f)
        print("\tint result = 0;\n", file=f)
        fnames = []
        fnames.append(format_file("include/ics/icsnVC40.h"))
        if use_internal:
            fnames.append(format_file("include/ics/icsnVC40Internal.h"))
        # Let's get to work here!
        for header_file in fnames:
            # if not os.path.isfile(header_file) and 'Internal' in header_file:
            #    # Ignore this file
            #    continue
            with open(header_file, "r") as fname:
                if "icsnVC40Internal" in header_file:
                    print(
                        "\n#ifdef _USE_INTERNAL_HEADER_ /* ALL THESE DEFINES ARE SPECIFIED IN THE INTERNAL HEADER */\n",
                        file=f,
                    )
                inside_enum = False
                inside_comment = False
                line_number = 0
                for line in fname:
                    line_number += 1
                    if line.lstrip().startswith("//"):
                        continue
                    if inside_enum and "}" in line:
                        inside_enum = False
                        if use_enums:
                            print("\t// end of enum - ", line, file=f)
                        continue
                    elif inside_comment and "*/" in line:
                        inside_comment = False
                        continue
                    elif inside_enum and not "{" in line:
                        sline = line.split()
                        if not sline:
                            continue
                        if any(x in sline[0] for x in ignores):
                            continue
                        if use_enums:
                            if "," in sline[0]:
                                # This removes anything after the comma as we don't need it
                                sline[0] = sline[0].split(",")[0]
                                # This removes anything after the equal sign as we don't need it
                                sline[0] = sline[0].split("=")[0]
                            print("\tresult += PyModule_AddIntMacro(module, %s);" % sline[0].replace(",", ""), file=f)
                        continue
                    if "#define" in line:
                        sline = line.split("//")[0].split()
                        # DEBUG: print('\t\t' + str(line_number) + '\t' + str(sline))
                        if any(x in sline[1] for x in ignores):
                            continue
                        if len(sline) >= 3 and re.match(r"^\d+?\.\d+?$", sline[2]) is not None:
                            # Value is a float
                            print(
                                '\tresult += PyModule_AddObject(module, "{0}", PyFloat_FromDouble({0}));'.format(
                                    sline[1]
                                ),
                                file=f,
                            )
                        elif len(sline) == 2:
                            # There is no value, this is used for preprocessor only
                            # and really shouldn't care about it in python. Going to set it as 0 "just in case"
                            print(
                                '\tresult += PyModule_AddObject(module, "{}", PyLong_FromLong(0));'.format(sline[1]),
                                file=f,
                            )
                        else:
                            print("\tresult += PyModule_AddIntMacro(module, %s);" % sline[1], file=f)

                    elif "/*" in line:
                        inside_comment = True
                        continue
                    elif "enum" in line.split("//")[0]:
                        inside_enum = True
                        if use_enums:
                            print("\t// enum", file=f)
                        if "{" in line and "};" in line:
                            # Special Case here
                            sline = "".join(line[line.find("{") + 1 : line.find("}")].split()).split(",")
                            # Remove =X assignments if present.
                            sline = [x.split("=")[0] for x in sline]
                            for e in sline:
                                print("\tresult += PyModule_AddIntMacro(module, %s);" % e, file=f)
                            inside_enum = False
                        continue
                if "icsnVC40Internal" in header_file:
                    print("\n#endif // _USE_INTERNAL_HEADER_\n", file=f)

        print("\n\treturn result == 0 ? 1 : 0;\n}", file=f)


if __name__ == "__main__":
    extract()
