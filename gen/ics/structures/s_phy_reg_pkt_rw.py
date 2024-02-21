# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class s_phy_reg_pkt_rw(enum.IntEnum):
    """A ctypes-compatible IntEnum superclass."""
    @classmethod
    def from_param(cls, obj):
        return int(obj)

    PHYREG_READ  = 0
    PHYREG_WRITE = enum.auto()
    PHYREG_BOTH = enum.auto()


SPhyRegPktRw = s_phy_reg_pkt_rw
PhyRegPktRw_t = s_phy_reg_pkt_rw

