# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

# vllupformat0
class vllupformat0(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
    ]

# Extra names go here:
# End of extra names

# vllupformat1
class vllupformat1(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
    ]

# Extra names go here:
# End of extra names

class s_pluto_vl_lookup_entry_s(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('vllupformat0', vllupformat0), 
        ('vllupformat1', vllupformat1), 
        ('macaddr', ctypes.c_uint64), 
        ('vlanid', ctypes.c_uint16), 
        ('destports', ctypes.c_uint8), 
        ('iscritical', ctypes.c_uint8), 
        ('port', ctypes.c_uint8), 
        ('vlanprior', ctypes.c_uint8), 
        ('vlid', ctypes.c_uint16), 
        ('egrmirr', ctypes.c_uint8), 
        ('ingrmirr', ctypes.c_uint8), 
    ]

# Extra names go here:
SPluto_VlLookupEntry = s_pluto_vl_lookup_entry_s
# End of extra names

