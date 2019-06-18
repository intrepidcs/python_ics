# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

from enum import IntEnum

class erad_gigalog_disk_layout(IntEnum):
    """A ctypes-compatible IntEnum superclass."""
    @classmethod
    def from_param(cls, obj):
        return int(obj)

    RADGigalogDiskLayoutSpanned  = 0
    RADGigalogDiskLayoutRAID0 = 1
    RADGigalogDiskLayoutRAID1 = 2
    RADGigalogDiskLayoutRAID5 = 3
    RADGigalogDiskLayoutIndividual = 4


# Extra names go here:
ERADGigalogDiskLayout = erad_gigalog_disk_layout
# End of extra names

