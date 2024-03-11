# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class Nameless63799(ctypes.Structure):
    _pack_ = 1
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



class mac_sec_map_(ctypes.Union):
    _pack_ = 1
    _anonymous_  = ('Nameless63799',)
    _fields_ = [
        ('Nameless63799', Nameless63799),
        ('byte', ctypes.c_uint8 * 20),
    ]


_MACSecMap = mac_sec_map_
MACSecMap_t = mac_sec_map_
MACSecMap_ = mac_sec_map_

