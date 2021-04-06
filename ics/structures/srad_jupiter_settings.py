# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

try: # 8
    from can_settings import can_settings
    from canfd_settings import canfd_settings
    from lin_settings import lin_settings
    from iso9141_keyword2000_settings import iso9141_keyword2000_settings
    from ethernet_settings import ethernet_settings
    from s_text_api_settings import s_text_api_settings
    from srad_jupiter_switch_settings import srad_jupiter_switch_settings
    from ethernet_settings2 import ethernet_settings2
except:
    from ics.structures.can_settings import can_settings
    from ics.structures.canfd_settings import canfd_settings
    from ics.structures.lin_settings import lin_settings
    from ics.structures.iso9141_keyword2000_settings import iso9141_keyword2000_settings
    from ics.structures.ethernet_settings import ethernet_settings
    from ics.structures.s_text_api_settings import s_text_api_settings
    from ics.structures.srad_jupiter_switch_settings import srad_jupiter_switch_settings
    from ics.structures.ethernet_settings2 import ethernet_settings2

# flags
class flags(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('disableUsbCheckOnBoot', ctypes.c_uint32, 1), # [Bitfield] 
        ('enableLatencyTest', ctypes.c_uint32, 1), # [Bitfield] 
        ('enablePcEthernetComm', ctypes.c_uint32, 1), # [Bitfield] 
        ('reserved', ctypes.c_uint32, 29), # [Bitfield] 
    ]

# Extra names go here:
# End of extra names

class srad_jupiter_settings(ctypes.Structure):
    _pack_ = 2
    _anonymous_ = ("flags",)
    _fields_ = [
        ('perf_en', ctypes.c_uint16), 
        ('can1', can_settings), 
        ('canfd1', canfd_settings), 
        ('can2', can_settings), 
        ('canfd2', canfd_settings), 
        ('lin1', lin_settings), 
        ('network_enables', ctypes.c_uint16), 
        ('network_enables_2', ctypes.c_uint16), 
        ('network_enables_3', ctypes.c_uint16), 
        ('termination_enables', ctypes.c_uint64), 
        ('misc_io_analog_enable', ctypes.c_uint16), 
        ('pwr_man_timeout', ctypes.c_uint32), 
        ('pwr_man_enable', ctypes.c_uint16), 
        ('network_enabled_on_boot', ctypes.c_uint16), 
        ('iso15765_separation_time_offset', ctypes.c_int16), 
        ('iso9141_kwp_enable_reserved', ctypes.c_uint16), 
        ('iso_tester_pullup_enable', ctypes.c_uint16), 
        ('iso_parity', ctypes.c_uint16), 
        ('iso_msg_termination', ctypes.c_uint16), 
        ('iso9141_kwp_settings', iso9141_keyword2000_settings), 
        ('ethernet', ethernet_settings), 
        ('text_api', s_text_api_settings), 
        ('flags', flags), 
        ('switchSettings', srad_jupiter_switch_settings), 
        ('ethernet2', ethernet_settings2), 
    ]

# Extra names go here:
SRADJupiterSettings = srad_jupiter_settings
# End of extra names

