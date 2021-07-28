# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.can_settings import *
from ics.structures.canfd_settings import *
from ics.structures.s_text_api_settings import *


class flags(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('', ctypes.c_uint32, 1),
        ('enableLatencyTest', ctypes.c_uint32, 1),
        ('reserved', ctypes.c_uint32, 30),
    ]



class sobd2_sim_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('can1', CAN_SETTINGS),
        ('can2', CAN_SETTINGS),
        ('canfd1', CANFD_SETTINGS),
        ('canfd2', CANFD_SETTINGS),
        ('network_enables', ctypes.c_uint64),
        ('network_enabled_on_boot', ctypes.c_uint16),
        ('iso15765_separation_time_offset', ctypes.c_int16),
        ('perf_en', ctypes.c_uint16),
        ('misc_io_initial_ddr', ctypes.c_uint16),
        ('misc_io_initial_latch', ctypes.c_uint16),
        ('misc_io_report_period', ctypes.c_uint16),
        ('misc_io_on_report_events', ctypes.c_uint16),
        ('misc_io_analog_enable', ctypes.c_uint16),
        ('ain_sample_period', ctypes.c_uint16),
        ('ain_threshold', ctypes.c_uint16),
        ('flags', flags),
        ('text_api', STextAPISettings),
    ]


_SOBD2SimSettings = sobd2_sim_settings
SOBD2SimSettings = sobd2_sim_settings

