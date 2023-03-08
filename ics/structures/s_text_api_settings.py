# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class Nameless5231(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('bExtended', ctypes.c_uint, 1),
        ('', ctypes.c_uint, 31),
    ]



class can1_options(ctypes.Union):
    _pack_ = 2
    _anonymous_  = ('Nameless5231',)
    _fields_ = [
        ('Nameless5231', Nameless5231),
        ('DWord', ctypes.c_uint32),
    ]



class Nameless56724(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('bExtended', ctypes.c_uint, 1),
        ('', ctypes.c_uint, 31),
    ]



class can2_options(ctypes.Union):
    _pack_ = 2
    _anonymous_  = ('Nameless56724',)
    _fields_ = [
        ('Nameless56724', Nameless56724),
        ('DWord', ctypes.c_uint32),
    ]



class Nameless51306(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('bExtended', ctypes.c_uint, 1),
        ('', ctypes.c_uint, 31),
    ]



class can3_options(ctypes.Union):
    _pack_ = 2
    _anonymous_  = ('Nameless51306',)
    _fields_ = [
        ('Nameless51306', Nameless51306),
        ('DWord', ctypes.c_uint32),
    ]



class Nameless42521(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('bExtended', ctypes.c_uint, 1),
        ('', ctypes.c_uint, 31),
    ]



class can4_options(ctypes.Union):
    _pack_ = 2
    _anonymous_  = ('Nameless42521',)
    _fields_ = [
        ('Nameless42521', Nameless42521),
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

