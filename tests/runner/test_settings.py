import unittest
import ics
from ics.py_neo_device_ex import PyNeoDeviceEx

unittest.TestLoader.sortTestMethodsUsing = None


# class TestSettings(unittest.TestCase):
#     __test__ = False

#     @classmethod
#     def setUpClass(cls): 
#         cls.device_type = None

#     def _get_device(self) -> PyNeoDeviceEx:
#         devices = ics.find_devices([self.device_type])
#         self.assertEqual(len(devices), 1, f"Failed to find any devices {self.device_type}! Expected 1, got {len(devices)}.")
#         return devices[0]

#     def test_load_defaults(self):
#         device = self._get_device()
#         device.open()
#         try:
#             ics.load_default_settings(device)
#         finally:
#             device.close()

#     def test_get_set_settings(self):
#         device = self._get_device()
#         device.open()
#         try:
#             ics.load_default_settings(device)
#             settings = ics.get_device_settings(device)
#             ics.set_device_settings(device, settings)
#             read_back_settings = ics.get_device_settings(device)
#             # TODO: compare both settings
#         finally:
#             device.close()

# class TestFire3Settings(TestSettings):
#     __test__ = True

#     @classmethod
#     def setUpClass(cls): 
#         cls.device_type = ics.NEODEVICE_FIRE3

# class TestFire2Settings(TestSettings):
#     __test__ = True

#     @classmethod
#     def setUpClass(cls): 
#         cls.device_type = ics.NEODEVICE_FIRE2
        

# class TestValueCAN42Settings(TestSettings):
#     __test__ = True

#     @classmethod
#     def setUpClass(cls): 
#         cls.device_type = ics.NEODEVICE_VCAN42
        



if __name__ == "__main__":
    unittest.main()
