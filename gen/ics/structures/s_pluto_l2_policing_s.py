# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class s_pluto_l2_policing_s(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('smax', ctypes.c_uint16),
        ('rate', ctypes.c_uint16),
        ('maxlen', ctypes.c_uint16),
        ('sharindx', ctypes.c_uint8),
        ('partition', ctypes.c_uint8),
    ]


SPluto_L2Policing_s = s_pluto_l2_policing_s
SPluto_L2Policing = s_pluto_l2_policing_s

