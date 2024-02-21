# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class s_pluto_vl_forwarding_entry_s(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('type', ctypes.c_uint8),
        ('priority', ctypes.c_uint8),
        ('partition', ctypes.c_uint8),
        ('destports', ctypes.c_uint8),
    ]


SPluto_VlForwardingEntry_s = s_pluto_vl_forwarding_entry_s
SPluto_VlForwardingEntry = s_pluto_vl_forwarding_entry_s

