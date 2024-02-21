# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.s_pluto_ptp_params_s import *


class s_pluto_custom_params_s(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('mode', ctypes.c_uint8 * 5),
        ('speed', ctypes.c_uint8 * 5),
        ('enablePhy', ctypes.c_uint8 * 5),
        ('ae1Select', ctypes.c_uint8),
        ('usbSelect', ctypes.c_uint8),
        ('pad', ctypes.c_uint8),
        ('ptpParams', PlutoPtpParams_t),
    ]


SPluto_CustomParams_s = s_pluto_custom_params_s
SPluto_CustomParams = s_pluto_custom_params_s

