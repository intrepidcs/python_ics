# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.can_settings import *
from ics.structures.iso9141_keyword2000_settings import *
from ics.structures.lin_settings import *
from ics.structures.s_text_api_settings import *
from ics.structures.uart_settings import *


class sievb_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('ecu_id', ctypes.c_uint32),
        ('selected_network', ctypes.c_uint16),
        ('can1', CAN_SETTINGS),
        ('lin1', LIN_SETTINGS),
        ('network_enables', ctypes.c_uint16),
        ('network_enables_2', ctypes.c_uint16),
        ('network_enabled_on_boot', ctypes.c_uint16),
        ('misc_io_initial_ddr', ctypes.c_uint16),
        ('misc_io_initial_latch', ctypes.c_uint16),
        ('misc_io_analog_enable', ctypes.c_uint16),
        ('misc_io_report_period', ctypes.c_uint16),
        ('misc_io_on_report_events', ctypes.c_uint16),
        ('ain_sample_period', ctypes.c_uint16),
        ('ain_threshold', ctypes.c_uint16),
        ('iso15765_separation_time_offset', ctypes.c_uint16),
        ('can2', CAN_SETTINGS),
        ('lin2', LIN_SETTINGS),
        ('uart', UART_SETTINGS),
        ('uart2', UART_SETTINGS),
        ('text_api', STextAPISettings),
        ('reserved_1', ctypes.c_uint32),
        ('reserved_2', ctypes.c_uint32),
        ('pwr_man_timeout', ctypes.c_uint32),
        ('pwr_man_enable', ctypes.c_uint16),
        ('idle_wakeup_network_enables_1', ctypes.c_uint16),
        ('idle_wakeup_network_enables_2', ctypes.c_uint16),
        ('misc_io_analog_enable_2', ctypes.c_uint16),
        ('iso9141_kwp_settings', ISO9141_KEYWORD2000_SETTINGS),
        ('iso_parity', ctypes.c_uint16),
        ('iso_msg_termination', ctypes.c_uint16),
        ('iso_tester_pullup_enable', ctypes.c_uint16),
        ('iso9141_kwp_settings_2', ISO9141_KEYWORD2000_SETTINGS),
        ('iso_parity_2', ctypes.c_uint16),
        ('iso_msg_termination_2', ctypes.c_uint16),
    ]


_SIEVBSettings = sievb_settings
SIEVBSettings = sievb_settings

