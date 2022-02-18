# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures._clock_quality import *


class system_identity(ctypes.Structure):
    _pack_ = 1
    _fields_ = [
        ('priority_1', ctypes.c_uint8),
        ('clock_quality', _clock_quality),
        ('priority_2', ctypes.c_uint8),
        ('clock_identity', ctypes.c_uint64),
    ]



