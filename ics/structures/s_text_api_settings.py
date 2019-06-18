# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

# can1_options
class can1_options(ctypes.Union):
    _pack_ = 2
    _fields_ = [
        ('bExtended', ctypes.c_uint32, 1), # [Bitfield] 
        ('DWord', ctypes.c_uint32), 
    ]

# Extra names go here:
# End of extra names

# can2_options
class can2_options(ctypes.Union):
    _pack_ = 2
    _fields_ = [
        ('bExtended', ctypes.c_uint32, 1), # [Bitfield] 
        ('DWord', ctypes.c_uint32), 
    ]

# Extra names go here:
# End of extra names

# can3_options
class can3_options(ctypes.Union):
    _pack_ = 2
    _fields_ = [
        ('bExtended', ctypes.c_uint32, 1), # [Bitfield] 
        ('DWord', ctypes.c_uint32), 
    ]

# Extra names go here:
# End of extra names

# can4_options
class can4_options(ctypes.Union):
    _pack_ = 2
    _fields_ = [
        ('bExtended', ctypes.c_uint32, 1), # [Bitfield] 
        ('DWord', ctypes.c_uint32), 
    ]

# Extra names go here:
# End of extra names

class s_text_api_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('can1_tx_id', ctypes.c_uint32), 
        ('can1_rx_id', ctypes.c_uint32), 
        ('can2_tx_id', ctypes.c_uint32), 
        ('can2_rx_id', ctypes.c_uint32), 
        ('network_enables', ctypes.c_uint32), 
        ('can3_tx_id', ctypes.c_uint32), 
        ('can3_rx_id', ctypes.c_uint32), 
        ('can4_tx_id', ctypes.c_uint32), 
        ('can4_rx_id', ctypes.c_uint32), 
        ('reserved', ctypes.c_uint32 * 5), 
        ('can1_options', can1_options), 
        ('can2_options', can2_options), 
        ('can3_options', can3_options), 
        ('can4_options', can4_options), 
    ]

# Extra names go here:
STextAPISettings = s_text_api_settings
# End of extra names

