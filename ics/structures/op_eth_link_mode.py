# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

from enum import IntEnum

class op_eth_link_mode(IntEnum):
    """A ctypes-compatible IntEnum superclass."""
    @classmethod
    def from_param(cls, obj):
        return int(obj)

    OPETH_LINK_AUTO  = 0
    OPETH_LINK_MASTER = 1
    OPETH_LINK_SLAVE = 2


# Extra names go here:
opEthLinkMode = op_eth_link_mode
# End of extra names

