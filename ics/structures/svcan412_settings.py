# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

try: # 3
    from can_settings import can_settings
    from canfd_settings import canfd_settings
    from s_text_api_settings import s_text_api_settings
except:
    from ics.structures.can_settings import can_settings
    from ics.structures.canfd_settings import canfd_settings
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

class svcan412_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('perf_en', ctypes.c_uint16), 
        ('can1', can_settings), 
        ('canfd1', canfd_settings), 
        ('can2', can_settings), 
        ('canfd2', canfd_settings), 
        ('network_enables', ctypes.c_uint64), 
        ('termination_enables', ctypes.c_uint64), 
        ('pwr_man_timeout', ctypes.c_uint32), 
        ('pwr_man_enable', ctypes.c_uint16), 
        ('network_enabled_on_boot', ctypes.c_uint16), 
        ('iso15765_separation_time_offset', ctypes.c_int16), 
        ('text_api', s_text_api_settings), 
        ('flags', flags), 
    ]

# Extra names go here:
VCAN412Settings = svcan412_settings
SVCAN412Settings = svcan412_settings
# End of extra names

