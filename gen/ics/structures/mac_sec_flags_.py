# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class Nameless8987(ctypes.Structure):
    _pack_ = 1
    _fields_ = [
        ('en', ctypes.c_uint32, 1),
        ('reserved', ctypes.c_uint32, 31),
    ]



class mac_sec_flags_(ctypes.Union):
    _pack_ = 1
    _anonymous_  = ('Nameless8987',)
    _fields_ = [
        ('Nameless8987', Nameless8987),
        ('flags_32b', ctypes.c_uint32),
    ]


_MACSecFlags = mac_sec_flags_
MACSecFlags_t = mac_sec_flags_
MACSecFlags_ = mac_sec_flags_

