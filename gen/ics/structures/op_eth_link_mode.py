# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class op_eth_link_mode(enum.IntEnum):
    """A ctypes-compatible IntEnum superclass."""
    @classmethod
    def from_param(cls, obj):
        return int(obj)

    OPETH_LINK_AUTO  = 0
    OPETH_LINK_MASTER = enum.auto()
    OPETH_LINK_SLAVE = enum.auto()


_opEthLinkMode = op_eth_link_mode
opEthLinkMode = op_eth_link_mode

