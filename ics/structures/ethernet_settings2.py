# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class ethernet_settings2(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('flags', ctypes.c_uint8),
        ('link_speed', ctypes.c_uint8),
        ('ip_addr', ctypes.c_uint32),
        ('netmask', ctypes.c_uint32),
        ('gateway', ctypes.c_uint32),
        ('flags2', ctypes.c_uint8),
        ('rsvd', ctypes.c_uint8),
    ]


ETHERNET_SETTINGS2_t = ethernet_settings2
ETHERNET_SETTINGS2 = ethernet_settings2

