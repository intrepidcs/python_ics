# Warning: This file is auto generated. Don't modify if you value your sanity!


try:
    # Bring the auto generated structures into scope
    from .structures import *
    from .structures.neo_device import NeoDevice, neo_device
except ValueError as ex:
    # This is only required when building
    print(ex)
except ImportError as ex:
    # If we are still building this won't work correctly.
    import sys
    print("Warning: .structures is not installed. .structures will not be available.", file=sys.stderr, flush=True)

# Bring the c module "ics" into the parent scope
try:
    from .c_mod import *
    from . import c_mod
    # Backwards compatibility mode for existing code
    from . import c_mod as ics
except ImportError as ex:
    # If we are still building this won't work correctly.
    import sys
    print("Warning: ics module is not installed. ics will not be available.", file=sys.stderr, flush=True)

# Bring the auto generated python files info into the parent scope
try:
    from . import __version
    __version__ = __version.__version__
    __full_version__ = __version.__full_version__
    from .hiddenimports import hidden_imports
except ValueError as ex:
    # This is only required when building
    print(ex)

# Bring python files into the parent scope
from .py_neo_device_ex import PyNeoDeviceEx
