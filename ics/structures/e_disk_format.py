# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

from enum import IntEnum

class e_disk_format(IntEnum):
    """A ctypes-compatible IntEnum superclass."""
    @classmethod
    def from_param(cls, obj):
        return int(obj)

    DiskFormatUnknown  = 0
    DiskFormatFAT32 = 1
    DiskFormatexFAT = 2


# Extra names go here:
EDiskFormat = e_disk_format
# End of extra names

