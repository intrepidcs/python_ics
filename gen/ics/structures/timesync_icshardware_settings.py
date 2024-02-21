# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class timesync_icshardware_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('MasterEnable', ctypes.c_uint8),
        ('SlaveEnable', ctypes.c_uint8),
        ('MasterNetwork', ctypes.c_uint8),
        ('SlaveNetwork', ctypes.c_uint8),
    ]


TIMESYNC_ICSHARDWARE_SETTINGS = timesync_icshardware_settings

