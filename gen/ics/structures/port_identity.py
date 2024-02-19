# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class port_identity(ctypes.Structure):
    _pack_ = 1
    _fields_ = [
        ('clock_identity', ctypes.c_uint64),
        ('port_number', ctypes.c_uint16),
    ]



