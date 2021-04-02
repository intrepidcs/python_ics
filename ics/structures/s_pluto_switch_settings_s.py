# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

try: # 10
    from s_extended_data_flash_header import s_extended_data_flash_header
    from s_pluto_l2_address_lookup_params_s import s_pluto_l2_address_lookup_params_s
    from s_pluto_l2_address_lookup_entry_s import s_pluto_l2_address_lookup_entry_s
    from s_pluto_l2_policing_s import s_pluto_l2_policing_s
    from s_pluto_l2_forwarding_params_s import s_pluto_l2_forwarding_params_s
    from s_pluto_l2_forwarding_entry_s import s_pluto_l2_forwarding_entry_s
    from s_pluto_vlan_lookup_s import s_pluto_vlan_lookup_s
    from s_pluto_mac_config_s import s_pluto_mac_config_s
    from s_pluto_general_params_s import s_pluto_general_params_s
    from s_pluto_retagging_entry_s import s_pluto_retagging_entry_s
except:
    from ics.structures.s_extended_data_flash_header import s_extended_data_flash_header
    from ics.structures.s_pluto_l2_address_lookup_params_s import s_pluto_l2_address_lookup_params_s
    from ics.structures.s_pluto_l2_address_lookup_entry_s import s_pluto_l2_address_lookup_entry_s
    from ics.structures.s_pluto_l2_policing_s import s_pluto_l2_policing_s
    from ics.structures.s_pluto_l2_forwarding_params_s import s_pluto_l2_forwarding_params_s
    from ics.structures.s_pluto_l2_forwarding_entry_s import s_pluto_l2_forwarding_entry_s
    from ics.structures.s_pluto_vlan_lookup_s import s_pluto_vlan_lookup_s
    from ics.structures.s_pluto_mac_config_s import s_pluto_mac_config_s
    from ics.structures.s_pluto_general_params_s import s_pluto_general_params_s
    from ics.structures.s_pluto_retagging_entry_s import s_pluto_retagging_entry_s

class s_pluto_switch_settings_s(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('flashHeader', s_extended_data_flash_header), 
        ('l2_addressLookupParams', s_pluto_l2_address_lookup_params_s), 
        ('l2_addressLookupEntries', s_pluto_l2_address_lookup_entry_s * 1024), 
        ('l2_policing', s_pluto_l2_policing_s * 45), 
        ('l2_forwardingParams', s_pluto_l2_forwarding_params_s), 
        ('l2_ForwardingEntries', s_pluto_l2_forwarding_entry_s * 13), 
        ('vlan_LookupEntries', s_pluto_vlan_lookup_s * 4096), 
        ('macConfig', s_pluto_mac_config_s * 5), 
        ('generalParams', s_pluto_general_params_s), 
        ('retagging', s_pluto_retagging_entry_s * 32), 
    ]

# Extra names go here:
SPlutoSwitchSettings = s_pluto_switch_settings_s
# End of extra names

