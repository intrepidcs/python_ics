# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class fire3_linux_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('allowBoot', ctypes.c_uint8),
        ('useExternalWifiAntenna', ctypes.c_uint8),
        ('ethConfigurationPort', ctypes.c_uint8),
        ('reserved', ctypes.c_uint8 * 5),
    ]


Fire3LinuxSettings = fire3_linux_settings

