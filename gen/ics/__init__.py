
from ics.structures import *

try:
    from ics import *
    from ics.ics import *
    from ics.structures import *
    from ics.hiddenimports import hidden_imports
except Exception as ex:
    print(ex)
    from ics.ics import *
    from ics.ics.ics import *
    from ics.ics.structures import *
    from ics.ics.hiddenimports import hidden_imports