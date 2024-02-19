# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class Nameless4038(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('bExtended', ctypes.c_uint, 1),
        ('', ctypes.c_uint, 31),
    ]



class can1_options(ctypes.Union):
    _pack_ = 2
    _anonymous_  = ('Nameless4038',)
    _fields_ = [
        ('Nameless4038', Nameless4038),
        ('DWord', ctypes.c_uint32),
    ]



class Nameless2076(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('bExtended', ctypes.c_uint, 1),
        ('', ctypes.c_uint, 31),
    ]



class can2_options(ctypes.Union):
    _pack_ = 2
    _anonymous_  = ('Nameless2076',)
    _fields_ = [
        ('Nameless2076', Nameless2076),
        ('DWord', ctypes.c_uint32),
    ]



class Nameless45362(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('bExtended', ctypes.c_uint, 1),
        ('', ctypes.c_uint, 31),
    ]



class can3_options(ctypes.Union):
    _pack_ = 2
    _anonymous_  = ('Nameless45362',)
    _fields_ = [
        ('Nameless45362', Nameless45362),
        ('DWord', ctypes.c_uint32),
    ]



class Nameless63471(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('bExtended', ctypes.c_uint, 1),
        ('', ctypes.c_uint, 31),
    ]



class can4_options(ctypes.Union):
    _pack_ = 2
    _anonymous_  = ('Nameless63471',)
    _fields_ = [
        ('Nameless63471', Nameless63471),
        ('DWord', ctypes.c_uint32),
    ]



class s_text_api_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('can1_tx_id', ctypes.c_uint32),
        ('can1_rx_id', ctypes.c_uint32),
        ('can1_options', can1_options),
        ('can2_tx_id', ctypes.c_uint32),
        ('can2_rx_id', ctypes.c_uint32),
        ('can2_options', can2_options),
        ('network_enables', ctypes.c_uint32),
        ('can3_tx_id', ctypes.c_uint32),
        ('can3_rx_id', ctypes.c_uint32),
        ('can3_options', can3_options),
        ('can4_tx_id', ctypes.c_uint32),
        ('can4_rx_id', ctypes.c_uint32),
        ('can4_options', can4_options),
        ('reserved', ctypes.c_uint32 * 5),
    ]


_STextAPISettings = s_text_api_settings
STextAPISettings = s_text_api_settings

