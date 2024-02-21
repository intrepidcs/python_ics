# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.rad_moon_duo_converter_settings import *


class flags(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('disableUsbCheckOnBoot', ctypes.c_uint32, 1),
        ('enableLatencyTest', ctypes.c_uint32, 1),
        ('reserved', ctypes.c_uint32, 30),
    ]



class s_rad_moon_duo_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('perf_en', ctypes.c_uint16),
        ('network_enabled_on_boot', ctypes.c_uint16),
        ('pwr_man_timeout', ctypes.c_uint32),
        ('pwr_man_enable', ctypes.c_uint16),
        ('converter', RadMoonDuoConverterSettings),
        ('network_enables', ctypes.c_uint64),
        ('flags', flags),
    ]


RadMoonDuoSettings = s_rad_moon_duo_settings
SRadMoonDuoSettings = s_rad_moon_duo_settings

