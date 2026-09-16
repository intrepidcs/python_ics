import pytest
import ics


def _make_device(serial: int) -> ics.PyNeoDeviceEx:
    device = ics.PyNeoDeviceEx()
    # No handle was opened; don't try to close one on GC.
    device._auto_handle_close = False
    # SerialNumber is an int32_t in the NeoDevice struct, so values with the
    # high bit set are stored as negative.
    device.neoDevice.SerialNumber = serial - 0x100000000 if serial > 0x7FFFFFFF else serial
    return device


def test_serial_number_decimal():
    assert _make_device(53123).serial_number == "53123"


def test_serial_number_first_base36():
    # MIN_BASE36_SERIAL is exactly "A0000" and must render as base36.
    assert int("A0000", 36) == ics.MIN_BASE36_SERIAL
    assert _make_device(ics.MIN_BASE36_SERIAL).serial_number == "A0000"


def test_serial_number_last_decimal():
    assert _make_device(ics.MIN_BASE36_SERIAL - 1).serial_number == str(ics.MIN_BASE36_SERIAL - 1)


def test_serial_number_high_bit_serial():
    # Serials ZIK0ZK..ZZZZZZ exceed 0x7FFFFFFF and read back negative from
    # the int32 struct field; the property must still render them correctly.
    assert int("ZZZZZZ", 36) == ics.MAX_SERIAL
    assert _make_device(ics.MAX_SERIAL).serial_number == "ZZZZZZ"
    assert _make_device(int("ZIK0ZK", 36)).serial_number == "ZIK0ZK"


def test_serial_number_out_of_range_raises():
    with pytest.raises(ValueError):
        _make_device(ics.MAX_SERIAL + 1).serial_number


@pytest.mark.parametrize("serial", [100, ics.MAX_SERIAL])
def test_equal_device_snapshots(serial):
    first, second = _make_device(serial), _make_device(serial)
    assert first is not second
    assert first == second
    assert second == first
    assert not (first != second)
    assert second in [first]


@pytest.mark.parametrize("serials", [(100, 200), (0x7FFFFFFF, 0x80000000)])
def test_different_serials_are_distinct_devices(serials):
    first, second = map(_make_device, serials)
    assert first != second
    assert second != first
    assert not (first == second)
    assert second not in [first]
    devices = [first]
    if second not in devices:
        devices.append(second)
    assert len(devices) == 2


@pytest.mark.parametrize("field", ["DeviceType", "Handle", "NumberOfClients", "MaxAllowedClients"])
def test_device_snapshot_fields_still_affect_equality(field):
    first, second = _make_device(100), _make_device(100)
    setattr(second.neoDevice, field, 1)
    assert first != second


@pytest.mark.parametrize("field", [
    "FirmwareMajor", "FirmwareMinor", "Status", "Options", "pAvailWIFINetwork",
    "isEthernetDevice", "hardwareRev", "revReserved", "tcpPort",
])
def test_extended_snapshot_fields_still_affect_equality(field):
    first, second = _make_device(100), _make_device(100)
    setattr(second, field, 1)
    assert first != second


@pytest.mark.parametrize("other", [None, object(), 100, "100"])
def test_unrelated_objects_compare_unequal(other):
    device = _make_device(100)
    assert device.__eq__(other) is NotImplemented
    assert not (device == other)
    assert not (other == device)
    assert device != other
    assert other != device


def test_equality_allows_reflected_comparison():
    class AcceptsDevice:
        def __eq__(self, other):
            return isinstance(other, ics.PyNeoDeviceEx)

    device = _make_device(100)
    assert device == AcceptsDevice()


if __name__ == "__main__":
    pytest.main(args=[__file__, "--verbose", "-s"])
