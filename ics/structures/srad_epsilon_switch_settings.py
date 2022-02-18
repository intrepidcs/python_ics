# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class srad_epsilon_switch_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('phyMode', ctypes.c_uint8 * 18),
        ('enablePhy', ctypes.c_uint8 * 18),
        ('speed', ctypes.c_uint8 * 18),
        ('legacy', ctypes.c_uint8 * 18),
        ('spoofedMac', ctypes.c_uint8 * 6),
        ('spoofMacFlag', ctypes.c_uint8),
        ('pad', ctypes.c_uint8),
    ]


_SRADEpsilonSwitchSettings = srad_epsilon_switch_settings
SRADEpsilonSwitchSettings = srad_epsilon_switch_settings

