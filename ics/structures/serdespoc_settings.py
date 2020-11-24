# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

class serdespoc_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('mode', ctypes.c_uint8), # no poc, generated supply, serializer passthrough
        ('rsvd', ctypes.c_uint8 * 6), 
        ('voltage', ctypes.c_uint8), # generated voltage
        ('chksum', ctypes.c_uint16), # checksum to protect settings structure (don't want corrupt voltage settings)
    ]

# Extra names go here:
SERDESPOC_SETTINGS = serdespoc_settings
# End of extra names

