# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.ethernet_network_status_t import *


class ics_rad_epsilon_device_status(ctypes.Structure):
    _fields_ = [
        ('ethernetStatus', ethernetNetworkStatus_t * 9),
    ]


icsRadEpsilonDeviceStatus = ics_rad_epsilon_device_status

