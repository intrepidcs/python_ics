# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class Nameless8462(ctypes.Structure):
    _pack_ = 1
    _fields_ = [
        ('index', ctypes.c_uint8),
        ('secYIndex', ctypes.c_uint8),
        ('sci', ctypes.c_uint64),
        ('sa_index0', ctypes.c_uint8),
        ('sa_index1', ctypes.c_uint8),
        ('sa_index0_in_use', ctypes.c_uint8),
        ('sa_index1_in_use', ctypes.c_uint8),
        ('enable_auto_rekey', ctypes.c_uint8),
        ('isActiveSA1', ctypes.c_uint8),
        ('rsvd', ctypes.c_uint8 * 7),
        ('enable', ctypes.c_uint8),
    ]



class mac_sec_sc_(ctypes.Union):
    _pack_ = 1
    _anonymous_  = ('Nameless8462',)
    _fields_ = [
        ('Nameless8462', Nameless8462),
        ('byte', ctypes.c_uint8 * 24),
    ]


_MACSecSc = mac_sec_sc_
MACSecSc_t = mac_sec_sc_
MACSecSc_ = mac_sec_sc_

