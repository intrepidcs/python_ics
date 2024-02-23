import unittest
import ics


class TestOpenClose(unittest.TestCase):
    @classmethod
    def setUpClass(self):
        self.expected_dev_count = 3
        self.devices = ics.find_devices()

    @classmethod
    def setUp(self):
        pass

    @classmethod
    def tearDownClass(self):
        # For some reason tp_dealloc doesn't get called on
        # ics.NeoDevice when initialzed in setUpClass().
        # Lets force it here.
        del self.devices

    def _check_devices(self):
        self.assertEqual(
            len(self.devices),
            self.expected_dev_count,
            f"Expected {self.expected_dev_count}, found {len(self.devices)}...",
        )

    def test_find_fire3(self):
        self._check_devices()
        devices = ics.find_devices([ics.NEODEVICE_FIRE3])
        self.assertTrue(len(devices) == 1)

    def test_find_fire2(self):
        self._check_devices()
        devices = ics.find_devices([ics.NEODEVICE_FIRE2])
        self.assertTrue(len(devices) == 1)

    def test_find_vcan42(self):
        self._check_devices()
        devices = ics.find_devices([ics.NEODEVICE_VCAN42])
        self.assertTrue(len(devices) == 1)

    def test_find_fire2_and_vcan42(self):
        self._check_devices()
        devices = ics.find_devices([ics.NEODEVICE_FIRE2, ics.NEODEVICE_VCAN42])
        self.assertTrue(len(devices) == 2)

    def test_open_close(self):
        self._check_devices()
        for device in self.devices:
            d = ics.open_device(device)
            self.assertEqual(device, d)
            ics.close_device(d)


if __name__ == "__main__":
    unittest.main()
