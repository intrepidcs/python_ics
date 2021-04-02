# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

# _U0
class _U0(ctypes.Union):
    _pack_ = 2
    _fields_ = [
        ('bOptions', ctypes.c_uint32), 
        ('invert_tx', ctypes.c_uint32, 1), # [Bitfield] 
        ('invert_rx', ctypes.c_uint32, 1), # [Bitfield] 
        ('half_duplex', ctypes.c_uint32, 1), # [Bitfield] 
        ('reserved_bits', ctypes.c_uint32, 13), # [Bitfield] 
        ('reserved_bits2', ctypes.c_uint32, 16), # [Bitfield] 
    ]

# Extra names go here:
# End of extra names

class uart_settings(ctypes.Structure):
    _pack_ = 2
    _anonymous_ = ("_U0",)
    _fields_ = [
        ('Baudrate', ctypes.c_uint16), 
        ('spbrg', ctypes.c_uint16), 
        ('brgh', ctypes.c_uint16), 
        ('parity', ctypes.c_uint16), 
        ('stop_bits', ctypes.c_uint16), 
        ('flow_control', ctypes.c_uint8), 
        ('reserved_1', ctypes.c_uint8), 
        ('_U0', _U0), 
    ]

# Extra names go here:
UART_SETTINGS = uart_settings
# End of extra names

