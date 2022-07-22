# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class extended_response_code(enum.IntEnum):
    """A ctypes-compatible IntEnum superclass."""
    @classmethod
    def from_param(cls, obj):
        return int(obj)

    EXTENDED_RESPONSE_OK  = 0
    EXTENDED_RESPONSE_INVALID_COMMAND  = -1
    EXTENDED_RESPONSE_INVALID_STATE  = -2
    EXTENDED_RESPONSE_OPERATION_FAILED  = -3
    EXTENDED_RESPONSE_OPERATION_PENDING  = -4
    EXTENDED_RESPONSE_INVALID_PARAMETER  = -5


_ExtendedResponseCode = extended_response_code
ExtendedResponseCode = extended_response_code

