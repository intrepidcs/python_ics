# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class vllupformat0(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('macaddr', ctypes.c_uint64),
        ('vlanid', ctypes.c_uint16),
        ('destports', ctypes.c_uint8),
        ('iscritical', ctypes.c_uint8),
        ('port', ctypes.c_uint8),
        ('vlanprior', ctypes.c_uint8),
    ]



class vllupformat1(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('vlid', ctypes.c_uint16),
        ('egrmirr', ctypes.c_uint8),
        ('ingrmirr', ctypes.c_uint8),
        ('port', ctypes.c_uint8),
    ]



class Nameless11656(ctypes.Union):
    _pack_ = 2
    _fields_ = [
        ('vllupformat0', vllupformat0),
        ('vllupformat1', vllupformat1),
    ]



class s_pluto_vl_lookup_entry_s(ctypes.Structure):
    _pack_ = 2
    _anonymous_  = ('Nameless11656',)
    _fields_ = [
        ('Nameless11656', Nameless11656),
    ]


SPluto_VlLookupEntry_s = s_pluto_vl_lookup_entry_s
SPluto_VlLookupEntry = s_pluto_vl_lookup_entry_s

