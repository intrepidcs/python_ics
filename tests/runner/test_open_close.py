import unittest
import ics


class TestOpenClose(unittest.TestCase):
    @classmethod
    def setUpClass(self):
        expected_dev_count = 3
        self.devices = ics.find_devices()
        self.assertEqual(len(self.devices), expected_dev_count, f"Expected {expected_dev_count}, found {len(self.devices)}...")

    @classmethod
    def setUp(self):
        pass  # time.sleep(2)

    @classmethod
    def tearDownClass(self):
        # For some reason tp_dealloc doesn't get called on
        # ics.NeoDevice when initialzed in setUpClass().
        # Lets force it here.
        del self.devices

    def test_find_fire3(self):
        devices = ics.find_devices([ics.NEODEVICE_FIRE3])
        self.assertTrue(len(devices) == 1)

    def test_find_fire2(self):
        devices = ics.find_devices([ics.NEODEVICE_FIRE2])
        self.assertTrue(len(devices) == 1)

    def test_find_vcan42(self):
        devices = ics.find_devices([ics.NEODEVICE_VCAN42])
        self.assertTrue(len(devices) == 1)

    def test_find_fire2_and_vcan42(self):
        devices = ics.find_devices([ics.NEODEVICE_FIRE2 | ics.NEODEVICE_VCAN42])
        self.assertTrue(len(devices) == 2)
    
    def test_open_close(self):
        for device in self.devices:
            d = ics.open_device(device)
            self.assertEquals(device, d)
            ics.close_device(d)

if __name__ == "__main__":
    unittest.main()