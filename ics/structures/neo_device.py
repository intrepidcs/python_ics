# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

class neo_device(ctypes.Structure):
    _fields_ = [
        ('DeviceType', ctypes.c_uint32), 
        ('Handle', ctypes.c_int32), 
        ('NumberOfClients', ctypes.c_int32), 
        ('SerialNumber', ctypes.c_int32), 
        ('MaxAllowedClients', ctypes.c_int32), 
    ]

# Extra names go here:
NeoDevice = neo_device
# End of extra names

