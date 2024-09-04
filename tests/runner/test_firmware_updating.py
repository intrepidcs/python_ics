import unittest
import ics

unittest.TestLoader.sortTestMethodsUsing = None


class BaseTests:
    """Base classes. These are isolated and won't be run/discovered. Used for inheritance"""

    class TestSettings(unittest.TestCase):
        @classmethod
        def setUpClass(cls):
            pass
        
        @classmethod
        def setUp(self):
            devices = ics.find_devices([self.device_type])
            self.device = ics.open_device(devices[0])
            ics.load_default_settings(self.device)
        
        @classmethod
        def tearDown(self):
            ics.close_device(self.device)
        
        def test_update_firmware(self):
            # First flash old firmware, check it says update needed, then flash new w/ force firmware update, check again that it says no now
            ics.firmware_update_required(self.device)
            # ics.flash_accessory_firmware(device, data, index[, check_success])
            # ics.force_firmware_update(device)
            # ics.generic_api_get_status(device, api_index, instance_index)
            # ics.generic_api_read_data(device, api_index, instance_index[, length])
            # ics.generic_api_send_command(device, api_index, instance_index, function_index, data)
            # ics.get_accessory_firmware_version()
            # ics.get_active_vnet_channel(device)
            # ics.get_all_chip_versions(device, api_index, instance_index)
            # ics.get_backup_power_enabled(device)
            # ics.get_backup_power_ready(device)
            # ics.get_bus_voltage(device, reserved)
            # ics.get_device_status(device)
            # ics.get_disk_details(device)
            # ics.get_disk_format_progress(device)
            # ics.get_dll_firmware_info(device)
            # ics.get_dll_version(device)
            # ics.get_gptp_status(device)
            # ics.get_hw_firmware_info(device)
            # ics.get_last_api_error(device)
            # ics.get_library_path()
            # ics.get_pcb_serial_number(device)
            # ics.get_performance_parameters(device)
            # ics.get_rtc(device)
            # ics.get_script_status()  # Documentation needs updating to include "device" parameter
            # ics.get_serial_number(device)
            # ics.get_timestamp_for_msg(device, msg)


class TestRADMoon2Settings(BaseTests.TestSettings):
    @classmethod
    def setUpClass(cls):
        cls.device_type = ics.NEODEVICE_RADMOON2
        cls.num_devices = 2
        print("DEBUG: Testing MOON2s...")

# HAVING ISSUES SETTING SETTINGS WITH THIS UNIT!
# class TestFire3Settings(BaseTests.TestSettings):
#     @classmethod
#     def setUpClass(cls):
#         cls.device_type = ics.NEODEVICE_FIRE3
#         cls.device_settings_type = e_device_settings_type.DeviceFire3SettingsType
#         cls.num_devices = 1
#         print("DEBUG: Testing FIRE3...")

# ISSUES CONNECTING TO THIS DEVICE AT ALL!!!
# class TestFire2Settings(BaseTests.TestSettings):
#     @classmethod
#     def setUpClass(cls):
#         cls.device_type = ics.NEODEVICE_FIRE2
#         cls.device_settings_type = e_device_settings_type.DeviceFire2SettingsType
#         cls.num_devices = 1
#         print("DEBUG: Testing FIRE2...")


class TestValueCAN42Settings(BaseTests.TestSettings):
    @classmethod
    def setUpClass(cls):
        cls.device_type = ics.NEODEVICE_VCAN42
        cls.num_devices = 1
        print("DEBUG: Testing VCAN42...")


if __name__ == "__main__":
    unittest.main()
