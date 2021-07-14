# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class serdespoc_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('mode', ctypes.c_uint8),
        ('rsvd', ctypes.c_uint8 * 6),
        ('voltage', ctypes.c_uint8),
        ('chksum', ctypes.c_uint16),
    ]


SERDESPOC_SETTINGS_t = serdespoc_settings
SERDESPOC_SETTINGS = serdespoc_settings

