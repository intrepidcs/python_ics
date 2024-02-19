# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.s_wil_fault_servicing_settings import *
from ics.structures.s_wil_network_data_capture_settings import *


class s_wil_connection_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('using_port_a', ctypes.c_uint8),
        ('using_port_b', ctypes.c_uint8),
        ('attemptConnect', ctypes.c_uint8),
        ('fault_servicing_config', sWIL_FAULT_SERVICING_SETTINGS),
        ('network_data_capture_config', sWIL_NETWORK_DATA_CAPTURE_SETTINGS),
        ('sensor_buffer_size', ctypes.c_uint16),
    ]


_sWIL_CONNECTION_SETTINGS = s_wil_connection_settings
sWIL_CONNECTION_SETTINGS = s_wil_connection_settings

