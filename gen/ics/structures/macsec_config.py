# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.mac_sec_flags import *
from ics.structures.mac_sec_map import *
from ics.structures.mac_sec_rule import *
from ics.structures.mac_sec_sa import *
from ics.structures.mac_sec_sc import *
from ics.structures.mac_sec_sec_y import *


class macsec_config(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('flags', MACSecFlags),
        ('rule', MACSecRule * 2),
        ('map', MACSecMap * 2),
        ('secy', MACSecSecY * 2),
        ('sc', MACSecSc * 2),
        ('sa', MACSecSa * 4),
    ]


MACSEC_CONFIG_t = macsec_config
MACSEC_CONFIG = macsec_config

