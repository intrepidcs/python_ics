# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class uart_port_port_bytes(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('len', ctypes.c_uint16),
        ('port', ctypes.c_uint8),
        ('flag', ctypes.c_uint8),
    ]


_UartPortPortBytes = uart_port_port_bytes
UartPortPortBytes = uart_port_port_bytes

