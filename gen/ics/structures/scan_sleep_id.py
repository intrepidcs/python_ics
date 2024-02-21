# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class id(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('can_sleep_command_id', ctypes.c_uint, 29),
        ('can_sleep_command_isExtended', ctypes.c_uint, 1),
        ('reserved', ctypes.c_uint, 2),
    ]



class scan_sleep_id(ctypes.Union):
    _pack_ = 2
    _fields_ = [
        ('word', ctypes.c_uint32),
        ('id', id),
    ]


SCANSleepID = scan_sleep_id

