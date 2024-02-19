# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class CANOptions(ctypes.Structure):
    _fields_ = [
        ('iNetworkID', ctypes.c_int32),
    ]



class tag_options_find_neo_ex(ctypes.Union):
    _fields_ = [
        ('CANOptions', CANOptions),
        ('Reserved', ctypes.c_uint32 * 16),
    ]


tagOptionsFindNeoEx = tag_options_find_neo_ex
OptionsFindNeoEx = tag_options_find_neo_ex
POptionsFindNeoEx = tag_options_find_neo_ex

