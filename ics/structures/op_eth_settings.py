# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class nameless46655(ctypes.Structure):
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



class nameless45525(ctypes.Union):
    _pack_ = 2
    _anonymous_  = ('nameless46655',)
    _fields_ = [
        ('nameless46655', nameless46655),
        ('reserved0', ctypes.c_ubyte * 14),
    ]



class op_eth_settings(ctypes.Structure):
    _pack_ = 2
    _anonymous_  = ('nameless45525',)
    _fields_ = [
        ('ucConfigMode', ctypes.c_uint8),
        ('preemption_en', ctypes.c_ubyte),
        ('nameless45525', nameless45525),
    ]


OP_ETH_SETTINGS_t = op_eth_settings
OP_ETH_SETTINGS = op_eth_settings

