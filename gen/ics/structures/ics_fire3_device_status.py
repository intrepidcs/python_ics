# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.ethernet_network_status_t import *


class ics_fire3_device_status(ctypes.Structure):
    _fields_ = [
        ('ethernetActivationLineEnabled', ctypes.c_uint8),
        ('ethernetStatus', ethernetNetworkStatus_t * 3),
        ('ethernetActivationLineEnabled_2', ctypes.c_uint8),
    ]


icsFire3DeviceStatus = ics_fire3_device_status

