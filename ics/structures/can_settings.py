# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class can_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('Mode', ctypes.c_uint8),
        ('SetBaudrate', ctypes.c_uint8),
        ('Baudrate', ctypes.c_uint8),
        ('transceiver_mode', ctypes.c_uint8),
        ('TqSeg1', ctypes.c_uint8),
        ('TqSeg2', ctypes.c_uint8),
        ('TqProp', ctypes.c_uint8),
        ('TqSync', ctypes.c_uint8),
        ('BRP', ctypes.c_uint16),
        ('auto_baud', ctypes.c_uint8),
        ('innerFrameDelay25us', ctypes.c_uint8),
    ]


CAN_SETTINGS = can_settings

