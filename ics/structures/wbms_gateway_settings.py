# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class wbms_gateway_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('wbms1_network', ctypes.c_uint8),
        ('wbms1_canfd_enable', ctypes.c_uint8),
        ('wbms2_network', ctypes.c_uint8),
        ('wbms2_canfd_enable', ctypes.c_uint8),
        ('reserved', ctypes.c_uint16 * 6),
    ]


WBMSGatewaySettings = wbms_gateway_settings

