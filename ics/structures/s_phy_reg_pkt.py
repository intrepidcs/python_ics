# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.phy_reg_pkt_clause22_mess_t import *
from ics.structures.phy_reg_pkt_clause45_mess_t import *


class nameless52872(ctypes.Structure):
    _fields_ = [
        ('Enabled', ctypes.c_uint16, 1),
        ('WriteEnable', ctypes.c_uint16, 1),
        ('Clause45Enable', ctypes.c_uint16, 1),
        ('reserved', ctypes.c_uint16, 9),
        ('version', ctypes.c_uint16, 4),
    ]



class nameless58328(ctypes.Union):
    _anonymous_  = ('nameless52872',)
    _fields_ = [
        ('nameless52872', nameless52872),
        ('flags', ctypes.c_uint16),
    ]



class nameless32574(ctypes.Union):
    _fields_ = [
        ('clause22', PhyRegPktClause22Mess_t),
        ('clause45', PhyRegPktClause45Mess_t),
    ]



class s_phy_reg_pkt(ctypes.Structure):
    _anonymous_  = ('nameless58328', 'nameless32574')
    _fields_ = [
        ('nameless58328', nameless58328),
        ('nameless32574', nameless32574),
    ]


SPhyRegPkt = s_phy_reg_pkt
PhyRegPkt_t = s_phy_reg_pkt

