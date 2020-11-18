# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

try: # 2
    from s_phy_reg_pkt_clause22_mess import s_phy_reg_pkt_clause22_mess
    from s_phy_reg_pkt_clause45_mess import s_phy_reg_pkt_clause45_mess
except:
    from ics.structures.s_phy_reg_pkt_clause22_mess import s_phy_reg_pkt_clause22_mess
    from ics.structures.s_phy_reg_pkt_clause45_mess import s_phy_reg_pkt_clause45_mess

class s_phy_reg_pkt(ctypes.Structure):
    _fields_ = [
        ('Enabled:1', ctypes.c_uint16), 
        ('WriteEnable:1', ctypes.c_uint16), 
        ('Clause45Enable:1', ctypes.c_uint16), 
        ('reserved:9', ctypes.c_uint16), 
        ('version:4', ctypes.c_uint16), 
        ('flags', ctypes.c_uint16), 
        ('clause22', s_phy_reg_pkt_clause22_mess), 
        ('clause45', s_phy_reg_pkt_clause45_mess), 
    ]

# Extra names go here:
PhyRegPkt_t = s_phy_reg_pkt
# End of extra names

