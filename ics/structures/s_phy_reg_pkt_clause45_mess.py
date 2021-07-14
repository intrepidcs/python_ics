# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class s_phy_reg_pkt_clause45_mess(ctypes.Structure):
    _fields_ = [
        ('port', ctypes.c_uint8),
        ('device', ctypes.c_uint8),
        ('regAddr', ctypes.c_uint16),
        ('regVal', ctypes.c_uint16),
    ]


SPhyRegPktClause45Mess = s_phy_reg_pkt_clause45_mess
PhyRegPktClause45Mess_t = s_phy_reg_pkt_clause45_mess

