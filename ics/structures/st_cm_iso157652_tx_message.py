# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class Nameless39639(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('id_29_bit_enable', ctypes.c_uint, 1),
        ('fc_id_29_bit_enable', ctypes.c_uint, 1),
        ('ext_address_enable', ctypes.c_uint, 1),
        ('fc_ext_address_enable', ctypes.c_uint, 1),
        ('overrideSTmin', ctypes.c_uint, 1),
        ('overrideBlockSize', ctypes.c_uint, 1),
        ('paddingEnable', ctypes.c_uint, 1),
        ('iscanFD', ctypes.c_uint, 1),
        ('isBRSEnabled', ctypes.c_uint, 1),
        ('', ctypes.c_uint, 15),
        ('tx_dl', ctypes.c_uint, 8),
    ]



class Nameless63050(ctypes.Union):
    _pack_ = 2
    _anonymous_  = ('Nameless39639',)
    _fields_ = [
        ('Nameless39639', Nameless39639),
        ('flags', ctypes.c_uint32),
    ]



class st_cm_iso157652_tx_message(ctypes.Structure):
    _pack_ = 2
    _anonymous_  = ('Nameless63050',)
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
        ('Nameless63050', Nameless63050),
    ]


_stCM_ISO157652_TxMessage = st_cm_iso157652_tx_message
stCM_ISO157652_TxMessage = st_cm_iso157652_tx_message

