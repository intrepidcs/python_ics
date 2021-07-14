# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.ethernet_network_status_t import *


class ics_flex_vnetz_device_status(ctypes.Structure):
    _fields_ = [
        ('ethernetActivationLineEnabled', ctypes.c_uint8),
        ('ethernetStatus', ethernetNetworkStatus_t),
        ('unused', ctypes.c_uint8),
    ]


icsFlexVnetzDeviceStatus = ics_flex_vnetz_device_status

