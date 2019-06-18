# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

try: # 2
    from srad_gigalog_disk_structure import srad_gigalog_disk_structure
    from srad_gigalog_disk_status import srad_gigalog_disk_status
except:
    from ics.structures.srad_gigalog_disk_structure import srad_gigalog_disk_structure
    from ics.structures.srad_gigalog_disk_status import srad_gigalog_disk_status

class srad_gigalog_disk_details(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('structure', srad_gigalog_disk_structure), 
        ('status', srad_gigalog_disk_status * 12), 
    ]

# Extra names go here:
SRADGigalogDiskDetails = srad_gigalog_disk_details
# End of extra names

