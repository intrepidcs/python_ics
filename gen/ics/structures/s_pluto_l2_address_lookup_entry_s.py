# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class s_pluto_l2_address_lookup_entry_s(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('index', ctypes.c_uint16),
        ('vlanID', ctypes.c_uint16),
        ('macaddr', ctypes.c_uint8 * 6),
        ('destports', ctypes.c_uint8),
        ('enfport', ctypes.c_uint8),
        ('learnedEntry', ctypes.c_uint8),
        ('pad1', ctypes.c_uint8),
        ('pad2', ctypes.c_uint8),
        ('pad3', ctypes.c_uint8),
    ]


SPluto_L2AddressLookupEntry_s = s_pluto_l2_address_lookup_entry_s
SPluto_L2AddressLookupEntry = s_pluto_l2_address_lookup_entry_s

