# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.s_phy_reg_pkt_clause22_mess import *
from ics.structures.s_phy_reg_pkt_clause45_mess import *


class Nameless3555(ctypes.Structure):
    _fields_ = [
        ('Enabled', ctypes.c_uint16, 1),
        ('WriteEnable', ctypes.c_uint16, 1),
        ('Clause45Enable', ctypes.c_uint16, 1),
        ('status', ctypes.c_uint16, 2),
        ('reserved', ctypes.c_uint16, 3),
        ('BusIndex', ctypes.c_uint16, 4),
        ('version', ctypes.c_uint16, 4),
    ]



class Nameless45381(ctypes.Union):
    _anonymous_  = ('Nameless3555',)
    _fields_ = [
        ('Nameless3555', Nameless3555),
        ('flags', ctypes.c_uint16),
    ]



class Nameless14534(ctypes.Union):
    _fields_ = [
        ('clause22', PhyRegPktClause22Mess_t),
        ('clause45', PhyRegPktClause45Mess_t),
    ]



class s_phy_reg_pkt(ctypes.Structure):
    _anonymous_  = ('Nameless45381', 'Nameless14534')
    _fields_ = [
        ('Nameless45381', Nameless45381),
        ('Nameless14534', Nameless14534),
    ]


SPhyRegPkt = s_phy_reg_pkt
PhyRegPkt_t = s_phy_reg_pkt

