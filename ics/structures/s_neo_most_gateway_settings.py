# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

class s_neo_most_gateway_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('netId', ctypes.c_uint16), 
        ('zero0', ctypes.c_uint8), 
        ('Config', ctypes.c_uint8), 
    ]

# Extra names go here:
SNeoMostGatewaySettings = s_neo_most_gateway_settings
# End of extra names

