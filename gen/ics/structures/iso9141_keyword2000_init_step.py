# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class iso9141_keyword2000_init_step(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('time_500us', ctypes.c_uint16),
        ('k', ctypes.c_uint16),
        ('l', ctypes.c_uint16),
    ]


ISO9141_KEYWORD2000__INIT_STEP = iso9141_keyword2000_init_step

