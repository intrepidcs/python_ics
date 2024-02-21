# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class s_pluto_l2_address_lookup_params_s(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('maxage', ctypes.c_uint16),
        ('dyn_tbsz', ctypes.c_uint8),
        ('poly', ctypes.c_uint8),
        ('shared_learn', ctypes.c_uint8),
        ('no_enf_hostprt', ctypes.c_uint8),
        ('no_mgmt_learn', ctypes.c_uint8),
        ('pad', ctypes.c_uint8),
    ]


SPluto_L2AddressLookupParams_s = s_pluto_l2_address_lookup_params_s
SPluto_L2AddressLookupParams = s_pluto_l2_address_lookup_params_s

