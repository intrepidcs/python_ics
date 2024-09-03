import time
import unittest
import ics
# from ics.py_neo_device_ex import PyNeoDeviceEx
from ics.structures.e_device_settings_type import e_device_settings_type

unittest.TestLoader.sortTestMethodsUsing = None


class BaseTests:
    """Base classes. These are isolated and won't be run/discovered. Used for inheritance"""

    class TestSettings(unittest.TestCase):
        @classmethod
        def setUpClass(cls):
            cls.device_type = None
            cls.device_settings_type = None
        
        def _get_device(self):
            devices = ics.find_devices([self.device_type])
            self.assertEqual(
                len(devices),
                self.num_devices,
                f"Failed to find correct number of devices of type {self.device_type}! Expected {self.num_devices}, got {len(devices)}.",
            )
            return devices[0]
        
        def _get_device_specific_settings(self, base_settings):
            setting_map = {e_device_settings_type.DeviceFire3SettingsType: "fire3", e_device_settings_type.DeviceFire2SettingsType: "cyan", e_device_settings_type.DeviceVCAN412SettingsType: "vcan4_12", e_device_settings_type.DeviceRADMoon2SettingsType: "radmoon2"}
            return getattr(base_settings.Settings, setting_map[self.device_settings_type])
        
        def test_load_defaults(self):
            device = self._get_device()
            ics.open_device(device)
            try:
                ics.load_default_settings(device)
            finally:
                ics.close_device(device)
        
        def test_get_set_settings(self):
            sleep_time = 0.1  #sec
            device = self._get_device()
            ics.open_device(device)
            try:
                # load default settings and verify type
                ics.load_default_settings(device)
                time.sleep(sleep_time)
                base_settings = ics.get_device_settings(device)
                self.assertEqual(base_settings.DeviceSettingType, self.device_settings_type, f"Wrong settings type on {device}")
                # change HSCAN1 term setting and verify (other stuff if Moon2)
                device_settings = self._get_device_specific_settings(base_settings)
                if self.device_type != 5:
                    device_settings.canfd1.FDBaudrate = ics.BPS1000  # change CAN1 baudrate
                else:
                    device_settings.opEth1.link_spd = 0x1  # change ETH1 speed
                ics.set_device_settings(device, base_settings)
                time.sleep(sleep_time)
                verify_new_settings = self._get_device_specific_settings(ics.get_device_settings(device))
                if self.device_type != 5:
                    self.assertEqual(verify_new_settings.canfd1.FDBaudrate, ics.BPS1000, f"Failed to set settings on {device}")
                else:
                    self.assertEqual(verify_new_settings.opEth1.link_spd, 0x1, f"Failed to set settings on {device}")
                # verify setting default
                ics.load_default_settings(device)
                time.sleep(sleep_time)
                verify_default_settings = self._get_device_specific_settings(ics.get_device_settings(device))
                if self.device_type != 5:
                    self.assertEqual(verify_default_settings.canfd1.FDBaudrate, ics.BPS2000, f"Failed to load default settings on {device}")
                else:
                    self.assertEqual(verify_default_settings.opEth1.link_spd, 0x2, f"Failed to load default settings on {device}")
            finally:
                ics.close_device(device)

class TestRADMoon2Settings(BaseTests.TestSettings):
    @classmethod
    def setUpClass(cls):
        cls.device_type = ics.NEODEVICE_RADMOON2
        cls.device_settings_type = e_device_settings_type.DeviceRADMoon2SettingsType
        cls.num_devices = 2
        print("DEBUG: Testing MOON2s...")

# HAVING ISSUES SETTING SETTINGS WITH THIS UNIT!
# class TestFire3Settings(BaseTests.TestSettings):
#     @classmethod
#     def setUpClass(cls):
#         cls.device_type = ics.NEODEVICE_FIRE3
#         cls.device_settings_type = e_device_settings_type.DeviceFire3SettingsType
#         cls.num_devices = 1
#         print("DEBUG: Testing FIRE3...")

# ISSUES CONNECTING TO THIS DEVICE AT ALL!!!
# class TestFire2Settings(BaseTests.TestSettings):
#     @classmethod
#     def setUpClass(cls):
#         cls.device_type = ics.NEODEVICE_FIRE2
#         cls.device_settings_type = e_device_settings_type.DeviceFire2SettingsType
#         cls.num_devices = 1
#         print("DEBUG: Testing FIRE2...")


class TestValueCAN42Settings(BaseTests.TestSettings):
    @classmethod
    def setUpClass(cls):
        cls.device_type = ics.NEODEVICE_VCAN42
        cls.device_settings_type = e_device_settings_type.DeviceVCAN412SettingsType
        cls.num_devices = 1
        print("DEBUG: Testing VCAN42...")


if __name__ == "__main__":
    unittest.main()
