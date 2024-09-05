import time
import unittest
import ics

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
        
        def test_coremini_load_start_clear(self):
            device = self._get_device()
            device.open()
            ics.coremini_clear(device, self.coremini_location)
            time.sleep(self.coremini_wait)
            self.assertFalse(ics.coremini_get_status(device))
            
            ics.coremini_load(device, self.coremini_path, self.coremini_location)
            ics.coremini_start(device, self.coremini_location)
            self.assertTrue(ics.coremini_get_status(device))
            
            ics.coremini_stop(device)
            time.sleep(self.coremini_wait)
            self.assertFalse(ics.coremini_get_status(device))
            
            ics.coremini_start(device, self.coremini_location)
            self.assertTrue(ics.coremini_get_status(device))
            time.sleep(2)
            
            ics.coremini_clear(device, self.coremini_location)
            time.sleep(self.coremini_wait)
            self.assertFalse(ics.coremini_get_status(device))
            
            for error in ics.get_error_messages(device):
                print("Coremini error: " + error)
            
            device.close()
        
        def test_coremini_fblock(self):
            device = self._get_device()
            device.open()
            ics.coremini_load(device, self.coremini_path, self.coremini_location)
            ics.coremini_start(device, self.coremini_location)
            self.assertTrue(ics.coremini_get_fblock_status(device, 0))  # coremini must be started otherwise fails
            self.assertTrue(ics.coremini_get_fblock_status(device, 1))
            
            ics.coremini_stop_fblock(device, 0)
            self.assertFalse(ics.coremini_get_fblock_status(device, 0))
            ics.coremini_start_fblock(device, 0)
            self.assertTrue(ics.coremini_get_fblock_status(device, 0))
            ics.coremini_stop_fblock(device, 1)
            self.assertFalse(ics.coremini_get_fblock_status(device, 1))
            ics.coremini_start_fblock(device, 1)
            self.assertTrue(ics.coremini_get_fblock_status(device, 1))
            
            ics.coremini_clear(device, self.coremini_location)
            time.sleep(self.coremini_wait)
            failed = None
            try:
                ics.coremini_get_fblock_status(device, 0)
                failed = False
            except:
                failed = True
            self.assertTrue(failed)
            
            for error in ics.get_error_messages(device):
                print("Coremini error: " + error)
            
            device.close()
        
        def test_coremini_signals(self):
            device = self._get_device()
            device.open()
            # using all white RGB LEDs coremini script to read signals
            ics.coremini_load(device, self.coremini_path, self.coremini_location)
            ics.coremini_start(device, self.coremini_location)
            
            self.assertEqual(ics.coremini_read_app_signal(device, 0), 255.0)
            self.assertEqual(ics.coremini_read_app_signal(device, 1), 255.0)
            self.assertEqual(ics.coremini_read_app_signal(device, 2), 255.0)
            failed = None
            try:
                ics.coremini_read_app_signal(device, 3)
                failed = False
            except:
                failed = True
            self.assertTrue(failed)
            
            ics.coremini_clear(device, self.coremini_location)
            time.sleep(self.coremini_wait)
            failed = None
            try:
                ics.coremini_read_app_signal(device, 0)
                failed = False
            except:
                failed = True
            self.assertTrue(failed)
            
            # using all black RGB LEDs coremini script -- TODO GENERATE VS3CMB!!
            # ics.coremini_load(device, self.coremini_path_off, self.coremini_location)
            # ics.coremini_start(device, self.coremini_location)
            
            # self.assertEqual(ics.coremini_read_app_signal(device, 0), 0.0)
            # self.assertEqual(ics.coremini_read_app_signal(device, 1), 0.0)
            # self.assertEqual(ics.coremini_read_app_signal(device, 2), 0.0)
            # failed = None
            # try:
            #     ics.coremini_read_app_signal(device, 3)
            #     failed = False
            # except:
            #     failed = True
            # self.assertTrue(failed)
            
            # write and read signals
            ics.coremini_load(device, self.coremini_path, self.coremini_location)
            ics.coremini_start(device, self.coremini_location)
            ics.coremini_write_app_signal(device, 0, 100.0)
            self.assertEqual(ics.coremini_read_app_signal(device, 0), 100.0)
            ics.coremini_write_app_signal(device, 1, 0.0)
            self.assertEqual(ics.coremini_read_app_signal(device, 1), 0.0)
            
            # write and read rx/tx messages
            # ics.coremini_write_rx_message(device, index, TODO)  # does this work?
            # ics.coremini_write_tx_message(device, index, msg)  # ?
            
            # ics.coremini_read_rx_message(device, index, j1850=False)  # ?
            # ics.coremini_read_tx_message(device, index, j1850=False)  # ?
            
            ics.coremini_clear(device, self.coremini_location)
            device.close()


# class TestRADMoon2Settings(BaseTests.TestSettings):
#     @classmethod
#     def setUpClass(cls):
#         cls.device_type = ics.NEODEVICE_RADMOON2
#         cls.num_devices = 2
#         print("DEBUG: Testing MOON2s...")

# HAVING ISSUES SETTING SETTINGS WITH THIS UNIT!
# class TestFire3Settings(BaseTests.TestSettings):
#     @classmethod
#     def setUpClass(cls):
#         cls.device_type = ics.NEODEVICE_FIRE3
#         cls.num_devices = 1
#         print("DEBUG: Testing FIRE3...")

# ISSUES CONNECTING TO THIS DEVICE AT ALL!!!
# class TestFire2Settings(BaseTests.TestSettings):
#     @classmethod
#     def setUpClass(cls):
#         cls.device_type = ics.NEODEVICE_FIRE2
#         cls.num_devices = 1
#         print("DEBUG: Testing FIRE2...")


class TestValueCAN42Settings(BaseTests.TestSettings):
    @classmethod
    def setUpClass(cls):
        cls.device_type = ics.NEODEVICE_VCAN42
        cls.num_devices = 1
        cls.coremini_location = ics.SCRIPT_LOCATION_FLASH_MEM
        cls.coremini_path = r"E:\Users\NCejka\Downloads\leds_white_v4_90.vs3cmb"
        cls.coremini_path_off = r"E:\Users\NCejka\Downloads\leds_off_v4_90.vs3cmb"
        cls.coremini_wait = 0.1  # sec to wait after stop/clear
        print("DEBUG: Testing VCAN42...")


if __name__ == "__main__":
    unittest.main()
