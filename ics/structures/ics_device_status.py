# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

try: # 3
    from ics_fire2_device_status import ics_fire2_device_status
    from ics_vcan4_device_status import ics_vcan4_device_status
    from ics_flex_vnetz_device_status import ics_flex_vnetz_device_status
except:
    from ics.structures.ics_fire2_device_status import ics_fire2_device_status
    from ics.structures.ics_vcan4_device_status import ics_vcan4_device_status
    from ics.structures.ics_flex_vnetz_device_status import ics_flex_vnetz_device_status

class ics_device_status(ctypes.Union):
    _fields_ = [
        ('fire2Status', ics_fire2_device_status), 
        ('vcan4Status', ics_vcan4_device_status), 
        ('flexVnetzStatus', ics_flex_vnetz_device_status), 
    ]

# Extra names go here:
icsDeviceStatus = ics_device_status
# End of extra names

