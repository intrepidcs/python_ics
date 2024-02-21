# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class s_pluto_ptp_params_s(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('neighborPropDelayThresh', ctypes.c_uint32),
        ('sys_phc_sync_interval', ctypes.c_uint32),
        ('logPDelayReqInterval', ctypes.c_int8),
        ('logSyncInterval', ctypes.c_int8),
        ('logAnnounceInterval', ctypes.c_int8),
        ('profile', ctypes.c_uint8),
        ('priority1', ctypes.c_uint8),
        ('clockclass', ctypes.c_uint8),
        ('clockaccuracy', ctypes.c_uint8),
        ('priority2', ctypes.c_uint8),
        ('offset_scaled_log_variance', ctypes.c_uint16),
        ('gPTPportRole', ctypes.c_uint8 * 4),
        ('portEnable', ctypes.c_uint8 * 4),
    ]


SPlutoPtpParams_s = s_pluto_ptp_params_s
PlutoPtpParams_t = s_pluto_ptp_params_s

