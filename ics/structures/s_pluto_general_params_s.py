# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class s_pluto_general_params_s(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('mac_fltres1', ctypes.c_uint64),
        ('mac_fltres0', ctypes.c_uint64),
        ('mac_flt1', ctypes.c_uint64),
        ('mac_flt0', ctypes.c_uint64),
        ('vlmarker', ctypes.c_uint32),
        ('vlmask', ctypes.c_uint32),
        ('tpid', ctypes.c_uint16),
        ('tpid2', ctypes.c_uint16),
        ('vllupformat', ctypes.c_uint8),
        ('mirr_ptacu', ctypes.c_uint8),
        ('switchid', ctypes.c_uint8),
        ('hostprio', ctypes.c_uint8),
        ('incl_srcpt1', ctypes.c_uint8),
        ('incl_srcpt0', ctypes.c_uint8),
        ('send_meta1', ctypes.c_uint8),
        ('send_meta0', ctypes.c_uint8),
        ('casc_port', ctypes.c_uint8),
        ('host_port', ctypes.c_uint8),
        ('mirr_port', ctypes.c_uint8),
        ('ignore2stf', ctypes.c_uint8),
    ]


SPluto_GeneralParams_s = s_pluto_general_params_s
SPluto_GeneralParams = s_pluto_general_params_s

