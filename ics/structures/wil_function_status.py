# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class wil_function_status(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('functionID', ctypes.c_uint8),
        ('functionError', ctypes.c_uint8),
        ('processing', ctypes.c_uint8),
        ('calbackError', ctypes.c_uint8),
    ]


_WILFunctionStatus = wil_function_status
WILFunctionStatus = wil_function_status

