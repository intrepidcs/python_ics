# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

class s_cm_probe_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('network_enables', ctypes.c_uint16), 
        ('network_enabled_on_boot', ctypes.c_uint16), 
    ]

# Extra names go here:
CmProbeSettings = s_cm_probe_settings
SCmProbeSettings = s_cm_probe_settings
# End of extra names

