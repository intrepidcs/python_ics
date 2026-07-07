import pytest
import ics

def test_unsigned_overflow():
    """Test that certain defines are correctly set to large unsigned values."""
    # These values are defined in icsnVC40.h/cicsSpyStatusBits.h and should be
    # interpreted as unsigned. No hasattr() guard: a missing name is a
    # regression in the define generation and must fail loudly.
    values = (
        "SPY_STATUS_EXTENDED",
        "SPY_STATUS2_ETHERNET_T1S_ETHERNET",
        "SPY_STATUS2_LIN_NO_SLAVE_DATA",
        "SPY_STATUS2_MOST_CHANGED_PAR",
        "NEODEVICE_OBD2_SIM_DEPRECATED",
        "ETHERNET_SETTINGS10G_FLAG_COMM_IN_USE",
    )
    for value in values:
        assert getattr(ics, value) == 0x80000000, value


def test_serial_range_defines():
    assert ics.MIN_BASE36_SERIAL == int("A0000", 36)
    assert ics.MAX_SERIAL == int("ZZZZZZ", 36)

if __name__ == "__main__":
    import pytest

    pytest.main(
        args=[
            __file__,
            "--verbose",
            "-s",
        ]
    )
