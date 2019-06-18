# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

class s_extended_data_flash_header(ctypes.Structure):
    _fields_ = [
        ('version', ctypes.c_uint16), 
        ('chksum', ctypes.c_uint16), 
        ('len', ctypes.c_uint32), 
    ]

# Extra names go here:
ExtendedDataFlashHeader_t = s_extended_data_flash_header
# End of extra names

