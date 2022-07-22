# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class flags(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('bTapEnSwitch', ctypes.c_uint32, 1),
        ('bTapEnPtp', ctypes.c_uint32, 1),
        ('bEnReportLinkQuality', ctypes.c_uint32, 1),
        ('bEnTapTxReceipts', ctypes.c_uint32, 1),
        ('reserved', ctypes.c_uint32, 28),
    ]



class Nameless19471(ctypes.Union):
    _pack_ = 2
    _fields_ = [
        ('flags', flags),
        ('uFlags', ctypes.c_uint32),
    ]



class op_eth_general_settings(ctypes.Structure):
    _pack_ = 2
    _anonymous_  = ('Nameless19471',)
    _fields_ = [
        ('ucInterfaceType', ctypes.c_uint8),
        ('reserved0', ctypes.c_uint8 * 3),
        ('tapPair0', ctypes.c_uint16),
        ('tapPair1', ctypes.c_uint16),
        ('tapPair2', ctypes.c_uint16),
        ('tapPair3', ctypes.c_uint16),
        ('tapPair4', ctypes.c_uint16),
        ('tapPair5', ctypes.c_uint16),
        ('Nameless19471', Nameless19471),
    ]


OP_ETH_GENERAL_SETTINGS_t = op_eth_general_settings
OP_ETH_GENERAL_SETTINGS = op_eth_general_settings

