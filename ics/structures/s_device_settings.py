# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

try: # 28
    from e_device_settings_type import e_device_settings_type
    from s_red_settings import s_red_settings
    from s_fire_settings import s_fire_settings
    from s_fire_vnet_settings import s_fire_vnet_settings
    from s_cyan_settings import s_cyan_settings
    from svcan3_settings import svcan3_settings
    from svcan4_settings import svcan4_settings
    from secu_settings import secu_settings
    from sievb_settings import sievb_settings
    from s_pendant_settings import s_pendant_settings
    from srad_galaxy_settings import srad_galaxy_settings
    from srad_star2_settings import srad_star2_settings
    from sobd2_sim_settings import sobd2_sim_settings
    from s_cm_probe_settings import s_cm_probe_settings
    from sobd2_pro_settings import sobd2_pro_settings
    from svcan412_settings import svcan412_settings
    from secu_avb_settings import secu_avb_settings
    from srad_super_moon_settings import srad_super_moon_settings
    from srad_moon2_settings import srad_moon2_settings
    from srad_pluto_settings import srad_pluto_settings
    from srad_gigalog_settings import srad_gigalog_settings
    from scan_hub_settings import scan_hub_settings
    from s_neo_ecu12_settings import s_neo_ecu12_settings
    from svcanrf_settings import svcanrf_settings
    from seevb_settings import seevb_settings
    from s_flex_vnetz_settings import s_flex_vnetz_settings
    from s_vivid_can_settings import s_vivid_can_settings
    from svcan4_ind_settings import svcan4_ind_settings
except:
    from ics.structures.e_device_settings_type import e_device_settings_type
    from ics.structures.s_red_settings import s_red_settings
    from ics.structures.s_fire_settings import s_fire_settings
    from ics.structures.s_fire_vnet_settings import s_fire_vnet_settings
    from ics.structures.s_cyan_settings import s_cyan_settings
    from ics.structures.svcan3_settings import svcan3_settings
    from ics.structures.svcan4_settings import svcan4_settings
    from ics.structures.secu_settings import secu_settings
    from ics.structures.sievb_settings import sievb_settings
    from ics.structures.s_pendant_settings import s_pendant_settings
    from ics.structures.srad_galaxy_settings import srad_galaxy_settings
    from ics.structures.srad_star2_settings import srad_star2_settings
    from ics.structures.sobd2_sim_settings import sobd2_sim_settings
    from ics.structures.s_cm_probe_settings import s_cm_probe_settings
    from ics.structures.sobd2_pro_settings import sobd2_pro_settings
    from ics.structures.svcan412_settings import svcan412_settings
    from ics.structures.secu_avb_settings import secu_avb_settings
    from ics.structures.srad_super_moon_settings import srad_super_moon_settings
    from ics.structures.srad_moon2_settings import srad_moon2_settings
    from ics.structures.srad_pluto_settings import srad_pluto_settings
    from ics.structures.srad_gigalog_settings import srad_gigalog_settings
    from ics.structures.scan_hub_settings import scan_hub_settings
    from ics.structures.s_neo_ecu12_settings import s_neo_ecu12_settings
    from ics.structures.svcanrf_settings import svcanrf_settings
    from ics.structures.seevb_settings import seevb_settings
    from ics.structures.s_flex_vnetz_settings import s_flex_vnetz_settings
    from ics.structures.s_vivid_can_settings import s_vivid_can_settings
    from ics.structures.svcan4_ind_settings import svcan4_ind_settings

class s_device_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('DeviceSettingType', ctypes.c_int), 
        ('red', s_red_settings), 
        ('fire', s_fire_settings), 
        ('firevnet', s_fire_vnet_settings), 
        ('cyan', s_cyan_settings), 
        ('vcan3', svcan3_settings), 
        ('vcan4', svcan4_settings), 
        ('ecu', secu_settings), 
        ('ievb', sievb_settings), 
        ('pendant', s_pendant_settings), 
        ('radgalaxy', srad_galaxy_settings), 
        ('radstar2', srad_star2_settings), 
        ('neoobd2_sim', sobd2_sim_settings), 
        ('cmprobe', s_cm_probe_settings), 
        ('obd2pro', sobd2_pro_settings), 
        ('vcan412', svcan412_settings), 
        ('vcan4_12', svcan412_settings), # backwards compatibility with older code
        ('neoecu_avb', secu_avb_settings), 
        ('radsupermoon', srad_super_moon_settings), 
        ('radmoon2', srad_moon2_settings), 
        ('pluto', srad_pluto_settings), 
        ('radgigalog', srad_gigalog_settings), 
        ('canhub', scan_hub_settings), 
        ('neoecu12', s_neo_ecu12_settings), 
        ('vcanrf', svcanrf_settings), 
        ('eevb', seevb_settings), 
        ('flexvnetz', s_flex_vnetz_settings), 
        ('vividcan', s_vivid_can_settings), 
        ('vcan4_ind', svcan4_ind_settings), 
    ]

# Extra names go here:
SDeviceSettings = s_device_settings
# End of extra names

