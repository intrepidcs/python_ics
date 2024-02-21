# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class st_api_firmware_info(ctypes.Structure):
    _pack_ = 1
    _fields_ = [
        ('iType', ctypes.c_int32),
        ('iMainFirmDateDay', ctypes.c_int32),
        ('iMainFirmDateMonth', ctypes.c_int32),
        ('iMainFirmDateYear', ctypes.c_int32),
        ('iMainFirmDateHour', ctypes.c_int32),
        ('iMainFirmDateMin', ctypes.c_int32),
        ('iMainFirmDateSecond', ctypes.c_int32),
        ('iMainFirmChkSum', ctypes.c_int32),
        ('iAppMajor', ctypes.c_uint8),
        ('iAppMinor', ctypes.c_uint8),
        ('iManufactureDay', ctypes.c_uint8),
        ('iManufactureMonth', ctypes.c_uint8),
        ('iManufactureYear', ctypes.c_uint16),
        ('iBoardRevMajor', ctypes.c_uint8),
        ('iBoardRevMinor', ctypes.c_uint8),
        ('iBootLoaderVersionMajor', ctypes.c_uint8),
        ('iBootLoaderVersionMinor', ctypes.c_uint8),
        ('iMainVnetHWrevMajor', ctypes.c_uint8),
        ('iMainVnetHWrevMinor', ctypes.c_uint8),
        ('iMainVnetSRAMSize', ctypes.c_uint8),
        ('iPhySiliconRev', ctypes.c_uint8),
    ]


_stAPIFirmwareInfo = st_api_firmware_info
stAPIFirmwareInfo = st_api_firmware_info

