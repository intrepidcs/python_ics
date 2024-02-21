# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class timestamp_(ctypes.Structure):
    _pack_ = 1
    _fields_ = [
        ('seconds_msb', ctypes.c_uint16),
        ('seconds_lsb', ctypes.c_uint32),
        ('nanoseconds', ctypes.c_uint32),
    ]


_timestamp = timestamp_

