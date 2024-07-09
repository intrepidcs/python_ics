import ctypes
from typing import Tuple
try:
    from . import c_mod
except (ModuleNotFoundError, ImportError) as ex:
    import sys
    print(f"Warning: py_neo_device_ex: c_mod module is not installed. c_mod will not be available.", file=sys.stderr, flush=True)
try:
    from .structures.neo_device_ex import neo_device_ex
except ValueError as ex:
    # This is only required when building
    print(ex)
    class neo_device_ex(ctypes.Structure):
        pass


class PyNeoDeviceEx(neo_device_ex):
    """Wrapper class around c_mod.neo_device_ex.neo_device_ex to support a more pythonic way of doing things."""
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
            c_mod.close_device(self)

    def __str__(self):
        return f"{self.Name} {self.serial_number}"

    def __repr__(self):
        return f"<python_c_mod.{self.__class__.__name__} {self.Name} {self.serial_number}>"

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
        if self.SerialNumber <= c_mod.MIN_BASE36_SERIAL:
            return str(self.SerialNumber)
        elif self.SerialNumber <= c_mod.MAX_SERIAL:
            return c_mod.base36enc(self.SerialNumber)
        else:
            raise ValueError(f"Failed to convert SerialNumber {self.SerialNumber} to a valid serial number.")

    def open(self, *args, **kwargs):
        """Open the device. Returns a reference to Self on open. See c_mod.open_device for details on arguments."""
        return c_mod.open_device(self, *args, **kwargs)

    def close(self):
        """Close the device. Returns the number of errors on close. See c_mod.close_device for details on arguments."""
        return c_mod.close_device(self)

    def load_default_settings(self):
        """Loads default settings on the device. Requires the device to be open. See c_mod.load_default_settings for details on arguments."""
        return c_mod.load_default_settings(self)

    def transmit_messages(self, *args, **kwargs):
        """Transmit messages on the device. Requires the device to be open. See c_mod.transmit_messages for details on arguments."""
        return c_mod.transmit_messages(self, *args, **kwargs)
    
    def get_messages(self, *args, **kwargs) -> Tuple[object, int]:
        """Get messages on the device. Requires the device to be open. See c_mod.get_messages for details on arguments."""
        return c_mod.get_messages(self, *args, **kwargs)

    def coremini_clear(self, *args, **kwargs):
        "See c_mod.coremini_clear for details on arguments."
        return c_mod.coremini_clear(self, *args, **kwargs)


    def coremini_get_fblock_status(self, *args, **kwargs):
        "See c_mod.coremini_get_fblock_status for details on arguments."
        return c_mod.coremini_get_fblock_status(self, *args, **kwargs)


    def coremini_get_status(self, *args, **kwargs):
        "See c_mod.coremini_get_status for details on arguments."
        return c_mod.coremini_get_status(self, *args, **kwargs)


    def coremini_load(self, *args, **kwargs):
        "See c_mod.coremini_load for details on arguments."
        return c_mod.coremini_load(self, *args, **kwargs)


    def coremini_read_app_signal(self, *args, **kwargs):
        "See c_mod.coremini_read_app_signal for details on arguments."
        return c_mod.coremini_read_app_signal(self, *args, **kwargs)


    def coremini_read_rx_message(self, *args, **kwargs):
        "See c_mod.coremini_read_rx_message for details on arguments."
        return c_mod.coremini_read_rx_message(self, *args, **kwargs)


    def coremini_read_tx_message(self, *args, **kwargs):
        "See c_mod.coremini_read_tx_message for details on arguments."
        return c_mod.coremini_read_tx_message(self, *args, **kwargs)


    def coremini_start(self, *args, **kwargs):
        "See c_mod.coremini_start for details on arguments."
        return c_mod.coremini_start(self, *args, **kwargs)


    def coremini_start_fblock(self, *args, **kwargs):
        "See c_mod.coremini_start_fblock for details on arguments."
        return c_mod.coremini_start_fblock(self, *args, **kwargs)


    def coremini_stop(self, *args, **kwargs):
        "See c_mod.coremini_stop for details on arguments."
        return c_mod.coremini_stop(self, *args, **kwargs)


    def coremini_stop_fblock(self, *args, **kwargs):
        "See c_mod.coremini_stop_fblock for details on arguments."
        return c_mod.coremini_stop_fblock(self, *args, **kwargs)


    def coremini_write_app_signal(self, *args, **kwargs):
        "See c_mod.coremini_write_app_signal for details on arguments."
        return c_mod.coremini_write_app_signal(self, *args, **kwargs)


    def coremini_write_rx_message(self, *args, **kwargs):
        "See c_mod.coremini_write_rx_message for details on arguments."
        return c_mod.coremini_write_rx_message(self, *args, **kwargs)


    def coremini_write_tx_message(self, *args, **kwargs):
        "See c_mod.coremini_write_tx_message for details on arguments."
        return c_mod.coremini_write_tx_message(self, *args, **kwargs)


    def create_neovi_radio_message(self, *args, **kwargs):
        "See c_mod.create_neovi_radio_message for details on arguments."
        return c_mod.create_neovi_radio_message(self, *args, **kwargs)


    def disk_format(self, *args, **kwargs):
        "See c_mod.disk_format for details on arguments."
        return c_mod.disk_format(self, *args, **kwargs)


    def disk_format_cancel(self, *args, **kwargs):
        "See c_mod.disk_format_cancel for details on arguments."
        return c_mod.disk_format_cancel(self, *args, **kwargs)


    def enable_bus_voltage_monitor(self, *args, **kwargs):
        "See c_mod.enable_bus_voltage_monitor for details on arguments."
        return c_mod.enable_bus_voltage_monitor(self, *args, **kwargs)


    def enable_doip_line(self, *args, **kwargs):
        "See c_mod.enable_doip_line for details on arguments."
        return c_mod.enable_doip_line(self, *args, **kwargs)


    def enable_network_com(self, *args, **kwargs):
        "See c_mod.enable_network_com for details on arguments."
        return c_mod.enable_network_com(self, *args, **kwargs)

    def firmware_update_required(self, *args, **kwargs):
        "See c_mod.firmware_update_required for details on arguments."
        return c_mod.firmware_update_required(self, *args, **kwargs)


    def flash_accessory_firmware(self, *args, **kwargs):
        "See c_mod.flash_accessory_firmware for details on arguments."
        return c_mod.flash_accessory_firmware(self, *args, **kwargs)


    def force_firmware_update(self, *args, **kwargs):
        "See c_mod.force_firmware_update for details on arguments."
        return c_mod.force_firmware_update(self, *args, **kwargs)


    def generic_api_get_status(self, *args, **kwargs):
        "See c_mod.generic_api_get_status for details on arguments."
        return c_mod.generic_api_get_status(self, *args, **kwargs)


    def generic_api_read_data(self, *args, **kwargs):
        "See c_mod.generic_api_read_data for details on arguments."
        return c_mod.generic_api_read_data(self, *args, **kwargs)


    def generic_api_send_command(self, *args, **kwargs):
        "See c_mod.generic_api_send_command for details on arguments."
        return c_mod.generic_api_send_command(self, *args, **kwargs)


    def get_accessory_firmware_version(self, *args, **kwargs):
        "See c_mod.get_accessory_firmware_version for details on arguments."
        return c_mod.get_accessory_firmware_version(self, *args, **kwargs)


    def get_active_vnet_channel(self, *args, **kwargs):
        "See c_mod.get_active_vnet_channel for details on arguments."
        return c_mod.get_active_vnet_channel(self, *args, **kwargs)


    def get_all_chip_versions(self, *args, **kwargs):
        "See c_mod.get_all_chip_versions for details on arguments."
        return c_mod.get_all_chip_versions(self, *args, **kwargs)


    def get_backup_power_enabled(self, *args, **kwargs):
        "See c_mod.get_backup_power_enabled for details on arguments."
        return c_mod.get_backup_power_enabled(self, *args, **kwargs)


    def get_backup_power_ready(self, *args, **kwargs):
        "See c_mod.get_backup_power_ready for details on arguments."
        return c_mod.get_backup_power_ready(self, *args, **kwargs)


    def get_bus_voltage(self, *args, **kwargs):
        "See c_mod.get_bus_voltage for details on arguments."
        return c_mod.get_bus_voltage(self, *args, **kwargs)


    def get_device_settings(self, *args, **kwargs):
        "See c_mod.get_device_settings for details on arguments."
        return c_mod.get_device_settings(self, *args, **kwargs)


    def get_device_status(self, *args, **kwargs):
        "See c_mod.get_device_status for details on arguments."
        return c_mod.get_device_status(self, *args, **kwargs)


    def get_disk_details(self, *args, **kwargs):
        "See c_mod.get_disk_details for details on arguments."
        return c_mod.get_disk_details(self, *args, **kwargs)


    def get_disk_format_progress(self, *args, **kwargs):
        "See c_mod.get_disk_format_progress for details on arguments."
        return c_mod.get_disk_format_progress(self, *args, **kwargs)


    def get_dll_firmware_info(self, *args, **kwargs):
        "See c_mod.get_dll_firmware_info for details on arguments."
        return c_mod.get_dll_firmware_info(self, *args, **kwargs)


    def get_error_messages(self, *args, **kwargs):
        "See c_mod.get_error_messages for details on arguments."
        return c_mod.get_error_messages(self, *args, **kwargs)


    def get_gptp_status(self, *args, **kwargs):
        "See c_mod.get_gptp_status for details on arguments."
        return c_mod.get_gptp_status(self, *args, **kwargs)


    def get_hw_firmware_info(self, *args, **kwargs):
        "See c_mod.get_hw_firmware_info for details on arguments."
        return c_mod.get_hw_firmware_info(self, *args, **kwargs)


    def get_last_api_error(self, *args, **kwargs):
        "See c_mod.get_last_api_error for details on arguments."
        return c_mod.get_last_api_error(self, *args, **kwargs)


    def get_pcb_serial_number(self, *args, **kwargs):
        "See c_mod.get_pcb_serial_number for details on arguments."
        return c_mod.get_pcb_serial_number(self, *args, **kwargs)


    def get_performance_parameters(self, *args, **kwargs):
        "See c_mod.get_performance_parameters for details on arguments."
        return c_mod.get_performance_parameters(self, *args, **kwargs)


    def get_rtc(self, *args, **kwargs):
        "See c_mod.get_rtc for details on arguments."
        return c_mod.get_rtc(self, *args, **kwargs)


    def get_script_status(self, *args, **kwargs):
        "See c_mod.get_script_status for details on arguments."
        return c_mod.get_script_status(self, *args, **kwargs)


    def get_serial_number(self, *args, **kwargs):
        "See c_mod.get_serial_number for details on arguments."
        return c_mod.get_serial_number(self, *args, **kwargs)


    def get_timestamp_for_msg(self, *args, **kwargs):
        "See c_mod.get_timestamp_for_msg for details on arguments."
        return c_mod.get_timestamp_for_msg(self, *args, **kwargs)


    def is_device_feature_supported(self, *args, **kwargs):
        "See c_mod.is_device_feature_supported for details on arguments."
        return c_mod.is_device_feature_supported(self, *args, **kwargs)


    def iso15765_disable_networks(self, *args, **kwargs):
        "See c_mod.iso15765_disable_networks for details on arguments."
        return c_mod.iso15765_disable_networks(self, *args, **kwargs)


    def iso15765_enable_networks(self, *args, **kwargs):
        "See c_mod.iso15765_enable_networks for details on arguments."
        return c_mod.iso15765_enable_networks(self, *args, **kwargs)


    def iso15765_receive_message(self, *args, **kwargs):
        "See c_mod.iso15765_receive_message for details on arguments."
        return c_mod.iso15765_receive_message(self, *args, **kwargs)


    def iso15765_transmit_message(self, *args, **kwargs):
        "See c_mod.iso15765_transmit_message for details on arguments."
        return c_mod.iso15765_transmit_message(self, *args, **kwargs)


    def read_jupiter_firmware(self, *args, **kwargs):
        "See c_mod.read_jupiter_firmware for details on arguments."
        return c_mod.read_jupiter_firmware(self, *args, **kwargs)


    def read_sdcard(self, *args, **kwargs):
        "See c_mod.read_sdcard for details on arguments."
        return c_mod.read_sdcard(self, *args, **kwargs)


    def request_enter_sleep_mode(self, *args, **kwargs):
        "See c_mod.request_enter_sleep_mode for details on arguments."
        return c_mod.request_enter_sleep_mode(self, *args, **kwargs)


    def set_active_vnet_channel(self, *args, **kwargs):
        "See c_mod.set_active_vnet_channel for details on arguments."
        return c_mod.set_active_vnet_channel(self, *args, **kwargs)


    def set_backup_power_enabled(self, *args, **kwargs):
        "See c_mod.set_backup_power_enabled for details on arguments."
        return c_mod.set_backup_power_enabled(self, *args, **kwargs)


    def set_bit_rate(self, *args, **kwargs):
        "See c_mod.set_bit_rate for details on arguments."
        return c_mod.set_bit_rate(self, *args, **kwargs)


    def set_bit_rate_ex(self, *args, **kwargs):
        "See c_mod.set_bit_rate_ex for details on arguments."
        return c_mod.set_bit_rate_ex(self, *args, **kwargs)


    def set_device_settings(self, *args, **kwargs):
        "See c_mod.set_device_settings for details on arguments."
        return c_mod.set_device_settings(self, *args, **kwargs)


    def set_fd_bit_rate(self, *args, **kwargs):
        "See c_mod.set_fd_bit_rate for details on arguments."
        return c_mod.set_fd_bit_rate(self, *args, **kwargs)


    def set_led_property(self, *args, **kwargs):
        "See c_mod.set_led_property for details on arguments."
        return c_mod.set_led_property(self, *args, **kwargs)

    def set_rtc(self, *args, **kwargs):
        "See c_mod.set_rtc for details on arguments."
        return c_mod.set_rtc(self, *args, **kwargs)


    def start_dhcp_server(self, *args, **kwargs):
        "See c_mod.start_dhcp_server for details on arguments."
        return c_mod.start_dhcp_server(self, *args, **kwargs)


    def stop_dhcp_server(self, *args, **kwargs):
        "See c_mod.stop_dhcp_server for details on arguments."
        return c_mod.stop_dhcp_server(self, *args, **kwargs)


    def uart_get_baudrate(self, *args, **kwargs):
        "See c_mod.uart_get_baudrate for details on arguments."
        return c_mod.uart_get_baudrate(self, *args, **kwargs)


    def uart_read(self, *args, **kwargs):
        "See c_mod.uart_read for details on arguments."
        return c_mod.uart_read(self, *args, **kwargs)


    def uart_set_baudrate(self, *args, **kwargs):
        "See c_mod.uart_set_baudrate for details on arguments."
        return c_mod.uart_set_baudrate(self, *args, **kwargs)


    def uart_write(self, *args, **kwargs):
        "See c_mod.uart_write for details on arguments."
        return c_mod.uart_write(self, *args, **kwargs)


    def validate_hobject(self, *args, **kwargs):
        "See c_mod.validate_hobject for details on arguments."
        return c_mod.validate_hobject(self, *args, **kwargs)


    def wbms_manager_reset(self, *args, **kwargs):
        "See c_mod.wbms_manager_reset for details on arguments."
        return c_mod.wbms_manager_reset(self, *args, **kwargs)


    def wbms_manager_write_lock(self, *args, **kwargs):
        "See c_mod.wbms_manager_write_lock for details on arguments."
        return c_mod.wbms_manager_write_lock(self, *args, **kwargs)


    def write_jupiter_firmware(self, *args, **kwargs):
        "See c_mod.write_jupiter_firmware for details on arguments."
        return c_mod.write_jupiter_firmware(self, *args, **kwargs)


    def write_sdcard(self, *args, **kwargs):
        "See c_mod.write_sdcard for details on arguments."
        return c_mod.write_sdcard(self, *args, **kwargs)

    def set_safe_boot_mode(self, *args, **kwargs):
        "See c_mod.set_safe_boot_mode for details on arguments."
        return c_mod.set_safe_boot_mode(self, *args, **kwargs)