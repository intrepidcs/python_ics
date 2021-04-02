# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

class ethernet_network_status_t(ctypes.Structure):
    _fields_ = [
        ('networkId', ctypes.c_uint16), 
        ('linkStatus', ctypes.c_uint8), 
        ('linkFullDuplex', ctypes.c_uint8), 
        ('linkSpeed', ctypes.c_uint8), 
        ('linkMode', ctypes.c_uint8), 
    ]

# Extra names go here:
ethernetNetworkStatus_t = ethernet_network_status_t
# End of extra names

