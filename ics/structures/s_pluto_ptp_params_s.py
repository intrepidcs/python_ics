# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

class s_pluto_ptp_params_s(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('neighborPropDelayThresh', ctypes.c_uint32), # ns
        ('sys_phc_sync_interval', ctypes.c_uint32), # ns
        ('logPDelayReqInterval', ctypes.c_int8), # log2ms
        ('logSyncInterval', ctypes.c_int8), # log2ms
        ('logAnnounceInterval', ctypes.c_int8), # log2ms
        ('profile', ctypes.c_uint8), 
        ('priority1', ctypes.c_uint8), 
        ('clockclass', ctypes.c_uint8), 
        ('clockaccuracy', ctypes.c_uint8), 
        ('priority2', ctypes.c_uint8), 
        ('offset_scaled_log_variance', ctypes.c_uint16), 
        ('gPTPportRole', ctypes.c_uint8 * 4), # the 5th port is used for SAM
        ('portEnable', ctypes.c_uint8 * 4), # the 5th port is used for SAM
    ]

# Extra names go here:
PlutoPtpParams_t = s_pluto_ptp_params_s
# End of extra names

