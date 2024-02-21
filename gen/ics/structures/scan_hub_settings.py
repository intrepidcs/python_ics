# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.can_settings import *
from ics.structures.canfd_settings import *
from ics.structures.scan_sleep_id import *


class scan_hub_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('can1', CAN_SETTINGS),
        ('canfd1', CANFD_SETTINGS),
        ('network_enables', ctypes.c_uint64),
        ('termination_enables', ctypes.c_uint64),
        ('pwr_man_timeout', ctypes.c_uint32),
        ('pwr_man_enable', ctypes.c_uint16),
        ('network_enabled_on_boot', ctypes.c_uint16),
        ('iso15765_separation_time_offset', ctypes.c_int16),
        ('ecu_id', ctypes.c_uint32),
        ('sleep_id', SCANSleepID),
    ]


CANHubSettings = scan_hub_settings
SCANHubSettings = scan_hub_settings

