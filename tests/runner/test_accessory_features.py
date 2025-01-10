# ruff: noqa: E501
import time
import unittest
import ctypes

# Load the DLL explicitly
# dll_path = r'C:\DevJonas\vspy3\Projects\icsneoVIDLL\Debug\icsneo40.dll'
# ctypes.CDLL(dll_path)

import ics

# from ics.py_neo_device_ex import PyNeoDeviceEx
from ics.structures.e_device_settings_type import e_device_settings_type

import faulthandler
import sys

faulthandler.enable(file=sys.stderr)

unittest.TestLoader.sortTestMethodsUsing = None


# class BaseTests:
#     """Base classes. These are isolated and won't be run/discovered. Used for inheritance"""

class TestSettings(unittest.TestCase):
    device = None
    @classmethod
    def setup(self):
        self.device = ics.find_devices([ics.NEODEVICE_FIRE3])
        self.device = ics.open_device(self.device[0])
        # pass

    def tearDown(self):
        ics.close_device(self.device)
        time.sleep(6)

    def _get_device(self):
        devices = ics.find_devices([self.device_type])
        return devices[0]

    def test_base36enc(self):
        # device = ics.find_devices([ics.NEODEVICE_FIRE3])
        # device = ics.open_device(device[0])
        # device = self._get_device()
        # device = ics.open_device(device)            
        base36 = ics.base36enc(self.device.SerialNumber)
        serial_range_min = None
        serial_range_max = None
        if self.device.DeviceType == ics.NEODEVICE_FIRE3:
            serial_range_min = int("ON0000", 36)
            serial_range_max =  int("ONZZZZ", 36)
        if self.device.DeviceType == ics.NEODEVICE_FIRE2:
            serial_range_min = int("CY0000", 36)
            serial_range_max =  int("CYZZZZ", 36)
        if self.device.DeviceType == ics.NEODEVICE_RADMOON2:
            serial_range_min = int("RM0000", 36)
            serial_range_max =  int("RNZZZZ", 36)
        if self.device.DeviceType == ics.NEODEVICE_VCAN42:
            serial_range_min = int("V10000", 36)
            serial_range_max =  int("V2ZZZZ", 36)                

        self.assertGreaterEqual(int(base36, 36), serial_range_min)
        self.assertLessEqual(int(base36, 36), serial_range_max)

        # print(base36)

    def test_disk_functions(self):
        # device = self._get_device()
        # device = ics.open_device(device)
        # device = ics.find_devices([ics.NEODEVICE_FIRE3])
        # device = ics.open_device(device[0])
        details = ics.get_disk_details(self.device)

        format = ics.disk_format(self.device, details)
        format_cancel = ics.disk_format_cancel(self.device)

        details = ics.get_disk_details(self.device)
        progress = ics.get_disk_format_progress(self.device)
        self.assertIsNot(details, None)
        self.assertIsNone(format)
        self.assertIsNone(format_cancel)

        # if (not device.DeviceType == ics.NEODEVICE_RADMOON2) and (not device.DeviceType == ics.NEODEVICE_VCAN42):
        #     ics.read_sdcard(device, 0)  # icsneoReadSDCard(), Accepts a PyNeoDeviceEx and sector index. Returns a bytearray of 512 bytes max. Exception on error.
        # pass

    def test_radio_message(self):
        # might need neovi radio device for this test
        # device = self._get_device()
        # device = ics.open_device(device)
        # device = ics.find_devices([ics.NEODEVICE_FIRE3])
        # device = ics.open_device(device[0])        
        msg = ics.SpyMessage()
        msg.Data = ics.create_neovi_radio_message(Relay1=True, Relay4=False,LED6=True, MSB_report_rate=10)
        ics.transmit_messages(self.device, msg)
        # msg.Data

        self.assertEqual(0, msg.Data)


    def test_bus_voltage(self):
        # device = self._get_device()
        # device = ics.open_device(device)
        # device = ics.find_devices([ics.NEODEVICE_FIRE3])
        # device = ics.open_device(device[0])
        voltage = False
        if self.device.DeviceType == (ics.NEODEVICE_FIRE3 or ics.NEODEVICE_FIRE2):
            ics.enable_bus_voltage_monitor(self.device, 1)
            voltage = ics.get_bus_voltage(self.device)

        if self.device.DeviceType == ics.NEODEVICE_FIRE3:
            self.assertAlmostEqual(voltage, 12000)
        elif self.device.DeviceType == ics.NEODEVICE_FIRE2:
            self.assertAlmostEqual(voltage, 12000)
        elif self.device.DeviceType == ics.NEODEVICE_RADMOON2:
            self.assertFalse(voltage)
            # moon2 does not allow for reading bus voltage
        elif self.device.DeviceType == ics.NEODEVICE_VCAN42:
            self.assertFalse(voltage)
            # vcan4 does not allow for reading bus voltage


    def test_enable_doip_line(self):
        # device = ics.find_devices([ics.NEODEVICE_FIRE3])
        # device = ics.open_device(device[0])
        # device = self._get_device()
        # device = ics.open_device(device)
        ics.enable_doip_line(self.device, 1)
        ics.enable_network_com(self.device, True, ics.NETID_HSCAN)


    def test_enable_network_com(self):
        # device = ics.find_devices([ics.NEODEVICE_FIRE3])
        # device = ics.open_device(device[0])
        # device = self._get_device()
        # device = ics.open_device(device)            
        ics.enable_network_com(self.device, True, ics.NETID_HSCAN)


    def test_generic_api(self):
        api_index = 1
        api_selected = 1
        instance_index = 0
        instance_selected = 0
        data = b"\ff, \ff"
        function_running = 8
        # device = self._get_device()
        # device = ics.open_device(device)  
        # device = ics.find_devices([ics.NEODEVICE_FIRE3])
        # device = ics.open_device(device[0])                  
        function_index, callback_error, finished_processing = ics.generic_api_get_status(self.device, api_index, instance_index) # fails
        function_return_error = ics.generic_api_send_command(self.device, api_selected, instance_selected, function_running, data) # fails

        # self.assertEqual(callback_error, 0)

        function_index, data = ics.generic_api_read_data(self.device, api_index, instance_index)
        function_return_error = ics.generic_api_send_command(self.device, api_selected, instance_selected, function_running, data)
        # self.assertEqual(function_return_error, 0)

        ics.get_last_api_error(self.device)

        msg = ics.SpyMessage()
        tmstmp = ics.get_timestamp_for_msg(self.device, msg) # need to explicitly test this function
        
        self.assertEqual(tmstmp, 0.0)  # TODO verify this actually works


    def test_backup_power(self):
        # device = self._get_device()
        # device = ics.open_device(device)
        # device = ics.find_devices([ics.NEODEVICE_FIRE3])
        # device = ics.open_device(device[0])        
        time.sleep(.5)
        ics.get_backup_power_enabled(self.device)
        ics.get_backup_power_ready(self.device)
        ics.get_bus_voltage(self.device, 0)


    def test_active_vnet_channel(self):
        import inspect
        import os

        # Get the file path for the imported module
        module_path = inspect.getfile(ics)

        # Print the absolute file path
        print(os.path.abspath(module_path))
        path = ics.get_library_path()
        print(path)
        # device = self._get_device()
        # device = ics.open_device(device)
        # device = ics.find_devices([ics.NEODEVICE_FIRE3])
        # device = ics.open_device(device[0])
        ics.set_active_vnet_channel(self.device, 1)
        
        vnet_channel = ics.get_active_vnet_channel(self.device)
        print(vnet_channel)
        # versions = ics.get_all_chip_versions(device)

        

        # msg = ics.SpyMessage()
        # tmstmp = ics.get_timestamp_for_msg(device, msg)
        
        self.assertEqual(vnet_channel, 1)  # TODO verify this actually works


    def test_get_all_chip_versions(self):
        # path = ics.get_library_path()
        # device = self._get_device()
        # device = ics.open_device(device)
        # device = ics.find_devices([ics.NEODEVICE_FIRE3])
        # device = ics.open_device(device[0])        
        # ics.get_chip_ids()
        versions = ics.get_all_chip_versions(self.device)

        # self.assetEqual(versions.)            
        # print(versions)


    def test_firmware_info(self):
        # device = self._get_device()
        # device = ics.open_device(device)
        # device = ics.find_devices([ics.NEODEVICE_FIRE3])
        # device = ics.open_device(device[0])        

        info = ics.get_dll_firmware_info(self.device)
        version = ics.get_dll_version()


        if self.device.DeviceType == ics.NEODEVICE_FIRE3:
            self.assertEqual(info.iAppMajor, 4)
            self.assertEqual(info.iAppMinor, 13)
            self.assertEqual(version, 917)
        if self.device.DeviceType == ics.NEODEVICE_FIRE2:
            self.assertEqual(info.iAppMajor, 9)
            self.assertEqual(info.iAppMinor, 5)
            self.assertEqual(version, 917)
        if self.device.DeviceType == ics.NEODEVICE_RADMOON2:
            self.assertEqual(info.iAppMajor, 3)
            self.assertEqual(info.iAppMinor, 4)
            self.assertEqual(version, 917)
        elif self.device.DeviceType == ics.NEODEVICE_VCAN42:
            self.assertEqual(info.iAppMajor, 5)
            self.assertEqual(info.iAppMinor, 4)
            self.assertEqual(version, 917)                
        # ics.get_gptp_status(device)

        # ics.get_pcb_serial_number(device)
        # ics.get_serial_number(device)

        # ics.get_performance_parameters(device)
        # ics.get_rtc(device)

        # ics.iso15765_enable_networks(device, ics.NETID_HSCAN)
        # ics.iso15765_disable_networks(device)

            
    def test_get_gptp_status(self):
        # device = self._get_device()
        # device = ics.open_device(device)
        # device = ics.find_devices([ics.NEODEVICE_FIRE3])
        # device = ics.open_device(device[0])      
        status = ics.get_gptp_status(self.device)
        
        self.assertIsNotNone(status)
        # print(status)

        
    def test_performance_parameters(self):
        # device = self._get_device()
        # device = ics.open_device()
        # device = ics.find_devices([ics.NEODEVICE_FIRE3])
        # device = ics.open_device(device[0])        
        perf_params = ics.get_performance_parameters(self.device)
        
        self.assertIn(24576, perf_params)
        print(perf_params)



    def test_set_led(self):
        # device = self._get_device()
        # device = ics.open_device(device)
        # device = ics.find_devices([ics.NEODEVICE_FIRE3])
        # device = ics.open_device(device[0])        
        prop = ics.set_led_property(self.device, 1, 100, 100)
        
        self.assertIsNone(prop)
        # pass


    def test_get_set_rtc(self):
        # device = self._get_device()
        # device = ics.open_device(device)
        # device = ics.find_devices([ics.NEODEVICE_FIRE3])
        # device = ics.open_device(device[0])        
        errors = ics.get_error_messages(self.device)
        rtc_time = ics.get_rtc(self.device)
        rtc = ics.set_rtc(self.device)
        print(rtc)
        
        self.assertEqual(errors, [])
        self.assertEqual(len(rtc_time), 2)
        self.assertIsNone(rtc)


    def test_is_device_feature_supported(self):
        from ics.structures.device_feature import DeviceFeature
        # device = self._get_device()
        # device = ics.open_device(device)
        # device = ics.find_devices([ics.NEODEVICE_FIRE3])
        # device = ics.open_device(device[0])        
        is_supported = ics.is_device_feature_supported(self.device, DeviceFeature.networkTerminationDWCAN01) # currently only works with fire3
        
        self.assertEqual(is_supported, 1)


    def test_read_jupiter_fw(self):
        # need RAD-Jupiter to perform test
        # device = self._get_device()
        # device = ics.open_device(device)
        # device = ics.find_devices([ics.NEODEVICE_FIRE3])
        # device = ics.open_device(device[0])        
        size = 8
        ics.read_jupiter_firmware(self.device, size)


    def test_write_jupiter_fw(self):
        # device = self._get_device()
        # device = ics.open_device(device)
        # device = ics.find_devices([ics.NEODEVICE_FIRE3])
        # device = ics.open_device(device[0])        
        bytes = 8
        ics.write_jupiter_firmware(self.device, bytes)


    def test_request_enter_sleep_mode(self):
        # device = self._get_device()
        # device = ics.open_device(device)
        # device = ics.find_devices([ics.NEODEVICE_FIRE3])
        # device = ics.open_device(device[0])
        ics.request_enter_sleep_mode(self.device, 1, 0) # Currently only supported for FIREVNET/PLASMA


    def test_get_script_status(self):
        # device = self._get_device()
        # device = ics.open_device(device)
        # device = ics.find_devices([ics.NEODEVICE_FIRE3])
        # device = ics.open_device(device[0])
        status = ics.get_script_status(self.device)
        # self.assertIn(514, status)
        
        self.assertIn(51, status)
        self.assertIn(270, status)
        print(status)


    def test_backup_power_enabled(self):
        # device = self._get_device()
        # device = ics.open_device(device)
        # device = ics.find_devices([ics.NEODEVICE_FIRE3])
        # device = ics.open_device(device[0])
        enabled = ics.set_backup_power_enabled(self.device)
        
        self.assertEqual(enabled, 1)


    def test_set_bit_rate(self):
        # device = self._get_device()
        # device = ics.open_device(device)
        # device = ics.find_devices([ics.NEODEVICE_FIRE3])
        # device = ics.open_device(device[0])        
        bit_rate = 2000
        # success = ics.set_bit_rate(device, bit_rate, ics.NETID_HSCAN) # will only work with NEODEVICE_VCAN3 and NEODEVICE_CT_OBD
        
        # ics.set_bit_rate definition might not be complete
        # missing args in documentation
        # print(success)


    def test_set_bit_rate_ex(self):
        # device = self._get_device()
        # device = ics.open_device(device)
        # device = ics.find_devices([ics.NEODEVICE_FIRE3])
        # device = ics.open_device(device[0])
        bit_rate = 2000
        # success = ics.set_bit_rate_ex(device, bit_rate, ics.NETID_HSCAN, iOptions) # missing example usage
        # missing args in documentation
        # print(success)


    def test_set_fd_bit_rate(self):
        # device = self._get_device()
        # device = ics.open_device(device)
        # device = ics.find_devices([ics.NEODEVICE_FIRE3])
        # device = ics.open_device(device[0])
        bit_rate = 2000
        ret_val = ics.set_fd_bit_rate(self.device, bit_rate, ics.NETID_HSCAN)
        
        self.assertEqual(ret_val, 1)


    def test_set_context(self):
        # device = self._get_device()
        # device = ics.open_device(device)
        # device = ics.find_devices([ics.NEODEVICE_FIRE3])
        # device = ics.open_device(device[0])        
        context = ics.set_context(self.device)
        
        self.assertEqual(context, 1)

    
    def test_set_reflash_callback(self):
        def callback(msg, progress):
            print(msg, progress)
        # device = self._get_device()
        # device = ics.open_device(device)
        # device = ics.find_devices([ics.NEODEVICE_FIRE3])
        # device = ics.open_device(device[0])
        success = ics.set_reflash_callback(callback)
        
        print(success)


    def test_safe_boot_mode(self):
        # device = self._get_device()
        # device = ics.open_device(device)
        # device = ics.find_devices([ics.NEODEVICE_FIRE3])
        # device = ics.open_device(device[0])
        mode = ics.set_safe_boot_mode(self.device, True)
        self.assertIsNone(mode)
        mode = ics.set_safe_boot_mode(self.device, False)
        
        self.assertIsNone(mode)


    def test_dhcp_server(self):
        # device = self._get_device()
        # device = ics.open_device(device)
        # device = ics.find_devices([ics.NEODEVICE_FIRE3])
        # device = ics.open_device(device[0])
        ics.start_dhcp_server(self.device, ics.NETID_HSCAN) # documentation is missing args usage
        ics.stop_dhcp_server(self.device, ics.NETID_HSCAN) # documentation is missing args usage


    def test_uart_get_baudrate(self):
        from ics.structures.e_uart_port_t import e_uart_port_t
        # device = self._get_device()
        # device = ics.open_device(device)
        # device = ics.find_devices([ics.NEODEVICE_FIRE3])
        # device = ics.open_device(device[0])
        baudrate = ics.uart_get_baudrate(self.device, e_uart_port_t.eUART0, 2000) # example usage uses ics.uart_set_baudrate() instead of get
        print(baudrate)

        # TypeError: meth_uart_get_baudrate() takes exactly 3 arguments (2 given)
        # documentation only has 2 arguments

    def test_uart_read(self):
        from ics.structures.e_uart_port_t import e_uart_port_t
        # device = self._get_device()
        # device = ics.open_device(device)
        # device = ics.find_devices([ics.NEODEVICE_FIRE3])
        # device = ics.open_device(device[0])
        data = ics.uart_read(self.device, e_uart_port_t.eUART0)
        # Error: uart_read(): icsneoUartRead() Failed
        print(f"Read {len(data)} bytes: {data}")


    def test_uart_write(self):
        from ics.structures.e_uart_port_t import e_uart_port_t
        # device = self._get_device()
        # device = ics.open_device(device)
        # device = ics.find_devices([ics.NEODEVICE_FIRE3])
        # device = ics.open_device(device[0])
        data = ics.uart_write(self.device, e_uart_port_t.eUART0, b'my uart data goes here')
        print(f"Read {len(data)} bytes: {data}")

        # ics.ics.RuntimeError: Error: uart_write(): icsneoUartWrite() Failed
    
    def test_validate_hobject(self):
        # device = self._get_device()
        # device = ics.open_device(device)
        # device = ics.find_devices([ics.NEODEVICE_FIRE3])
        # device = ics.open_device(device[0])
        validated = ics.validate_hobject(self.device)
        
        self.assertEqual(validated, 1)


    def test_write_sdcard(self):
        # device = self._get_device()
        # device = ics.open_device(device)
        # device = ics.find_devices([ics.NEODEVICE_FIRE3])
        # device = ics.open_device(device[0])
        byte_arr = bytearray(512)
        ics.write_sdcard(self.device, 0, byte_arr) # no example usage in documentation
        print()

            

