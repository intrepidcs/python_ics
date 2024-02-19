# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class device_feature(enum.IntEnum):
    """A ctypes-compatible IntEnum superclass."""
    @classmethod
    def from_param(cls, obj):
        return int(obj)

    networkDWCAN01 = 0
    networkDWCAN02 = enum.auto()
    networkDWCAN03 = enum.auto()
    networkDWCAN04 = enum.auto()
    networkDWCAN05 = enum.auto()
    networkDWCAN06 = enum.auto()
    networkDWCAN07 = enum.auto()
    networkDWCAN08 = enum.auto()
    networkTerminationDWCAN01 = enum.auto()
    networkTerminationDWCAN02 = enum.auto()
    networkTerminationDWCAN03 = enum.auto()
    networkTerminationDWCAN04 = enum.auto()
    networkTerminationDWCAN05 = enum.auto()
    networkTerminationDWCAN06 = enum.auto()
    networkTerminationDWCAN07 = enum.auto()
    networkTerminationDWCAN08 = enum.auto()
    enhancedFlashDriver = enum.auto()
    NUM_VALID_DEVICE_FEATURES = enum.auto()
    supportedFeatureMax  = 65535


DeviceFeature = device_feature

