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
        
        def test_dll_features(self):
            ics.get_library_path()
            ics.get_dll_version()  # Documentation for this needs to be updated -- does not take any device arg
            
            device = self._get_device()
            device.open()
            info = ics.get_dll_firmware_info(device)  # must be open! Only gives ief ver that dll has
            print(f"DLL MCHIP IEF v{info.iAppMajor}.{info.iAppMinor}")
            device.close()
            
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
            
            # ics.get_pcb_serial_number(device)
            # ics.get_performance_parameters(device)
            # ics.get_rtc(device)
            # ics.get_script_status()  # Documentation needs updating to include "device" parameter
            # ics.get_serial_number(device)
            # ics.get_timestamp_for_msg(device, msg)


class TestSettings(BaseTests.TestSettings):
    @classmethod
    def setUpClass(cls):
        pass


if __name__ == "__main__":
    unittest.main()
