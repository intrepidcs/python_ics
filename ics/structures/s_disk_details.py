# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

try: # 2
    from s_disk_structure import s_disk_structure
    from s_disk_status import s_disk_status
except:
    from ics.structures.s_disk_structure import s_disk_structure
    from ics.structures.s_disk_status import s_disk_status

class s_disk_details(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('structure', s_disk_structure), 
        ('status', s_disk_status * 12), 
    ]

# Extra names go here:
SDiskDetails = s_disk_details
# End of extra names

