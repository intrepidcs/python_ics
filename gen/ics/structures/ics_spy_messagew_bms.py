# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class Nameless23244(ctypes.Structure):
    _fields_ = [
        ('', ctypes.c_uint32, 8),
        ('PacketType', ctypes.c_uint32, 8),
        ('PacketID', ctypes.c_uint32, 8),
        ('PacketSource', ctypes.c_uint32, 8),
    ]



class Nameless35608(ctypes.Union):
    _anonymous_  = ('Nameless23244',)
    _fields_ = [
        ('ArbIDOrHeader', ctypes.c_uint32),
        ('Nameless23244', Nameless23244),
    ]



class Nameless20259(ctypes.Structure):
    _fields_ = [
        ('APICode', ctypes.c_uint32, 8),
        ('', ctypes.c_uint32, 24),
    ]



class Nameless39357(ctypes.Union):
    _anonymous_  = ('Nameless20259',)
    _fields_ = [
        ('StatusBitField3', ctypes.c_uint32),
        ('Nameless20259', Nameless20259),
    ]



class Nameless20257(ctypes.Structure):
    _anonymous_  = ('Nameless39357',)
    _fields_ = [
        ('Nameless39357', Nameless39357),
        ('StatusBitField4', ctypes.c_uint32),
    ]



class Nameless60883(ctypes.Union):
    _anonymous_  = ('Nameless20257',)
    _fields_ = [
        ('Nameless20257', Nameless20257),
        ('AckBytes', ctypes.c_uint8 * 8),
    ]



class ics_spy_messagew_bms(ctypes.Structure):
    _anonymous_  = ('Nameless35608', 'Nameless60883')
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
        ('Nameless35608', Nameless35608),
        ('Data', ctypes.c_uint8 * 8),
        ('Nameless60883', Nameless60883),
        ('ExtraDataPtr', ctypes.c_void_p),
        ('MiscData', ctypes.c_uint8),
        ('Reserved', ctypes.c_uint8 * 3),
    ]


_icsSpyMessagewBMS = ics_spy_messagew_bms
icsSpyMessagewBMS = ics_spy_messagew_bms

