# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.ethernet_network_status_t import *


class ics_fire3_device_status(ctypes.Structure):
    _pack_ = 4
    _fields_ = [
        ('ethernetActivationLineEnabled', ctypes.c_uint8),
        ('ethernetStatus', ethernetNetworkStatus_t),
        ('backupPowerGood', ctypes.c_uint8),
        ('backupPowerEnabled', ctypes.c_uint8),
        ('backupPowerPercent', ctypes.c_uint8),
        ('backupPowermV', ctypes.c_uint16),
    ]


icsFire3DeviceStatus = ics_fire3_device_status

