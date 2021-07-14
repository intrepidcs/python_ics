# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class spy_filter_long(ctypes.Structure):
    _fields_ = [
        ('StatusValue', ctypes.c_uint32),
        ('StatusMask', ctypes.c_uint32),
        ('Status2Value', ctypes.c_uint32),
        ('Status2Mask', ctypes.c_uint32),
        ('Header', ctypes.c_uint32),
        ('HeaderMask', ctypes.c_uint32),
        ('MiscData', ctypes.c_uint32),
        ('MiscDataMask', ctypes.c_uint32),
        ('ByteDataMSB', ctypes.c_uint32),
        ('ByteDataLSB', ctypes.c_uint32),
        ('ByteDataMaskMSB', ctypes.c_uint32),
        ('ByteDataMaskLSB', ctypes.c_uint32),
        ('HeaderLength', ctypes.c_uint32),
        ('ByteDataLength', ctypes.c_uint32),
        ('NetworkID', ctypes.c_uint32),
        ('FrameMaster', ctypes.c_uint16),
        ('bUseArbIdRangeFilter', ctypes.c_uint8),
        ('bStuff2', ctypes.c_uint8),
        ('ExpectedLength', ctypes.c_uint32),
        ('NodeID', ctypes.c_uint32),
    ]


spyFilterLong = spy_filter_long

