# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.port_identity import *
from ics.structures.system_identity import *


class priority_vector(ctypes.Structure):
    _pack_ = 1
    _fields_ = [
        ('sysid', system_identity),
        ('steps_removed', ctypes.c_uint16),
        ('portid', port_identity),
        ('port_number', ctypes.c_uint16),
    ]



