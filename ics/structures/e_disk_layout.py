# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class e_disk_layout(enum.IntEnum):
    """A ctypes-compatible IntEnum superclass."""
    @classmethod
    def from_param(cls, obj):
        return int(obj)

    DiskLayoutSpanned  = 0
    DiskLayoutRAID0 = enum.auto()
    DiskLayoutRAID1 = enum.auto()
    DiskLayoutRAID5 = enum.auto()
    DiskLayoutIndividual = enum.auto()


_EDiskLayout = e_disk_layout
EDiskLayout = e_disk_layout

