# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class macsec_vlantag_t(ctypes.Structure):
    _pack_ = 1
    _fields_ = [
        ('VID', ctypes.c_uint16),
        ('PRI_CFI', ctypes.c_uint8),
    ]


MACSEC_VLANTAG_t = macsec_vlantag_t

