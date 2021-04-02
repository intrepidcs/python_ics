# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

try: # 1
    from rad_moon_duo_converter_settings import rad_moon_duo_converter_settings
except:
    from ics.structures.rad_moon_duo_converter_settings import rad_moon_duo_converter_settings

# flags
class flags(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('disableUsbCheckOnBoot', ctypes.c_uint32, 1), # [Bitfield] 
        ('enableLatencyTest', ctypes.c_uint32, 1), # [Bitfield] 
        ('reserved', ctypes.c_uint32, 30), # [Bitfield] 
    ]

# Extra names go here:
# End of extra names

class s_rad_moon_duo_settings(ctypes.Structure):
    _pack_ = 2
    _anonymous_ = ("flags",)
    _fields_ = [
        ('perf_en', ctypes.c_uint16), 
        ('network_enabled_on_boot', ctypes.c_uint16), 
        ('pwr_man_timeout', ctypes.c_uint32), 
        ('pwr_man_enable', ctypes.c_uint16), 
        ('converter', rad_moon_duo_converter_settings), 
        ('network_enables', ctypes.c_uint64), 
        ('flags', flags), 
    ]

# Extra names go here:
RadMoonDuoSettings = s_rad_moon_duo_settings
SRadMoonDuoSettings = s_rad_moon_duo_settings
# End of extra names

