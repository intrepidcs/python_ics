# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class Nameless23998(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('mac_addr1', ctypes.c_ubyte * 6),
        ('mac_addr2', ctypes.c_ubyte * 6),
        ('mac_spoofing_en', ctypes.c_ushort, 1),
        ('mac_spoofing_isDstOrSrc', ctypes.c_ushort, 1),
        ('link_spd', ctypes.c_ushort, 2),
        ('q2112_phy_mode', ctypes.c_ushort, 1),
        ('reserved', ctypes.c_ushort, 11),
    ]



class Nameless14996(ctypes.Union):
    _pack_ = 2
    _anonymous_  = ('Nameless23998',)
    _fields_ = [
        ('Nameless23998', Nameless23998),
        ('reserved0', ctypes.c_ubyte * 14),
    ]



class op_eth_settings(ctypes.Structure):
    _pack_ = 2
    _anonymous_  = ('Nameless14996',)
    _fields_ = [
        ('ucConfigMode', ctypes.c_uint8),
        ('preemption_en', ctypes.c_ubyte),
        ('Nameless14996', Nameless14996),
    ]


OP_ETH_SETTINGS_t = op_eth_settings
OP_ETH_SETTINGS = op_eth_settings

