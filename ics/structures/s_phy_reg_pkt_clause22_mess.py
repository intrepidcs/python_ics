# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

class s_phy_reg_pkt_clause22_mess(ctypes.Structure):
    _fields_ = [
        ('phyAddr', ctypes.c_uint8), 
        ('page', ctypes.c_uint8), 
        ('regAddr', ctypes.c_uint16), 
        ('regVal', ctypes.c_uint16), 
    ]

# Extra names go here:
PhyRegPktClause22Mess_t = s_phy_reg_pkt_clause22_mess
# End of extra names

