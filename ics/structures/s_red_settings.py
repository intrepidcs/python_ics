# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

try: # 2
    from can_settings import can_settings
    from lin_settings import lin_settings
except:
    from ics.structures.can_settings import can_settings
    from ics.structures.lin_settings import lin_settings

class s_red_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('can1', can_settings), 
        ('can2', can_settings), 
        ('lin1', lin_settings), 
        ('lin2', lin_settings), 
    ]

# Extra names go here:
SRedSettings = s_red_settings
# End of extra names

