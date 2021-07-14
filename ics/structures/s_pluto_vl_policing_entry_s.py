# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class s_pluto_vl_policing_entry_s(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('type', ctypes.c_uint64),
        ('maxlen', ctypes.c_uint64),
        ('sharindx', ctypes.c_uint64),
        ('bag', ctypes.c_uint64),
        ('jitter', ctypes.c_uint64),
    ]


SPluto_VlPolicingEntry_s = s_pluto_vl_policing_entry_s
SPluto_VlPolicingEntry = s_pluto_vl_policing_entry_s

