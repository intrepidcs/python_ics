# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class s_ext_sub_cmd_hdr(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('command', ctypes.c_uint16),
        ('length', ctypes.c_uint16),
    ]


_SExtSubCmdHdr = s_ext_sub_cmd_hdr
SExtSubCmdHdr = s_ext_sub_cmd_hdr

