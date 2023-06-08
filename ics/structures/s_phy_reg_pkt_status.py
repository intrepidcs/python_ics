# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class s_phy_reg_pkt_status(enum.IntEnum):
    """A ctypes-compatible IntEnum superclass."""
    @classmethod
    def from_param(cls, obj):
        return int(obj)

    PHYREG_SUCCESS  = 0
    PHYREG_FAILURE = enum.auto()
    PHYREG_INVALID_MDIO_BUS_INDEX = enum.auto()
    PHYREG_INVALID_PHY_ADDR = enum.auto()
    PHYREG_UNSUPPORTED_MDIO_CLAUSE = enum.auto()
    PHYREG_RESERVED1 = enum.auto()
    PHYREG_RESERVED2 = enum.auto()
    PHYREG_RESERVED3 = enum.auto()


SPhyRegPktStatus = s_phy_reg_pkt_status
PhyRegPktStatus_t = s_phy_reg_pkt_status

