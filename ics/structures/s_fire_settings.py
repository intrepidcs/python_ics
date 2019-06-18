# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

try: # 7
    from can_settings import can_settings
    from swcan_settings import swcan_settings
    from lin_settings import lin_settings
    from iso9141_keyword2000_settings import iso9141_keyword2000_settings
    from uart_settings import uart_settings
    from s_text_api_settings import s_text_api_settings
    from s_neo_most_gateway_settings import s_neo_most_gateway_settings
except:
    from ics.structures.can_settings import can_settings
    from ics.structures.swcan_settings import swcan_settings
    from ics.structures.lin_settings import lin_settings
    from ics.structures.iso9141_keyword2000_settings import iso9141_keyword2000_settings
    from ics.structures.uart_settings import uart_settings
    from ics.structures.s_text_api_settings import s_text_api_settings
    from ics.structures.s_neo_most_gateway_settings import s_neo_most_gateway_settings

class s_fire_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('can1', can_settings), 
        ('can2', can_settings), 
        ('can3', can_settings), 
        ('can4', can_settings), 
        ('swcan', swcan_settings), 
        ('lsftcan', can_settings), 
        ('lin1', lin_settings), 
        ('lin2', lin_settings), 
        ('lin3', lin_settings), 
        ('lin4', lin_settings), 
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
        ('iso9141_kwp_settings', iso9141_keyword2000_settings), 
        ('perf_en', ctypes.c_uint16), 
        ('iso_parity', ctypes.c_uint16), 
        ('iso_msg_termination', ctypes.c_uint16), 
        ('iso_tester_pullup_enable', ctypes.c_uint16), 
        ('network_enables_2', ctypes.c_uint16), 
        ('iso9141_kwp_settings_2', iso9141_keyword2000_settings), 
        ('iso_parity_2', ctypes.c_uint16), 
        ('iso_msg_termination_2', ctypes.c_uint16), 
        ('iso9141_kwp_settings_3', iso9141_keyword2000_settings), 
        ('iso_parity_3', ctypes.c_uint16), 
        ('iso_msg_termination_3', ctypes.c_uint16), 
        ('iso9141_kwp_settings_4', iso9141_keyword2000_settings), 
        ('iso_parity_4', ctypes.c_uint16), 
        ('iso_msg_termination_4', ctypes.c_uint16), 
        ('fast_init_network_enables_1', ctypes.c_uint16), 
        ('fast_init_network_enables_2', ctypes.c_uint16), 
        ('uart', uart_settings), 
        ('uart2', uart_settings), 
        ('text_api', s_text_api_settings), 
        ('neoMostGateway', s_neo_most_gateway_settings), 
        ('vnetBits', ctypes.c_uint16), 
    ]

# Extra names go here:
SFireSettings = s_fire_settings
# End of extra names

