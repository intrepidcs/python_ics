import ics
from ics.structures.s_device_settings import s_device_settings
from ics.structures.e_device_settings_type import e_device_settings_type


def get_device_specific_settings(s: s_device_settings) -> object:
    """
    Returns the device specific setting structure for our device in question
    """
    setting_map = {}
    # We need to map the Union type to the DeviceSettingType
    setting_map[e_device_settings_type.DeviceCANHUBSettingsType] = "canhub"
    setting_map[e_device_settings_type.DeviceCMProbeSettingsType] = "cmprobe"
    setting_map[e_device_settings_type.DeviceECU_AVBSettingsType] = "neoecu_avb"
    setting_map[e_device_settings_type.DeviceEEVBSettingsType] = "eevb"
    setting_map[e_device_settings_type.DeviceFire2SettingsType] = "cyan"
    setting_map[e_device_settings_type.DeviceFireSettingsType] = "fire"
    setting_map[e_device_settings_type.DeviceFireVnetSettingsType] = "firevnet"
    setting_map[e_device_settings_type.DeviceFlexVnetzSettingsType] = "flexvnetz"
    setting_map[e_device_settings_type.DeviceNeoECU12SettingsType] = "neoecu12"
    setting_map[e_device_settings_type.DeviceOBD2ProSettingsType] = "obd2pro"
    setting_map[e_device_settings_type.DeviceRADGalaxySettingsType] = "radgalaxy"
    setting_map[e_device_settings_type.DeviceRADGigalogSettingsType] = "radgigalog"
    setting_map[e_device_settings_type.DeviceRADGigastarSettingsType] = "radgigastar"
    setting_map[e_device_settings_type.DeviceRADMoon2SettingsType] = "radmoon2"
    setting_map[e_device_settings_type.DeviceRADPlutoSettingsType] = "pluto"
    setting_map[e_device_settings_type.DeviceRADStar2SettingsType] = "radstar2"
    setting_map[e_device_settings_type.DeviceRADSuperMoonSettingsType] = "radsupermoon"
    setting_map[e_device_settings_type.DeviceRADMoon2SettingsType] = "radmoon2"
    setting_map[e_device_settings_type.DeviceRedSettingsType] = "red"
    setting_map[e_device_settings_type.DeviceVCAN3SettingsType] = "vcan3"
    setting_map[e_device_settings_type.DeviceVCAN412SettingsType] = "vcan412"
    setting_map[e_device_settings_type.DeviceVCAN4IndSettingsType] = "vcan4_ind"
    setting_map[e_device_settings_type.DeviceVCAN4SettingsType] = "vcan4"
    setting_map[e_device_settings_type.DeviceVCANRFSettingsType] = "vcanrf"
    setting_map[e_device_settings_type.DeviceVividCANSettingsType] = "vividcan"
    setting_map[e_device_settings_type.DeviceRADJupiterSettingsType] = "jupiter"
    setting_map[e_device_settings_type.DeviceFire3SettingsType] = "fire3"
    setting_map[e_device_settings_type.DeviceFire3FlexraySettingsType] = "fire3Flexray"
    setting_map[e_device_settings_type.DeviceRed2SettingsType] = "red2"
    setting_map[e_device_settings_type.DeviceRADA2BSettingsType] = "rad_a2b"
    setting_map[e_device_settings_type.DeviceOBD2LCSettingsType] = "obd2lc"

    if s.DeviceSettingType not in setting_map:
        raise KeyError(f"Error: {s.DeviceSettingType} is not a known type in setting_map")
    return getattr(s.Settings, setting_map[s.DeviceSettingType])


def print_settings(device_specific_settings):
    if hasattr(device_specific_settings, "lin1"):
        print(f"LIN 1 Baudrate: {settings.Settings.fire3.lin1.Baudrate}")
        print(f"LIN 1 Master resistor: {device_specific_settings.lin1.MasterResistor}")
    else:
        print("This device doesn't have a lin1 structure!")


if __name__ == "__main__":
    try:
        # Open the first device
        device = ics.open_device()
        print(f"Opened Device {device} (Open Client handles: {device.NumberOfClients})...")
    except ics.RuntimeError as ex:
        print(f"Failed to open first device: {ex}")
        exit(1)

    print("Loading default settings...")
    ics.load_default_settings(device)

    print("Reading settings...")
    settings = ics.get_device_settings(device)
    device_specific_settings = get_device_specific_settings(settings)
    print_settings(device_specific_settings)

    print("Writing settings...")
    device_specific_settings = get_device_specific_settings(settings)
    if hasattr(device_specific_settings, "lin1"):
        device_specific_settings.lin1.Baudrate = 19200
        device_specific_settings.lin1.MasterResistor = 0
    else:
        print("This device doesn't have a lin1 structure to change!")
    ics.set_device_settings(device, settings)
    print_settings(device_specific_settings)

    print("Reading settings...")
    settings = ics.get_device_settings(device)
    device_specific_settings = get_device_specific_settings(settings)
    print_settings(device_specific_settings)
