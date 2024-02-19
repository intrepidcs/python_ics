# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class macsec_strip_sectag_icv(enum.IntEnum):
    """A ctypes-compatible IntEnum superclass."""
    @classmethod
    def from_param(cls, obj):
        return int(obj)

    MACSEC_SECTAG_ICV_BOTH_STRIP  = 0
    MACSEC_SECTAG_ICV_RESERVED  = 1
    MACSEC_SECTAG_ICV_STRIP_ICV_ONLY  = 2
    MACSEC_SECTAG_ICV_NO_STRIP  = 3


MACSEC_STRIP_SECTAG_ICV_t = macsec_strip_sectag_icv
MACSEC_STRIP_SECTAG_ICV = macsec_strip_sectag_icv

