# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

try: # 10
    from can_settings import can_settings
    from canfd_settings import canfd_settings
    from swcan_settings import swcan_settings
    from lin_settings import lin_settings
    from iso9141_keyword2000_settings import iso9141_keyword2000_settings
    from s_text_api_settings import s_text_api_settings
    from ethernet_settings import ethernet_settings
    from timesync_icshardware_settings import timesync_icshardware_settings
    from disk_settings import disk_settings
    from ethernet_settings2 import ethernet_settings2
except:
    from ics.structures.can_settings import can_settings
    from ics.structures.canfd_settings import canfd_settings
    from ics.structures.swcan_settings import swcan_settings
    from ics.structures.lin_settings import lin_settings
    from ics.structures.iso9141_keyword2000_settings import iso9141_keyword2000_settings
    from ics.structures.s_text_api_settings import s_text_api_settings
    from ics.structures.ethernet_settings import ethernet_settings
    from ics.structures.timesync_icshardware_settings import timesync_icshardware_settings
    from ics.structures.disk_settings import disk_settings
    from ics.structures.ethernet_settings2 import ethernet_settings2

# flags
class flags(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('disableUsbCheckOnBoot', ctypes.c_uint32, 1), # [Bitfield] 
        ('enableLatencyTest', ctypes.c_uint32, 1), # [Bitfield] 
        ('busMessagesToAndroid', ctypes.c_uint32, 1), # [Bitfield] 
        ('enablePcEthernetComm', ctypes.c_uint32, 1), # [Bitfield] 
        ('enableDefaultLogger', ctypes.c_uint32, 1), # [Bitfield] 
        ('enableDefaultUpload', ctypes.c_uint32, 1), # [Bitfield] 
        ('reserved', ctypes.c_uint32, 26), # [Bitfield] 
    ]

# Extra names go here:
# End of extra names

class s_cyan_settings(ctypes.Structure):
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
        ('can5', can_settings), 
        ('canfd5', canfd_settings), 
        ('can6', can_settings), 
        ('canfd6', canfd_settings), 
        ('can7', can_settings), 
        ('canfd7', canfd_settings), 
        ('can8', can_settings), 
        ('canfd8', canfd_settings), 
        ('swcan1', swcan_settings), 
        ('network_enables', ctypes.c_uint16), 
        ('swcan2', swcan_settings), 
        ('network_enables_2', ctypes.c_uint16), 
        ('lsftcan1', can_settings), 
        ('lsftcan2', can_settings), 
        ('lin1', lin_settings), 
        ('misc_io_initial_ddr', ctypes.c_uint16), 
        ('lin2', lin_settings), 
        ('misc_io_initial_latch', ctypes.c_uint16), 
        ('lin3', lin_settings), 
        ('misc_io_report_period', ctypes.c_uint16), 
        ('lin4', lin_settings), 
        ('misc_io_on_report_events', ctypes.c_uint16), 
        ('lin5', lin_settings), 
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
        ('iso9141_kwp_settings_2', iso9141_keyword2000_settings), 
        ('iso_parity_2', ctypes.c_uint16), 
        ('iso9141_kwp_settings_3', iso9141_keyword2000_settings), 
        ('iso_parity_3', ctypes.c_uint16), 
        ('iso9141_kwp_settings_4', iso9141_keyword2000_settings), 
        ('iso_parity_4', ctypes.c_uint16), 
        ('iso_msg_termination_1', ctypes.c_uint16), 
        ('iso_msg_termination_2', ctypes.c_uint16), 
        ('iso_msg_termination_3', ctypes.c_uint16), 
        ('iso_msg_termination_4', ctypes.c_uint16), 
        ('idle_wakeup_network_enables_1', ctypes.c_uint16), 
        ('idle_wakeup_network_enables_2', ctypes.c_uint16), 
        ('network_enables_3', ctypes.c_uint16), 
        ('idle_wakeup_network_enables_3', ctypes.c_uint16), 
        ('can_switch_mode', ctypes.c_uint16), 
        ('text_api', s_text_api_settings), 
        ('termination_enables', ctypes.c_uint64), 
        ('lin6', lin_settings), 
        ('ethernet', ethernet_settings), 
        ('slaveVnetA', ctypes.c_uint16), 
        ('slaveVnetB', ctypes.c_uint16), 
        ('flags', flags), 
        ('digitalIoThresholdTicks', ctypes.c_uint16), 
        ('digitalIoThresholdEnable', ctypes.c_uint16), 
        ('timeSync', timesync_icshardware_settings), 
        ('disk', disk_settings), 
        ('ethernet2', ethernet_settings2), # supercedes ethernet settings
    ]

# Extra names go here:
SCyanSettings = s_cyan_settings
# End of extra names

