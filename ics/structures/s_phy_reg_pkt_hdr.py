# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class s_phy_reg_pkt_hdr(ctypes.Structure):
    _fields_ = [
        ('numEntries', ctypes.c_uint16),
        ('version', ctypes.c_uint8),
        ('entryBytes', ctypes.c_uint8),
    ]


SPhyRegPktHdr = s_phy_reg_pkt_hdr
PhyRegPktHdr_t = s_phy_reg_pkt_hdr

