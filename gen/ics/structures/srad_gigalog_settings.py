# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.can_settings import *
from ics.structures.canfd_settings import *
from ics.structures.disk_settings import *
from ics.structures.ethernet10_g_settings import *
from ics.structures.ethernet_settings2 import *
from ics.structures.iso9141_keyword2000_settings import *
from ics.structures.lin_settings import *
from ics.structures.logger_settings import *
from ics.structures.rad_reporting_settings import *
from ics.structures.s_text_api_settings import *
from ics.structures.serdescam_settings import *
from ics.structures.serdesgen_settings import *
from ics.structures.serdespoc_settings import *
from ics.structures.timesync_icshardware_settings import *


class flags(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('hwComLatencyTestEn', ctypes.c_uint16, 1),
        ('disableUsbCheckOnBoot', ctypes.c_uint16, 1),
        ('reserved', ctypes.c_uint16, 14),
    ]



class srad_gigalog_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('ecu_id', ctypes.c_uint32),
        ('perf_en', ctypes.c_uint16),
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
        ('network_enables', ctypes.c_uint16),
        ('network_enables_2', ctypes.c_uint16),
        ('pwr_man_timeout', ctypes.c_uint32),
        ('pwr_man_enable', ctypes.c_uint16),
        ('network_enabled_on_boot', ctypes.c_uint16),
        ('iso15765_separation_time_offset', ctypes.c_uint16),
        ('iso_9141_kwp_enable_reserved', ctypes.c_uint16),
        ('iso9141_kwp_settings_1', ISO9141_KEYWORD2000_SETTINGS),
        ('iso_parity_1', ctypes.c_uint16),
        ('iso_msg_termination_1', ctypes.c_uint16),
        ('idle_wakeup_network_enables_1', ctypes.c_uint16),
        ('idle_wakeup_network_enables_2', ctypes.c_uint16),
        ('network_enables_3', ctypes.c_uint16),
        ('idle_wakeup_network_enables_3', ctypes.c_uint16),
        ('text_api', STextAPISettings),
        ('termination_enables', ctypes.c_uint64),
        ('rsvd1', ctypes.c_uint8 * 8),
        ('rsvd2', ctypes.c_uint8 * 8),
        ('disk', DISK_SETTINGS),
        ('timeSyncSettings', TIMESYNC_ICSHARDWARE_SETTINGS),
        ('flags', flags),
        ('ethernet', ETHERNET_SETTINGS2),
        ('serdescam1', SERDESCAM_SETTINGS),
        ('ethernet10g', ETHERNET10G_SETTINGS),
        ('lin1', LIN_SETTINGS),
        ('serdespoc', SERDESPOC_SETTINGS),
        ('logger', LOGGER_SETTINGS),
        ('serdescam2', SERDESCAM_SETTINGS),
        ('serdescam3', SERDESCAM_SETTINGS),
        ('serdescam4', SERDESCAM_SETTINGS),
        ('ethernet2', ETHERNET_SETTINGS2),
        ('network_enables_4', ctypes.c_uint16),
        ('reporting', RAD_REPORTING_SETTINGS),
        ('serdesgen', SERDESGEN_SETTINGS),
        ('network_enables_5', ctypes.c_uint64),
    ]


_SRADGigalogSettings = srad_gigalog_settings
SRADGigalogSettings = srad_gigalog_settings

