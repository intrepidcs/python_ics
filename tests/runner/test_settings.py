import unittest
import ics

unittest.TestLoader.sortTestMethodsUsing = None

class TestFIRE3Settings(unittest.TestCase):
    def _get_device(self) -> ics.NeoDevice:
        devices = ics.find_devices([ics.NEODEVICE_FIRE3])
        self.assertEqual(len(devices), 1, f"Failed to find any neoVI FIRE3 devices! Expected 1, got {len(devices)}.")
        return devices[0]

    def test_load_defaults(self):
        device = self._get_device()
        ics.load_default_settings(device)
        #settings = ics.get_device_settings(device)

    def test_get_set_settings(self):
        device = self._get_device()
        ics.load_default_settings(device)
        settings = ics.get_device_settings(device)
        ics.set_device_settings(device, settings)
        read_back_settings = ics.get_device_settings(device)
        # TODO: compare both settings



if __name__ == "__main__":
    unittest.main()
