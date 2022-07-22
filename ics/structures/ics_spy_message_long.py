# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class Nameless9992(ctypes.Structure):
    _fields_ = [
        ('StatusBitField3', ctypes.c_uint32),
        ('StatusBitField4', ctypes.c_uint32),
    ]



class Nameless65087(ctypes.Union):
    _anonymous_  = ('Nameless9992',)
    _fields_ = [
        ('Nameless9992', Nameless9992),
        ('AckBytes', ctypes.c_uint8 * 8),
    ]



class ics_spy_message_long(ctypes.Structure):
    _anonymous_  = ('Nameless65087',)
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
        ('DescriptionID', ctypes.c_uint16),
        ('ArbIDOrHeader', ctypes.c_uint32),
        ('DataMsb', ctypes.c_uint32),
        ('DataLsb', ctypes.c_uint32),
        ('Nameless65087', Nameless65087),
        ('ExtraDataPtr', ctypes.c_void_p),
        ('MiscData', ctypes.c_uint8),
        ('Reserved', ctypes.c_uint8 * 3),
    ]


_icsSpyMessageLong = ics_spy_message_long
icsSpyMessageLong = ics_spy_message_long

