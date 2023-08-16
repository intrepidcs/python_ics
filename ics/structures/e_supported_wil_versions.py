# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class e_supported_wil_versions(enum.IntEnum):
    """A ctypes-compatible IntEnum superclass."""
    @classmethod
    def from_param(cls, obj):
        return int(obj)

    eSupportedWILVersions_WIL_1_1_0  = 1
    eSupportedWILVersions_WIL_2_0_0 = enum.auto()


eSupportedWILVersions = e_supported_wil_versions

