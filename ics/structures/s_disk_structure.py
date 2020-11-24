# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

try: # 1
    from disk_settings import disk_settings
except:
    from ics.structures.disk_settings import disk_settings

class s_disk_structure(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('settings', disk_settings), 
        ('options', ctypes.c_uint16), # 0x01 full format
    ]

# Extra names go here:
SDiskStructure = s_disk_structure
# End of extra names

