# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.mac_sec_global_flags_ import *
from ics.structures.macsec_config import *


class Nameless6024(ctypes.Structure):
    _pack_ = 1
    _fields_ = [
        ('flags', MACSecGlobalFlags_t),
        ('rx', MACSEC_CONFIG),
        ('tx', MACSEC_CONFIG),
    ]



class macsec_settings(ctypes.Union):
    _pack_ = 1
    _anonymous_  = ('Nameless6024',)
    _fields_ = [
        ('Nameless6024', Nameless6024),
        ('byte', ctypes.c_uint8 * 2040),
    ]


_MACSEC_SETTINGS = macsec_settings
MACSEC_SETTINGS = macsec_settings

