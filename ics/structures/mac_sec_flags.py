# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class mac_sec_flags(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('en', ctypes.c_uint32, 1),
        ('reserved', ctypes.c_uint32, 31),
    ]


MACSecFlags_t = mac_sec_flags
MACSecFlags = mac_sec_flags

