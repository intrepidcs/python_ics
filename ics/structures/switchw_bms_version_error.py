# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class switchw_bms_version_error(enum.IntEnum):
    """A ctypes-compatible IntEnum superclass."""
    @classmethod
    def from_param(cls, obj):
        return int(obj)

    SwitchwBMSVersion_Failed  = 0
    SwitchwBMSVersion_OK = enum.auto()
    SwitchwBMSVersion_Reflashed = enum.auto()
    SwitchwBMSVersion_ParameterNotValid = enum.auto()


SwitchwBMSVersionError = switchw_bms_version_error
SwitchwBMSVersionError = switchw_bms_version_error

