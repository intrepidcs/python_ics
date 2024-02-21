# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class version_report(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('valid', ctypes.c_uint8),
        ('expansionSlot', ctypes.c_uint8),
        ('componentInfo', ctypes.c_uint8),
        ('reserved', ctypes.c_uint8),
        ('identifier', ctypes.c_uint32),
        ('dotVersion', ctypes.c_uint32),
        ('commitHash', ctypes.c_uint32),
    ]


_VersionReport = version_report
VersionReport = version_report

