# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

class ethernet10_g_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('flags', ctypes.c_uint32), 
        ('ip_addr', ctypes.c_uint32), 
        ('netmask', ctypes.c_uint32), 
        ('gateway', ctypes.c_uint32), 
        ('link_speed', ctypes.c_uint8), # 0=10, 1=100, 2=1000, 3=2500, 4=5000, 5=10000
        ('rsvd2', ctypes.c_uint8 * 7), 
    ]

# Extra names go here:
ETHERNET10G_SETTINGS = ethernet10_g_settings
# End of extra names

