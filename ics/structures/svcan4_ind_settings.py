# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

try: # 5
    from can_settings import can_settings
    from canfd_settings import canfd_settings
    from ethernet_settings import ethernet_settings
    from lin_settings import lin_settings
    from iso9141_keyword2000_settings import iso9141_keyword2000_settings
except:
    from ics.structures.can_settings import can_settings
    from ics.structures.canfd_settings import canfd_settings
    from ics.structures.ethernet_settings import ethernet_settings
    from ics.structures.lin_settings import lin_settings
    from ics.structures.iso9141_keyword2000_settings import iso9141_keyword2000_settings

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

class svcan4_ind_settings(ctypes.Structure):
    _pack_ = 2
    _anonymous_ = ("network_enables", "flags",)
    _fields_ = [
        ('can1', can_settings), 
        ('canfd1', canfd_settings), 
        ('can2', can_settings), 
        ('canfd2', canfd_settings), 
        ('ethernet', ethernet_settings), 
        ('lin1', lin_settings), 
        ('iso9141_kwp_settings', iso9141_keyword2000_settings), 
        ('iso_parity', ctypes.c_uint16), 
        ('iso_msg_termination', ctypes.c_uint16), 
        ('pwr_man_timeout', ctypes.c_uint32), 
        ('pwr_man_enable', ctypes.c_uint16), 
        ('perf_en', ctypes.c_uint16), 
        ('iso15765_separation_time_offset', ctypes.c_int16), 
        ('network_enabled_on_boot', ctypes.c_uint16), 
        ('network_enables', network_enables), 
        ('termination_enables', ctypes.c_uint64), 
        ('flags', flags), 
    ]

# Extra names go here:
VCAN4IndSettings = svcan4_ind_settings
SVCAN4IndSettings = svcan4_ind_settings
# End of extra names

