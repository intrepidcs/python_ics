# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

try: # 2
    from s_phy_reg_pkt_clause22_mess import s_phy_reg_pkt_clause22_mess
    from s_phy_reg_pkt_clause45_mess import s_phy_reg_pkt_clause45_mess
except:
    from ics.structures.s_phy_reg_pkt_clause22_mess import s_phy_reg_pkt_clause22_mess
    from ics.structures.s_phy_reg_pkt_clause45_mess import s_phy_reg_pkt_clause45_mess

# _U15
class _U15(ctypes.Union):
    _fields_ = [
        ('Enabled', ctypes.c_uint16, 1), # [Bitfield] 
        ('WriteEnable', ctypes.c_uint16, 1), # [Bitfield] 
        ('Clause45Enable', ctypes.c_uint16, 1), # [Bitfield] 
        ('reserved', ctypes.c_uint16, 9), # [Bitfield] 
        ('version', ctypes.c_uint16, 4), # [Bitfield] 
        ('flags', ctypes.c_uint16), 
    ]

# Extra names go here:
# End of extra names

# _U16
class _U16(ctypes.Union):
    _fields_ = [
        ('clause22', s_phy_reg_pkt_clause22_mess), 
        ('clause45', s_phy_reg_pkt_clause45_mess), 
    ]

# Extra names go here:
# End of extra names

class s_phy_reg_pkt(ctypes.Structure):
    _anonymous_ = ("_U15", "_U16",)
    _fields_ = [
        ('_U15', _U15), 
        ('_U16', _U16), 
    ]

# Extra names go here:
PhyRegPkt_t = s_phy_reg_pkt
# End of extra names

