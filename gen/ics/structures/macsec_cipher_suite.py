# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class macsec_cipher_suite(enum.IntEnum):
    """A ctypes-compatible IntEnum superclass."""
    @classmethod
    def from_param(cls, obj):
        return int(obj)

    MACSEC_CIPHER_GCM_AES_128  = 0
    MACSEC_CIPHER_GCM_AES_256  = 1
    MACSEC_CIPHER_GCM_AES_128_XPN  = 2
    MACSEC_CIPHER_GCM_AES_256_XPN  = 3


MACSEC_CIPHER_SUITE_t = macsec_cipher_suite
MACSEC_CIPHER_SUITE = macsec_cipher_suite

