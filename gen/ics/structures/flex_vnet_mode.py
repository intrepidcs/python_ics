# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class flex_vnet_mode(enum.IntEnum):
    """A ctypes-compatible IntEnum superclass."""
    @classmethod
    def from_param(cls, obj):
        return int(obj)

    flexVnetModeDisabled = 0
    flexVnetModeOneSingle = enum.auto()
    flexVnetModeOneDual = enum.auto()
    flexVnetModeTwoSingle = enum.auto()
    flexVnetModeColdStart = enum.auto()


_flexVnetMode = flex_vnet_mode
flexVnetMode = flex_vnet_mode

