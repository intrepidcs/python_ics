import ctypes

import pytest
import ics
from ics.structures.e_device_settings_type import e_device_settings_type
from ics.structures.s_device_settings import s_device_settings
from ics.structures.ics_spy_message_flex_ray import ics_spy_message_flex_ray
from ics.structures.ics_spy_message_vsb import ics_spy_message_vsb


def test_device_settings_none_consistent():
    # The module constant, the generated enum, and the struct field must all
    # agree on 0xFFFFFFFF on every platform. MSVC used to wrap the module
    # constant to -1.
    assert ics.DeviceSettingsNone == 0xFFFFFFFF
    assert e_device_settings_type.DeviceSettingsNone.value == 0xFFFFFFFF


def test_device_setting_type_field_roundtrip():
    settings = s_device_settings()
    settings.DeviceSettingType = 0xFFFFFFFF
    assert settings.DeviceSettingType == ics.DeviceSettingsNone


def test_description_id_is_signed_int16():
    # descIdType is int16_t in icsnVC40.h (EXTERNAL_PROJECT build).
    for struct in (ics_spy_message_flex_ray, ics_spy_message_vsb):
        instance = struct()
        instance.DescriptionID = -1
        assert instance.DescriptionID == -1, struct.__name__
        assert type(instance).DescriptionID.size == 2, struct.__name__


if __name__ == "__main__":
    pytest.main(args=[__file__, "--verbose", "-s"])
