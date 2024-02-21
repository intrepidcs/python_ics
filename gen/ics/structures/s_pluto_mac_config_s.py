# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class s_pluto_mac_config_s(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('top', ctypes.c_uint16 * 8),
        ('base', ctypes.c_uint16 * 8),
        ('tp_delin', ctypes.c_uint16),
        ('tp_delout', ctypes.c_uint16),
        ('vlanid', ctypes.c_uint16),
        ('enabled', ctypes.c_uint8 * 8),
        ('ifg', ctypes.c_uint8),
        ('speed', ctypes.c_uint8),
        ('maxage', ctypes.c_uint8),
        ('vlanprio', ctypes.c_uint8),
        ('ing_mirr', ctypes.c_uint8),
        ('egr_mirr', ctypes.c_uint8),
        ('drpnona664', ctypes.c_uint8),
        ('drpdtag', ctypes.c_uint8),
        ('drpuntag', ctypes.c_uint8),
        ('retag', ctypes.c_uint8),
        ('dyn_learn', ctypes.c_uint8),
        ('egress', ctypes.c_uint8),
        ('ingress', ctypes.c_uint8),
        ('pad', ctypes.c_uint8),
    ]


SPluto_MacConfig_s = s_pluto_mac_config_s
SPluto_MacConfig = s_pluto_mac_config_s

