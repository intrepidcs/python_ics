# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.can_settings import *
from ics.structures.canfd_settings import *
from ics.structures.ethernet_settings import *
from ics.structures.ethernet_settings2 import *
from ics.structures.iso9141_keyword2000_settings import *
from ics.structures.lin_settings import *


class Nameless35335(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('network_enables', ctypes.c_uint16),
        ('network_enables_2', ctypes.c_uint16),
        ('network_enables_3', ctypes.c_uint16),
    ]



class network_enables(ctypes.Union):
    _pack_ = 2
    _anonymous_  = ('Nameless35335',)
    _fields_ = [
        ('word', ctypes.c_uint64),
        ('Nameless35335', Nameless35335),
    ]



class flags(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('disableUsbCheckOnBoot', ctypes.c_uint32, 1),
        ('enableLatencyTest', ctypes.c_uint32, 1),
        ('busMessagesToAndroid', ctypes.c_uint32, 1),
        ('enablePcEthernetComm', ctypes.c_uint32, 1),
        ('reserved', ctypes.c_uint32, 28),
    ]



class svcan4_ind_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('can1', CAN_SETTINGS),
        ('canfd1', CANFD_SETTINGS),
        ('can2', CAN_SETTINGS),
        ('canfd2', CANFD_SETTINGS),
        ('ethernet', ETHERNET_SETTINGS),
        ('lin1', LIN_SETTINGS),
        ('iso9141_kwp_settings', ISO9141_KEYWORD2000_SETTINGS),
        ('iso_parity', ctypes.c_uint16),
        ('iso_msg_termination', ctypes.c_uint16),
        ('pwr_man_timeout', ctypes.c_uint32),
        ('pwr_man_enable', ctypes.c_uint16),
        ('perf_en', ctypes.c_uint16),
        ('iso15765_separation_time_offset', ctypes.c_int16),
        ('network_enabled_on_boot', ctypes.c_uint16),
        ('network_enables', network_enables),
        ('termination_enables', ctypes.c_uint64),
        ('flags', flags),
        ('ethernet2', ETHERNET_SETTINGS2),
    ]


_VCAN4IndSettings = svcan4_ind_settings
VCAN4IndSettings = svcan4_ind_settings
SVCAN4IndSettings = svcan4_ind_settings

