# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.ethernet_network_status_t import *


class ics_obd2_pro_device_status(ctypes.Structure):
    _fields_ = [
        ('ethernetStatus', ethernetNetworkStatus_t),
    ]


icsOBD2ProDeviceStatus = ics_obd2_pro_device_status

