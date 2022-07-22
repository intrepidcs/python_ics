# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class wil_function_data(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('functionID', ctypes.c_uint8),
        ('parameters', ctypes.c_uint8 * 194),
        ('resevered', ctypes.c_uint8),
    ]


_WILFunctionData = wil_function_data
WILFunctionData = wil_function_data

