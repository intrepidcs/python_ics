# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class s_pluto_l2_forwarding_params_s(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('part_spc', ctypes.c_uint16 * 8),
        ('max_dynp', ctypes.c_uint8),
        ('pad', ctypes.c_uint8),
    ]


SPluto_L2ForwardingParams_s = s_pluto_l2_forwarding_params_s
SPluto_L2ForwardingParams = s_pluto_l2_forwarding_params_s

