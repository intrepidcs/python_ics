# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class Nameless757(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('id_29_bit_enable', ctypes.c_uint16, 1),
        ('fc_id_29_bit_enable', ctypes.c_uint16, 1),
        ('ext_address_enable', ctypes.c_uint16, 1),
        ('fc_ext_address_enable', ctypes.c_uint16, 1),
        ('overrideSTmin', ctypes.c_uint16, 1),
        ('overrideBlockSize', ctypes.c_uint16, 1),
        ('paddingEnable', ctypes.c_uint16, 1),
        ('iscanFD', ctypes.c_uint16, 1),
        ('isBRSEnabled', ctypes.c_uint16, 1),
        ('', ctypes.c_uint16, 7),
    ]



class Nameless43713(ctypes.Union):
    _pack_ = 2
    _anonymous_  = ('Nameless757',)
    _fields_ = [
        ('Nameless757', Nameless757),
        ('flags', ctypes.c_uint16),
    ]



class iso15765_2015_tx_message(ctypes.Structure):
    _pack_ = 2
    _anonymous_  = ('Nameless43713',)
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
        ('data', ctypes.POINTER(ctypes.c_uint8)),
        ('num_bytes', ctypes.c_uint32),
        ('tx_dl', ctypes.c_uint8),
        ('Nameless43713', Nameless43713),
    ]


ISO15765_2015_TxMessage = iso15765_2015_tx_message

