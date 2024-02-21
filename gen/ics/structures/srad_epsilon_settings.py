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
from ics.structures.srad_epsilon_switch_settings import *


class flags(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('disableUsbCheckOnBoot', ctypes.c_uint32, 1),
        ('enableLatencyTest', ctypes.c_uint32, 1),
        ('enablePcEthernetComm', ctypes.c_uint32, 1),
        ('reserved', ctypes.c_uint32, 29),
    ]



class srad_epsilon_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('perf_en', ctypes.c_uint16),
        ('can1', CAN_SETTINGS),
        ('canfd1', CANFD_SETTINGS),
        ('can2', CAN_SETTINGS),
        ('canfd2', CANFD_SETTINGS),
        ('lin1', LIN_SETTINGS),
        ('network_enables', ctypes.c_uint16),
        ('network_enables_2', ctypes.c_uint16),
        ('network_enables_3', ctypes.c_uint16),
        ('termination_enables', ctypes.c_uint64),
        ('misc_io_analog_enable', ctypes.c_uint16),
        ('pwr_man_timeout', ctypes.c_uint32),
        ('pwr_man_enable', ctypes.c_uint16),
        ('network_enabled_on_boot', ctypes.c_uint16),
        ('iso15765_separation_time_offset', ctypes.c_int16),
        ('iso9141_kwp_enable_reserved', ctypes.c_uint16),
        ('iso_tester_pullup_enable', ctypes.c_uint16),
        ('iso_parity', ctypes.c_uint16),
        ('iso_msg_termination', ctypes.c_uint16),
        ('iso9141_kwp_settings', ISO9141_KEYWORD2000_SETTINGS),
        ('ethernet', ETHERNET_SETTINGS),
        ('text_api', STextAPISettings),
        ('flags', flags),
        ('switchSettings', SRADEpsilonSwitchSettings),
        ('ethernet2', ETHERNET_SETTINGS2),
        ('misc_io_on_report_events', ctypes.c_uint16),
    ]


_SRADEpsilonSettings = srad_epsilon_settings
SRADEpsilonSettings = srad_epsilon_settings

