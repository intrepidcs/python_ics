# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.ethernet_network_status_t import *


class ics_rad_moon_duo_device_status(ctypes.Structure):
    _fields_ = [
        ('ethernetStatus', ethernetNetworkStatus_t * 4),
    ]


icsRadMoonDuoDeviceStatus = ics_rad_moon_duo_device_status

