import inspect
import python_ics


def generate_structures():
    # data = '.. autosummary::\n'
    """
    \t.. automodule:: python_ics.structures.{name}.{name}\n\t\t:members:\n\t\t:undoc-members:\n\n"
    """
    data = ""
    for name, value in inspect.getmembers(python_ics.structures, inspect.ismodule):
        # data += f"\t.. automodule:: python_ics.structures.{name}\n\t\t:members:\n\t\t:show-inheritance:\n\t\t:undoc-members:\n\n"
        data += f"\t.. autoclass:: python_ics.structures.{name}.{name}\n\t\t:members:\n\t\t:undoc-members:\n\n"
    return data


def generate_functions():
    data = ""
    functions = inspect.getmembers(python_ics, inspect.isroutine)
    new_style_functions = []
    icsneo_style_functions = []
    inbetween_style_functions = []
    for function_name, function_type in functions:
        if function_name.startswith("icsneo"):
            icsneo_style_functions.append(function_name)
        elif "_" in function_name:
            new_style_functions.append(function_name)
        else:
            inbetween_style_functions.append(function_name)

    data += ".. autosummary::\n"
    for name in new_style_functions + inbetween_style_functions + icsneo_style_functions:
        if name:
            data += f"\tpython_ics.{name}\n"
    return data


def generate_variables():
    data = ""
    for variable in [item for item in dir(python_ics) if not item.startswith("__") and item.isupper()]:
        data += f"\t.. py:data:: {str(variable)}\n\t\t:annotation: = {str(getattr(python_ics, variable))}\n\n"
    return data


def generate_documentation():
    return inspect.cleandoc(
        f""".. include:: header.rst
    .. include:: examples.rst

    ##############################################################################
    PyNeoDeviceEx
    ##############################################################################
    .. autoclass:: python_ics.PyNeoDeviceEx
        :members:
        :show-inheritance:
        :undoc-members:

    ##############################################################################
    Module Documentation
    ##############################################################################
    .. automodule:: python_ics.c_mod
        :members:
        :show-inheritance:
        :undoc-members:

    ##############################################################################
    Module Functions
    ##############################################################################

    {generate_functions()}

    ##############################################################################
    Module Structures
    ##############################################################################

    {generate_structures()}

    ##############################################################################
    Module Variables
    ##############################################################################

    {generate_variables()}

    """
    )


with open("index.rst", "w+") as f:
    f.write(generate_documentation())
print("Done.")
