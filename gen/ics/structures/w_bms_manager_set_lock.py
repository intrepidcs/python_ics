# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class w_bms_manager_set_lock(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('managerIndex', ctypes.c_uint8),
        ('setLock', ctypes.c_uint8),
    ]


_wBMSManagerSetLock = w_bms_manager_set_lock
wBMSManagerSetLock = w_bms_manager_set_lock

