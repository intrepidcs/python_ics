# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class nameless7476(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('invert_tx', ctypes.c_uint, 1),
        ('invert_rx', ctypes.c_uint, 1),
        ('half_duplex', ctypes.c_uint, 1),
        ('reserved_bits', ctypes.c_uint, 13),
        ('reserved_bits2', ctypes.c_uint, 16),
    ]



class nameless308(ctypes.Union):
    _pack_ = 2
    _anonymous_  = ('nameless7476',)
    _fields_ = [
        ('bOptions', ctypes.c_uint32),
        ('nameless7476', nameless7476),
    ]



class uart_settings(ctypes.Structure):
    _pack_ = 2
    _anonymous_  = ('nameless308',)
    _fields_ = [
        ('Baudrate', ctypes.c_uint16),
        ('spbrg', ctypes.c_uint16),
        ('brgh', ctypes.c_uint16),
        ('parity', ctypes.c_uint16),
        ('stop_bits', ctypes.c_uint16),
        ('flow_control', ctypes.c_uint8),
        ('reserved_1', ctypes.c_uint8),
        ('nameless308', nameless308),
    ]


_UART_SETTINGS = uart_settings
UART_SETTINGS = uart_settings

