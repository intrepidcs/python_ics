# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class generic_api_selector(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('apiIndex', ctypes.c_uint8),
        ('instance', ctypes.c_uint8),
        ('functionID', ctypes.c_uint8),
    ]


_GenericAPISelector = generic_api_selector
GenericAPISelector = generic_api_selector

