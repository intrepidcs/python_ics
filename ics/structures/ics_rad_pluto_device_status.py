# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

try: # 1
    from ethernet_network_status_t import ethernet_network_status_t
except:
    from ics.structures.ethernet_network_status_t import ethernet_network_status_t

class ics_rad_pluto_device_status(ctypes.Structure):
    _fields_ = [
        ('ethernetStatus', ethernet_network_status_t), 
    ]

# Extra names go here:
icsRadPlutoDeviceStatus = ics_rad_pluto_device_status
# End of extra names

