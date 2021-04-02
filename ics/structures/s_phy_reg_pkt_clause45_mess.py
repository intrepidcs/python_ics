# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

class s_phy_reg_pkt_clause45_mess(ctypes.Structure):
    _fields_ = [
        ('port', ctypes.c_uint8), 
        ('device', ctypes.c_uint8), 
        ('regAddr', ctypes.c_uint16), 
        ('regVal', ctypes.c_uint16), 
    ]

# Extra names go here:
PhyRegPktClause45Mess_t = s_phy_reg_pkt_clause45_mess
# End of extra names

