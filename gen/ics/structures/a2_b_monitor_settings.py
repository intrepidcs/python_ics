# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class a2_b_monitor_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('tdmMode', ctypes.c_uint8),
        ('upstreamChannelOffset', ctypes.c_uint8),
        ('downstreamChannelOffset', ctypes.c_uint8),
        ('nodeType', ctypes.c_uint8),
        ('flags', ctypes.c_uint8),
        ('reserved', ctypes.c_uint8 * 15),
    ]


A2BMonitorSettings = a2_b_monitor_settings

