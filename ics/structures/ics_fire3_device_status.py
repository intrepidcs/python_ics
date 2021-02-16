# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

try: # 1
    from ethernet_network_status_t import ethernet_network_status_t
except:
    from ics.structures.ethernet_network_status_t import ethernet_network_status_t

class ics_fire3_device_status(ctypes.Structure):
    _fields_ = [
        ('ethernetActivationLineEnabled', ctypes.c_uint8), 
        ('ethernetStatus', ethernet_network_status_t), 
        ('unused', ctypes.c_uint8), 
    ]

# Extra names go here:
icsFire3DeviceStatus = ics_fire3_device_status
# End of extra names

