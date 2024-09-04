import unittest
import ics

unittest.TestLoader.sortTestMethodsUsing = None


def message_callback(msg, success):
    try:
        # print("message_callback:", msg, success)
        complete_msg = msg + ": " + str(success)
        print(complete_msg)
        # self.testUpdated.emit(self.current_test_name, str(self.parameters.sn_info.classic.tester), complete_msg)
    except Exception as ex:
        print(ex)


def reflash_callback(msg, progress):
    try:
        # print("reflash_callback:", msg, progress)
        complete_msg = msg + " " + str(progress) + "%"
        print(complete_msg)
        print(msg, progress)
    except Exception as ex:
        print(ex)


class BaseTests:
    """Base classes. These are isolated and won't be run/discovered. Used for inheritance"""

    class TestSettings(unittest.TestCase):
        def _get_device(self):
            devices = ics.find_devices([self.device_type])
            self.assertEqual(
                len(devices),
                self.num_devices,
                f"Failed to find correct number of devices of type {self.device_type}! Expected {self.num_devices}, got {len(devices)}.",
            )
            return devices[0]
        
        def test_update_firmware(self):
            device = self._get_device()
            device.open()
            # get firmware version
            print(device.Name, device.SerialNumber)
            info = ics.get_hw_firmware_info(device)  # must be open! Gives iefs ver, pcb rev, bootloader rev, manuf date
            print(f"MCHIP IEF v{info.iAppMajor}.{info.iAppMinor}")
            print(f"MCHIP BL v{info.iBootLoaderVersionMajor}.{info.iBootLoaderVersionMinor}")
            print(f"PCB Rev v{info.iBoardRevMajor}.{info.iBoardRevMinor}")
            print(f"Made {info.iManufactureMonth}/{info.iManufactureDay}/{info.iManufactureYear}")
            device.close()
            
            # first flash old firmware
            old_firmware_path = r"E:\Users\NCejka\Downloads\vcan42_mchip_v1_23.ief"
            iefs = {ics.VCAN42_MCHIP_ID: old_firmware_path}
            ics.set_reflash_callback(reflash_callback)
            ics.flash_devices(device, iefs, message_callback)  # device must be closed?!?!
            
            # check IEF version and that update is needed
            device.open()
            # info = ics.get_hw_firmware_info(device)
            # print(f"Flashed MCHIP IEF v{info.iAppMajor}.{info.iAppMinor}")
            # print("Firmware update needed: " + str(bool(ics.firmware_update_required(device))))
            self.assertEqual(1, ics.firmware_update_required(device))
            
            # then force firmware update
            ics.force_firmware_update(device)  # device needs to be open and will stay open!
            
            # check it again
            self.assertEqual(0, ics.firmware_update_required(device))
            device.close()
            
            # update with new iefs
            new_firmware_path = r"E:\Users\NCejka\Downloads\vcan42_mchip_v4_90.ief"
            iefs = {ics.VCAN42_MCHIP_ID: new_firmware_path}
            ics.flash_devices(device, iefs, message_callback)
            
            # check one last time
            device.open()
            self.assertEqual(0, ics.firmware_update_required(device))
            device.close()
            
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
