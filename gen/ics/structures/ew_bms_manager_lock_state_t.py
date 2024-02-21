# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class ew_bms_manager_lock_state_t(enum.IntEnum):
    """A ctypes-compatible IntEnum superclass."""
    @classmethod
    def from_param(cls, obj):
        return int(obj)

    eLockManager  = 0
    eUnlockManager = enum.auto()


_EwBMSManagerLockState_t = ew_bms_manager_lock_state_t
EwBMSManagerLockState_t = ew_bms_manager_lock_state_t

