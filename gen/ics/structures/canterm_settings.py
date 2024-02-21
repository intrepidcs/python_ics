# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class canterm_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('term_enabled', ctypes.c_uint8),
        ('term_network', ctypes.c_uint8),
        ('reserved', ctypes.c_uint16 * 2),
    ]


CANTERM_SETTINGS = canterm_settings

