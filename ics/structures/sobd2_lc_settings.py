# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.can_settings import *
from ics.structures.canfd_settings import *
from ics.structures.disk_settings import *
from ics.structures.ethernet_settings import *
from ics.structures.ethernet_settings2 import *
from ics.structures.iso9141_keyword2000_settings import *
from ics.structures.lin_settings import *
from ics.structures.s_text_api_settings import *
from ics.structures.swcan_settings import *


class Nameless8267(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('network_enables', ctypes.c_uint16),
        ('network_enables_2', ctypes.c_uint16),
        ('network_enables_3', ctypes.c_uint16),
    ]



class network_enables(ctypes.Union):
    _pack_ = 2
    _anonymous_  = ('Nameless8267',)
    _fields_ = [
        ('word', ctypes.c_uint64),
        ('Nameless8267', Nameless8267),
    ]



class flags(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('disableUsbCheckOnBoot', ctypes.c_uint32, 1),
        ('enableLatencyTest', ctypes.c_uint32, 1),
        ('busMessagesToAndroid', ctypes.c_uint32, 1),
        ('enablePcEthernetComm', ctypes.c_uint32, 1),
        ('enableDefaultLogger', ctypes.c_uint32, 1),
        ('enableDefaultUpload', ctypes.c_uint32, 1),
        ('reserved', ctypes.c_uint32, 26),
    ]



class sobd2_lc_settings(ctypes.Structure):
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
        ('swcan1', SWCAN_SETTINGS),
        ('lin1', LIN_SETTINGS),
        ('iso9141_kwp_settings_1', ISO9141_KEYWORD2000_SETTINGS),
        ('iso_parity_1', ctypes.c_uint16),
        ('iso_msg_termination_1', ctypes.c_uint16),
        ('network_enables', network_enables),
        ('pwr_man_timeout', ctypes.c_uint32),
        ('pwr_man_enable', ctypes.c_uint16),
        ('network_enabled_on_boot', ctypes.c_uint16),
        ('iso15765_separation_time_offset', ctypes.c_int16),
        ('text_api', STextAPISettings),
        ('flags', flags),
        ('can_switch_mode', ctypes.c_uint16),
        ('misc_io_on_report_events', ctypes.c_uint16),
        ('disk', DISK_SETTINGS),
        ('ethernet', ETHERNET_SETTINGS),
        ('ethernet2', ETHERNET_SETTINGS2),
    ]


_SOBD2LCSettings = sobd2_lc_settings
OBD2LCSettings = sobd2_lc_settings
SOBD2LCSettings = sobd2_lc_settings

