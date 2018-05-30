import inspect
import ics

functions = inspect.getmembers(ics, inspect.isroutine)
new_style_functions = []
icsneo_style_functions = []
inbetween_style_functions = []
for function_name, function_type in functions:
    if function_name.startswith('icsneo'):
        icsneo_style_functions.append(function_name)
    elif '_' in function_name:
        new_style_functions.append(function_name)
    else:
        inbetween_style_functions.append(function_name)

print('.. autosummary::\n')
for name in new_style_functions:
    print('\tics.' + name)
for name in inbetween_style_functions:
    print('\tics.' + name)
for name in icsneo_style_functions:
    print('\tics.' + name)
