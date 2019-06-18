# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

try: # 2
    from can_settings import can_settings
    from swcan_settings import swcan_settings
except:
    from ics.structures.can_settings import can_settings
    from ics.structures.swcan_settings import swcan_settings

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

class s_vivid_can_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('ecu_id', ctypes.c_uint32), 
        ('can1', can_settings), # 12 bytes
        ('swcan1', swcan_settings), # 14 bytes
        ('lsftcan1', can_settings), # 12 bytes
        ('network_enables', ctypes.c_uint16), 
        ('network_enabled_on_boot', ctypes.c_uint16), 
        ('iso15765_separation_time_offset', ctypes.c_uint16), 
        ('perf_en', ctypes.c_uint16), 
        ('pwr_man_timeout', ctypes.c_uint32), 
        ('pwr_man_enable', ctypes.c_uint16), 
        ('can_switch_mode', ctypes.c_uint16), 
        ('termination_enables', ctypes.c_uint16), 
        ('flags', flags), 
    ]

# Extra names go here:
SVividCANSettings = s_vivid_can_settings
# End of extra names

