# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

from enum import IntEnum

class e_plasma_ion_vnet_channel_t(IntEnum):
    """A ctypes-compatible IntEnum superclass."""
    @classmethod
    def from_param(cls, obj):
        return int(obj)

    PlasmaIonVnetChannelMain = 0
    PlasmaIonVnetChannelA = 1
    PlasmaIonVnetChannelB = 2
    eSoftCore = 3
    eFpgaStatusResp = 4


# Extra names go here:
EPlasmaIonVnetChannel_t = e_plasma_ion_vnet_channel_t
# End of extra names

