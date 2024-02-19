# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class rad_moon_duo_converter_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('linkMode0', ctypes.c_uint8),
        ('linkMode1', ctypes.c_uint8),
        ('converter1Mode', ctypes.c_uint8),
        ('ipAddress', ctypes.c_uint32),
        ('ipMask', ctypes.c_uint32),
        ('ipGateway', ctypes.c_uint32),
    ]


_RadMoonDuoConverterSettings = rad_moon_duo_converter_settings
RadMoonDuoConverterSettings = rad_moon_duo_converter_settings

