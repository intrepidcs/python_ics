try:
    # Release environment
    from ics.ics import *
    from ics.ics.structures import *
    from ics.ics.hiddenimports import hidden_imports
except Exception as ex:
    # Build environment
    from ics import *
    from ics.structures import *
    from ics.hiddenimports import hidden_imports

