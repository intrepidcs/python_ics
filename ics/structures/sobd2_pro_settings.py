# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

try: # 7
    from can_settings import can_settings
    from canfd_settings import canfd_settings
    from swcan_settings import swcan_settings
    from lin_settings import lin_settings
    from ethernet_settings import ethernet_settings
    from iso9141_keyword2000_settings import iso9141_keyword2000_settings
    from s_text_api_settings import s_text_api_settings
except:
    from ics.structures.can_settings import can_settings
    from ics.structures.canfd_settings import canfd_settings
    from ics.structures.swcan_settings import swcan_settings
    from ics.structures.lin_settings import lin_settings
    from ics.structures.ethernet_settings import ethernet_settings
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

class sobd2_pro_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('perf_en', ctypes.c_uint16), 
        ('can1', can_settings), 
        ('canfd1', canfd_settings), 
        ('can2', can_settings), 
        ('canfd2', canfd_settings), 
        ('can3', can_settings), 
        ('canfd3', canfd_settings), 
        ('can4', can_settings), 
        ('canfd4', canfd_settings), 
        ('swcan1', swcan_settings), 
        ('lin1', lin_settings), 
        ('lin2', lin_settings), 
        ('ethernet', ethernet_settings), 
        ('iso9141_kwp_settings_1', iso9141_keyword2000_settings), 
        ('iso_parity_1', ctypes.c_uint16), 
        ('iso_msg_termination_1', ctypes.c_uint16), 
        ('iso9141_kwp_settings_2', iso9141_keyword2000_settings), 
        ('iso_parity_2', ctypes.c_uint16), 
        ('iso_msg_termination_2', ctypes.c_uint16), 
        ('network_enables', ctypes.c_uint64), 
        ('pwr_man_timeout', ctypes.c_uint32), 
        ('pwr_man_enable', ctypes.c_uint16), 
        ('network_enabled_on_boot', ctypes.c_uint16), 
        ('iso15765_separation_time_offset', ctypes.c_int16), 
        ('text_api', s_text_api_settings), 
        ('can_switch_mode', ctypes.c_uint16), 
        ('flags', flags), 
    ]

# Extra names go here:
OBD2ProSettings = sobd2_pro_settings
SOBD2ProSettings = sobd2_pro_settings
# End of extra names

