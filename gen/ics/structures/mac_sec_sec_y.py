# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.macsec_cipher_suite import *
from ics.structures.macsec_strip_sectag_icv import *
from ics.structures.macsec_validateframe import *


class mac_sec_sec_y(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('index', ctypes.c_uint8),
        ('controlled_port_enabled', ctypes.c_uint8),
        ('validate_frames', ctypes.c_int32),
        ('strip_sectag_icv', ctypes.c_int32),
        ('cipher', ctypes.c_int32),
        ('confidential_offset', ctypes.c_uint8),
        ('icv_includes_da_sa', ctypes.c_uint8),
        ('replay_protect', ctypes.c_uint8),
        ('replay_window', ctypes.c_uint32),
        ('protect_frames', ctypes.c_uint8),
        ('sectag_offset', ctypes.c_uint8),
        ('sectag_tci', ctypes.c_uint8),
        ('mtu', ctypes.c_uint16),
        ('rsvd', ctypes.c_uint8 * 6),
        ('enable', ctypes.c_uint8),
    ]


MACSecSecY_t = mac_sec_sec_y
MACSecSecY = mac_sec_sec_y

