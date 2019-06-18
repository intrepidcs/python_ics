# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

try: # 8
    from op_eth_general_settings import op_eth_general_settings
    from op_eth_settings import op_eth_settings
    from can_settings import can_settings
    from canfd_settings import canfd_settings
    from lin_settings import lin_settings
    from iso9141_keyword2000_settings import iso9141_keyword2000_settings
    from s_text_api_settings import s_text_api_settings
    from timesync_icshardware_settings import timesync_icshardware_settings
except:
    from ics.structures.op_eth_general_settings import op_eth_general_settings
    from ics.structures.op_eth_settings import op_eth_settings
    from ics.structures.can_settings import can_settings
    from ics.structures.canfd_settings import canfd_settings
    from ics.structures.lin_settings import lin_settings
    from ics.structures.iso9141_keyword2000_settings import iso9141_keyword2000_settings
    from ics.structures.s_text_api_settings import s_text_api_settings
    from ics.structures.timesync_icshardware_settings import timesync_icshardware_settings

class srad_star2_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('perf_en', ctypes.c_uint16), 
        ('opEthGen', op_eth_general_settings), 
        ('opEth1', op_eth_settings), 
        ('opEth2', op_eth_settings), 
        ('can1', can_settings), 
        ('canfd1', canfd_settings), 
        ('can2', can_settings), 
        ('canfd2', canfd_settings), 
        ('network_enables', ctypes.c_uint16), 
        ('network_enables_2', ctypes.c_uint16), 
        ('lin1', lin_settings), 
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
        ('iso9141_kwp_settings_1', iso9141_keyword2000_settings), 
        ('iso_parity_1', ctypes.c_uint16), 
        ('iso_msg_termination_1', ctypes.c_uint16), 
        ('idle_wakeup_network_enables_1', ctypes.c_uint16), 
        ('idle_wakeup_network_enables_2', ctypes.c_uint16), 
        ('network_enables_3', ctypes.c_uint16), 
        ('idle_wakeup_network_enables_3', ctypes.c_uint16), 
        ('can_switch_mode', ctypes.c_uint16), 
        ('text_api', s_text_api_settings), 
        ('pc_com_mode', ctypes.c_uint16), 
        ('timeSyncSettings', timesync_icshardware_settings), 
        ('hwComLatencyTestEn', ctypes.c_uint16), 
    ]

# Extra names go here:
SRADStar2Settings = srad_star2_settings
# End of extra names

