# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class start_dhcp_server_command(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('networkId', ctypes.c_uint16),
        ('serverIpAddress', ctypes.c_uint32),
        ('subnetMask', ctypes.c_uint32),
        ('gatewayAddress', ctypes.c_uint32),
        ('startAddress', ctypes.c_uint32),
        ('endAddress', ctypes.c_uint32),
        ('leaseTime', ctypes.c_uint32),
        ('overwrite', ctypes.c_uint32),
    ]


_StartDHCPServerCommand = start_dhcp_server_command
StartDHCPServerCommand = start_dhcp_server_command

