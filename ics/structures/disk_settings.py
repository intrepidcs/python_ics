# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

class disk_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('disk_layout', ctypes.c_uint8), # RAID0, spanned, etc
        ('disk_format', ctypes.c_uint8), # FAT32
        ('disk_enables', ctypes.c_uint32), # mask of enabled disks in this layout
        ('rsvd', ctypes.c_uint8 * 8), 
    ]

# Extra names go here:
DISK_SETTINGS = disk_settings
# End of extra names

