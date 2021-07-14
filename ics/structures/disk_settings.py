# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class disk_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('disk_layout', ctypes.c_uint8),
        ('disk_format', ctypes.c_uint8),
        ('disk_enables', ctypes.c_uint32),
        ('rsvd', ctypes.c_uint8 * 8),
    ]


DISK_SETTINGS_t = disk_settings
DISK_SETTINGS = disk_settings

