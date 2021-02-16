# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

class logger_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('extraction_timeout', ctypes.c_uint8), 
        ('rsvd', ctypes.c_uint8 * 3), 
    ]

# Extra names go here:
LOGGER_SETTINGS = logger_settings
# End of extra names

