# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.ics_fire2_device_status import *
from ics.structures.ics_fire3_device_status import *
from ics.structures.ics_flex_vnetz_device_status import *
from ics.structures.ics_obd2_pro_device_status import *
from ics.structures.ics_rad_bms_device_status import *
from ics.structures.ics_rad_epsilon_device_status import *
from ics.structures.ics_rad_jupiter_device_status import *
from ics.structures.ics_rad_moon_duo_device_status import *
from ics.structures.ics_rad_pluto_device_status import *
from ics.structures.ics_vcan4_device_status import *
from ics.structures.ics_vcan4_industrial_device_status import *


class ics_device_status(ctypes.Union):
    _pack_ = 4
    _fields_ = [
        ('fire2Status', icsFire2DeviceStatus),
        ('vcan4Status', icsVcan4DeviceStatus),
        ('flexVnetzStatus', icsFlexVnetzDeviceStatus),
        ('fire3Status', icsFire3DeviceStatus),
        ('radMoonDuoStatus', icsRadMoonDuoDeviceStatus),
        ('jupiterStatus', icsRadJupiterDeviceStatus),
        ('obd2proStatus', icsOBD2ProDeviceStatus),
        ('plutoStatus', icsRadPlutoDeviceStatus),
        ('epsilonStatus', icsRadEpsilonDeviceStatus),
        ('vcan4indStatus', icsVcan4IndustrialDeviceStatus),
        ('radBMSStatus', icsRadBMSDeviceStatus),
    ]


icsDeviceStatus = ics_device_status

