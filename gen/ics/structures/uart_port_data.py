# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class uart_port_data(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('len', ctypes.c_uint16),
        ('port', ctypes.c_uint8),
        ('bData', ctypes.c_uint8 * 256),
    ]


_UartPortData = uart_port_data
UartPortData = uart_port_data

