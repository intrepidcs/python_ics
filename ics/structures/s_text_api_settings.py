# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class nameless57310(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('bExtended', ctypes.c_uint, 1),
        ('', ctypes.c_uint, 31),
    ]



class can1_options(ctypes.Union):
    _pack_ = 2
    _anonymous_  = ('nameless57310',)
    _fields_ = [
        ('nameless57310', nameless57310),
        ('DWord', ctypes.c_uint32),
    ]



class nameless29787(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('bExtended', ctypes.c_uint, 1),
        ('', ctypes.c_uint, 31),
    ]



class can2_options(ctypes.Union):
    _pack_ = 2
    _anonymous_  = ('nameless29787',)
    _fields_ = [
        ('nameless29787', nameless29787),
        ('DWord', ctypes.c_uint32),
    ]



class nameless22645(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('bExtended', ctypes.c_uint, 1),
        ('', ctypes.c_uint, 31),
    ]



class can3_options(ctypes.Union):
    _pack_ = 2
    _anonymous_  = ('nameless22645',)
    _fields_ = [
        ('nameless22645', nameless22645),
        ('DWord', ctypes.c_uint32),
    ]



class nameless29441(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('bExtended', ctypes.c_uint, 1),
        ('', ctypes.c_uint, 31),
    ]



class can4_options(ctypes.Union):
    _pack_ = 2
    _anonymous_  = ('nameless29441',)
    _fields_ = [
        ('nameless29441', nameless29441),
        ('DWord', ctypes.c_uint32),
    ]



class s_text_api_settings(ctypes.Structure):
    _pack_ = 2
    _anonymous_  = ('can1_options', 'can2_options', 'can3_options', 'can4_options')
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

