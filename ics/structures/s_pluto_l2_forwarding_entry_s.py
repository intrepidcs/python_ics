# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class s_pluto_l2_forwarding_entry_s(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('vlan_pmap', ctypes.c_uint8 * 8),
        ('bc_domain', ctypes.c_uint8),
        ('reach_port', ctypes.c_uint8),
        ('fl_domain', ctypes.c_uint8),
        ('pad', ctypes.c_uint8),
    ]


SPluto_L2ForwardingEntry_s = s_pluto_l2_forwarding_entry_s
SPluto_L2ForwardingEntry = s_pluto_l2_forwarding_entry_s

