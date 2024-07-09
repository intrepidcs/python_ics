import unittest
import python_ics
from python_ics.py_neo_device_ex import PyNeoDeviceEx
from python_ics.structures.e_device_settings_type import e_device_settings_type

unittest.TestLoader.sortTestMethodsUsing = None


class BaseTests:
    """Base classes. These are isolated and won't be run/discovered. Used for inheritance"""

    class TestSettings(unittest.TestCase):
        @classmethod
        def setUpClass(cls):
            cls.device_type = None
            cls.device_settings_type = None

        def _get_device(self) -> PyNeoDeviceEx:
            devices = python_ics.find_devices([self.device_type])
            self.assertEqual(
                len(devices),
                1,
                f"Failed to find any device types of {self.device_type}! Expected 1, got {len(devices)}.",
            )
            return devices[0]

        def test_load_defaults(self):
            device = self._get_device()
            device.open()
            try:
                python_ics.load_default_settings(device)
            finally:
                device.close()

        def test_get_set_settings(self):
            device = self._get_device()
            device.open()
            try:
                python_ics.load_default_settings(device)
                settings = python_ics.get_device_settings(device)
                self.assertEqual(settings.DeviceSettingType, self.device_settings_type)
                python_ics.set_device_settings(device, settings)
                _ = python_ics.get_device_settings(device)
                # TODO: compare both settings
            finally:
                device.close()


class TestFire3Settings(BaseTests.TestSettings):
    @classmethod
    def setUpClass(cls):
        cls.device_type = python_ics.NEODEVICE_FIRE3
        cls.device_settings_type = e_device_settings_type.DeviceFire3SettingsType


class TestFire2Settings(BaseTests.TestSettings):
    @classmethod
    def setUpClass(cls):
        cls.device_type = python_ics.NEODEVICE_FIRE2
        cls.device_settings_type = e_device_settings_type.DeviceFire2SettingsType


class TestValueCAN42Settings(BaseTests.TestSettings):
    @classmethod
    def setUpClass(cls):
        cls.device_type = python_ics.NEODEVICE_VCAN42
        cls.device_settings_type = e_device_settings_type.DeviceVCAN412SettingsType


if __name__ == "__main__":
    unittest.main()
