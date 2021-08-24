# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class e_plasma_ion_vnet_channel_t(enum.IntEnum):
    """A ctypes-compatible IntEnum superclass."""
    @classmethod
    def from_param(cls, obj):
        return int(obj)

    PlasmaIonVnetChannelMain = 0
    PlasmaIonVnetChannelA = enum.auto()
    PlasmaIonVnetChannelB = enum.auto()
    eSoftCore = enum.auto()
    eFpgaStatusResp = enum.auto()


_EPlasmaIonVnetChannel_t = e_plasma_ion_vnet_channel_t
EPlasmaIonVnetChannel_t = e_plasma_ion_vnet_channel_t

