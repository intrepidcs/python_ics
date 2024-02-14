# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class macsec_vlantag(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('VID', ctypes.c_uint16),
        ('PRI_CFI', ctypes.c_uint8),
    ]


MACSEC_VLANTAG_t = macsec_vlantag
MACSEC_VLANTAG = macsec_vlantag

