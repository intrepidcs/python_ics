# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

class srad_gigalog_disk_status(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('status', ctypes.c_uint16), # 0x1 = present, 0x2 = initialized, 0x04 included in formatting
        ('sectors', ctypes.c_uint8 * 8), 
        ('bytesPerSector', ctypes.c_uint8 * 4), 
    ]

# Extra names go here:
SRADGigalogDiskStatus = srad_gigalog_disk_status
# End of extra names

