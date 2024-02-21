# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class e_gptp_port(enum.IntEnum):
    """A ctypes-compatible IntEnum superclass."""
    @classmethod
    def from_param(cls, obj):
        return int(obj)

    ePortDisabled  = 0
    ePortOpEth1  = 1
    ePortOpEth2  = 2
    ePortOpEth3  = 3
    ePortOpEth4  = 4
    ePortOpEth5  = 5
    ePortOpEth6  = 6
    ePortOpEth7  = 7
    ePortOpEth8  = 8
    ePortOpEth9  = 9
    ePortOpEth10  = 10
    ePortOpEth11  = 11
    ePortOpEth12  = 12
    ePortStdEth1  = 13
    ePortStdEth2  = 14


eGPTPPort = e_gptp_port

