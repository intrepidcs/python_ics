# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class generic_binary_status(ctypes.Structure):
    _pack_ = 1
    _fields_ = [
        ('size', ctypes.c_uint32),
        ('index', ctypes.c_uint16),
        ('status', ctypes.c_uint16),
        ('reserved', ctypes.c_uint8 * 8),
    ]


_GenericBinaryStatus = generic_binary_status
GenericBinaryStatus = generic_binary_status

