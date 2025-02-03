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

        def _test_update_firmware(self):
            device = self._get_device()
            device.open()
            # get firmware version
            self.assertEqual(device.SerialNumber, ics.get_serial_number(device))
            self.assertEqual(device.get_serial_number(), ics.get_serial_number(device))
            info = ics.get_hw_firmware_info(
                device
            )  # must be open! Gives iefs ver, pcb rev, bootloader rev, manuf date
            # print(device.Name, device.serial_number)
            # print(f"MCHIP IEF v{info.iAppMajor}.{info.iAppMinor}")
            # print(f"MCHIP BL v{info.iBootLoaderVersionMajor}.{info.iBootLoaderVersionMinor}")
            # print(f"Made {info.iManufactureMonth}/{info.iManufactureDay}/{info.iManufactureYear}")
            self.assertEqual(device.FirmwareMajor, info.iAppMajor)
            self.assertEqual(device.FirmwareMinor, info.iAppMinor)
            pcbsn = ics.get_pcb_serial_number(device)
            self.assertEqual(int(pcbsn[5]), info.iBoardRevMajor)
            self.assertEqual(int(pcbsn[6], 36), info.iBoardRevMinor)
            self.assertEqual(pcbsn, device.get_pcb_serial_number())

            # Mass check ics vs device func attributes
            info_comp = device.get_hw_firmware_info()
            for attr in dir(info_comp):
                if attr[0] == "_":
                    continue
                self.assertEqual(getattr(info_comp, attr), getattr(info, attr))

            device.close()

            # first flash old firmware
            iefs = {ics.VCAN42_MCHIP_ID: self.old_firmware_path}
            ics.set_reflash_callback(reflash_callback)
            ics.flash_devices(
                device, iefs, message_callback
            )  # device must be closed?!?!

            # check IEF version and that update is needed
            device.open()
            self.assertEqual(1, ics.firmware_update_required(device))

            # then force firmware update
            ics.force_firmware_update(
                device
            )  # device needs to be open and will stay open!

            # check it again
            self.assertEqual(0, ics.firmware_update_required(device))
            device.close()

            # update with new iefs
            iefs = {ics.VCAN42_MCHIP_ID: self.new_firmware_path}
            ics.flash_devices(device, iefs, message_callback)

            # check one last time
            device.open()
            self.assertEqual(0, ics.firmware_update_required(device))
            device.close()

            # ics.flash_accessory_firmware(device, data, index[, check_success])
            # ics.get_accessory_firmware_version()

            # ics.get_all_chip_versions(device, api_index, instance_index)
            # ics.get_backup_power_enabled(device)
            # ics.get_backup_power_ready(device)
            # ics.get_bus_voltage(device, reserved)
            # ics.get_device_status(device)

            # ics.get_last_api_error(device)

            # ics.get_performance_parameters(device)
            # ics.get_rtc(device)
            # ics.get_script_status()  # Documentation needs updating to include "device" parameter
            # ics.get_timestamp_for_msg(device, msg)

        def test_accessary_firmware(self):
            device = self._get_device()
            device.open()
            ics.flash_accessory_firmware(device, data, index[, check_success])
            ics.get_accessory_firmware_version()            

class TestValueCAN42Settings(BaseTests.TestSettings):
    @classmethod
    def setUpClass(cls):
        cls.device_type = ics.NEODEVICE_VCAN42
        cls.chip_id = ics.VCAN42_MCHIP_ID
        cls.num_devices = 1
        cls.new_firmware_path = r"C:\Users\JHarrison\Downloads\vcan42_mchip.ief"
        cls.old_firmware_path = r"C:\Users\JHarrison\Downloads\vcan42_mchip_v4_90.ief"
        print("DEBUG: Testing VCAN42...")

    def test_update_firmware(self):
        self._test_update_firmware()

class TestRADMoon2Settings(BaseTests.TestSettings):
    @classmethod
    def setUpClass(cls):
        cls.device_type = ics.NEODEVICE_RADMOON2
        cls.chip_id = ics.RADMOON2_ZL_MCHIP_ID
        cls.num_devices = 2
        print("DEBUG: Testing MOON2s...")


class TestFire3Settings(BaseTests.TestSettings):
    @classmethod
    def setUpClass(cls):
        cls.device_type = ics.NEODEVICE_FIRE3
        cls.num_devices = 1
        print("DEBUG: Testing FIRE3...")

class TestFire2Settings(BaseTests.TestSettings):
    @classmethod
    def setUpClass(cls):
        cls.device_type = ics.NEODEVICE_FIRE2
        cls.num_devices = 1
        print("DEBUG: Testing FIRE2...")

if __name__ == "__main__":
    unittest.main()
