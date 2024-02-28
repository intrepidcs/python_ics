import unittest
import ics

unittest.TestLoader.sortTestMethodsUsing = None


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
        self.assertEqual(devices[0].DeviceType, ics.NEODEVICE_FIRE3)

    def test_find_fire2(self):
        self._check_devices()
        devices = ics.find_devices([ics.NEODEVICE_FIRE2])
        self.assertTrue(len(devices) == 1)
        self.assertEqual(devices[0].DeviceType, ics.NEODEVICE_FIRE2)

    def test_find_vcan42(self):
        self._check_devices()
        devices = ics.find_devices([ics.NEODEVICE_VCAN42])
        self.assertTrue(len(devices) == 1)
        self.assertEqual(devices[0].DeviceType, ics.NEODEVICE_VCAN42)

    def test_find_fire2_and_vcan42(self):
        self._check_devices()
        devices = ics.find_devices([ics.NEODEVICE_FIRE2, ics.NEODEVICE_VCAN42])
        self.assertTrue(len(devices) == 2)

    def test_open_close(self):
        self._check_devices()
        for device in self.devices:
            self.assertEqual(device.NumberOfClients, 0)
            self.assertEqual(device.MaxAllowedClients, 1)
            d = ics.open_device(device)
            try:
                self.assertEqual(device, d)
                self.assertEqual(device.NumberOfClients, 1)
                self.assertEqual(device.MaxAllowedClients, 1)
            finally:
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
        for device in enumerate(self.devices):
            try:
                print(device)
                first_devices.append(ics.open_device())
            except ics.RuntimeError as ex:
                raise RuntimeError(f"Failed to open {device}... Iteration {len(first_devices)} ({ex})")
        self.assertEqual(len(self.devices), len(first_devices))
        # Close by API
        for device in first_devices:
            ics.close_device(device)

    def test_open_close_10_times(self):
        for device in self.devices:
            for x in range(10):
                try:
                    ics.open_device(device)
                    error_count = ics.close_device(device)
                    self.assertEqual(error_count, 0, "Error count was not 0 on {device} iteration {x}...")
                except Exception as ex:
                    print(f"Failed at iteration {x} {device}: {ex}...")

if __name__ == "__main__":
    unittest.main()
