import string
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
            # self.assertEqual(
            #     len(devices),
            #     1,
            #     f"Failed to find any device types of {self.device_type}! Expected 1, got {len(devices)}.",
            # )
            return devices[0]

        def _setup_settings_map(self):
            """Stolen and defiled from Aws' device.py class"""
            # We need to map the Union type to the DeviceSettingType
            hw_names = []
            self.setting_map = {}
            # Grab all the settings structure names
            s = ics.s_device_settings.s_device_settings()
            for name in dir(s.Settings):
                if name.startswith("_"):
                    continue
                hw_names.append(name)
            # Grab a list of all the settings type enums
            hw_enums = [
                attr
                for attr in dir(e_device_settings_type)
                if not callable(getattr(e_device_settings_type, attr)) and not attr.startswith("__")
            ]
            # Match up the hw_names to the enums
            for settings_type in hw_enums:
                settings_type_hw_name = self.__remove_string_in_list(settings_type, ["Device", "SettingsType", "RAD"])
                if settings_type_hw_name == "fire2":
                    settings_type_hw_name = "cyan"
                for hw_name in hw_names:
                    new_hw_name = self.__remove_string_in_list(hw_name, ["neo", "_", "rad"])  # (-_-)
                    if new_hw_name == settings_type_hw_name:
                        self.setting_map[getattr(e_device_settings_type, settings_type)] = hw_name
        
        def __remove_string_in_list(self, o_str: string, str_list: list):
            """Stolen and defiled from Aws' device.py class"""
            for item in str_list:
                o_str = o_str.replace(item, "")
            return o_str.lower()
            
        def _get_device_settings(self, device):
            """Stolen and defiled from Aws' device.py class"""
            # Read the settings and determine DeviceSettingType
            settings = ics.get_device_settings(device)
            # Implementation error if we can't find the type in the setting map
            if settings.DeviceSettingType not in self.setting_map:
                raise NotImplementedError(f"{self}: Unknown setting type found for {settings.DeviceSettingType}")
            # Finally lets map the actual structure to the device_settings
            return getattr(settings.Settings, self.setting_map[settings.DeviceSettingType])
        
        def test_load_defaults(self):
            device = self._get_device()
            ics.open_device(device)
            try:
                ics.load_default_settings(device)
            finally:
                ics.close_device(device)
        
        def test_get_set_settings(self):
            self._setup_settings_map()
            device = self._get_device()
            ics.open_device(device)
            try:
                # load default settings and verify type
                ics.load_default_settings(device)
                default_settings = self._get_device_settings(device)
                self.assertEqual(default_settings.DeviceSettingType, self.device_settings_type)
                # change CAN1 term setting and verify
                device_settings = self._get_device_settings(device)
                device_settings.termination_enables = 0x1
                device_settings.termination_enables_1 = 0x1
                device_settings.canfd1.FDBaudrate = ics.BPS1000
                ics.set_device_settings(device, device_settings)
                
                verify_settings = self._get_device_settings(device)
                self.assertEqual(verify_settings.termination_enables, 0x1)
                self.assertEqual(verify_settings.termination_enables_1, 0x1)
                self.assertEqual(verify_settings.canfd1.FDBaudrate, ics.BPS1000)
                # verify setting default
                ics.load_default_settings(device)
                verify_default_settings = self._get_device_settings(device)
                self.assertEqual(verify_default_settings.termination_enables, default_settings.termination_enables)
                self.assertEqual(verify_default_settings.termination_enables_1, default_settings.termination_enables_1)
                self.assertEqual(verify_default_settings.canfd1.FDBaudrate, default_settings.canfd1.FDBaudrate)
                self.assertEqual(verify_default_settings, default_settings)
                
            finally:
                ics.close_device(device)



# class TestFire3Settings(BaseTests.TestSettings):
#     @classmethod
#     def setUpClass(cls):
#         cls.device_type = ics.NEODEVICE_FIRE3
#         cls.device_settings_type = e_device_settings_type.DeviceFire3SettingsType


# class TestFire2Settings(BaseTests.TestSettings):
#     @classmethod
#     def setUpClass(cls):
#         cls.device_type = ics.NEODEVICE_FIRE2
#         cls.device_settings_type = e_device_settings_type.DeviceFire2SettingsType


class TestValueCAN42Settings(BaseTests.TestSettings):
    @classmethod
    def setUpClass(cls):
        cls.device_type = ics.NEODEVICE_VCAN42
        cls.device_settings_type = e_device_settings_type.DeviceVCAN412SettingsType


# class TestRADMoon2Settings(BaseTests.TestSettings):
#     @classmethod
#     def setUpClass(cls):
#         cls.device_type = ics.NEODEVICE_RADMOON2
#         cls.device_settings_type = e_device_settings_type.DeviceRADMoon2SettingsType


if __name__ == "__main__":
    unittest.main()
