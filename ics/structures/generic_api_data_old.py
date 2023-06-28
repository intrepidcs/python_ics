# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.generic_api_selector import *


class generic_api_data_old(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('api', GenericAPISelector),
        ('bData', ctypes.c_uint8 * 513),
        ('length', ctypes.c_uint16),
    ]


_GenericAPIData_OLD = generic_api_data_old
GenericAPIData_OLD = generic_api_data_old

