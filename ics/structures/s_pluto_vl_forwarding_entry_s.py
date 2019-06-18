# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

class s_pluto_vl_forwarding_entry_s(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('type', ctypes.c_uint8), 
        ('priority', ctypes.c_uint8), 
        ('partition', ctypes.c_uint8), 
        ('destports', ctypes.c_uint8), 
    ]

# Extra names go here:
SPluto_VlForwardingEntry = s_pluto_vl_forwarding_entry_s
# End of extra names

