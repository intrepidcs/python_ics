# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class e_gptp_role(enum.IntEnum):
    """A ctypes-compatible IntEnum superclass."""
    @classmethod
    def from_param(cls, obj):
        return int(obj)

    eRoleDisabled  = 0
    eRolePassive  = 1
    eRoleMaster  = 2
    eRoleSlave  = 3


eGPTPRole = e_gptp_role

