# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

from enum import IntEnum

class erad_gigalog_disk_format(IntEnum):
    """A ctypes-compatible IntEnum superclass."""
    @classmethod
    def from_param(cls, obj):
        return int(obj)

    RADGigalogDiskFormatUnknown  = 0
    RADGigalogDiskFormatFAT32 = 1
    RADGigalogDiskFormatexFAT = 2


# Extra names go here:
ERADGigalogDiskFormat = erad_gigalog_disk_format
# End of extra names

