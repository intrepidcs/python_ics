# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.a2_b_monitor_settings import *
from ics.structures.can_settings import *
from ics.structures.canfd_settings import *
from ics.structures.disk_settings import *
from ics.structures.ethernet_settings2 import *
from ics.structures.iso9141_keyword2000_settings import *
from ics.structures.lin_settings import *
from ics.structures.logger_settings import *
from ics.structures.rad_reporting_settings import *
from ics.structures.srad_gptp_settings_s import *
from ics.structures.timesync_icshardware_settings import *


class flags(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('hwComLatencyTestEn', ctypes.c_uint16, 1),
        ('disableUsbCheckOnBoot', ctypes.c_uint16, 1),
        ('', ctypes.c_uint16, 14),
    ]



class srada2_b_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('perf_en', ctypes.c_uint16),
        ('flags', flags),
        ('network_enabled_on_boot', ctypes.c_uint16),
        ('can1', CAN_SETTINGS),
        ('canfd1', CANFD_SETTINGS),
        ('can2', CAN_SETTINGS),
        ('canfd2', CANFD_SETTINGS),
        ('lin1', LIN_SETTINGS),
        ('iso9141_kwp_settings_1', ISO9141_KEYWORD2000_SETTINGS),
        ('iso_parity_1', ctypes.c_uint16),
        ('iso_msg_termination_1', ctypes.c_uint16),
        ('network_enables', ctypes.c_uint64),
        ('termination_enables', ctypes.c_uint64),
        ('timeSyncSettings', TIMESYNC_ICSHARDWARE_SETTINGS),
        ('reporting', RAD_REPORTING_SETTINGS),
        ('disk', DISK_SETTINGS),
        ('logger', LOGGER_SETTINGS),
        ('iso15765_separation_time_offset', ctypes.c_int16),
        ('a2b_monitor', A2BMonitorSettings),
        ('a2b_node', A2BMonitorSettings),
        ('pwr_man_timeout', ctypes.c_uint32),
        ('pwr_man_enable', ctypes.c_uint16),
        ('ethernet', ETHERNET_SETTINGS2),
        ('gPTP', RAD_GPTP_SETTINGS),
        ('network_enables_5', ctypes.c_uint64),
    ]


_SRADA2BSettings = srada2_b_settings
SRADA2BSettings = srada2_b_settings

