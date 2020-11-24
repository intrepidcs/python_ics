# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

class rad_reporting_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('flags', ctypes.c_uint32), 
        ('temp_interval_ms', ctypes.c_uint16), 
        ('gps_interval_ms', ctypes.c_uint16), 
        ('serdes_interval_ms', ctypes.c_uint16), 
        ('io_interval_ms', ctypes.c_uint16), 
        ('rsvd', ctypes.c_uint8 * 4), 
    ]

# Extra names go here:
RAD_REPORTING_SETTINGS = rad_reporting_settings
# End of extra names

