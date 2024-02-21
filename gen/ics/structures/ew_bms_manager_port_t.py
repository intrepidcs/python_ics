# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class ew_bms_manager_port_t(enum.IntEnum):
    """A ctypes-compatible IntEnum superclass."""
    @classmethod
    def from_param(cls, obj):
        return int(obj)

    eManagerPortA  = 0
    eManagerPortB = enum.auto()


_EwBMSManagerPort_t = ew_bms_manager_port_t
EwBMSManagerPort_t = ew_bms_manager_port_t

