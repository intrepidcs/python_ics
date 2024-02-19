# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class uart_port_config(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('baudrate', ctypes.c_uint32),
        ('port', ctypes.c_uint8),
        ('reserve', ctypes.c_uint8 * 7),
    ]


_UartPortConfig = uart_port_config
UartPortConfig = uart_port_config

