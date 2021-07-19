# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.can_settings import *
from ics.structures.lin_settings import *


class s_red_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('can1', CAN_SETTINGS),
        ('can2', CAN_SETTINGS),
        ('lin1', LIN_SETTINGS),
        ('lin2', LIN_SETTINGS),
    ]


_SRedSettings = s_red_settings
SRedSettings = s_red_settings

