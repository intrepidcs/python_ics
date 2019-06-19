# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

# CANOptions
class CANOptions(ctypes.Structure):
    _fields_ = [
        ('iNetworkID', ctypes.c_int32), 
    ]

# Extra names go here:
# End of extra names

class tag_options_find_neo_ex(ctypes.Union):
    _fields_ = [
        ('Reserved', ctypes.c_uint32 * 16), 
        ('CANOptions', CANOptions), 
    ]

# Extra names go here:
OptionsFindNeoEx = tag_options_find_neo_ex
POptionsFindNeoEx = tag_options_find_neo_ex
# End of extra names

