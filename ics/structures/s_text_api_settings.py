# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class nameless58148(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('bExtended', ctypes.c_uint, 1),
        ('', ctypes.c_uint, 31),
    ]



class can1_options(ctypes.Union):
    _pack_ = 2
    _anonymous_  = ('nameless58148',)
    _fields_ = [
        ('nameless58148', nameless58148),
        ('DWord', ctypes.c_uint32),
    ]



class nameless13494(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('bExtended', ctypes.c_uint, 1),
        ('', ctypes.c_uint, 31),
    ]



class can2_options(ctypes.Union):
    _pack_ = 2
    _anonymous_  = ('nameless13494',)
    _fields_ = [
        ('nameless13494', nameless13494),
        ('DWord', ctypes.c_uint32),
    ]



class nameless35611(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('bExtended', ctypes.c_uint, 1),
        ('', ctypes.c_uint, 31),
    ]



class can3_options(ctypes.Union):
    _pack_ = 2
    _anonymous_  = ('nameless35611',)
    _fields_ = [
        ('nameless35611', nameless35611),
        ('DWord', ctypes.c_uint32),
    ]



class nameless30009(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('bExtended', ctypes.c_uint, 1),
        ('', ctypes.c_uint, 31),
    ]



class can4_options(ctypes.Union):
    _pack_ = 2
    _anonymous_  = ('nameless30009',)
    _fields_ = [
        ('nameless30009', nameless30009),
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

