# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

try: # 6
    from can_settings import can_settings
    from canfd_settings import canfd_settings
    from swcan_settings import swcan_settings
    from lin_settings import lin_settings
    from iso9141_keyword2000_settings import iso9141_keyword2000_settings
    from s_text_api_settings import s_text_api_settings
except:
    from ics.structures.can_settings import can_settings
    from ics.structures.canfd_settings import canfd_settings
    from ics.structures.swcan_settings import swcan_settings
    from ics.structures.lin_settings import lin_settings
    from ics.structures.iso9141_keyword2000_settings import iso9141_keyword2000_settings
    from ics.structures.s_text_api_settings import s_text_api_settings

# flags
class flags(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('disableUsbCheckOnBoot', ctypes.c_uint32, 1), # [Bitfield] 
        ('enableLatencyTest', ctypes.c_uint32, 1), # [Bitfield] 
        ('reserved', ctypes.c_uint32, 30), # [Bitfield] 
    ]

# Extra names go here:
# End of extra names

class s_neo_ecu12_settings(ctypes.Structure):
    _pack_ = 2
    _anonymous_ = ("flags",)
    _fields_ = [
        ('ecu_id', ctypes.c_uint32), 
        ('can1', can_settings), 
        ('canfd1', canfd_settings), 
        ('can2', can_settings), 
        ('canfd2', canfd_settings), 
        ('swcan1', swcan_settings), 
        ('swcan2', swcan_settings), 
        ('lsftcan1', can_settings), 
        ('lsftcan2', can_settings), 
        ('lin1', lin_settings), 
        ('network_enables', ctypes.c_uint64), 
        ('network_enabled_on_boot', ctypes.c_uint16), 
        ('termination_enables', ctypes.c_uint64), 
        ('can_switch_mode', ctypes.c_uint16), 
        ('iso_9141_kwp_enable_reserved', ctypes.c_uint16), 
        ('iso9141_kwp_settings', iso9141_keyword2000_settings), 
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
        ('text_api', s_text_api_settings), 
        ('flags', flags), 
    ]

# Extra names go here:
SNeoECU12Settings = s_neo_ecu12_settings
# End of extra names

