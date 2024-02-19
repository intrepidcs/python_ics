# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.can_settings import *


class svcan3_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('can1', CAN_SETTINGS),
        ('can2', CAN_SETTINGS),
        ('network_enables', ctypes.c_uint16),
        ('network_enabled_on_boot', ctypes.c_uint16),
        ('iso15765_separation_time_offset', ctypes.c_uint16),
        ('perf_en', ctypes.c_uint16),
        ('misc_io_initial_ddr', ctypes.c_uint16),
        ('misc_io_initial_latch', ctypes.c_uint16),
        ('misc_io_report_period', ctypes.c_uint16),
        ('misc_io_on_report_events', ctypes.c_uint16),
    ]


_SVCAN3Settings = svcan3_settings
SVCAN3Settings = svcan3_settings

