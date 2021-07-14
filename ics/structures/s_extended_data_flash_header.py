# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class s_extended_data_flash_header(ctypes.Structure):
    _fields_ = [
        ('version', ctypes.c_uint16),
        ('chksum', ctypes.c_uint16),
        ('len', ctypes.c_uint32),
    ]


SExtendedDataFlashHeader = s_extended_data_flash_header
ExtendedDataFlashHeader_t = s_extended_data_flash_header

