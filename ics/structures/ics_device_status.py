# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

try: # 9
    from ics_fire2_device_status import ics_fire2_device_status
    from ics_vcan4_device_status import ics_vcan4_device_status
    from ics_flex_vnetz_device_status import ics_flex_vnetz_device_status
    from ics_fire3_device_status import ics_fire3_device_status
    from ics_rad_moon_duo_device_status import ics_rad_moon_duo_device_status
    from ics_rad_jupiter_device_status import ics_rad_jupiter_device_status
    from ics_obd2_pro_device_status import ics_obd2_pro_device_status
    from ics_rad_pluto_device_status import ics_rad_pluto_device_status
    from ics_vcan4_industrial_device_status import ics_vcan4_industrial_device_status
except:
    from ics.structures.ics_fire2_device_status import ics_fire2_device_status
    from ics.structures.ics_vcan4_device_status import ics_vcan4_device_status
    from ics.structures.ics_flex_vnetz_device_status import ics_flex_vnetz_device_status
    from ics.structures.ics_fire3_device_status import ics_fire3_device_status
    from ics.structures.ics_rad_moon_duo_device_status import ics_rad_moon_duo_device_status
    from ics.structures.ics_rad_jupiter_device_status import ics_rad_jupiter_device_status
    from ics.structures.ics_obd2_pro_device_status import ics_obd2_pro_device_status
    from ics.structures.ics_rad_pluto_device_status import ics_rad_pluto_device_status
    from ics.structures.ics_vcan4_industrial_device_status import ics_vcan4_industrial_device_status

class ics_device_status(ctypes.Union):
    _fields_ = [
        ('fire2Status', ics_fire2_device_status), 
        ('vcan4Status', ics_vcan4_device_status), 
        ('flexVnetzStatus', ics_flex_vnetz_device_status), 
        ('fire3Status', ics_fire3_device_status), 
        ('radMoonDuoStatus', ics_rad_moon_duo_device_status), 
        ('jupiterStatus', ics_rad_jupiter_device_status), 
        ('obd2proStatus', ics_obd2_pro_device_status), 
        ('plutoStatus', ics_rad_pluto_device_status), 
        ('vcan4indStatus', ics_vcan4_industrial_device_status), 
    ]

# Extra names go here:
icsDeviceStatus = ics_device_status
# End of extra names

