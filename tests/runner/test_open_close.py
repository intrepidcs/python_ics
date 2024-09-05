import time
import unittest
import ics

unittest.TestLoader.sortTestMethodsUsing = None


class TestOpenClose(unittest.TestCase):
    @classmethod
    def setUpClass(self):
        self.expected_dev_count = 5
        self.devices = ics.find_devices([ics.ics.NEODEVICE_FIRE2, ics.NEODEVICE_FIRE3, ics.NEODEVICE_VCAN42, ics.NEODEVICE_RADMOON2])

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
            f"Expected {self.expected_dev_count}, found {len(self.devices)} ({self.devices})...",
        )

    def test_find_moon2s(self):
        self._check_devices()
        devices = ics.find_devices([ics.NEODEVICE_RADMOON2])
        self.assertTrue(len(devices) == 2)
        self.assertEqual(devices[0].DeviceType, ics.NEODEVICE_RADMOON2)

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
    
    def test_find_fire3_and_moon2(self):
        self._check_devices()
        devices = ics.find_devices([ics.NEODEVICE_FIRE3, ics.NEODEVICE_RADMOON2])
        self.assertTrue(len(devices) == 3)

    def test_open_close(self):
        self._check_devices()
        for dev in self.devices:
            dev.AutoHandleClose = False
            self.assertEqual(dev.NumberOfClients, 0)
            self.assertEqual(dev.MaxAllowedClients, 1)        
            d = ics.open_device(dev)
            try:
                self.assertEqual(dev, d)
                self.assertEqual(dev.NumberOfClients, 1)
                self.assertEqual(dev.MaxAllowedClients, 1)

                self.assertEqual(d.NumberOfClients, 1)
                self.assertEqual(d.MaxAllowedClients, 1)
            finally:
                self.assertEqual(dev.NumberOfClients, 1)
                self.assertEqual(d.NumberOfClients, 1)
                ics.close_device(d)
                time.sleep(6)
                self.assertEqual(dev.NumberOfClients, 0)
                self.assertEqual(d.NumberOfClients, 0)

    def test_open_close_by_serial(self):
        # Open by serial number
        for dev in self.devices:
            d = ics.open_device(dev.SerialNumber)
            self.assertEqual(d.SerialNumber, dev.SerialNumber)
            ics.close_device(d)

    def test_open_close_first_found(self):
        # Open by first found
        first_devices = []
        for _ in range(self.expected_dev_count):
            try:
                d = ics.open_device()
                first_devices.append(d)
                self.assertEqual(d.NumberOfClients, 1, f"Device {d} failed to increment NumberOfClients after opening")  # TODO figure out why VCAN42 is failing to go to 1
            except ics.RuntimeError as ex:
                raise RuntimeError(f"Failed to open first found device on iteration {len(first_devices)}: {ex}")
        self.assertEqual(self.expected_dev_count, len(first_devices))
        # Close by API
        for device in first_devices:
            ics.close_device(device)
            self.assertEqual(device.NumberOfClients, 0, f"{device}", f"Device {d} failed to decrement NumberOfClients after closing")

    def test_open_close_10_times(self):
        for dev in self.devices:
            for x in range(10):
                try:
                    self.assertEqual(dev.NumberOfClients, 0)
                    ics.open_device(dev)
                    self.assertEqual(dev.NumberOfClients, 1)  # TODO figure out why VCAN42 is failing to go to 1
                    error_count = ics.close_device(dev)
                    self.assertEqual(dev.NumberOfClients, 0)
                    self.assertEqual(error_count, 0, f"Error count was not 0 on {dev} iteration {x}...")
                except Exception as ex:
                    print(f"Failed at iteration {x} {dev}: {ex}...")
                    raise ex
    
    def test_auto_close(self):
        devices = ics.find_devices()
        for dev in devices:
            ics.open_device(dev)
        del devices
        devices = ics.find_devices()
        for dev in devices:
            ics.open_device(dev)
        del devices

if __name__ == "__main__":
    unittest.main()
