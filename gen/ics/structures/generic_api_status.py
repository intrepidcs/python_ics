# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.generic_api_selector import *


class generic_api_status(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('api', GenericAPISelector),
        ('functionError', ctypes.c_uint8),
        ('calbackError', ctypes.c_uint8),
        ('finishedProcessing', ctypes.c_uint8),
    ]


_GenericAPIStatus = generic_api_status
GenericAPIStatus = generic_api_status

