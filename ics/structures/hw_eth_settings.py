# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.op_eth_general_settings import *


class hw_eth_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('General_Settings', OP_ETH_GENERAL_SETTINGS),
    ]


HW_ETH_SETTINGS_t = hw_eth_settings
HW_ETH_SETTINGS = hw_eth_settings

