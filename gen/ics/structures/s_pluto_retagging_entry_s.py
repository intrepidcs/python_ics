# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class s_pluto_retagging_entry_s(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('vlan_egr', ctypes.c_uint16),
        ('vlan_ing', ctypes.c_uint16),
        ('egr_port', ctypes.c_uint8),
        ('ing_port', ctypes.c_uint8),
        ('do_not_learn', ctypes.c_uint8),
        ('use_dest_ports', ctypes.c_uint8),
        ('destports', ctypes.c_uint8),
        ('pad', ctypes.c_uint8),
    ]


SPluto_RetaggingEntry_s = s_pluto_retagging_entry_s
SPluto_RetaggingEntry = s_pluto_retagging_entry_s

