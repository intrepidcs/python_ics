import pytest
import ics


def test_data_roundtrip():
    msg = ics.SpyMessage()
    msg.Data = (1, 2, 3, 4, 5, 6, 7, 8)
    assert msg.Data == (1, 2, 3, 4, 5, 6, 7, 8)
    assert msg.NumberBytesData == 8


def test_data_partial_roundtrip():
    msg = ics.SpyMessage()
    msg.Data = (0xAA, 0xBB)
    assert msg.Data == (0xAA, 0xBB)
    assert msg.NumberBytesData == 2


def test_data_rejects_more_than_8_bytes():
    msg = ics.SpyMessage()
    with pytest.raises(ValueError):
        msg.Data = tuple(range(9))


def test_data_rejects_non_int_elements():
    msg = ics.SpyMessage()
    with pytest.raises(TypeError):
        msg.Data = (1, "x", 3)
    # No exception may be left pending after the failed assignment.
    assert msg.NumberBytesData == 0


def test_ack_bytes_rejects_more_than_8_bytes():
    msg = ics.SpyMessage()
    with pytest.raises(ValueError):
        msg.AckBytes = tuple(range(9))


def test_ack_bytes_rejects_non_int_elements():
    msg = ics.SpyMessage()
    with pytest.raises(TypeError):
        msg.AckBytes = (None,)


def test_header_does_not_overflow_into_data():
    # icsSpyMessageJ1850.Header is only 4 bytes; a longer tuple used to
    # spill into Data[0..3].
    msg = ics.SpyMessageJ1850()
    msg.Data = (1, 2, 3, 4, 5, 6, 7, 8)
    with pytest.raises(ValueError):
        msg.Header = (0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x11, 0x22)
    assert msg.Data == (1, 2, 3, 4, 5, 6, 7, 8)


def test_header_roundtrip():
    msg = ics.SpyMessageJ1850()
    msg.Header = (0xAA, 0xBB, 0xCC, 0xDD)
    assert msg.Header == (0xAA, 0xBB, 0xCC, 0xDD)
    assert msg.NumberBytesHeader == 4


def test_header_rejects_non_int_elements():
    msg = ics.SpyMessageJ1850()
    with pytest.raises(TypeError):
        msg.Header = ("a",)


def test_extra_data_ptr_roundtrip():
    msg = ics.SpyMessage()
    msg.Protocol = ics.SPY_PROTOCOL_CANFD
    payload = tuple(x & 0xFF for x in range(64))
    msg.ExtraDataPtr = payload
    assert msg.ExtraDataPtr == payload


def test_extra_data_ptr_large_roundtrip_packing_protocol():
    # A2B/Ethernet/SPI/WBMS pack a 16-bit length into
    # NumberBytesHeader:NumberBytesData.
    msg = ics.SpyMessage()
    msg.Protocol = ics.SPY_PROTOCOL_ETHERNET
    payload = tuple(x & 0xFF for x in range(1500))
    msg.ExtraDataPtr = payload
    assert msg.ExtraDataPtr == payload


def test_extra_data_ptr_rejects_unrepresentable_length():
    # Length is carried in 16 bits at most; longer payloads used to be
    # silently truncated to (len & 0xFFFF) bytes.
    msg = ics.SpyMessage()
    msg.Protocol = ics.SPY_PROTOCOL_ETHERNET
    with pytest.raises(ValueError):
        msg.ExtraDataPtr = tuple(x & 0xFF for x in range(0x10000))


def test_extra_data_ptr_rejects_unrepresentable_length_non_packing_protocol():
    # Non length-packing protocols only have the 8-bit NumberBytesData.
    msg = ics.SpyMessage()
    msg.Protocol = ics.SPY_PROTOCOL_CANFD
    with pytest.raises(ValueError):
        msg.ExtraDataPtr = tuple(x & 0xFF for x in range(0x100))


def test_extra_data_ptr_rejects_non_int_elements():
    msg = ics.SpyMessage()
    msg.Protocol = ics.SPY_PROTOCOL_CANFD
    with pytest.raises(TypeError):
        msg.ExtraDataPtr = (1, 2, "x")


def test_extra_data_ptr_none_when_unset():
    msg = ics.SpyMessage()
    assert msg.ExtraDataPtr is None


def test_status_bit_field_high_bit_roundtrip():
    msg = ics.SpyMessage()
    msg.StatusBitField = ics.SPY_STATUS_EXTENDED
    assert msg.StatusBitField == 0x80000000


if __name__ == "__main__":
    pytest.main(args=[__file__, "--verbose", "-s"])
