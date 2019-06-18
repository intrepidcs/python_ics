# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

try: # 5
    from can_settings import can_settings
    from canfd_settings import canfd_settings
    from ethernet_settings import ethernet_settings
    from timesync_icshardware_settings import timesync_icshardware_settings
    from s_text_api_settings import s_text_api_settings
except:
    from ics.structures.can_settings import can_settings
    from ics.structures.canfd_settings import canfd_settings
    from ics.structures.ethernet_settings import ethernet_settings
    from ics.structures.timesync_icshardware_settings import timesync_icshardware_settings
    from ics.structures.s_text_api_settings import s_text_api_settings

# flags
class flags(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('disableUsbCheckOnBoot', ctypes.c_uint32, 1), # [Bitfield] 
        ('enableLatencyTest', ctypes.c_uint32, 1), # [Bitfield] 
        ('busMessagesToAndroid', ctypes.c_uint32, 1), # [Bitfield] 
        ('enablePcEthernetComm', ctypes.c_uint32, 1), # [Bitfield] 
        ('reserved', ctypes.c_uint32, 28), # [Bitfield] 
    ]

# Extra names go here:
# End of extra names

# network_enables
class network_enables(ctypes.Union):
    _pack_ = 2
    _fields_ = [
        ('word', ctypes.c_uint64), 
        ('network_enables', ctypes.c_uint16), 
        ('network_enables_2', ctypes.c_uint16), 
        ('network_enables_3', ctypes.c_uint16), 
    ]

# Extra names go here:
# End of extra names

class s_flex_vnetz_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('perf_en', ctypes.c_uint16), 
        ('network_enabled_on_boot', ctypes.c_uint16), 
        ('misc_io_on_report_events', ctypes.c_uint16), 
        ('pwr_man_enable', ctypes.c_uint16), 
        ('iso15765_separation_time_offset', ctypes.c_int16), 
        ('flex_mode', ctypes.c_uint16), 
        ('flex_termination', ctypes.c_uint16), 
        ('slaveVnetA', ctypes.c_uint16), 
        ('termination_enables', ctypes.c_uint64), 
        ('pwr_man_timeout', ctypes.c_uint32), 
        ('slaveVnetB', ctypes.c_uint16), 
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
        ('ethernet', ethernet_settings), 
        ('timeSync', timesync_icshardware_settings), 
        ('text_api', s_text_api_settings), 
        ('flags', flags), 
        ('network_enables', network_enables), 
    ]

# Extra names go here:
SFlexVnetzSettings = s_flex_vnetz_settings
# End of extra names

