# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.can_settings import *
from ics.structures.iso9141_keyword2000_settings import *
from ics.structures.lin_settings import *
from ics.structures.s_text_api_settings import *
from ics.structures.swcan_settings import *
from ics.structures.uart_settings import *


class secu_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('ecu_id', ctypes.c_uint32),
        ('selected_network', ctypes.c_uint16),
        ('can1', CAN_SETTINGS),
        ('can2', CAN_SETTINGS),
        ('lin1', LIN_SETTINGS),
        ('lin2', LIN_SETTINGS),
        ('iso15765_separation_time_offset', ctypes.c_uint16),
        ('iso9141_kwp_settings', ISO9141_KEYWORD2000_SETTINGS),
        ('iso_parity', ctypes.c_uint16),
        ('iso_msg_termination', ctypes.c_uint16),
        ('iso9141_kwp_settings_2', ISO9141_KEYWORD2000_SETTINGS),
        ('iso_parity_2', ctypes.c_uint16),
        ('iso_msg_termination_2', ctypes.c_uint16),
        ('network_enables', ctypes.c_uint16),
        ('network_enables_2', ctypes.c_uint16),
        ('network_enabled_on_boot', ctypes.c_uint16),
        ('pwr_man_timeout', ctypes.c_uint32),
        ('pwr_man_enable', ctypes.c_uint16),
        ('misc_io_initial_ddr', ctypes.c_uint16),
        ('misc_io_initial_latch', ctypes.c_uint16),
        ('misc_io_analog_enable', ctypes.c_uint16),
        ('misc_io_report_period', ctypes.c_uint16),
        ('misc_io_on_report_events', ctypes.c_uint16),
        ('ain_sample_period', ctypes.c_uint16),
        ('ain_threshold', ctypes.c_uint16),
        ('swcan', SWCAN_SETTINGS),
        ('swcan2', SWCAN_SETTINGS),
        ('lsftcan', CAN_SETTINGS),
        ('lsftcan2', CAN_SETTINGS),
        ('uart', UART_SETTINGS),
        ('uart2', UART_SETTINGS),
        ('text_api', STextAPISettings),
    ]


_SECUSettings = secu_settings
SECUSettings = secu_settings

