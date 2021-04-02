# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

# _U7
class _U7(ctypes.Union):
    _pack_ = 2
    _fields_ = [
        ('id_29_bit_enable', ctypes.c_uint16, 1), # [Bitfield] 
        ('fc_id_29_bit_enable', ctypes.c_uint16, 1), # [Bitfield] 
        ('ext_address_enable', ctypes.c_uint16, 1), # [Bitfield] 
        ('fc_ext_address_enable', ctypes.c_uint16, 1), # [Bitfield] 
        ('overrideSTmin', ctypes.c_uint16, 1), # [Bitfield] 
        ('overrideBlockSize', ctypes.c_uint16, 1), # [Bitfield] 
        ('paddingEnable', ctypes.c_uint16, 1), # [Bitfield] 
        ('iscanFD', ctypes.c_uint16, 1), # [Bitfield] 
        ('isBRSEnabled', ctypes.c_uint16, 1), # [Bitfield] 
        ('flags', ctypes.c_uint16), 
    ]

# Extra names go here:
# End of extra names

class iso15765_2015_tx_message(ctypes.Structure):
    _pack_ = 2
    _anonymous_ = ("_U7",)
    _fields_ = [
        ('vs_netid', ctypes.c_uint16), 
        ('padding', ctypes.c_uint8), 
        ('tx_index', ctypes.c_uint8), 
        ('id', ctypes.c_uint32), 
        ('fc_id', ctypes.c_uint32), 
        ('fc_id_mask', ctypes.c_uint32), 
        ('stMin', ctypes.c_uint8), 
        ('blockSize', ctypes.c_uint8), 
        ('flowControlExtendedAddress', ctypes.c_uint8), 
        ('extendedAddress', ctypes.c_uint8), 
        ('fs_timeout', ctypes.c_uint16), 
        ('fs_wait', ctypes.c_uint16), 
        ('data', ctypes.POINTER(ctypes.c_uint8 )), 
        ('num_bytes', ctypes.c_uint32), 
        ('tx_dl', ctypes.c_uint8), 
        ('_U7', _U7), 
    ]

# Extra names go here:
ISO15765_2015_TxMessage = iso15765_2015_tx_message
# End of extra names

