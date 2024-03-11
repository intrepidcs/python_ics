# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.macsec_mpls_outer_t import *
from ics.structures.macsec_vlantag_t import *


class Nameless1916(ctypes.Structure):
    _pack_ = 1
    _fields_ = [
        ('index', ctypes.c_uint8),
        ('key_MAC_DA', ctypes.c_uint8 * 6),
        ('mask_MAC_DA', ctypes.c_uint8 * 6),
        ('key_MAC_SA', ctypes.c_uint8 * 6),
        ('mask_MAC_SA', ctypes.c_uint8 * 6),
        ('key_Ethertype', ctypes.c_uint16),
        ('mask_Ethertype', ctypes.c_uint16),
        ('key_vlantag_outer1', MACSEC_VLANTAG_t),
        ('key_MPLS_outer1', MACSEC_MPLS_OUTER_t),
        ('mask_vlantag_outer1', MACSEC_VLANTAG_t),
        ('mask_MPLS_outer1', MACSEC_MPLS_OUTER_t),
        ('key_vlantag_outer2', MACSEC_VLANTAG_t),
        ('key_MPLS_outer2', MACSEC_MPLS_OUTER_t),
        ('mask_vlantag_outer2', MACSEC_VLANTAG_t),
        ('mask_MPLS_outer2', MACSEC_MPLS_OUTER_t),
        ('key_bonus_data', ctypes.c_uint16),
        ('mask_bonus_data', ctypes.c_uint16),
        ('key_tag_match_bitmap', ctypes.c_uint8),
        ('mask_tag_match_bitmap', ctypes.c_uint8),
        ('key_packet_type', ctypes.c_uint8),
        ('mask_packet_type', ctypes.c_uint8),
        ('key_inner_vlan_type', ctypes.c_uint16),
        ('mask_inner_vlan_type', ctypes.c_uint16),
        ('key_outer_vlan_type', ctypes.c_uint16),
        ('mask_outer_vlan_type', ctypes.c_uint16),
        ('key_num_tags', ctypes.c_uint8),
        ('mask_num_tags', ctypes.c_uint8),
        ('key_express', ctypes.c_uint8),
        ('mask_express', ctypes.c_uint8),
        ('isMPLS', ctypes.c_uint8),
        ('rsvd', ctypes.c_uint8 * 5),
        ('enable', ctypes.c_uint8),
    ]



class mac_sec_rule_(ctypes.Union):
    _pack_ = 1
    _anonymous_  = ('Nameless1916',)
    _fields_ = [
        ('Nameless1916', Nameless1916),
        ('byte', ctypes.c_uint8 * 88),
    ]


_MACSecRule = mac_sec_rule_
MACSecRule_t = mac_sec_rule_
MACSecRule_ = mac_sec_rule_

