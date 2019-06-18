# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

try: # 1
    from iso9141_keyword2000_init_step import iso9141_keyword2000_init_step
except:
    from ics.structures.iso9141_keyword2000_init_step import iso9141_keyword2000_init_step

class iso9141_keyword2000_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('Baudrate', ctypes.c_uint32), 
        ('spbrg', ctypes.c_uint16), 
        ('brgh', ctypes.c_uint16), 
        ('init_steps', iso9141_keyword2000_init_step * 16), 
        ('init_step_count', ctypes.c_uint8), 
        ('p2_500us', ctypes.c_uint16), 
        ('p3_500us', ctypes.c_uint16), 
        ('p4_500us', ctypes.c_uint16), 
        ('chksum_enabled', ctypes.c_uint16), 
    ]

# Extra names go here:
ISO9141_KEYWORD2000_SETTINGS = iso9141_keyword2000_settings
# End of extra names

