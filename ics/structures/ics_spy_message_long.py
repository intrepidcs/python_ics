# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

# _U12
class _U12(ctypes.Union):
    _fields_ = [
        ('StatusBitField3', ctypes.c_uint32), 
        ('StatusBitField4', ctypes.c_uint32), 
        ('AckBytes', ctypes.c_uint8 * 8), 
    ]

# Extra names go here:
# End of extra names

class ics_spy_message_long(ctypes.Structure):
    _anonymous_ = ("_U12",)
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
        ('DataMsb', ctypes.c_uint32), 
        ('DataLsb', ctypes.c_uint32), 
        ('_U12', _U12), 
        ('ExtraDataPtr', ctypes.c_voidp), 
        ('MiscData', ctypes.c_uint8), 
        ('Reserved', ctypes.c_uint8 * 3), 
    ]

# Extra names go here:
icsSpyMessageLong = ics_spy_message_long
# End of extra names

