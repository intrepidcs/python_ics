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
            
            device.close()
            
        def test_coremini_signals(self):
            
            # ics.coremini_read_app_signal(device, index)  # index (int): Index of the application signal. Returns: float on Success
            # ics.coremini_read_rx_message(device, index, j1850=False)
            # ics.coremini_read_tx_message(device, index, j1850=False)
            # ics.coremini_write_app_signal(device, index, value)
            # ics.coremini_write_rx_message(device, index, TODO)  # TODO???
            # ics.coremini_write_tx_message(device, index, msg)  # TODO???
            
            # ics.get_timestamp_for_msg(device, msg)
            pass

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
        cls.coremini_wait = 0.1  # sec to wait after stop/clear
        print("DEBUG: Testing VCAN42...")


if __name__ == "__main__":
    unittest.main()
