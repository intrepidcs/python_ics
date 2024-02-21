# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.op_eth_general_settings import *
from ics.structures.srad_gptp_settings_s import *


class srad_gptp_and_tap_settings_s(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('gPTP', RAD_GPTP_SETTINGS),
        ('tap', OP_ETH_GENERAL_SETTINGS),
    ]


SRAD_GPTP_AND_TAP_SETTINGS_s = srad_gptp_and_tap_settings_s
RAD_GPTP_AND_TAP_SETTINGS = srad_gptp_and_tap_settings_s

