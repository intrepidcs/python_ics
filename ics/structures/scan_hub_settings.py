# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

try: # 2
    from can_settings import can_settings
    from canfd_settings import canfd_settings
except:
    from ics.structures.can_settings import can_settings
    from ics.structures.canfd_settings import canfd_settings

class scan_hub_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('can1', can_settings), 
        ('canfd1', canfd_settings), 
        ('network_enables', ctypes.c_uint64), 
        ('termination_enables', ctypes.c_uint64), 
        ('pwr_man_timeout', ctypes.c_uint32), 
        ('pwr_man_enable', ctypes.c_uint16), 
        ('network_enabled_on_boot', ctypes.c_uint16), 
        ('iso15765_separation_time_offset', ctypes.c_int16), 
        ('ecu_id', ctypes.c_uint32), 
    ]

# Extra names go here:
CANHubSettings = scan_hub_settings
SCANHubSettings = scan_hub_settings
# End of extra names

