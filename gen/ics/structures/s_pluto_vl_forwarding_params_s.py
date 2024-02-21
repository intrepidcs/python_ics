# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class s_pluto_vl_forwarding_params_s(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('partspc', ctypes.c_uint16 * 8),
        ('debugen', ctypes.c_uint8),
        ('pad', ctypes.c_uint8),
    ]


SPluto_VlForwardingParams_s = s_pluto_vl_forwarding_params_s
SPluto_VlForwardingParams = s_pluto_vl_forwarding_params_s

