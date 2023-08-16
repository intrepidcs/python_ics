# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class fire_versions(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('mpic_maj', ctypes.c_uint8),
        ('mpic_min', ctypes.c_uint8),
        ('upic_maj', ctypes.c_uint8),
        ('upic_min', ctypes.c_uint8),
        ('lpic_maj', ctypes.c_uint8),
        ('lpic_min', ctypes.c_uint8),
        ('jpic_maj', ctypes.c_uint8),
        ('jpic_min', ctypes.c_uint8),
    ]



class plasma_fire_vnet(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('mpic_maj', ctypes.c_uint8),
        ('mpic_min', ctypes.c_uint8),
        ('core_maj', ctypes.c_uint8),
        ('core_min', ctypes.c_uint8),
        ('lpic_maj', ctypes.c_uint8),
        ('lpic_min', ctypes.c_uint8),
        ('hid_maj', ctypes.c_uint8),
        ('hid_min', ctypes.c_uint8),
    ]



class vcan3_versions(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('mpic_maj', ctypes.c_uint8),
        ('mpic_min', ctypes.c_uint8),
    ]



class vcanrf_versions(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('mpic_maj', ctypes.c_uint8),
        ('mpic_min', ctypes.c_uint8),
    ]



class radgalaxy_versions(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('zynq_core_major', ctypes.c_uint8),
        ('zynq_core_minor', ctypes.c_uint8),
    ]



class radstar2_versions(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('zynq_core_major', ctypes.c_uint8),
        ('zynq_core_minor', ctypes.c_uint8),
    ]



class vividcan_versions(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('mpic_maj', ctypes.c_uint8),
        ('mpic_min', ctypes.c_uint8),
        ('ext_flash_maj', ctypes.c_uint8),
        ('ext_flash_min', ctypes.c_uint8),
        ('nrf52_maj', ctypes.c_uint8),
        ('nrf52_min', ctypes.c_uint8),
    ]



class cmprobe_versions(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('zynq_core_major', ctypes.c_uint8),
        ('zynq_core_minor', ctypes.c_uint8),
    ]



class obd2pro_versions(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('mchip_major', ctypes.c_uint8),
        ('mchip_minor', ctypes.c_uint8),
        ('schip_major', ctypes.c_uint8),
        ('schip_minor', ctypes.c_uint8),
        ('core_major', ctypes.c_uint8),
        ('core_minor', ctypes.c_uint8),
    ]



class vcan41_versions(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('mchip_major', ctypes.c_uint8),
        ('mchip_minor', ctypes.c_uint8),
    ]



class vcan42_versions(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('mchip_major', ctypes.c_uint8),
        ('mchip_minor', ctypes.c_uint8),
    ]



class neoecu_avb_versions(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('mchip_major', ctypes.c_uint8),
        ('mchip_minor', ctypes.c_uint8),
    ]



class radsupermoon_versions(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('zynq_core_major', ctypes.c_uint8),
        ('zynq_core_minor', ctypes.c_uint8),
    ]



class radmoon2_versions(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('zynq_core_major', ctypes.c_uint8),
        ('zynq_core_minor', ctypes.c_uint8),
    ]



class radmoon2_z7010_versions(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('zynq_core_major', ctypes.c_uint8),
        ('zynq_core_minor', ctypes.c_uint8),
    ]



class radmoon3_versions(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('mchip_major', ctypes.c_uint8),
        ('mchip_minor', ctypes.c_uint8),
    ]



class pluto_versions(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('mchip_major', ctypes.c_uint8),
        ('mchip_minor', ctypes.c_uint8),
    ]



class radgigalog_versions(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('zynq_core_major', ctypes.c_uint8),
        ('zynq_core_minor', ctypes.c_uint8),
    ]



class radgigalog3_versions(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('zynq_core_major', ctypes.c_uint8),
        ('zynq_core_minor', ctypes.c_uint8),
    ]



class radgigastar_versions(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('zynq_core_major', ctypes.c_uint8),
        ('zynq_core_minor', ctypes.c_uint8),
    ]



class radgigastar_usbz_versions(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('zynq_core_major', ctypes.c_uint8),
        ('zynq_core_minor', ctypes.c_uint8),
    ]



class obd2lc_versions(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('mchip_major', ctypes.c_uint8),
        ('mchip_minor', ctypes.c_uint8),
        ('schip_major', ctypes.c_uint8),
        ('schip_minor', ctypes.c_uint8),
    ]



