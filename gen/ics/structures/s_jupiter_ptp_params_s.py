# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class s_jupiter_ptp_params_s(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('neighborPropDelay', ctypes.c_uint32),
        ('initLogPDelayReqInterval', ctypes.c_int8),
        ('initLogSyncInterval', ctypes.c_int8),
        ('operationLogPDelayReqInterval', ctypes.c_int8),
        ('operationLogSyncInterval', ctypes.c_int8),
        ('gPTPportRole', ctypes.c_uint8 * 8),
    ]


SJupiterPtpParams_s = s_jupiter_ptp_params_s
JupiterPtpParams_t = s_jupiter_ptp_params_s

