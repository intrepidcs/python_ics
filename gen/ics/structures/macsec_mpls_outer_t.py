# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class macsec_mpls_outer_t(ctypes.Structure):
    _pack_ = 1
    _fields_ = [
        ('MPLS_label', ctypes.c_uint32),
        ('exp', ctypes.c_uint8),
    ]


MACSEC_MPLS_OUTER_t = macsec_mpls_outer_t

