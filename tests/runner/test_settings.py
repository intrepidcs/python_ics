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
                1,
                f"Failed to find any device types of {self.device_type}! Expected 1, got {len(devices)}.",
            )
            return devices[0]

        def test_load_defaults(self):
            device = self._get_device()
            ics.open_device(device)
            try:
                ics.load_default_settings(device)
            finally:
                ics.close_device(device)

        def test_get_set_settings(self):
            device = self._get_device()
            ics.open_device(device)
            try:
                ics.load_default_settings(device)
                settings = ics.get_device_settings(device)
                self.assertEqual(settings.DeviceSettingType, self.device_settings_type)
                ics.set_device_settings(device, settings)
                _ = ics.get_device_settings(device)
                # TODO: compare both settings
            finally:
                ics.close_device(device)


class TestFire3Settings(BaseTests.TestSettings):
    @classmethod
    def setUpClass(cls):
        cls.device_type = ics.NEODEVICE_FIRE3
        cls.device_settings_type = e_device_settings_type.DeviceFire3SettingsType


class TestFire2Settings(BaseTests.TestSettings):
    @classmethod
    def setUpClass(cls):
        cls.device_type = ics.NEODEVICE_FIRE2
        cls.device_settings_type = e_device_settings_type.DeviceFire2SettingsType


class TestValueCAN42Settings(BaseTests.TestSettings):
    @classmethod
    def setUpClass(cls):
        cls.device_type = ics.NEODEVICE_VCAN42
        cls.device_settings_type = e_device_settings_type.DeviceVCAN412SettingsType


class TestRADMoon2Settings(BaseTests.TestSettings):
    @classmethod
    def setUpClass(cls):
        cls.device_type = ics.NEODEVICE_RADMOON2
        cls.device_settings_type = e_device_settings_type.DeviceRADMoon2SettingsType


if __name__ == "__main__":
    unittest.main()
