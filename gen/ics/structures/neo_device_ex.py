# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.neo_device import *


class neo_device_ex(ctypes.Structure):
    _fields_ = [
        ('neoDevice', NeoDevice),
        ('FirmwareMajor', ctypes.c_uint32),
        ('FirmwareMinor', ctypes.c_uint32),
        ('Status', ctypes.c_uint32),
        ('Options', ctypes.c_uint32),
        ('pAvailWIFINetwork', ctypes.c_void_p),
        ('pWIFIInterfaceInfo', ctypes.c_void_p),
        ('isEthernetDevice', ctypes.c_int),
        ('MACAddress', ctypes.c_uint8 * 6),
        ('hardwareRev', ctypes.c_uint16),
        ('revReserved', ctypes.c_uint16),
        ('tcpIpAddress', ctypes.c_uint32 * 4),
        ('tcpPort', ctypes.c_uint16),
        ('Reserved0', ctypes.c_uint16),
        ('Reserved1', ctypes.c_uint32),
    ]


_NeoDeviceEx = neo_device_ex
NeoDeviceEx = neo_device_ex

