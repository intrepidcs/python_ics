# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class s_pluto_vlan_lookup_s(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('vlanid', ctypes.c_uint16),
        ('ving_mirr', ctypes.c_uint8),
        ('vegr_mirr', ctypes.c_uint8),
        ('vmemb_port', ctypes.c_uint8),
        ('vlan_bc', ctypes.c_uint8),
        ('tag_port', ctypes.c_uint8),
        ('pad', ctypes.c_uint8),
    ]


SPluto_VlanLookup_s = s_pluto_vlan_lookup_s
SPluto_VlanLookup = s_pluto_vlan_lookup_s

