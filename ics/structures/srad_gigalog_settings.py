# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

try: # 13
    from can_settings import can_settings
    from canfd_settings import canfd_settings
    from iso9141_keyword2000_settings import iso9141_keyword2000_settings
    from s_text_api_settings import s_text_api_settings
    from disk_settings import disk_settings
    from timesync_icshardware_settings import timesync_icshardware_settings
    from ethernet_settings2 import ethernet_settings2
    from serdescam_settings import serdescam_settings
    from ethernet10_g_settings import ethernet10_g_settings
    from lin_settings import lin_settings
    from serdespoc_settings import serdespoc_settings
    from logger_settings import logger_settings
    from rad_reporting_settings import rad_reporting_settings
except:
    from ics.structures.can_settings import can_settings
    from ics.structures.canfd_settings import canfd_settings
    from ics.structures.iso9141_keyword2000_settings import iso9141_keyword2000_settings
    from ics.structures.s_text_api_settings import s_text_api_settings
    from ics.structures.disk_settings import disk_settings
    from ics.structures.timesync_icshardware_settings import timesync_icshardware_settings
    from ics.structures.ethernet_settings2 import ethernet_settings2
    from ics.structures.serdescam_settings import serdescam_settings
    from ics.structures.ethernet10_g_settings import ethernet10_g_settings
    from ics.structures.lin_settings import lin_settings
    from ics.structures.serdespoc_settings import serdespoc_settings
    from ics.structures.logger_settings import logger_settings
    from ics.structures.rad_reporting_settings import rad_reporting_settings

# flags
class flags(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('hwComLatencyTestEn', ctypes.c_uint16, 1), # [Bitfield] 
        ('disableUsbCheckOnBoot', ctypes.c_uint16, 1), # [Bitfield] 
        ('reserved', ctypes.c_uint16, 14), # [Bitfield] 
    ]

# Extra names go here:
# End of extra names

class srad_gigalog_settings(ctypes.Structure):
    _pack_ = 2
    _anonymous_ = ("flags",)
    _fields_ = [
        ('ecu_id', ctypes.c_uint32), 
        ('perf_en', ctypes.c_uint16), 
        ('can1', can_settings), 
        ('canfd1', canfd_settings), 
        ('can2', can_settings), 
        ('canfd2', canfd_settings), 
        ('can3', can_settings), 
        ('canfd3', canfd_settings), 
        ('can4', can_settings), 
        ('canfd4', canfd_settings), 
        ('can5', can_settings), 
        ('canfd5', canfd_settings), 
        ('can6', can_settings), 
        ('canfd6', canfd_settings), 
        ('can7', can_settings), 
        ('canfd7', canfd_settings), 
        ('can8', can_settings), 
        ('canfd8', canfd_settings), 
        ('network_enables', ctypes.c_uint16), 
        ('network_enables_2', ctypes.c_uint16), 
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
        ('text_api', s_text_api_settings), 
        ('termination_enables', ctypes.c_uint64), 
        ('rsvd1', ctypes.c_uint8 * 8), 
        ('rsvd2', ctypes.c_uint8 * 8), 
        ('disk', disk_settings), 
        ('timeSyncSettings', timesync_icshardware_settings), 
        ('flags', flags), 
        ('ethernet', ethernet_settings2), 
        ('serdescam1', serdescam_settings), 
        ('ethernet10g', ethernet10_g_settings), 
        ('lin1', lin_settings), 
        ('serdespoc', serdespoc_settings), 
        ('logger', logger_settings), 
        ('serdescam2', serdescam_settings), 
        ('serdescam3', serdescam_settings), 
        ('serdescam4', serdescam_settings), 
        ('ethernet2', ethernet_settings2), 
        ('network_enables_4', ctypes.c_uint16), 
        ('reporting', rad_reporting_settings), 
    ]

# Extra names go here:
SRADGigalogSettings = srad_gigalog_settings
# End of extra names

