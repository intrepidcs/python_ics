# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class accessory_error_type(enum.IntEnum):
    """A ctypes-compatible IntEnum superclass."""
    @classmethod
    def from_param(cls, obj):
        return int(obj)

    AccessoryOperationError  = 0
    AccessoryOperationSuccess  = 1
    AccessoryFlashingInitError  = 2
    AccessoryFlashingEraseError  = 3
    AccessoryFlashingWriteError  = 4
    AccessoryFlashingReadError  = 5
    AccessoryFlashingVerifyError  = 6
    AccessoryFlashingDeinitError  = 7
    AccessoryFlashingInvalidHardware  = 8
    AccessoryFlashingInvalidDataFile  = 9
    AccessoryGetVersionError  = 10
    AccessoryIndexError  = 11
    AccessoryParamApiVersionError  = 12
    AccessoryParamSizeMismatchError  = 13
    AccessoryParameterNull  = 14


AccessoryErrorType = accessory_error_type
AccessoryOperationErrorType = accessory_error_type

