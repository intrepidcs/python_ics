# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class Nameless14534(ctypes.Structure):
    _fields_ = [
        ('', ctypes.c_uint32, 8),
        ('PacketType', ctypes.c_uint32, 8),
        ('PacketID', ctypes.c_uint32, 8),
        ('PacketSource', ctypes.c_uint32, 8),
    ]



class Nameless18511(ctypes.Union):
    _anonymous_  = ('Nameless14534',)
    _fields_ = [
        ('ArbIDOrHeader', ctypes.c_uint32),
        ('Nameless14534', Nameless14534),
    ]



class Nameless40028(ctypes.Structure):
    _fields_ = [
        ('APICode', ctypes.c_uint32, 8),
        ('', ctypes.c_uint32, 24),
    ]



class Nameless59525(ctypes.Union):
    _anonymous_  = ('Nameless40028',)
    _fields_ = [
        ('StatusBitField3', ctypes.c_uint32),
        ('Nameless40028', Nameless40028),
    ]



class Nameless5189(ctypes.Structure):
    _anonymous_  = ('Nameless59525',)
    _fields_ = [
        ('Nameless59525', Nameless59525),
        ('StatusBitField4', ctypes.c_uint32),
    ]



class Nameless54558(ctypes.Union):
    _anonymous_  = ('Nameless5189',)
    _fields_ = [
        ('Nameless5189', Nameless5189),
        ('AckBytes', ctypes.c_uint8 * 8),
    ]



class ics_spy_messagew_bms(ctypes.Structure):
    _anonymous_  = ('Nameless18511', 'Nameless54558')
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
        ('Nameless18511', Nameless18511),
        ('Data', ctypes.c_uint8 * 8),
        ('Nameless54558', Nameless54558),
        ('ExtraDataPtr', ctypes.c_void_p),
        ('MiscData', ctypes.c_uint8),
        ('Reserved', ctypes.c_uint8 * 3),
    ]


_icsSpyMessagewBMS = ics_spy_messagew_bms
icsSpyMessagewBMS = ics_spy_messagew_bms

