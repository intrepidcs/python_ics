import ics


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
            self.MACAddress == other.MACAddress and \
            self.hardwareRev == other.hardwareRev and \
            self.revReserved == other.revReserved and \
            self.tcpIpAddress == other.tcpIpAddress and \
            self.tcpPort == other.tcpPort

    @property
    def _Handle(self):
        """Return the internal device handle from icsneoOpenDevice()"""
        return self._handle

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
