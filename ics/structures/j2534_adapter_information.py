# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class j2534_adapter_information(ctypes.Structure):
    _fields_ = [
        ('szName', ctypes.c_char * 128),
        ('szDeviceName', ctypes.c_char * 64),
        ('Status', ctypes.c_ulong),
        ('bMAC_Address', ctypes.c_ubyte * 6),
        ('bIPV6_Address', ctypes.c_ubyte * 16),
        ('bIPV4_Address', ctypes.c_ubyte * 4),
    ]


J2534_ADAPTER_INFORMATION = j2534_adapter_information

