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
        
        def test_coremini_load_clear(self):
            # ics.coremini_clear(device, location)  # location = ics.ics.SCRIPT_LOCATION_FLASH_MEM, ics.ics.SCRIPT_LOCATION_SDCARD, or ics.ics.SCRIPT_LOCATION_VCAN3_MEM
            # ics.coremini_get_fblock_status(device, index)  # index (int): Index of the function block
            # ics.coremini_get_status(device)  # True if running, otherwise False
            # ics.coremini_load(device, coremini, location)  # coremini (str/tuple): Use string to load from file, Use Tuple if file data.
            # ics.coremini_read_app_signal(device, index)  # index (int): Index of the application signal. Returns: float on Success
            # ics.coremini_read_rx_message(device, index, j1850=False)
            # ics.coremini_read_tx_message(device, index, j1850=False)
            # ics.coremini_start(device, location)
            # ics.coremini_start_fblock(device, index)
            # ics.coremini_stop(device)
            # ics.coremini_stop_fblock(device, index)
            # ics.coremini_write_app_signal(device, index, value)
            # ics.coremini_write_rx_message(device, index, TODO)  # TODO???
            # ics.coremini_write_tx_message(device, index, msg)  # TODO???
            # ics.create_neovi_radio_message(.....)
            # ics.disk_format(device)
            # ics.disk_format_cancel(device)
            # ics.enable_bus_voltage_monitor(device, enable, reserved)
            # ics.enable_doip_line(device, enable)
            # ics.enable_network_com(device, enable, net_id)
            # ics.firmware_update_required(device)
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
            pass
        
        def test_coremini_execute(self):
            pass
        
        def test_coremini_start_stop(self):
            pass

class TestRADMoon2Settings(BaseTests.TestSettings):
    @classmethod
    def setUpClass(cls):
        cls.device_type = ics.NEODEVICE_RADMOON2
        cls.device_settings_type = e_device_settings_type.DeviceRADMoon2SettingsType
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
        cls.device_settings_type = e_device_settings_type.DeviceVCAN412SettingsType
        cls.num_devices = 1
        print("DEBUG: Testing VCAN42...")


if __name__ == "__main__":
    unittest.main()
