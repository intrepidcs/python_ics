# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class mac_sec_sa(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('index', ctypes.c_uint8),
        ('sak', ctypes.c_uint8 * 32),
        ('hashKey', ctypes.c_uint8 * 16),
        ('salt', ctypes.c_uint8 * 12),
        ('ssci', ctypes.c_uint32),
        ('AN', ctypes.c_uint8),
        ('nextPN', ctypes.c_uint64),
        ('rsvd', ctypes.c_uint8 * 5),
        ('enable', ctypes.c_uint8),
    ]


MACSecSa_t = mac_sec_sa
MACSecSa = mac_sec_sa

