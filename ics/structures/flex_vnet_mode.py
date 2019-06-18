# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

from enum import IntEnum

class flex_vnet_mode(IntEnum):
    """A ctypes-compatible IntEnum superclass."""
    @classmethod
    def from_param(cls, obj):
        return int(obj)

    flexVnetModeDisabled = 0
    flexVnetModeOneSingle = 1
    flexVnetModeOneDual = 2
    flexVnetModeTwoSingle = 3
    flexVnetModeColdStart = 4


# Extra names go here:
flexVnetMode = flex_vnet_mode
# End of extra names

