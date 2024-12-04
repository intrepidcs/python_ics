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
            pass

        def _get_device(self):
            devices = ics.find_devices([self.device_type])
            self.assertEqual(
                len(devices),
                self.num_devices,
                f"Failed to find correct number of devices of type {self.device_type}! Expected {self.num_devices}, got {len(devices)}.",
            )
            return devices[0]

        def test_dll_features(self):
            self.assertGreater(len(ics.get_library_path()), 0)
            self.assertGreater(
                ics.get_dll_version(), 0
            )  # Documentation for this needs to be updated -- does not take any device arg

        def test_device_dll_features(self):
            device = self._get_device()
            device.open()
            info = ics.get_dll_firmware_info(
                device
            )  # must be open! Only gives ief ver that dll has
            info_comp = device.get_dll_firmware_info()
            self.assertEqual(info.iAppMajor, info_comp.iAppMajor)
            self.assertEqual(info.iAppMinor, info_comp.iAppMinor)
            # device.close()
            time.sleep(4)
            # ics.get_device_status(device)
            # ics.get_last_api_error(device)  # TODO figure out best way to replicate api error to read

        def test_library_location(self):
            device = self._get_device()
            device = ics.open_device(device)
            path = ics.get_library_path()
            print(path)
            ics.override_library_name(r"./icsneo40-v2")
            path = ics.get_library_path()
            print(path)
            # need to put dlls in proper locations and write assertions

class TestValueCAN42Settings(BaseTests.TestSettings):
    @classmethod
    def setUpClass(cls):
        cls.device_type = ics.NEODEVICE_VCAN42
        cls.num_devices = 1
        print("DEBUG: Testing VCAN42...")


if __name__ == "__main__":
    unittest.main()
