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
