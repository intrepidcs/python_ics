# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class can_options(ctypes.Structure):
    _fields_ = [
        ('iNetworkID', ctypes.c_int32),
    ]


CANOptions = can_options

class tag_options_open_neo_ex(ctypes.Union):
    _anonymous_  = ('can_options',)
    _fields_ = [
        ('can_options', can_options),
        ('Reserved', ctypes.c_uint32 * 16),
    ]


tagOptionsOpenNeoEx = tag_options_open_neo_ex
OptionsOpenNeoEx = tag_options_open_neo_ex
POptionsOpenNeoEx = tag_options_open_neo_ex

