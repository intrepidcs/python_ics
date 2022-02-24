# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class clock_quality_(ctypes.Structure):
    _pack_ = 1
    _fields_ = [
        ('clock_class', ctypes.c_uint8),
        ('clock_accuracy', ctypes.c_uint8),
        ('offset_scaled_log_variance', ctypes.c_uint16),
    ]


_clock_quality = clock_quality_

