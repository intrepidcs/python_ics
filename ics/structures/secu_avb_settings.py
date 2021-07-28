# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.can_settings import *
from ics.structures.canfd_settings import *
from ics.structures.s_text_api_settings import *


class flags(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('disableUsbCheckOnBoot', ctypes.c_uint32, 1),
        ('enableLatencyTest', ctypes.c_uint32, 1),
        ('reserved', ctypes.c_uint32, 30),
    ]



class secu_avb_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('perf_en', ctypes.c_uint16),
        ('can1', CAN_SETTINGS),
        ('canfd1', CANFD_SETTINGS),
        ('can2', CAN_SETTINGS),
        ('canfd2', CANFD_SETTINGS),
        ('network_enables', ctypes.c_uint64),
        ('termination_enables', ctypes.c_uint64),
        ('pwr_man_timeout', ctypes.c_uint32),
        ('pwr_man_enable', ctypes.c_uint16),
        ('network_enabled_on_boot', ctypes.c_uint16),
        ('iso15765_separation_time_offset', ctypes.c_int16),
        ('text_api', STextAPISettings),
        ('flags', flags),
    ]


_neoECU_AVBSettings = secu_avb_settings
ECU_AVBSettings = secu_avb_settings
SECU_AVBSettings = secu_avb_settings

