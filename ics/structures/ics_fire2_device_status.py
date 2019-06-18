# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

class ics_fire2_device_status(ctypes.Structure):
    _fields_ = [
        ('backupPowerGood', ctypes.c_uint8), 
        ('backupPowerEnabled', ctypes.c_uint8), 
        ('usbHostPowerEnabled', ctypes.c_uint8), 
        ('ethernetActivationLineEnabled', ctypes.c_uint8), 
    ]

# Extra names go here:
icsFire2DeviceStatus = ics_fire2_device_status
# End of extra names

