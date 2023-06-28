# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class ethernet10_t1_s_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('max_burst_count', ctypes.c_uint8),
        ('burst_timer', ctypes.c_uint8),
        ('max_num_nodes', ctypes.c_uint8),
        ('local_id', ctypes.c_uint8),
        ('to_timer', ctypes.c_uint8),
        ('flags', ctypes.c_uint8),
        ('local_id_alternate', ctypes.c_uint8),
        ('rsvd', ctypes.c_uint8 * 5),
    ]


ETHERNET10T1S_SETTINGS_t = ethernet10_t1_s_settings
ETHERNET10T1S_SETTINGS = ethernet10_t1_s_settings

