# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

class st_cm_iso157652_rx_message(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('vs_netid', ctypes.c_uint16), 
        ('padding', ctypes.c_uint8), 
        ('id', ctypes.c_uint32), 
        ('id_mask', ctypes.c_uint32), 
        ('fc_id', ctypes.c_uint32), 
        ('flowControlExtendedAddress', ctypes.c_uint8), 
        ('extendedAddress', ctypes.c_uint8), 
        ('blockSize', ctypes.c_uint8), 
        ('stMin', ctypes.c_uint8), 
        ('cf_timeout', ctypes.c_uint16), 
        ('id_29_bit_enable', ctypes.c_uint32, 1), # [Bitfield] 
        ('fc_id_29_bit_enable', ctypes.c_uint32, 1), # [Bitfield] 
        ('ext_address_enable', ctypes.c_uint32, 1), # [Bitfield] 
        ('fc_ext_address_enable', ctypes.c_uint32, 1), # [Bitfield] 
        ('enableFlowControlTransmission', ctypes.c_uint32, 1), # [Bitfield] 
        ('paddingEnable', ctypes.c_uint32, 1), # [Bitfield] 
        ('iscanFD', ctypes.c_uint32, 1), # [Bitfield] 
        ('isBRSEnabled', ctypes.c_uint32, 1), # [Bitfield] 
        ('flags', ctypes.c_uint32), 
        ('reserved', ctypes.c_uint8 * 16), 
    ]

# Extra names go here:
stCM_ISO157652_RxMessage = st_cm_iso157652_rx_message
# End of extra names

