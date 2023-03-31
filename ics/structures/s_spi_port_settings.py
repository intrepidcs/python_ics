# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class s_spi_port_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('port_a_onbaord_external', ctypes.c_uint8),
        ('port_b_onbaord_external', ctypes.c_uint8),
    ]


_sSPI_PORT_SETTINGS = s_spi_port_settings
sSPI_PORT_SETTINGS = s_spi_port_settings

