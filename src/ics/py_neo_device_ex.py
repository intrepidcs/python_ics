import ics
from ics.ics import SpyMessage
import ctypes
from typing import Tuple

class PyNeoDeviceEx(ics.neo_device_ex.neo_device_ex):
    """Wrapper class around ics.neo_device_ex.neo_device_ex to support a more pythonic way of doing things."""
    # Internal handle from icsneoOpenDevice()
    _handle = None
    # python_ics extension for grabbing the name of the device
    _name: str = "Unknown"
    # Automatically close the handle on garbage collection
    _auto_handle_close: bool = True

    def __init__(self):
        super().__init__()

    def __del__(self):
        if self._auto_handle_close is True:
            ics.close_device(self)

    def __str__(self):
        return f"{self.Name} {self.serial_number}"

    def __repr__(self):
        return f"<ics.{self.__class__.__name__} {self.Name} {self.serial_number}>"

    def __eq__(self, other) -> bool:
        return \
            self.DeviceType == other.DeviceType and \
            self.Handle == other.Handle and \
            self.NumberOfClients == other.NumberOfClients and \
            self.MaxAllowedClients == other.MaxAllowedClients and \
            self.FirmwareMajor == other.FirmwareMajor and \
            self.FirmwareMinor == other.FirmwareMinor and \
            self.Status == other.Status and \
            self.Options == other.Options and \
            self.pAvailWIFINetwork == other.pAvailWIFINetwork and \
            self.isEthernetDevice == other.isEthernetDevice and \
            self.hardwareRev == other.hardwareRev and \
            self.revReserved == other.revReserved and \
            self.tcpPort == other.tcpPort

    @property
    def _Handle(self):
        """Return the internal device handle from icsneoOpenDevice()"""
        if self._handle is None:
            raise RuntimeError("Handle isn't valid for {self}. Is the device open?")
        ctypes.pythonapi.PyCapsule_GetPointer.restype = ctypes.c_void_p
        ctypes.pythonapi.PyCapsule_GetPointer.argtypes = [ctypes.py_object, ctypes.c_char_p]
        return ctypes.pythonapi.PyCapsule_GetPointer(self._handle, None)

    @property
    def Name(self) -> str:
        """Return the internal device name from python_ics"""
        return self._name

    @property
    def DeviceType(self) -> int:
        """Return the DeviceType from the internal NeoDevice object."""
        return self.neoDevice.DeviceType
    
    @property
    def Handle(self):
        """Return the Handle from the internal NeoDevice object."""
        return self.neoDevice.Handle

    @property
    def NumberOfClients(self) -> int:
        """Return the NumberOfClients from the internal NeoDevice object."""
        return self.neoDevice.NumberOfClients

    @property
    def MaxAllowedClients(self) -> int:
        """Return the MaxAllowedClients from the internal NeoDevice object."""
        return self.neoDevice.MaxAllowedClients

    @property
    def SerialNumber(self) -> int:
        """Return the SerialNumber from the internal NeoDevice object."""
        return self.neoDevice.SerialNumber

    @property
    def serial_number(self) -> str:
        """Return the serial number as a string."""
        if self.SerialNumber <= ics.MIN_BASE36_SERIAL:
            return str(self.SerialNumber)
        elif self.SerialNumber <= ics.MAX_SERIAL:
            return ics.base36enc(self.SerialNumber)
        else:
            raise ValueError(f"Failed to convert SerialNumber {self.SerialNumber} to a valid serial number.")
    
    @property
    def AutoHandleClose(self) -> bool:
        """Return the AutoHandleClose from the internal NeoDevice object."""
        return self._auto_handle_close

    def open(self, *args, **kwargs):
        """Open the device. Returns a reference to Self on open. See ics.open_device for details on arguments."""
        return ics.open_device(self, *args, **kwargs)

    def close(self):
        """Close the device. Returns the number of errors on close. See ics.close_device for details on arguments."""
        return ics.close_device(self)

    def load_default_settings(self):
        """Loads default settings on the device. Requires the device to be open. See ics.load_default_settings for details on arguments."""
        return ics.load_default_settings(self)


    def transmit_messages(self, *args, **kwargs):
        """Transmit messages on the device. Requires the device to be open. See ics.transmit_messages for details on arguments."""
        return ics.transmit_messages(self, *args, **kwargs)
    
    def get_messages(self, *args, **kwargs) -> Tuple[SpyMessage, int]:
        """Get messages on the device. Requires the device to be open. See ics.get_messages for details on arguments."""
        return ics.get_messages(self, *args, **kwargs)

    def coremini_clear(self, *args, **kwargs):
        "See ics.coremini_clear for details on arguments."
        return ics.coremini_clear(self, *args, **kwargs)


    def coremini_get_fblock_status(self, *args, **kwargs):
        "See ics.coremini_get_fblock_status for details on arguments."
        return ics.coremini_get_fblock_status(self, *args, **kwargs)


    def coremini_get_status(self, *args, **kwargs):
        "See ics.coremini_get_status for details on arguments."
        return ics.coremini_get_status(self, *args, **kwargs)


    def coremini_load(self, *args, **kwargs):
        "See ics.coremini_load for details on arguments."
        return ics.coremini_load(self, *args, **kwargs)


    def coremini_read_app_signal(self, *args, **kwargs):
        "See ics.coremini_read_app_signal for details on arguments."
        return ics.coremini_read_app_signal(self, *args, **kwargs)


    def coremini_read_rx_message(self, *args, **kwargs):
        "See ics.coremini_read_rx_message for details on arguments."
        return ics.coremini_read_rx_message(self, *args, **kwargs)


    def coremini_read_tx_message(self, *args, **kwargs):
        "See ics.coremini_read_tx_message for details on arguments."
        return ics.coremini_read_tx_message(self, *args, **kwargs)


    def coremini_start(self, *args, **kwargs):
        "See ics.coremini_start for details on arguments."
        return ics.coremini_start(self, *args, **kwargs)


    def coremini_start_fblock(self, *args, **kwargs):
        "See ics.coremini_start_fblock for details on arguments."
        return ics.coremini_start_fblock(self, *args, **kwargs)


    def coremini_stop(self, *args, **kwargs):
        "See ics.coremini_stop for details on arguments."
        return ics.coremini_stop(self, *args, **kwargs)


    def coremini_stop_fblock(self, *args, **kwargs):
        "See ics.coremini_stop_fblock for details on arguments."
        return ics.coremini_stop_fblock(self, *args, **kwargs)


    def coremini_write_app_signal(self, *args, **kwargs):
        "See ics.coremini_write_app_signal for details on arguments."
        return ics.coremini_write_app_signal(self, *args, **kwargs)


    def coremini_write_rx_message(self, *args, **kwargs):
        "See ics.coremini_write_rx_message for details on arguments."
        return ics.coremini_write_rx_message(self, *args, **kwargs)


    def coremini_write_tx_message(self, *args, **kwargs):
        "See ics.coremini_write_tx_message for details on arguments."
        return ics.coremini_write_tx_message(self, *args, **kwargs)


    def create_neovi_radio_message(self, *args, **kwargs):
        "See ics.create_neovi_radio_message for details on arguments."
        return ics.create_neovi_radio_message(self, *args, **kwargs)


    def disk_format(self, *args, **kwargs):
        "See ics.disk_format for details on arguments."
        return ics.disk_format(self, *args, **kwargs)


    def disk_format_cancel(self, *args, **kwargs):
        "See ics.disk_format_cancel for details on arguments."
        return ics.disk_format_cancel(self, *args, **kwargs)


    def enable_bus_voltage_monitor(self, *args, **kwargs):
        "See ics.enable_bus_voltage_monitor for details on arguments."
        return ics.enable_bus_voltage_monitor(self, *args, **kwargs)


    def enable_doip_line(self, *args, **kwargs):
        "See ics.enable_doip_line for details on arguments."
        return ics.enable_doip_line(self, *args, **kwargs)


    def enable_network_com(self, *args, **kwargs):
        "See ics.enable_network_com for details on arguments."
        return ics.enable_network_com(self, *args, **kwargs)

    def firmware_update_required(self, *args, **kwargs):
        "See ics.firmware_update_required for details on arguments."
        return ics.firmware_update_required(self, *args, **kwargs)


    def flash_accessory_firmware(self, *args, **kwargs):
        "See ics.flash_accessory_firmware for details on arguments."
        return ics.flash_accessory_firmware(self, *args, **kwargs)


    def force_firmware_update(self, *args, **kwargs):
        "See ics.force_firmware_update for details on arguments."
        return ics.force_firmware_update(self, *args, **kwargs)


    def generic_api_get_status(self, *args, **kwargs):
        "See ics.generic_api_get_status for details on arguments."
        return ics.generic_api_get_status(self, *args, **kwargs)


    def generic_api_read_data(self, *args, **kwargs):
        "See ics.generic_api_read_data for details on arguments."
        return ics.generic_api_read_data(self, *args, **kwargs)


    def generic_api_send_command(self, *args, **kwargs):
        "See ics.generic_api_send_command for details on arguments."
        return ics.generic_api_send_command(self, *args, **kwargs)


    def get_accessory_firmware_version(self, *args, **kwargs):
        "See ics.get_accessory_firmware_version for details on arguments."
        return ics.get_accessory_firmware_version(self, *args, **kwargs)


    def get_active_vnet_channel(self, *args, **kwargs):
        "See ics.get_active_vnet_channel for details on arguments."
        return ics.get_active_vnet_channel(self, *args, **kwargs)


    def get_all_chip_versions(self, *args, **kwargs):
        "See ics.get_all_chip_versions for details on arguments."
        return ics.get_all_chip_versions(self, *args, **kwargs)


    def get_backup_power_enabled(self, *args, **kwargs):
        "See ics.get_backup_power_enabled for details on arguments."
        return ics.get_backup_power_enabled(self, *args, **kwargs)


    def get_backup_power_ready(self, *args, **kwargs):
        "See ics.get_backup_power_ready for details on arguments."
        return ics.get_backup_power_ready(self, *args, **kwargs)


    def get_bus_voltage(self, *args, **kwargs):
        "See ics.get_bus_voltage for details on arguments."
        return ics.get_bus_voltage(self, *args, **kwargs)


    def get_device_settings(self, *args, **kwargs):
        "See ics.get_device_settings for details on arguments."
        return ics.get_device_settings(self, *args, **kwargs)


    def get_device_status(self, *args, **kwargs):
        "See ics.get_device_status for details on arguments."
        return ics.get_device_status(self, *args, **kwargs)


    def get_disk_details(self, *args, **kwargs):
        "See ics.get_disk_details for details on arguments."
        return ics.get_disk_details(self, *args, **kwargs)


    def get_disk_format_progress(self, *args, **kwargs):
        "See ics.get_disk_format_progress for details on arguments."
        return ics.get_disk_format_progress(self, *args, **kwargs)


    def get_dll_firmware_info(self, *args, **kwargs):
        "See ics.get_dll_firmware_info for details on arguments."
        return ics.get_dll_firmware_info(self, *args, **kwargs)


    def get_error_messages(self, *args, **kwargs):
        "See ics.get_error_messages for details on arguments."
        return ics.get_error_messages(self, *args, **kwargs)


    def get_gptp_status(self, *args, **kwargs):
        "See ics.get_gptp_status for details on arguments."
        return ics.get_gptp_status(self, *args, **kwargs)


    def get_hw_firmware_info(self, *args, **kwargs):
        "See ics.get_hw_firmware_info for details on arguments."
        return ics.get_hw_firmware_info(self, *args, **kwargs)


    def get_last_api_error(self, *args, **kwargs):
        "See ics.get_last_api_error for details on arguments."
        return ics.get_last_api_error(self, *args, **kwargs)


    def get_pcb_serial_number(self, *args, **kwargs):
        "See ics.get_pcb_serial_number for details on arguments."
        return ics.get_pcb_serial_number(self, *args, **kwargs)


    def get_performance_parameters(self, *args, **kwargs):
        "See ics.get_performance_parameters for details on arguments."
        return ics.get_performance_parameters(self, *args, **kwargs)


    def get_rtc(self, *args, **kwargs):
        "See ics.get_rtc for details on arguments."
        return ics.get_rtc(self, *args, **kwargs)


    def get_script_status(self, *args, **kwargs):
        "See ics.get_script_status for details on arguments."
        return ics.get_script_status(self, *args, **kwargs)


    def get_serial_number(self, *args, **kwargs):
        "See ics.get_serial_number for details on arguments."
        return ics.get_serial_number(self, *args, **kwargs)


    def get_timestamp_for_msg(self, *args, **kwargs):
        "See ics.get_timestamp_for_msg for details on arguments."
        return ics.get_timestamp_for_msg(self, *args, **kwargs)


    def is_device_feature_supported(self, *args, **kwargs):
        "See ics.is_device_feature_supported for details on arguments."
        return ics.is_device_feature_supported(self, *args, **kwargs)


    def iso15765_disable_networks(self, *args, **kwargs):
        "See ics.iso15765_disable_networks for details on arguments."
        return ics.iso15765_disable_networks(self, *args, **kwargs)


    def iso15765_enable_networks(self, *args, **kwargs):
        "See ics.iso15765_enable_networks for details on arguments."
        return ics.iso15765_enable_networks(self, *args, **kwargs)


    def iso15765_receive_message(self, *args, **kwargs):
        "See ics.iso15765_receive_message for details on arguments."
        return ics.iso15765_receive_message(self, *args, **kwargs)


    def iso15765_transmit_message(self, *args, **kwargs):
        "See ics.iso15765_transmit_message for details on arguments."
        return ics.iso15765_transmit_message(self, *args, **kwargs)


    def read_jupiter_firmware(self, *args, **kwargs):
        "See ics.read_jupiter_firmware for details on arguments."
        return ics.read_jupiter_firmware(self, *args, **kwargs)


    def read_sdcard(self, *args, **kwargs):
        "See ics.read_sdcard for details on arguments."
        return ics.read_sdcard(self, *args, **kwargs)


    def request_enter_sleep_mode(self, *args, **kwargs):
        "See ics.request_enter_sleep_mode for details on arguments."
        return ics.request_enter_sleep_mode(self, *args, **kwargs)


    def set_active_vnet_channel(self, *args, **kwargs):
        "See ics.set_active_vnet_channel for details on arguments."
        return ics.set_active_vnet_channel(self, *args, **kwargs)


    def set_backup_power_enabled(self, *args, **kwargs):
        "See ics.set_backup_power_enabled for details on arguments."
        return ics.set_backup_power_enabled(self, *args, **kwargs)


    def set_bit_rate(self, *args, **kwargs):
        "See ics.set_bit_rate for details on arguments."
        return ics.set_bit_rate(self, *args, **kwargs)


    def set_bit_rate_ex(self, *args, **kwargs):
        "See ics.set_bit_rate_ex for details on arguments."
        return ics.set_bit_rate_ex(self, *args, **kwargs)


    def set_device_settings(self, *args, **kwargs):
        "See ics.set_device_settings for details on arguments."
        return ics.set_device_settings(self, *args, **kwargs)


    def set_fd_bit_rate(self, *args, **kwargs):
        "See ics.set_fd_bit_rate for details on arguments."
        return ics.set_fd_bit_rate(self, *args, **kwargs)


    def set_led_property(self, *args, **kwargs):
        "See ics.set_led_property for details on arguments."
        return ics.set_led_property(self, *args, **kwargs)

    def set_rtc(self, *args, **kwargs):
        "See ics.set_rtc for details on arguments."
        return ics.set_rtc(self, *args, **kwargs)


    def start_dhcp_server(self, *args, **kwargs):
        "See ics.start_dhcp_server for details on arguments."
        return ics.start_dhcp_server(self, *args, **kwargs)


    def stop_dhcp_server(self, *args, **kwargs):
        "See ics.stop_dhcp_server for details on arguments."
        return ics.stop_dhcp_server(self, *args, **kwargs)


    def uart_get_baudrate(self, *args, **kwargs):
        "See ics.uart_get_baudrate for details on arguments."
        return ics.uart_get_baudrate(self, *args, **kwargs)


    def uart_read(self, *args, **kwargs):
        "See ics.uart_read for details on arguments."
        return ics.uart_read(self, *args, **kwargs)


    def uart_set_baudrate(self, *args, **kwargs):
        "See ics.uart_set_baudrate for details on arguments."
        return ics.uart_set_baudrate(self, *args, **kwargs)


    def uart_write(self, *args, **kwargs):
        "See ics.uart_write for details on arguments."
        return ics.uart_write(self, *args, **kwargs)


    def validate_hobject(self, *args, **kwargs):
        "See ics.validate_hobject for details on arguments."
        return ics.validate_hobject(self, *args, **kwargs)


    def wbms_manager_reset(self, *args, **kwargs):
        "See ics.wbms_manager_reset for details on arguments."
        return ics.wbms_manager_reset(self, *args, **kwargs)


    def wbms_manager_write_lock(self, *args, **kwargs):
        "See ics.wbms_manager_write_lock for details on arguments."
        return ics.wbms_manager_write_lock(self, *args, **kwargs)


    def write_jupiter_firmware(self, *args, **kwargs):
        "See ics.write_jupiter_firmware for details on arguments."
        return ics.write_jupiter_firmware(self, *args, **kwargs)


    def write_sdcard(self, *args, **kwargs):
        "See ics.write_sdcard for details on arguments."
        return ics.write_sdcard(self, *args, **kwargs)

    def set_safe_boot_mode(self, *args, **kwargs):
        "See ics.set_safe_boot_mode for details on arguments."
        return ics.set_safe_boot_mode(self, *args, **kwargs)
    
    def flash_devices(self, *args, **kwargs):
        "See ics.flash_devices for details on arguments. This is an internal intrepid function only."
        return ics.flash_device(self, *args, **kwargs)