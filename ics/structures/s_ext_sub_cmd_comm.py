# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

try: # 4
    from s_ext_sub_cmd_hdr import s_ext_sub_cmd_hdr
    from s_disk_structure import s_disk_structure
    from s_disk_details import s_disk_details
    from s_disk_format_progress import s_disk_format_progress
except:
    from ics.structures.s_ext_sub_cmd_hdr import s_ext_sub_cmd_hdr
    from ics.structures.s_disk_structure import s_disk_structure
    from ics.structures.s_disk_details import s_disk_details
    from ics.structures.s_disk_format_progress import s_disk_format_progress

class s_ext_sub_cmd_comm(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('hdr', s_ext_sub_cmd_hdr), 
        ('structure', s_disk_structure), 
        ('details', s_disk_details), 
        ('progress', s_disk_format_progress), 
    ]

# Extra names go here:
SExtSubCmdComm = s_ext_sub_cmd_comm
# End of extra names

