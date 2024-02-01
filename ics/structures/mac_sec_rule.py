# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.macsec_mpls_outer import *
from ics.structures.macsec_packet_type import *
from ics.structures.macsec_vlantag import *


class mac_sec_rule(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('index', ctypes.c_uint8),
        ('key_MAC_DA', ctypes.c_uint8 * 6),
        ('mask_MAC_DA', ctypes.c_uint8 * 6),
        ('key_MAC_SA', ctypes.c_uint8 * 6),
        ('mask_MAC_SA', ctypes.c_uint8 * 6),
        ('key_Ethertype', ctypes.c_uint16),
        ('mask_Ethertype', ctypes.c_uint16),
        ('key_vlantag_outer1', MACSEC_VLANTAG),
        ('key_MPLS_outer1', MACSEC_MPLS_OUTER),
        ('mask_vlantag_outer1', MACSEC_VLANTAG),
        ('mask_MPLS_outer1', MACSEC_MPLS_OUTER),
        ('key_vlantag_outer2', MACSEC_VLANTAG),
        ('key_MPLS_outer2', MACSEC_MPLS_OUTER),
        ('mask_vlantag_outer2', MACSEC_VLANTAG),
        ('mask_MPLS_outer2', MACSEC_MPLS_OUTER),
        ('key_bonus_data', ctypes.c_uint16),
        ('mask_bonus_data', ctypes.c_uint16),
        ('key_tag_match_bitmap', ctypes.c_uint8),
        ('mask_tag_match_bitmap', ctypes.c_uint8),
        ('key_packet_type', ctypes.c_int32),
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


MACSecRule_t = mac_sec_rule
MACSecRule = mac_sec_rule

