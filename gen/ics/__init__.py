try:
    import ics.__version
    __version__ = ics.__version.__version__
    __full_version__ = ics.__version.__full_version__
except Exception as ex:
    print(ex)

try:
    # Release environment
    #print("Release")
    from ics.ics import *
    from ics.structures import *
    from ics.hiddenimports import hidden_imports
except Exception as ex:
    # Build environment
    #print("Debug", ex)
    from ics import *
    from ics.structures import *
    from ics.hiddenimports import hidden_imports

