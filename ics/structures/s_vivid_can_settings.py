# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.can_settings import *
from ics.structures.swcan_settings import *


class flags(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('disableUsbCheckOnBoot', ctypes.c_uint32, 1),
        ('enableLatencyTest', ctypes.c_uint32, 1),
        ('reserved', ctypes.c_uint32, 30),
    ]



class s_vivid_can_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('ecu_id', ctypes.c_uint32),
        ('can1', CAN_SETTINGS),
        ('swcan1', SWCAN_SETTINGS),
        ('lsftcan1', CAN_SETTINGS),
        ('network_enables', ctypes.c_uint16),
        ('network_enabled_on_boot', ctypes.c_uint16),
        ('iso15765_separation_time_offset', ctypes.c_uint16),
        ('perf_en', ctypes.c_uint16),
        ('pwr_man_timeout', ctypes.c_uint32),
        ('pwr_man_enable', ctypes.c_uint16),
        ('can_switch_mode', ctypes.c_uint16),
        ('termination_enables', ctypes.c_uint16),
        ('flags', flags),
    ]


_SVividCANSettings = s_vivid_can_settings
SVividCANSettings = s_vivid_can_settings

