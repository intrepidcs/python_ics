# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.ethernet10_g_settings import *


class flags(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('enableLatencyTest', ctypes.c_uint16, 1),
        ('reserved', ctypes.c_uint16, 15),
    ]



class srad_moon3_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('perf_en', ctypes.c_uint16),
        ('autoEth10g', ETHERNET10G_SETTINGS),
        ('eth10g', ETHERNET10G_SETTINGS),
        ('network_enables', ctypes.c_uint16),
        ('network_enables_2', ctypes.c_uint16),
        ('network_enabled_on_boot', ctypes.c_uint16),
        ('network_enables_3', ctypes.c_uint16),
        ('flags', flags),
        ('network_enables_5', ctypes.c_uint64),
    ]


_SRADMoon3Settings = srad_moon3_settings
SRADMoon3Settings = srad_moon3_settings

