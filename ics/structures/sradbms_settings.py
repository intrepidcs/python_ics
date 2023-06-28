# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.can_settings import *
from ics.structures.canfd_settings import *
from ics.structures.ethernet_settings import *
from ics.structures.ethernet_settings2 import *
from ics.structures.s_spi_port_settings import *
from ics.structures.s_wil_bridge_config import *
from ics.structures.s_wil_connection_settings import *
from ics.structures.wbms_gateway_settings import *


class flags(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('disableUsbCheckOnBoot', ctypes.c_uint32, 1),
        ('enableLatencyTest', ctypes.c_uint32, 1),
        ('enablePcEthernetComm', ctypes.c_uint32, 1),
        ('reserved', ctypes.c_uint32, 29),
    ]



class sradbms_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('perf_en', ctypes.c_uint16),
        ('termination_enables', ctypes.c_uint64),
        ('can1', CAN_SETTINGS),
        ('canfd1', CANFD_SETTINGS),
        ('can2', CAN_SETTINGS),
        ('canfd2', CANFD_SETTINGS),
        ('network_enables', ctypes.c_uint16),
        ('network_enables_2', ctypes.c_uint16),
        ('network_enables_3', ctypes.c_uint16),
        ('iso15765_separation_time_offset', ctypes.c_int16),
        ('flags', flags),
        ('ethernet', ETHERNET_SETTINGS),
        ('ethernet2', ETHERNET_SETTINGS2),
        ('pwr_man_timeout', ctypes.c_uint32),
        ('pwr_man_enable', ctypes.c_uint16),
        ('network_enabled_on_boot', ctypes.c_uint16),
        ('wil_config', sWILBridgeConfig),
        ('spi_config', sSPI_PORT_SETTINGS),
        ('wbms_wil_1', sWIL_CONNECTION_SETTINGS),
        ('wbms_wil_2', sWIL_CONNECTION_SETTINGS),
        ('wil1_nwk_metadata_buff_count', ctypes.c_uint16),
        ('wil2_nwk_metadata_buff_count', ctypes.c_uint16),
        ('gateway', WBMSGatewaySettings),
        ('network_enables_4', ctypes.c_uint16),
        ('network_enables_5', ctypes.c_uint64),
    ]


_SRADBMSSettings = sradbms_settings
SRADBMSSettings = sradbms_settings

