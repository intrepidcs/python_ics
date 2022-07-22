# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.priority_vector import *
from ics.structures.timestamp_ import *


class gptp_status(ctypes.Structure):
    _pack_ = 1
    _fields_ = [
        ('current_time', timestamp_),
        ('gm_priority', priority_vector),
        ('ms_offset_ns', ctypes.c_int64),
        ('is_sync', ctypes.c_uint8),
        ('link_status', ctypes.c_uint8),
        ('link_delay_ns', ctypes.c_int64),
        ('selected_role', ctypes.c_uint8),
        ('as_capable', ctypes.c_uint8),
        ('is_syntonized', ctypes.c_uint8),
        ('reserved', ctypes.c_uint8 * 8),
    ]


_GPTPStatus = gptp_status
GPTPStatus = gptp_status

