# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class Nameless18844(ctypes.Structure):
    _fields_ = [
        ('id', ctypes.c_uint32, 12),
        ('res1', ctypes.c_uint32, 4),
        ('cycle', ctypes.c_uint32, 6),
        ('chA', ctypes.c_uint32, 1),
        ('chB', ctypes.c_uint32, 1),
        ('startup', ctypes.c_uint32, 1),
        ('sync', ctypes.c_uint32, 1),
        ('null_frame', ctypes.c_uint32, 1),
        ('payload_preamble', ctypes.c_uint32, 1),
        ('frame_reserved', ctypes.c_uint32, 1),
        ('dynamic', ctypes.c_uint32, 1),
    ]



class Nameless61974(ctypes.Union):
    _anonymous_  = ('Nameless18844',)
    _fields_ = [
        ('ArbIDOrHeader', ctypes.c_uint32),
        ('Nameless18844', Nameless18844),
    ]



class Nameless49459(ctypes.Structure):
    _fields_ = [
        ('StatusBitField3', ctypes.c_uint32),
        ('StatusBitField4', ctypes.c_uint32),
    ]



class Nameless21903(ctypes.Structure):
    _fields_ = [
        ('hcrc_msbs', ctypes.c_uint32, 3),
        ('res2', ctypes.c_uint32, 5),
        ('hcrc_lsbs', ctypes.c_uint32, 8),
        ('frame_len_12_5ns', ctypes.c_uint32, 16),
        ('fcrc0', ctypes.c_uint32, 8),
        ('fcrc1', ctypes.c_uint32, 8),
        ('fcrc2', ctypes.c_uint32, 8),
        ('tss_len_12_5ns', ctypes.c_uint32, 8),
    ]



class Nameless7100(ctypes.Union):
    _anonymous_  = ('Nameless49459', 'Nameless21903')
    _fields_ = [
        ('Nameless49459', Nameless49459),
        ('AckBytes', ctypes.c_uint8 * 8),
        ('Nameless21903', Nameless21903),
    ]



class ics_spy_message_flex_ray(ctypes.Structure):
    _anonymous_  = ('Nameless61974', 'Nameless7100')
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
        ('Nameless61974', Nameless61974),
        ('Data', ctypes.c_uint8 * 8),
        ('Nameless7100', Nameless7100),
        ('ExtraDataPtr', ctypes.c_void_p),
        ('MiscData', ctypes.c_uint8),
        ('Reserved', ctypes.c_uint8 * 3),
    ]


_icsSpyMessageFlexRay = ics_spy_message_flex_ray
icsSpyMessageFlexRay = ics_spy_message_flex_ray

