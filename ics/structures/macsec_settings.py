# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.macsec_config import *


class macsec_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('rx', MACSEC_CONFIG),
        ('tx', MACSEC_CONFIG),
    ]


MACSEC_SETTINGS_t = macsec_settings
MACSEC_SETTINGS = macsec_settings

