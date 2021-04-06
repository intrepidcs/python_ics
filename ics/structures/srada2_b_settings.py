# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

try: # 8
    from can_settings import can_settings
    from canfd_settings import canfd_settings
    from lin_settings import lin_settings
    from iso9141_keyword2000_settings import iso9141_keyword2000_settings
    from timesync_icshardware_settings import timesync_icshardware_settings
    from rad_reporting_settings import rad_reporting_settings
    from disk_settings import disk_settings
    from logger_settings import logger_settings
except:
    from ics.structures.can_settings import can_settings
    from ics.structures.canfd_settings import canfd_settings
    from ics.structures.lin_settings import lin_settings
    from ics.structures.iso9141_keyword2000_settings import iso9141_keyword2000_settings
    from ics.structures.timesync_icshardware_settings import timesync_icshardware_settings
    from ics.structures.rad_reporting_settings import rad_reporting_settings
    from ics.structures.disk_settings import disk_settings
    from ics.structures.logger_settings import logger_settings

# flags
class flags(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('hwComLatencyTestEn', ctypes.c_uint16, 1), # [Bitfield] 
    ]

# Extra names go here:
# End of extra names

class srada2_b_settings(ctypes.Structure):
    _pack_ = 2
    _anonymous_ = ("flags",)
    _fields_ = [
        ('perf_en', ctypes.c_uint16), 
        ('flags', flags), 
        ('network_enabled_on_boot', ctypes.c_uint16), 
        ('can1', can_settings), 
        ('canfd1', canfd_settings), 
        ('can2', can_settings), 
        ('canfd2', canfd_settings), 
        ('lin1', lin_settings), 
        ('iso9141_kwp_settings_1', iso9141_keyword2000_settings), 
        ('iso_parity_1', ctypes.c_uint16), 
        ('iso_msg_termination_1', ctypes.c_uint16), 
        ('network_enables', ctypes.c_uint64), 
        ('termination_enables', ctypes.c_uint64), 
        ('timeSyncSettings', timesync_icshardware_settings), 
        ('reporting', rad_reporting_settings), 
        ('disk', disk_settings), 
        ('logger', logger_settings), 
        ('iso15765_separation_time_offset', ctypes.c_int16), 
    ]

# Extra names go here:
SRADA2BSettings = srada2_b_settings
# End of extra names

