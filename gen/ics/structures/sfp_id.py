# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class sfp_id(enum.IntEnum):
    """A ctypes-compatible IntEnum superclass."""
    @classmethod
    def from_param(cls, obj):
        return int(obj)

    SFP_ID_UNKNOWN  = 0
    SFP_ID_FINISAR_FCLF8522P2BTL = enum.auto()
    SFP_ID_FS_GB_GE_T = enum.auto()
    SFP_ID_ICS_MV2112A2 = enum.auto()
    SFP_ID_ICS_MV2221MB1 = enum.auto()
    SFP_ID_ICS_MV3244 = enum.auto()
    SFP_ID_MAX = enum.auto()


SfpId = sfp_id

