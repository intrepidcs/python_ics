# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

class s_text_api_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('can1_tx_id', ctypes.c_uint32), 
        ('can1_rx_id', ctypes.c_uint32), 
        ('DWord', ctypes.c_uint32), 
        ('can2_tx_id', ctypes.c_uint32), 
        ('can2_rx_id', ctypes.c_uint32), 
        ('network_enables', ctypes.c_uint32), 
        ('can3_tx_id', ctypes.c_uint32), 
        ('can3_rx_id', ctypes.c_uint32), 
        ('can4_tx_id', ctypes.c_uint32), 
        ('can4_rx_id', ctypes.c_uint32), 
        ('reserved', ctypes.c_uint32 * 5), 
        ('bExtended', ctypes.c_uint32, 1), # [Bitfield] 
    ]

# Extra names go here:
STextAPISettings = s_text_api_settings
# End of extra names

