# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class Nameless44788(ctypes.Structure):
    _fields_ = [
        ('StatusBitField3', ctypes.c_uint32),
        ('StatusBitField4', ctypes.c_uint32),
    ]



class Nameless61357(ctypes.Union):
    _anonymous_  = ('Nameless44788',)
    _fields_ = [
        ('Nameless44788', Nameless44788),
        ('AckBytes', ctypes.c_uint8 * 8),
    ]



class ics_spy_message_vsb(ctypes.Structure):
    _anonymous_  = ('Nameless61357',)
    _fields_ = [
        ('StatusBitField', ctypes.c_uint32),
        ('StatusBitField2', ctypes.c_uint32),
        ('TimeHardware', ctypes.c_uint32),
        ('TimeHardware2', ctypes.c_uint32),
        ('TimeSystem', ctypes.c_uint32),
        ('TimeSystem2', ctypes.c_uint32),
        ('TimeStampHardwareID', ctypes.c_uint8),
        ('TimeStampSystemID', ctypes.c_uint8),
        ('NetworkID', ctypes.c_uint8),
        ('NodeID', ctypes.c_uint8),
        ('Protocol', ctypes.c_uint8),
        ('MessagePieceID', ctypes.c_uint8),
        ('ExtraDataPtrEnabled', ctypes.c_uint8),
        ('NumberBytesHeader', ctypes.c_uint8),
        ('NumberBytesData', ctypes.c_uint8),
        ('NetworkID2', ctypes.c_uint8),
        ('DescriptionID', ctypes.c_int16),
        ('ArbIDOrHeader', ctypes.c_uint32),
        ('Data', ctypes.c_uint8 * 8),
        ('Nameless61357', Nameless61357),
        ('ExtraDataPtr', ctypes.c_uint32),
        ('MiscData', ctypes.c_uint8),
        ('Reserved', ctypes.c_uint8 * 3),
    ]


_icsSpyMessageVSB = ics_spy_message_vsb
icsSpyMessageVSB = ics_spy_message_vsb

