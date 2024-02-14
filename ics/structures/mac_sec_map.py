# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class mac_sec_map(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('index', ctypes.c_uint8),
        ('sectag_sci', ctypes.c_uint64),
        ('secYIndex', ctypes.c_uint8),
        ('isControlPacket', ctypes.c_uint8),
        ('scIndex', ctypes.c_uint8),
        ('auxiliary_plcy', ctypes.c_uint8),
        ('ruleId', ctypes.c_uint8),
        ('rsvd', ctypes.c_uint8 * 5),
        ('enable', ctypes.c_uint8),
    ]


MACSecMap_t = mac_sec_map
MACSecMap = mac_sec_map

