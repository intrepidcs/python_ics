# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class software_update_command(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('componentIdentifier', ctypes.c_uint32),
        ('commandType', ctypes.c_uint8),
        ('offset', ctypes.c_uint32),
        ('commandSizeOrProgress', ctypes.c_uint32),
        ('commandData', ctypes.c_uint8),
    ]


SoftwareUpdateCommand = software_update_command

