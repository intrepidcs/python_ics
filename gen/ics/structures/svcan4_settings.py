# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.can_settings import *
from ics.structures.canfd_settings import *
from ics.structures.ethernet_settings import *
from ics.structures.ethernet_settings2 import *
from ics.structures.iso9141_keyword2000_settings import *
from ics.structures.lin_settings import *
from ics.structures.s_text_api_settings import *


class flags(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('enableLatencyTest', ctypes.c_uint32, 1),
        ('enablePcEthernetComm', ctypes.c_uint32, 1),
        ('reserved', ctypes.c_uint32, 30),
    ]



class svcan4_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('perf_en', ctypes.c_uint16),
        ('can1', CAN_SETTINGS),
        ('canfd1', CANFD_SETTINGS),
        ('can2', CAN_SETTINGS),
        ('canfd2', CANFD_SETTINGS),
        ('can3', CAN_SETTINGS),
        ('canfd3', CANFD_SETTINGS),
        ('can4', CAN_SETTINGS),
        ('canfd4', CANFD_SETTINGS),
        ('network_enables', ctypes.c_uint16),
        ('network_enables_2', ctypes.c_uint16),
        ('lin1', LIN_SETTINGS),
        ('network_enabled_on_boot', ctypes.c_uint16),
        ('iso15765_separation_time_offset', ctypes.c_int16),
        ('iso_9141_kwp_enable_reserved', ctypes.c_uint16),
        ('iso9141_kwp_settings_1', ISO9141_KEYWORD2000_SETTINGS),
        ('iso_parity_1', ctypes.c_uint16),
        ('iso_msg_termination_1', ctypes.c_uint16),
        ('network_enables_3', ctypes.c_uint16),
        ('text_api', STextAPISettings),
        ('termination_enables', ctypes.c_uint64),
        ('ethernet', ETHERNET_SETTINGS),
        ('flags', flags),
        ('pwr_man_enable', ctypes.c_uint16),
        ('pwr_man_timeout', ctypes.c_uint16),
        ('ethernet2', ETHERNET_SETTINGS2),
    ]


_SVCAN4Settings = svcan4_settings
SVCAN4Settings = svcan4_settings

