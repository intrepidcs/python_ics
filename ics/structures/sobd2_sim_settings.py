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
        ('enableLatencyTest', ctypes.c_uint32, 1), # [Bitfield] 
        ('reserved', ctypes.c_uint32, 30), # [Bitfield] 
    ]

# Extra names go here:
# End of extra names

class sobd2_sim_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('can1', can_settings), 
        ('can2', can_settings), 
        ('canfd1', canfd_settings), 
        ('canfd2', canfd_settings), 
        ('network_enables', ctypes.c_uint64), 
        ('network_enabled_on_boot', ctypes.c_uint16), 
        ('iso15765_separation_time_offset', ctypes.c_int16), 
        ('perf_en', ctypes.c_uint16), 
        ('misc_io_initial_ddr', ctypes.c_uint16), 
        ('misc_io_initial_latch', ctypes.c_uint16), 
        ('misc_io_report_period', ctypes.c_uint16), 
        ('misc_io_on_report_events', ctypes.c_uint16), 
        ('misc_io_analog_enable', ctypes.c_uint16), 
        ('ain_sample_period', ctypes.c_uint16), 
        ('ain_threshold', ctypes.c_uint16), 
        ('flags', flags), 
        ('text_api', s_text_api_settings), 
    ]

# Extra names go here:
SOBD2SimSettings = sobd2_sim_settings
# End of extra names

