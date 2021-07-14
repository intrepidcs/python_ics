# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class canfd_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('FDMode', ctypes.c_uint8),
        ('FDBaudrate', ctypes.c_uint8),
        ('FDTqSeg1', ctypes.c_uint8),
        ('FDTqSeg2', ctypes.c_uint8),
        ('FDTqProp', ctypes.c_uint8),
        ('FDTqSync', ctypes.c_uint8),
        ('FDBRP', ctypes.c_uint16),
        ('FDTDC', ctypes.c_uint8),
        ('reserved', ctypes.c_uint8),
    ]


_CANFD_SETTINGS = canfd_settings
CANFD_SETTINGS = canfd_settings

