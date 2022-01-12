# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.can_settings import *
from ics.structures.canfd_settings import *
from ics.structures.iso9141_keyword2000_settings import *
from ics.structures.lin_settings import *
from ics.structures.s_text_api_settings import *
from ics.structures.swcan_settings import *


class flags(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('disableUsbCheckOnBoot', ctypes.c_uint32, 1),
        ('enableLatencyTest', ctypes.c_uint32, 1),
        ('reserved', ctypes.c_uint32, 30),
    ]



class s_neo_ecu12_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('ecu_id', ctypes.c_uint32),
        ('can1', CAN_SETTINGS),
        ('canfd1', CANFD_SETTINGS),
        ('can2', CAN_SETTINGS),
        ('canfd2', CANFD_SETTINGS),
        ('swcan1', SWCAN_SETTINGS),
        ('swcan2', SWCAN_SETTINGS),
        ('lsftcan1', CAN_SETTINGS),
        ('lsftcan2', CAN_SETTINGS),
        ('lin1', LIN_SETTINGS),
        ('network_enables', ctypes.c_uint64),
        ('network_enabled_on_boot', ctypes.c_uint16),
        ('termination_enables', ctypes.c_uint64),
        ('can_switch_mode', ctypes.c_uint16),
        ('iso_9141_kwp_enable_reserved', ctypes.c_uint16),
        ('iso9141_kwp_settings', ISO9141_KEYWORD2000_SETTINGS),
        ('iso_parity', ctypes.c_uint16),
        ('iso_msg_termination', ctypes.c_uint16),
        ('pwr_man_timeout', ctypes.c_uint32),
        ('pwr_man_enable', ctypes.c_uint16),
        ('perf_en', ctypes.c_uint16),
        ('misc_io_initial_ddr', ctypes.c_uint16),
        ('misc_io_initial_latch', ctypes.c_uint16),
        ('misc_io_analog_enable', ctypes.c_uint16),
        ('misc_io_report_period', ctypes.c_uint16),
        ('misc_io_on_report_events', ctypes.c_uint16),
        ('ain_sample_period', ctypes.c_uint16),
        ('ain_threshold', ctypes.c_uint16),
        ('iso15765_separation_time_offset', ctypes.c_int16),
        ('text_api', STextAPISettings),
        ('flags', flags),
        ('reserved_field', ctypes.c_uint32 * 2),
    ]


_NeoECU12Settings = s_neo_ecu12_settings
SNeoECU12Settings = s_neo_ecu12_settings

