"""Pins that the module is generated from the vspy 3.26.3.9 header."""
import pytest
import ics


def test_deprecated_device_constants_renamed():
    # 3.26.3.9 renamed the legacy device defines; old names must be gone.
    assert ics.NEODEVICE_BLUE_DEPRECATED == 0x00000001
    assert ics.NEODEVICE_FIRE_DEPRECATED == 0x00000008
    assert ics.NEODEVICE_VCAN3_DEPRECATED == 0x00000010
    assert not hasattr(ics, "NEODEVICE_BLUE")
    assert not hasattr(ics, "NEODEVICE_FIRE")
    assert not hasattr(ics, "NEODEVICE_VCAN3")


def test_grown_settings_structs():
    # Struct growth pinned from the 3.26.3.9 header's _SIZE macros.
    assert ics.SRADGalaxy2Settings_SIZE == 1204
    assert ics.SRADComet3Settings_SIZE == 918
    assert ics.SRADGigastar2Settings_SIZE == 2400


def test_legacy_settings_structs_removed():
    import ics.structures
    with pytest.raises(ImportError):
        from ics.structures import s_red_settings  # noqa: F401


if __name__ == "__main__":
    pytest.main(args=[__file__, "--verbose", "-s"])
