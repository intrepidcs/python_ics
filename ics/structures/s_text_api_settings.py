# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class nameless44483(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('bExtended', ctypes.c_uint, 1),
        ('', ctypes.c_uint, 31),
    ]



class can1_options(ctypes.Union):
    _pack_ = 2
    _anonymous_  = ('nameless44483',)
    _fields_ = [
        ('nameless44483', nameless44483),
        ('DWord', ctypes.c_uint32),
    ]



class nameless33071(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('bExtended', ctypes.c_uint, 1),
        ('', ctypes.c_uint, 31),
    ]



class can2_options(ctypes.Union):
    _pack_ = 2
    _anonymous_  = ('nameless33071',)
    _fields_ = [
        ('nameless33071', nameless33071),
        ('DWord', ctypes.c_uint32),
    ]



class nameless10428(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('bExtended', ctypes.c_uint, 1),
        ('', ctypes.c_uint, 31),
    ]



class can3_options(ctypes.Union):
    _pack_ = 2
    _anonymous_  = ('nameless10428',)
    _fields_ = [
        ('nameless10428', nameless10428),
        ('DWord', ctypes.c_uint32),
    ]



class nameless7525(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('bExtended', ctypes.c_uint, 1),
        ('', ctypes.c_uint, 31),
    ]



class can4_options(ctypes.Union):
    _pack_ = 2
    _anonymous_  = ('nameless7525',)
    _fields_ = [
        ('nameless7525', nameless7525),
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

