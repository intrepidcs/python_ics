# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.can_settings import *
from ics.structures.canfd_settings import *
from ics.structures.disk_settings import *
from ics.structures.ethernet_settings import *
from ics.structures.ethernet_settings2 import *
from ics.structures.fire3_linux_settings import *
from ics.structures.iso9141_keyword2000_settings import *
from ics.structures.lin_settings import *
from ics.structures.s_text_api_settings import *
from ics.structures.srad_gptp_settings_s import *
from ics.structures.timesync_icshardware_settings import *


class Nameless39639(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('network_enables', ctypes.c_uint16),
        ('network_enables_2', ctypes.c_uint16),
        ('network_enables_3', ctypes.c_uint16),
        ('network_enables_4', ctypes.c_uint16),
    ]



class network_enables(ctypes.Union):
    _pack_ = 2
    _anonymous_  = ('Nameless39639',)
    _fields_ = [
        ('word', ctypes.c_uint64),
        ('Nameless39639', Nameless39639),
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



class s_fire3_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('perf_en', ctypes.c_uint16),
        ('network_enabled_on_boot', ctypes.c_uint16),
        ('misc_io_on_report_events', ctypes.c_uint16),
        ('pwr_man_enable', ctypes.c_uint16),
        ('iso15765_separation_time_offset', ctypes.c_int16),
        ('slaveVnetA', ctypes.c_uint16),
        ('reserved', ctypes.c_uint32),
        ('termination_enables', ctypes.c_uint64),
        ('network_enables', network_enables),
        ('pwr_man_timeout', ctypes.c_uint32),
        ('can1', CAN_SETTINGS),
        ('canfd1', CANFD_SETTINGS),
        ('can2', CAN_SETTINGS),
        ('canfd2', CANFD_SETTINGS),
        ('can3', CAN_SETTINGS),
        ('canfd3', CANFD_SETTINGS),
        ('can4', CAN_SETTINGS),
        ('canfd4', CANFD_SETTINGS),
        ('can5', CAN_SETTINGS),
        ('canfd5', CANFD_SETTINGS),
        ('can6', CAN_SETTINGS),
        ('canfd6', CANFD_SETTINGS),
        ('can7', CAN_SETTINGS),
        ('canfd7', CANFD_SETTINGS),
        ('can8', CAN_SETTINGS),
        ('canfd8', CANFD_SETTINGS),
        ('lin1', LIN_SETTINGS),
        ('lin2', LIN_SETTINGS),
        ('iso9141_kwp_settings_1', ISO9141_KEYWORD2000_SETTINGS),
        ('iso_parity_1', ctypes.c_uint16),
        ('iso_msg_termination_1', ctypes.c_uint16),
        ('iso9141_kwp_settings_2', ISO9141_KEYWORD2000_SETTINGS),
        ('iso_parity_2', ctypes.c_uint16),
        ('iso_msg_termination_2', ctypes.c_uint16),
        ('ethernet_1', ETHERNET_SETTINGS),
        ('timeSync', TIMESYNC_ICSHARDWARE_SETTINGS),
        ('text_api', STextAPISettings),
        ('flags', flags),
        ('disk', DISK_SETTINGS),
        ('misc_io_report_period', ctypes.c_uint16),
        ('ain_threshold', ctypes.c_uint16),
        ('misc_io_analog_enable', ctypes.c_uint16),
        ('digitalIoThresholdTicks', ctypes.c_uint16),
        ('digitalIoThresholdEnable', ctypes.c_uint16),
        ('misc_io_initial_ddr', ctypes.c_uint16),
        ('misc_io_initial_latch', ctypes.c_uint16),
        ('ethernet2_1', ETHERNET_SETTINGS2),
        ('ethernet_2', ETHERNET_SETTINGS),
        ('ethernet2_2', ETHERNET_SETTINGS2),
        ('os_settings', Fire3LinuxSettings),
        ('gPTP', RAD_GPTP_SETTINGS),
    ]


_SFire3Settings = s_fire3_settings
SFire3Settings = s_fire3_settings

