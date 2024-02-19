# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class lin_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('Baudrate', ctypes.c_uint32),
        ('spbrg', ctypes.c_uint16),
        ('brgh', ctypes.c_uint8),
        ('numBitsDelay', ctypes.c_uint8),
        ('MasterResistor', ctypes.c_uint8),
        ('Mode', ctypes.c_uint8),
    ]


_LIN_SETTINGS = lin_settings
LIN_SETTINGS = lin_settings

