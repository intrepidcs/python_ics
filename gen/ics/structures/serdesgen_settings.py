# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class serdesgen_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('flags', ctypes.c_uint16),
        ('rsvd1', ctypes.c_uint8),
        ('mod_id', ctypes.c_uint8),
        ('tx_speed', ctypes.c_uint16),
        ('rx_speed', ctypes.c_uint16),
        ('rsvd2', ctypes.c_uint8 * 24),
    ]


SERDESGEN_SETTINGS_t = serdesgen_settings
SERDESGEN_SETTINGS = serdesgen_settings

