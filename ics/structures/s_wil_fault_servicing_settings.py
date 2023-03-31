# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class s_wil_fault_servicing_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('wBMSDeviceID', ctypes.c_uint8),
        ('enabled', ctypes.c_uint8),
    ]


sWIL_FAULT_SERVICING_SETTINGS = s_wil_fault_servicing_settings

