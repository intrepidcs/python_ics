# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

# _U2
class _U2(ctypes.Union):
    _pack_ = 2
    _fields_ = [
        ('mac_addr1', ctypes.c_ubyte * 6), 
        ('mac_addr2', ctypes.c_ubyte * 6), 
        ('mac_spoofing_en', ctypes.c_ushort, 1), # [Bitfield] 
        ('mac_spoofing_isDstOrSrc', ctypes.c_ushort, 1), # [Bitfield] 
        ('link_spd', ctypes.c_ushort, 2), # [Bitfield] 
        ('q2112_phy_mode', ctypes.c_ushort, 1), # [Bitfield] 
        ('reserved', ctypes.c_ushort, 11), # [Bitfield] 
        ('reserved0', ctypes.c_ubyte * 14), 
    ]

# Extra names go here:
# End of extra names

class op_eth_settings(ctypes.Structure):
    _pack_ = 2
    _anonymous_ = ("_U2",)
    _fields_ = [
        ('ucConfigMode', ctypes.c_uint8), 
        ('preemption_en', ctypes.c_ubyte), 
        ('_U2', _U2), 
    ]

# Extra names go here:
OP_ETH_SETTINGS = op_eth_settings
# End of extra names

