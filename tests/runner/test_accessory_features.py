# ruff: noqa: E501
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
            return devices[0]
        
        def test_disk_functions(self):
            # ics.disk_format(device)
            # ics.disk_format_cancel(device)
            
            # ics.get_disk_details(device)
            # ics.get_disk_format_progress(device)
            
            # ics.read_sdcard()  # icsneoReadSDCard(), Accepts a PyNeoDeviceEx and sector index. Returns a bytearray of 512 bytes max. Exception on error.
            pass
        
        def test_radio_message(self):
            # ics.create_neovi_radio_message(.....)
            
            # ics.enable_bus_voltage_monitor(device, enable, reserved)
            # ics.enable_doip_line(device, enable)
            # ics.enable_network_com(device, enable, net_id)
            pass
        
        def test_generic_api(self):
            device = self._get_device()
            # ics.generic_api_get_status(device, api_index, instance_index)
            # ics.generic_api_read_data(device, api_index, instance_index[, length])
            # ics.generic_api_send_command(device, api_index, instance_index, function_index, data)
            
            # ics.get_last_api_error(device)
            
            
            # ics.get_active_vnet_channel(device)
            # ics.get_all_chip_versions(device, api_index, instance_index)
            
            # ics.get_backup_power_enabled(device)
            # ics.get_backup_power_ready(device)
            # ics.get_bus_voltage(device, reserved)
            
            # ics.get_device_status(device)  # Doesnt seem to work?? Script needs to be running first??
            ics.get_script_status(device)  # Documentation needs updating to include "device" parameter
            
            msg = ics.SpyMessage()
            tmstmp = ics.get_timestamp_for_msg(device, msg)
            self.assertEqual(tmstmp, 0.0)  # TODO verify this actually works
        
        def test_firmware_info(self):
            device = self._get_device()
            
            ics.get_dll_firmware_info(device)
            ics.get_dll_version(device)
            # ics.get_gptp_status(device)
            ics.get_hw_firmware_info(device)
            
            ics.get_pcb_serial_number(device)
            ics.get_serial_number(device)
            
            # ics.get_performance_parameters(device)
            # ics.get_rtc(device)
            
            # ics.iso15765_disable_networks(device)
            # ics.iso15765_enable_networks(device, networks)


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
