# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class get_supported_features_response(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('cmdVersion', ctypes.c_uint16),
        ('numValidBits', ctypes.c_uint16),
        ('featureBitfields', ctypes.c_uint32),
    ]


GetSupportedFeaturesResponse = get_supported_features_response

