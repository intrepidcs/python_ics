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

    def test_open_close_by_serial(self):
        # Open by serial number
        for device in self.devices:
            d = ics.open_device(device.SerialNumber)
            self.assertEqual(d.SerialNumber, device.SerialNumber)
            ics.close_device(d)

    def test_open_close_first_found(self):
        # Open by first found
        first_devices = []
        for device in self.devices:
            first_devices.append(ics.open_device())
        self.assertEqual(len(self.devices), len(first_devices))
        # Close by API
        for device in first_devices:
            ics.close_device(device)

    def test_open_close_100_times(self):
        for device in self.devices:
            for x in range(100):
                ics.open_device(device)
                ics.close_device(device)


if __name__ == "__main__":
    unittest.main()
