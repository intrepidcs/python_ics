# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

try: # 3
    from can_settings import can_settings
    from lin_settings import lin_settings
    from iso9141_keyword2000_settings import iso9141_keyword2000_settings
except:
    from ics.structures.can_settings import can_settings
    from ics.structures.lin_settings import lin_settings
    from ics.structures.iso9141_keyword2000_settings import iso9141_keyword2000_settings

class svcanrf_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('can1', can_settings), 
        ('can2', can_settings), 
        ('can3', can_settings), 
        ('can4', can_settings), 
        ('lin1', lin_settings), 
        ('lin2', lin_settings), 
        ('network_enables', ctypes.c_uint16), 
        ('network_enabled_on_boot', ctypes.c_uint16), 
        ('pwr_man_timeout', ctypes.c_uint32), 
        ('pwr_man_enable', ctypes.c_uint16), 
        ('misc_io_initial_ddr', ctypes.c_uint16), 
        ('misc_io_initial_latch', ctypes.c_uint16), 
        ('misc_io_analog_enable', ctypes.c_uint16), 
        ('misc_io_report_period', ctypes.c_uint16), 
        ('misc_io_on_report_events', ctypes.c_uint16), 
        ('iso15765_separation_time_offset', ctypes.c_uint16), 
        ('iso9141_kwp_enable_reserved', ctypes.c_uint16), 
        ('iso9141_kwp_settings', iso9141_keyword2000_settings), 
        ('perf_en', ctypes.c_uint16), 
        ('iso_parity', ctypes.c_uint16), 
        ('iso_msg_termination', ctypes.c_uint16), 
        ('iso_tester_pullup_enable', ctypes.c_uint16), 
        ('network_enables_2', ctypes.c_uint16), 
        ('iso9141_kwp_settings_2', iso9141_keyword2000_settings), 
        ('iso_parity_2', ctypes.c_uint16), 
        ('iso_msg_termination_2', ctypes.c_uint16), 
        ('idle_wakeup_network_enables_1', ctypes.c_uint16), 
        ('idle_wakeup_network_enables_2', ctypes.c_uint16), 
        ('disableFwLEDs', ctypes.c_uint16, 1), # [Bitfield] 
        ('reservedZero', ctypes.c_uint16, 15), # [Bitfield] 
    ]

# Extra names go here:
SVCANRFSettings = svcanrf_settings
# End of extra names

