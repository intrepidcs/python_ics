# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

class op_eth_settings_t(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('ucConfigMode', ctypes.c_uint8), 
        ('preemption_en', ctypes.c_ubyte), 
        ('reserved0', ctypes.c_ubyte * 14), 
        ('mac_addr1', ctypes.c_ubyte * 6), # Original Addr for spoofing
        ('mac_addr2', ctypes.c_ubyte * 6), # Target Addr for spoofing
        ('mac_spoofing_en', ctypes.c_ushort, 1), # [Bitfield] 
        ('mac_spoofing_isDstOrSrc', ctypes.c_ushort, 1), # [Bitfield] 
        ('reserved', ctypes.c_ushort, 14), # [Bitfield] 
    ]

# Extra names go here:
OP_ETH_SETTINGS = op_eth_settings_t
# End of extra names

