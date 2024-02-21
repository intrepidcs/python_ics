# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class s_neo_most_gateway_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('netId', ctypes.c_uint16),
        ('zero0', ctypes.c_uint8),
        ('Config', ctypes.c_uint8),
    ]


_SNeoMostGatewaySettings = s_neo_most_gateway_settings
SNeoMostGatewaySettings = s_neo_most_gateway_settings

