import pytest
import ics

def test_unsigned_overflow():
    """Test that certain defines are correctly set to large unsigned values."""
    # These values are defined in icsnVC40.h and should be interpreted as unsigned
    values = (
        "SPY_STATUS_EXTENDED",
        "SPY_STATUS2_ETHERNET_T1S_ETHERNET",
        "SPY_STATUS2_LIN_NO_SLAVE_DATA",
        "SPY_STATUS2_MOST_CHANGED_PAR"
    )
    for value in values:
        if hasattr(ics, value):
            assert getattr(ics, value) == 0x80000000

if __name__ == "__main__":
    import pytest

    pytest.main(
        args=[
            __file__,
            "--verbose",
            "-s",
        ]
    )
