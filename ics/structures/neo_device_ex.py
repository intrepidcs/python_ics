# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

try: # 1
    from neo_device import neo_device
except:
    from ics.structures.neo_device import neo_device

class neo_device_ex(ctypes.Structure):
    _fields_ = [
        ('neoDevice', neo_device), 
        ('FirmwareMajor', ctypes.c_uint32), 
        ('FirmwareMinor', ctypes.c_uint32), 
        ('Status', ctypes.c_uint32), # Bitfield, see defs above
        ('Options', ctypes.c_uint32), 
        ('pAvailWIFINetwork', ctypes.c_voidp), 
        ('pWIFIInterfaceInfo', ctypes.c_voidp), 
        ('isEthernetDevice', ctypes.c_int), 
        ('MACAddress', ctypes.c_uint8 * 6), 
        ('hardwareRev', ctypes.c_uint16), 
        ('revReserved', ctypes.c_uint16), 
        ('Reserved', ctypes.c_uint32 * 6), # may be expanded in future revisions
    ]

# Extra names go here:
NeoDeviceEx = neo_device_ex
# End of extra names

