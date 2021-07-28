# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.s_cm_probe_settings import *
from ics.structures.s_cyan_settings import *
from ics.structures.s_ether_badge_settings import *
from ics.structures.s_fire3_settings import *
from ics.structures.s_fire_settings import *
from ics.structures.s_fire_vnet_settings import *
from ics.structures.s_flex_vnetz_settings import *
from ics.structures.s_neo_ecu12_settings import *
from ics.structures.s_pendant_settings import *
from ics.structures.s_rad_moon_duo_settings import *
from ics.structures.s_red_settings import *
from ics.structures.s_vivid_can_settings import *
from ics.structures.scan_hub_settings import *
from ics.structures.secu_avb_settings import *
from ics.structures.secu_settings import *
from ics.structures.seevb_settings import *
from ics.structures.sievb_settings import *
from ics.structures.sobd2_pro_settings import *
from ics.structures.sobd2_sim_settings import *
from ics.structures.srad_galaxy_settings import *
from ics.structures.srad_gigalog_settings import *
from ics.structures.srad_gigastar_settings import *
from ics.structures.srad_jupiter_settings import *
from ics.structures.srad_moon2_settings import *
from ics.structures.srad_pluto_settings import *
from ics.structures.srad_star2_settings import *
from ics.structures.srad_super_moon_settings import *
from ics.structures.srada2_b_settings import *
from ics.structures.svcan3_settings import *
from ics.structures.svcan412_settings import *
from ics.structures.svcan4_ind_settings import *
from ics.structures.svcan4_settings import *
from ics.structures.svcanrf_settings import *


class Nameless8267(ctypes.Union):
    _pack_ = 2
    _fields_ = [
        ('red', SRedSettings),
        ('fire', SFireSettings),
        ('firevnet', SFireVnetSettings),
        ('cyan', SCyanSettings),
        ('vcan3', SVCAN3Settings),
        ('vcan4', SVCAN4Settings),
        ('ecu', SECUSettings),
        ('ievb', SIEVBSettings),
        ('pendant', SPendantSettings),
        ('radgalaxy', SRADGalaxySettings),
        ('radstar2', SRADStar2Settings),
        ('neoobd2_sim', SOBD2SimSettings),
        ('cmprobe', SCmProbeSettings),
        ('obd2pro', SOBD2ProSettings),
        ('vcan412', SVCAN412Settings),
        ('vcan4_12', SVCAN412Settings),
        ('neoecu_avb', SECU_AVBSettings),
        ('radsupermoon', SRADSuperMoonSettings),
        ('radmoon2', SRADMoon2Settings),
        ('pluto', SRADPlutoSettings),
        ('radgigalog', SRADGigalogSettings),
        ('canhub', SCANHubSettings),
        ('neoecu12', SNeoECU12Settings),
        ('vcanrf', SVCANRFSettings),
        ('eevb', SEEVBSettings),
        ('flexvnetz', SFlexVnetzSettings),
        ('vividcan', SVividCANSettings),
        ('vcan4_ind', VCAN4IndSettings),
        ('radgigastar', SRADGigastarSettings),
        ('jupiter', SRADJupiterSettings),
        ('fire3', SFire3Settings),
        ('radmoonduo', SRadMoonDuoSettings),
        ('etherBadge', SEtherBadgeSettings),
        ('rad_a2b', SRADA2BSettings),
    ]



class global_settings(ctypes.Structure):
    _pack_ = 2
    _anonymous_  = ('Nameless8267',)
    _fields_ = [
        ('version', ctypes.c_uint16),
        ('len', ctypes.c_uint16),
        ('chksum', ctypes.c_uint16),
        ('Nameless8267', Nameless8267),
    ]


_GLOBAL_SETTINGS = global_settings
GLOBAL_SETTINGS = global_settings

