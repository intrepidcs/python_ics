# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class e_disk_format(enum.IntEnum):
    """A ctypes-compatible IntEnum superclass."""
    @classmethod
    def from_param(cls, obj):
        return int(obj)

    DiskFormatUnknown  = 0
    DiskFormatFAT32 = enum.auto()
    DiskFormatexFAT = enum.auto()


_EDiskFormat = e_disk_format
EDiskFormat = e_disk_format

