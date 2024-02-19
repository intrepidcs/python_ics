# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class a2_btdm_mode(enum.IntEnum):
    """A ctypes-compatible IntEnum superclass."""
    @classmethod
    def from_param(cls, obj):
        return int(obj)

    tdmModeTDM2  = 0
    tdmModeTDM4 = enum.auto()
    tdmModeTDM8 = enum.auto()
    tdmModeTDM12 = enum.auto()
    tdmModeTDM16 = enum.auto()
    tdmModeTDM20 = enum.auto()
    tdmModeTDM24 = enum.auto()
    tdmModeTDM32 = enum.auto()


A2BTDMMode = a2_btdm_mode

