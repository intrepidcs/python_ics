# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class macsec_validateframe(enum.IntEnum):
    """A ctypes-compatible IntEnum superclass."""
    @classmethod
    def from_param(cls, obj):
        return int(obj)

    MACSEC_VF_DISABLED  = 0
    MACSEC_VF_CHECK  = 1
    MACSEC_VF_STRICT  = 2
    MACSEC_VF_NA  = 3


MACSEC_VALIDATEFRAME_t = macsec_validateframe
MACSEC_VALIDATEFRAME = macsec_validateframe

