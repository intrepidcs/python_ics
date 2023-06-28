# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class phy_error_type(enum.IntEnum):
    """A ctypes-compatible IntEnum superclass."""
    @classmethod
    def from_param(cls, obj):
        return int(obj)

    PhyOperationError  = 0
    PhyOperationSuccess  = 1
    PhyFlashingInitError  = 2
    PhyFlashingEraseError  = 3
    PhyFlashingWriteError  = 4
    PhyFlashingReadError  = 5
    PhyFlashingVerifyError  = 6
    PhyFlashingDeinitError  = 7
    PhyFlashingInvalidHardware  = 8
    PhyFlashingInvalidDataFile  = 9
    PhyGetVersionError  = 10
    PhyIndexError  = 11


PhyErrorType = phy_error_type
PhyErrorType = phy_error_type

