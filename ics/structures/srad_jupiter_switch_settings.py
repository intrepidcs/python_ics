# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class srad_jupiter_switch_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('phyMode', ctypes.c_uint8 * 8),
        ('enablePhy', ctypes.c_uint8 * 8),
        ('port7Select', ctypes.c_uint8),
        ('port8Select', ctypes.c_uint8),
        ('port8Speed', ctypes.c_uint8),
        ('port8Legacy', ctypes.c_uint8),
        ('spoofMacFlag', ctypes.c_uint8),
        ('spoofedMac', ctypes.c_uint8 * 6),
        ('pad', ctypes.c_uint8),
    ]


_SRADJupiterSwitchSettings = srad_jupiter_switch_settings
SRADJupiterSwitchSettings = srad_jupiter_switch_settings

