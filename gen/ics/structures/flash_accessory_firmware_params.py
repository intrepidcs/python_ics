# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class flash_accessory_firmware_params(ctypes.Structure):
    _pack_ = 1
    _fields_ = [
        ('apiVersion', ctypes.c_uint32),
        ('size', ctypes.c_uint32),
        ('index', ctypes.c_uint8),
        ('data', ctypes.POINTER(ctypes.c_uint8)),
        ('dataSize', ctypes.c_uint32),
    ]


_FlashAccessoryFirmwareParams = flash_accessory_firmware_params
FlashAccessoryFirmwareParams = flash_accessory_firmware_params

