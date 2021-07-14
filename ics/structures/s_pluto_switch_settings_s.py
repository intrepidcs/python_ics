# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.s_pluto_l2_forwarding_params import *
from ics.structures.s_pluto_vlan_lookup import *
from ics.structures.s_pluto_l2_policing import *
from ics.structures.s_pluto_mac_config import *
from ics.structures.s_pluto_l2_address_lookup_params import *
from ics.structures.extended_data_flash_header_t import *
from ics.structures.s_pluto_retagging_entry import *
from ics.structures.s_pluto_l2_address_lookup_entry import *
from ics.structures.s_pluto_general_params import *
from ics.structures.s_pluto_l2_forwarding_entry import *


class s_pluto_switch_settings_s(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('flashHeader', ExtendedDataFlashHeader_t),
        ('l2_addressLookupParams', SPluto_L2AddressLookupParams),
        ('l2_addressLookupEntries', SPluto_L2AddressLookupEntry * 1024),
        ('l2_policing', SPluto_L2Policing * 45),
        ('l2_forwardingParams', SPluto_L2ForwardingParams),
        ('l2_ForwardingEntries', SPluto_L2ForwardingEntry * 13),
        ('vlan_LookupEntries', SPluto_VlanLookup * 4096),
        ('macConfig', SPluto_MacConfig * 5),
        ('generalParams', SPluto_GeneralParams),
        ('retagging', SPluto_RetaggingEntry * 32),
    ]


SPlutoSwitchSettings_s = s_pluto_switch_settings_s
SPlutoSwitchSettings = s_pluto_switch_settings_s

