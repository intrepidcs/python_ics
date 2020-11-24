# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

class s_disk_format_progress(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('state', ctypes.c_uint16), # state of formatting (not started, writing file system, formatting, writing VSAs, finished)
        ('sectorsRemaining', ctypes.c_uint8 * 8), 
    ]

# Extra names go here:
SDiskFormatProgress = s_disk_format_progress
# End of extra names

