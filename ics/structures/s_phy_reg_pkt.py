# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.s_phy_reg_pkt_clause45_mess import *
from ics.structures.s_phy_reg_pkt_clause22_mess import *


class nameless29878(ctypes.Structure):
    _fields_ = [
        ('Enabled', ctypes.c_uint16, 1),
        ('WriteEnable', ctypes.c_uint16, 1),
        ('Clause45Enable', ctypes.c_uint16, 1),
        ('reserved', ctypes.c_uint16, 9),
        ('version', ctypes.c_uint16, 4),
    ]



class nameless42242(ctypes.Union):
    _anonymous_  = ('nameless29878',)
    _fields_ = [
        ('nameless29878', nameless29878),
        ('flags', ctypes.c_uint16),
    ]



class nameless49399(ctypes.Union):
    _fields_ = [
        ('clause22', PhyRegPktClause22Mess_t),
        ('clause45', PhyRegPktClause45Mess_t),
    ]



class s_phy_reg_pkt(ctypes.Structure):
    _anonymous_  = ('nameless42242', 'nameless49399')
    _fields_ = [
        ('nameless42242', nameless42242),
        ('nameless49399', nameless49399),
    ]


SPhyRegPkt = s_phy_reg_pkt
PhyRegPkt_t = s_phy_reg_pkt

