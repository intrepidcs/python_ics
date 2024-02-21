# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class s_cm_probe_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('network_enables', ctypes.c_uint16),
        ('network_enabled_on_boot', ctypes.c_uint16),
    ]


_CmProbeSettings = s_cm_probe_settings
CmProbeSettings = s_cm_probe_settings
SCmProbeSettings = s_cm_probe_settings

