# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class unlock(ctypes.Structure):
    _pack_ = 1
    _fields_ = [
        ('apiVersion', ctypes.c_uint32),
        ('code', ctypes.c_uint32),
    ]



class manufacturing_operation(ctypes.Union):
    _pack_ = 1
    _fields_ = [
        ('rtcCalEnable', ctypes.c_uint32),
        ('rtcCalValue', ctypes.c_int),
        ('unlock', unlock),
        ('bytes', ctypes.c_uint8 * 256),
    ]


ManufacturingOperation = manufacturing_operation
ManufacturingOperation = manufacturing_operation

