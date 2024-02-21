# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class extended_response_generic(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('commandType', ctypes.c_uint16),
        ('returnCode', ctypes.c_int32),
    ]


_ExtendedResponseGeneric = extended_response_generic
ExtendedResponseGeneric = extended_response_generic

