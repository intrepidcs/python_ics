# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.disk_settings import *


class s_disk_structure(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('settings', DISK_SETTINGS),
        ('options', ctypes.c_uint16),
    ]


_SDiskStructure = s_disk_structure
SDiskStructure = s_disk_structure

