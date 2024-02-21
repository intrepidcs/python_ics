# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.generic_api_selector import *


class generic_api_data(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('length', ctypes.c_uint16),
        ('api', GenericAPISelector),
        ('bData', ctypes.c_uint8 * 513),
    ]


_GenericAPIData = generic_api_data
GenericAPIData = generic_api_data

