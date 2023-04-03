# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.s_phy_reg_pkt_clause22_mess import *
from ics.structures.s_phy_reg_pkt_clause45_mess import *


class Nameless14534(ctypes.Structure):
    _fields_ = [
        ('Enabled', ctypes.c_uint16, 1),
        ('WriteEnable', ctypes.c_uint16, 1),
        ('Clause45Enable', ctypes.c_uint16, 1),
        ('status', ctypes.c_uint16, 3),
        ('reserved', ctypes.c_uint16, 2),
        ('BusIndex', ctypes.c_uint16, 4),
        ('version', ctypes.c_uint16, 4),
    ]



class Nameless18511(ctypes.Union):
    _anonymous_  = ('Nameless14534',)
    _fields_ = [
        ('Nameless14534', Nameless14534),
        ('flags', ctypes.c_uint16),
    ]



class Nameless40028(ctypes.Union):
    _fields_ = [
        ('clause22', PhyRegPktClause22Mess_t),
        ('clause45', PhyRegPktClause45Mess_t),
    ]



class s_phy_reg_pkt(ctypes.Structure):
    _anonymous_  = ('Nameless18511', 'Nameless40028')
    _fields_ = [
        ('Nameless18511', Nameless18511),
        ('Nameless40028', Nameless40028),
    ]


SPhyRegPkt = s_phy_reg_pkt
PhyRegPkt_t = s_phy_reg_pkt

