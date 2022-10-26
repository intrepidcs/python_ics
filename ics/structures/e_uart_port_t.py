# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class e_uart_port_t(enum.IntEnum):
    """A ctypes-compatible IntEnum superclass."""
    @classmethod
    def from_param(cls, obj):
        return int(obj)

    eUART0  = 0
    eUART1 = enum.auto()


_EUartPort_t = e_uart_port_t
EUartPort_t = e_uart_port_t

