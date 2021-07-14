# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class s_disk_format_progress(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('state', ctypes.c_uint16),
        ('sectorsRemaining', ctypes.c_uint8 * 8),
    ]


_SDiskFormatProgress = s_disk_format_progress
SDiskFormatProgress = s_disk_format_progress