# class TestRADMoon2Settings(BaseTests.TestSettings):
#     @classmethod
#     def setUpClass(cls):
#         cls.device_type = ics.NEODEVICE_RADMOON2
#         cls.device_settings_type = e_device_settings_type.DeviceRADMoon2SettingsType
#         cls.num_devices = 2
#         print("DEBUG: Testing MOON2s...")


# class TestFire3Settings(BaseTests.TestSettings):
#     @classmethod
#     def setUpClass(cls):
#         cls.device_type = ics.NEODEVICE_FIRE3
#         cls.device_settings_type = e_device_settings_type.DeviceFire3SettingsType
#         cls.num_devices = 1
#         print("DEBUG: Testing FIRE3...")

# class TestFire2Settings(BaseTests.TestSettings):
#     @classmethod
#     def setUpClass(cls):
#         cls.device_type = ics.NEODEVICE_FIRE2
#         cls.device_settings_type = e_device_settings_type.DeviceFire2SettingsType
#         cls.num_devices = 1
#         print("DEBUG: Testing FIRE2...")


# class TestValueCAN42Settings(BaseTests.TestSettings):
#     @classmethod
#     def setUpClass(cls):
#         cls.device_type = ics.NEODEVICE_VCAN42
#         cls.device_settings_type = e_device_settings_type.DeviceVCAN412SettingsType
#         cls.num_devices = 1
#         print("DEBUG: Testing VCAN42...")

    def suite():
        suite = unittest.TestSuite()
        suite.addTest(TestSettings('test_base36enc'))
        suite.addTest(TestSettings('test_disk_functions'))
        suite.addTest(TestSettings('test_radio_message'))
        suite.addTest(TestSettings('test_bus_voltage'))
        suite.addTest(TestSettings('test_enable_doip_line'))
        suite.addTest(TestSettings('test_enable_network_com'))
        suite.addTest(TestSettings('test_generic_api'))
        suite.addTest(TestSettings('test_backup_power'))
        suite.addTest(TestSettings('test_active_vnet_channel'))
        suite.addTest(TestSettings('test_get_all_chip_versions'))
        suite.addTest(TestSettings('test_firmware_info'))
        suite.addTest(TestSettings('test_get_gptp_status'))
        suite.addTest(TestSettings('test_performance_parameters'))
        suite.addTest(TestSettings('test_set_led'))
        suite.addTest(TestSettings('test_get_set_rtc'))
        suite.addTest(TestSettings('test_is_device_feature_supported'))
        suite.addTest(TestSettings('test_read_jupiter_fw'))
        suite.addTest(TestSettings('test_write_jupiter_fw'))
        suite.addTest(TestSettings('test_request_enter_sleep_mode'))
        suite.addTest(TestSettings('test_get_script_status'))
        suite.addTest(TestSettings('test_backup_power_enabled'))
        suite.addTest(TestSettings('test_set_bit_rate'))
        suite.addTest(TestSettings('test_set_bit_rate_ex'))
        suite.addTest(TestSettings('test_set_fd_bit_rate'))
        suite.addTest(TestSettings('test_set_context'))
        suite.addTest(TestSettings('test_set_reflash_callback'))
        suite.addTest(TestSettings('test_safe_boot_mode'))
        suite.addTest(TestSettings('test_dhcp_server'))
        suite.addTest(TestSettings('test_uart_get_baudrate'))
        suite.addTest(TestSettings('test_uart_read'))
        suite.addTest(TestSettings('test_uart_write'))
        suite.addTest(TestSettings('test_validate_hobject'))
        suite.addTest(TestSettings('test_write_sdcard'))
        return suite
    
if __name__ == "__main__":
    # unittest.main()
    runner = unittest.TextTestRunner()
    runner.run(TestSettings.suite())
