# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class a2_b_node_type(enum.IntEnum):
    """A ctypes-compatible IntEnum superclass."""
    @classmethod
    def from_param(cls, obj):
        return int(obj)

    a2bNodeTypeMonitor  = 0
    a2bNodeTypeMaster = enum.auto()
    a2bNodeTypeSlave = enum.auto()


A2BNodeType = a2_b_node_type

