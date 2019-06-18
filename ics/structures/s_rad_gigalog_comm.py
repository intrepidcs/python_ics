# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

try: # 4
    from s_rad_gigalog_sub_cmd_hdr import s_rad_gigalog_sub_cmd_hdr
    from srad_gigalog_disk_structure import srad_gigalog_disk_structure
    from srad_gigalog_disk_details import srad_gigalog_disk_details
    from srad_gigalog_disk_format_progress import srad_gigalog_disk_format_progress
except:
    from ics.structures.s_rad_gigalog_sub_cmd_hdr import s_rad_gigalog_sub_cmd_hdr
    from ics.structures.srad_gigalog_disk_structure import srad_gigalog_disk_structure
    from ics.structures.srad_gigalog_disk_details import srad_gigalog_disk_details
    from ics.structures.srad_gigalog_disk_format_progress import srad_gigalog_disk_format_progress

class s_rad_gigalog_comm(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('hdr', s_rad_gigalog_sub_cmd_hdr), 
        ('structure', srad_gigalog_disk_structure), 
        ('details', srad_gigalog_disk_details), 
        ('progress', srad_gigalog_disk_format_progress), 
    ]

# Extra names go here:
SRadGigalogComm = s_rad_gigalog_comm
# End of extra names

