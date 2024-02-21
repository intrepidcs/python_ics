# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class s_phy_reg_pkt_clause22_mess(ctypes.Structure):
    _fields_ = [
        ('phyAddr', ctypes.c_uint8),
        ('page', ctypes.c_uint8),
        ('regAddr', ctypes.c_uint16),
        ('regVal', ctypes.c_uint16),
    ]


SPhyRegPktClause22Mess = s_phy_reg_pkt_clause22_mess
PhyRegPktClause22Mess_t = s_phy_reg_pkt_clause22_mess

