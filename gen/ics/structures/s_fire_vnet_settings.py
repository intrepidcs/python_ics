# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.can_settings import *
from ics.structures.iso9141_keyword2000_settings import *
from ics.structures.lin_settings import *
from ics.structures.s_neo_most_gateway_settings import *
from ics.structures.s_text_api_settings import *
from ics.structures.swcan_settings import *
from ics.structures.uart_settings import *


class s_fire_vnet_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('can1', CAN_SETTINGS),
        ('can2', CAN_SETTINGS),
        ('can3', CAN_SETTINGS),
        ('can4', CAN_SETTINGS),
        ('swcan', SWCAN_SETTINGS),
        ('lsftcan', CAN_SETTINGS),
        ('lin1', LIN_SETTINGS),
        ('lin2', LIN_SETTINGS),
        ('lin3', LIN_SETTINGS),
        ('lin4', LIN_SETTINGS),
        ('cgi_enable_reserved', ctypes.c_uint16),
        ('cgi_baud', ctypes.c_uint16),
        ('cgi_tx_ifs_bit_times', ctypes.c_uint16),
        ('cgi_rx_ifs_bit_times', ctypes.c_uint16),
        ('cgi_chksum_enable', ctypes.c_uint16),
        ('network_enables', ctypes.c_uint16),
        ('network_enabled_on_boot', ctypes.c_uint16),
        ('pwm_man_timeout', ctypes.c_uint32),
        ('pwr_man_enable', ctypes.c_uint16),
        ('misc_io_initial_ddr', ctypes.c_uint16),
        ('misc_io_initial_latch', ctypes.c_uint16),
        ('misc_io_analog_enable', ctypes.c_uint16),
        ('misc_io_report_period', ctypes.c_uint16),
        ('misc_io_on_report_events', ctypes.c_uint16),
        ('ain_sample_period', ctypes.c_uint16),
        ('ain_threshold', ctypes.c_uint16),
        ('iso15765_separation_time_offset', ctypes.c_uint16),
        ('iso9141_kwp_enable_reserved', ctypes.c_uint16),
        ('iso9141_kwp_settings', ISO9141_KEYWORD2000_SETTINGS),
        ('perf_en', ctypes.c_uint16),
        ('iso_parity', ctypes.c_uint16),
        ('iso_msg_termination', ctypes.c_uint16),
        ('iso_tester_pullup_enable', ctypes.c_uint16),
        ('network_enables_2', ctypes.c_uint16),
        ('iso9141_kwp_settings_2', ISO9141_KEYWORD2000_SETTINGS),
        ('iso_parity_2', ctypes.c_uint16),
        ('iso_msg_termination_2', ctypes.c_uint16),
        ('iso9141_kwp_settings_3', ISO9141_KEYWORD2000_SETTINGS),
        ('iso_parity_3', ctypes.c_uint16),
        ('iso_msg_termination_3', ctypes.c_uint16),
        ('iso9141_kwp_settings_4', ISO9141_KEYWORD2000_SETTINGS),
        ('iso_parity_4', ctypes.c_uint16),
        ('iso_msg_termination_4', ctypes.c_uint16),
        ('fast_init_network_enables_1', ctypes.c_uint16),
        ('fast_init_network_enables_2', ctypes.c_uint16),
        ('uart', UART_SETTINGS),
        ('uart2', UART_SETTINGS),
        ('text_api', STextAPISettings),
        ('neoMostGateway', SNeoMostGatewaySettings),
        ('vnetBits', ctypes.c_uint16),
        ('can5', CAN_SETTINGS),
        ('can6', CAN_SETTINGS),
        ('lin5', LIN_SETTINGS),
        ('swcan2', SWCAN_SETTINGS),
    ]


_SFireVnetSettings = s_fire_vnet_settings
SFireVnetSettings = s_fire_vnet_settings

