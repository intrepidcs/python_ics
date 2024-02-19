# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class macsec_packet_type(enum.IntEnum):
    """A ctypes-compatible IntEnum superclass."""
    @classmethod
    def from_param(cls, obj):
        return int(obj)

    MACSEC_PACKET_NO_VLAN_OR_MPLS  = 0
    MACSEC_PACKET_SINGLE_VLAN  = 1
    MACSEC_PACKET_DUAL_VLAN  = 2
    MACSEC_PACKET_MPLS  = 3
    MACSEC_PACKET_SINGLE_VLAN_FOLLOW_BY_MPLS  = 4
    MACSEC_PACKET_DUAL_VLAN_FOLLOW_BY_MPLS  = 5
    MACSEC_PACKET_UNSUPPORTED_TYPE  = 6


MACSEC_PACKET_TYPE_t = macsec_packet_type
MACSEC_PACKET_TYPE = macsec_packet_type

