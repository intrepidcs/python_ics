# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.mac_sec_flags_ import *
from ics.structures.mac_sec_map_ import *
from ics.structures.mac_sec_rule_ import *
from ics.structures.mac_sec_sa_ import *
from ics.structures.mac_sec_sc_ import *
from ics.structures.mac_sec_sec_y_ import *


class macsec_config(ctypes.Structure):
    _pack_ = 1
    _fields_ = [
        ('flags', MACSecFlags_t),
        ('rule', MACSecRule_t * 2),
        ('map', MACSecMap_t * 2),
        ('secy', MACSecSecY_t * 2),
        ('sc', MACSecSc_t * 2),
        ('sa', MACSecSa_t * 4),
    ]


MACSEC_CONFIG_t = macsec_config
MACSEC_CONFIG = macsec_config

