# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.op_eth_general_settings import *
from ics.structures.op_eth_settings import *
from ics.structures.s_text_api_settings import *
from ics.structures.srad_gptp_settings_s import *
from ics.structures.timesync_icshardware_settings import *


class srad_moon2_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('perf_en', ctypes.c_uint16),
        ('opEthGen', OP_ETH_GENERAL_SETTINGS),
        ('opEth1', OP_ETH_SETTINGS),
        ('network_enables', ctypes.c_uint16),
        ('network_enables_2', ctypes.c_uint16),
        ('network_enabled_on_boot', ctypes.c_uint16),
        ('network_enables_3', ctypes.c_uint16),
        ('text_api', STextAPISettings),
        ('pc_com_mode', ctypes.c_uint16),
        ('timeSyncSettings', TIMESYNC_ICSHARDWARE_SETTINGS),
        ('hwComLatencyTestEn', ctypes.c_uint16),
        ('gPTP', RAD_GPTP_SETTINGS),
        ('network_enables_5', ctypes.c_uint64),
    ]


_SRADMoon2Settings = srad_moon2_settings
SRADMoon2Settings = srad_moon2_settings

