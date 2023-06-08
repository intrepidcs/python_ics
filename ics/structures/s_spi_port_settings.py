# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.s_spi_port_setting import *


class s_spi_port_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('port_a', sSPI_PORT_SETTING),
        ('port_b', sSPI_PORT_SETTING),
    ]


sSPI_PORT_SETTINGS = s_spi_port_settings

