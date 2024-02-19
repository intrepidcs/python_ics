# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class rad_reporting_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('flags', ctypes.c_uint32),
        ('temp_interval_ms', ctypes.c_uint16),
        ('gps_interval_ms', ctypes.c_uint16),
        ('serdes_interval_ms', ctypes.c_uint16),
        ('io_interval_ms', ctypes.c_uint16),
        ('fan_speed_interval_ms', ctypes.c_uint16),
        ('rsvd', ctypes.c_uint8 * 2),
    ]


RAD_REPORTING_SETTINGS_t = rad_reporting_settings
RAD_REPORTING_SETTINGS = rad_reporting_settings