class jupiter_versions(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('mchip_major', ctypes.c_uint8),
        ('mchip_minor', ctypes.c_uint8),
    ]



class red2_versions(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('zchip_major', ctypes.c_uint8),
        ('zchip_minor', ctypes.c_uint8),
        ('schip_major', ctypes.c_uint8),
        ('schip_minor', ctypes.c_uint8),
    ]



class fire3_versions(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('zchip_major', ctypes.c_uint8),
        ('zchip_minor', ctypes.c_uint8),
        ('schip_major', ctypes.c_uint8),
        ('schip_minor', ctypes.c_uint8),
        ('vem_z_major', ctypes.c_uint8),
        ('vem_z_minor', ctypes.c_uint8),
    ]



class fire3_flexray_versions(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('zchip_major', ctypes.c_uint8),
        ('zchip_minor', ctypes.c_uint8),
        ('schip_major', ctypes.c_uint8),
        ('schip_minor', ctypes.c_uint8),
        ('vem_z_major', ctypes.c_uint8),
        ('vem_z_minor', ctypes.c_uint8),
        ('vem_f_major', ctypes.c_uint8),
        ('vem_f_minor', ctypes.c_uint8),
    ]



class rad_moon_duo_versions(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('mchip_major', ctypes.c_uint8),
        ('mchip_minor', ctypes.c_uint8),
    ]



class obd2dev_versions(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('mchip_major', ctypes.c_uint8),
        ('mchip_minor', ctypes.c_uint8),
        ('schip_major', ctypes.c_uint8),
        ('schip_minor', ctypes.c_uint8),
    ]



class ether_badge_versions(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('mchip_major', ctypes.c_uint8),
        ('mchip_minor', ctypes.c_uint8),
    ]



class rad_a2b_versions(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('zynq_core_major', ctypes.c_uint8),
        ('zynq_core_minor', ctypes.c_uint8),
    ]



class epsilon_versions(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('mchip_major', ctypes.c_uint8),
        ('mchip_minor', ctypes.c_uint8),
    ]



class rad_wbms_versions(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('mchip_major', ctypes.c_uint8),
        ('mchip_minor', ctypes.c_uint8),
        ('wil_major', ctypes.c_uint8),
        ('wil_minor', ctypes.c_uint8),
    ]



class rad_comet_versions(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('zynq_core_major', ctypes.c_uint8),
        ('zynq_core_minor', ctypes.c_uint8),
    ]



class st_chip_versions(ctypes.Union):
    _pack_ = 2
    _fields_ = [
        ('fire_versions', fire_versions),
        ('plasma_fire_vnet', plasma_fire_vnet),
        ('vcan3_versions', vcan3_versions),
        ('vcanrf_versions', vcanrf_versions),
        ('radgalaxy_versions', radgalaxy_versions),
        ('radstar2_versions', radstar2_versions),
        ('vividcan_versions', vividcan_versions),
        ('cmprobe_versions', cmprobe_versions),
        ('obd2pro_versions', obd2pro_versions),
        ('vcan41_versions', vcan41_versions),
        ('vcan42_versions', vcan42_versions),
        ('neoecu_avb_versions', neoecu_avb_versions),
        ('radsupermoon_versions', radsupermoon_versions),
        ('radmoon2_versions', radmoon2_versions),
        ('radmoon2_z7010_versions', radmoon2_z7010_versions),
        ('radmoon3_versions', radmoon3_versions),
        ('pluto_versions', pluto_versions),
        ('radgigalog_versions', radgigalog_versions),
        ('radgigalog3_versions', radgigalog3_versions),
        ('radgigastar_versions', radgigastar_versions),
        ('radgigastar_usbz_versions', radgigastar_usbz_versions),
        ('obd2lc_versions', obd2lc_versions),
        ('jupiter_versions', jupiter_versions),
        ('red2_versions', red2_versions),
        ('fire3_versions', fire3_versions),
        ('fire3_flexray_versions', fire3_flexray_versions),
        ('rad_moon_duo_versions', rad_moon_duo_versions),
        ('obd2dev_versions', obd2dev_versions),
        ('ether_badge_versions', ether_badge_versions),
        ('rad_a2b_versions', rad_a2b_versions),
        ('epsilon_versions', epsilon_versions),
        ('rad_wbms_versions', rad_wbms_versions),
        ('rad_comet_versions', rad_comet_versions),
    ]


_stChipVersions = st_chip_versions
stChipVersions = st_chip_versions

