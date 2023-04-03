# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class config(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('onboard_external', ctypes.c_uint8, 1),
        ('type', ctypes.c_uint8, 1),
        ('mode', ctypes.c_uint8, 3),
        ('reserved', ctypes.c_uint8, 3),
    ]



class s_spi_port_setting(ctypes.Union):
    _pack_ = 2
    _fields_ = [
        ('byte', ctypes.c_uint8),
        ('config', config),
    ]


sSPI_PORT_SETTING = s_spi_port_setting

