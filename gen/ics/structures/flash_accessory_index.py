# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class flash_accessory_index(enum.IntEnum):
    """A ctypes-compatible IntEnum superclass."""
    @classmethod
    def from_param(cls, obj):
        return int(obj)

    FLASH_ACCESSORY_EPSILON_SWITCH_A = 0
    FLASH_ACCESSORY_EPSILON_SWITCH_B = enum.auto()
    FLASH_ACCESSORY_EPSILON_10G_PHY1 = enum.auto()
    FLASH_ACCESSORY_EPSILON_10G_PHY2 = enum.auto()
    FLASH_ACCESSORY_EPSILON_10G_PHY1_PHY2 = enum.auto()


_flashAccessoryIndex = flash_accessory_index
flashAccessoryIndex = flash_accessory_index

