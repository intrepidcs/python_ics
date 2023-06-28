# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.can_settings import *
from ics.structures.canfd_settings import *
from ics.structures.disk_settings import *
from ics.structures.ethernet_settings2 import *
from ics.structures.iso9141_keyword2000_settings import *
from ics.structures.lin_settings import *
from ics.structures.logger_settings import *
from ics.structures.op_eth_general_settings import *
from ics.structures.op_eth_settings import *
from ics.structures.rad_reporting_settings import *
from ics.structures.s_text_api_settings import *
from ics.structures.srad_gptp_settings_s import *
from ics.structures.swcan_settings import *
from ics.structures.timesync_icshardware_settings import *


class srad_galaxy_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('perf_en', ctypes.c_uint16),
        ('opEthGen', OP_ETH_GENERAL_SETTINGS),
        ('opEth1', OP_ETH_SETTINGS),
        ('opEth2', OP_ETH_SETTINGS),
        ('opEth3', OP_ETH_SETTINGS),
        ('opEth4', OP_ETH_SETTINGS),
        ('opEth5', OP_ETH_SETTINGS),
        ('opEth6', OP_ETH_SETTINGS),
        ('opEth7', OP_ETH_SETTINGS),
        ('opEth8', OP_ETH_SETTINGS),
        ('opEth9', OP_ETH_SETTINGS),
        ('opEth10', OP_ETH_SETTINGS),
        ('opEth11', OP_ETH_SETTINGS),
        ('opEth12', OP_ETH_SETTINGS),
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
        ('swcan1', SWCAN_SETTINGS),
        ('network_enables', ctypes.c_uint16),
        ('swcan2', SWCAN_SETTINGS),
        ('network_enables_2', ctypes.c_uint16),
        ('lin1', LIN_SETTINGS),
        ('misc_io_initial_ddr', ctypes.c_uint16),
        ('misc_io_initial_latch', ctypes.c_uint16),
        ('misc_io_report_period', ctypes.c_uint16),
        ('misc_io_on_report_events', ctypes.c_uint16),
        ('misc_io_analog_enable', ctypes.c_uint16),
        ('ain_sample_period', ctypes.c_uint16),
        ('ain_threshold', ctypes.c_uint16),
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
        ('can_switch_mode', ctypes.c_uint16),
        ('text_api', STextAPISettings),
        ('timeSyncSettings', TIMESYNC_ICSHARDWARE_SETTINGS),
        ('hwComLatencyTestEn', ctypes.c_uint16),
        ('reporting', RAD_REPORTING_SETTINGS),
        ('disk', DISK_SETTINGS),
        ('logger', LOGGER_SETTINGS),
        ('ethernet1', ETHERNET_SETTINGS2),
        ('ethernet2', ETHERNET_SETTINGS2),
        ('network_enables_4', ctypes.c_uint16),
        ('gPTP', RAD_GPTP_SETTINGS),
        ('network_enables_5', ctypes.c_uint64),
    ]


_SRADGalaxySettings = srad_galaxy_settings
SRADGalaxySettings = srad_galaxy_settings

