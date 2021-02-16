# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

from enum import IntEnum

class e_disk_layout(IntEnum):
    """A ctypes-compatible IntEnum superclass."""
    @classmethod
    def from_param(cls, obj):
        return int(obj)

    DiskLayoutSpanned  = 0
    DiskLayoutRAID0 = 1
    DiskLayoutRAID1 = 2
    DiskLayoutRAID5 = 3
    DiskLayoutIndividual = 4


# Extra names go here:
EDiskLayout = e_disk_layout
# End of extra names

