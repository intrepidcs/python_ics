# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

try: # 1
    from ethernet_network_status_t import ethernet_network_status_t
except:
    from ics.structures.ethernet_network_status_t import ethernet_network_status_t

class ics_rad_moon_duo_device_status(ctypes.Structure):
    _fields_ = [
        ('ethernetStatus', ethernet_network_status_t * 4), 
    ]

# Extra names go here:
icsRadMoonDuoDeviceStatus = ics_rad_moon_duo_device_status
# End of extra names

