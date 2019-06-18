# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

try: # 1
    from can_settings import can_settings
except:
    from ics.structures.can_settings import can_settings

class svcan3_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('can1', can_settings), 
        ('can2', can_settings), 
        ('network_enables', ctypes.c_uint16), 
        ('network_enabled_on_boot', ctypes.c_uint16), 
        ('iso15765_separation_time_offset', ctypes.c_uint16), 
        ('perf_en', ctypes.c_uint16), 
        ('misc_io_initial_ddr', ctypes.c_uint16), 
        ('misc_io_initial_latch', ctypes.c_uint16), 
        ('misc_io_report_period', ctypes.c_uint16), 
        ('misc_io_on_report_events', ctypes.c_uint16), 
    ]

# Extra names go here:
SVCAN3Settings = svcan3_settings
# End of extra names

