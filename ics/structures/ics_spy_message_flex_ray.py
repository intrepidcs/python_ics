# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class nameless47718(ctypes.Structure):
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



class nameless30009(ctypes.Union):
    _anonymous_  = ('nameless47718',)
    _fields_ = [
        ('ArbIDOrHeader', ctypes.c_uint32),
        ('nameless47718', nameless47718),
    ]



class nameless50896(ctypes.Structure):
    _fields_ = [
        ('StatusBitField3', ctypes.c_uint32),
        ('StatusBitField4', ctypes.c_uint32),
    ]



class nameless34903(ctypes.Structure):
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



class nameless11546(ctypes.Union):
    _anonymous_  = ('nameless50896', 'nameless34903')
    _fields_ = [
        ('nameless50896', nameless50896),
        ('AckBytes', ctypes.c_uint8 * 8),
        ('nameless34903', nameless34903),
    ]



class ics_spy_message_flex_ray(ctypes.Structure):
    _anonymous_  = ('nameless30009', 'nameless11546')
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
        ('nameless30009', nameless30009),
        ('Data', ctypes.c_uint8 * 8),
        ('nameless11546', nameless11546),
        ('ExtraDataPtr', ctypes.c_void_p),
        ('MiscData', ctypes.c_uint8),
        ('Reserved', ctypes.c_uint8 * 3),
    ]


_icsSpyMessageFlexRay = ics_spy_message_flex_ray
icsSpyMessageFlexRay = ics_spy_message_flex_ray

