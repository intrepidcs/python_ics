# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

class st_cm_iso157652_tx_message(ctypes.Structure):
    _pack_ = 2
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
        ('data', ctypes.c_uint8 * 4096), 
        ('num_bytes', ctypes.c_uint32), 
        ('flags', ctypes.c_uint32), 
        ('id_29_bit_enable', ctypes.c_uint32, 1), # [Bitfield] 
        ('fc_id_29_bit_enable', ctypes.c_uint32, 1), # [Bitfield] 
        ('ext_address_enable', ctypes.c_uint32, 1), # [Bitfield] 
        ('fc_ext_address_enable', ctypes.c_uint32, 1), # [Bitfield] 
        ('overrideSTmin', ctypes.c_uint32, 1), # [Bitfield] 
        ('overrideBlockSize', ctypes.c_uint32, 1), # [Bitfield] 
        ('paddingEnable', ctypes.c_uint32, 1), # [Bitfield] 
        ('iscanFD', ctypes.c_uint32, 1), # [Bitfield] 
        ('isBRSEnabled', ctypes.c_uint32, 1), # [Bitfield] 
        ('tx_dl', ctypes.c_uint32, 8), # [Bitfield] 
    ]

# Extra names go here:
stCM_ISO157652_TxMessage = st_cm_iso157652_tx_message
# End of extra names

