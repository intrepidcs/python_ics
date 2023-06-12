import ics
import random
import time

def dev_name(device):
    # Return a friendly name of the device (ie. neoVI FIRE2 CY1234)
    if int("A00000", 36) <= device.SerialNumber <= int("ZZZZZZ", 36):
        return device.Name + " " + ics.base36enc(device.SerialNumber)
    else:
        return device.Name + " " + str(device.SerialNumber)

def print_settings(settings):
    print("LIN 1 Baudrate:" + str(settings.Settings.fire3.lin1.Baudrate))
    print("LIN 1 Master resistor:" + ("OFF" if settings.Settings.fire3.lin1.MasterResistor else "ON"))
    print("LIN 2 Baudrate:" + str(settings.Settings.fire3.lin2.Baudrate))
    print("LIN 2 Master resistor:" + ("OFF" if settings.Settings.fire3.lin2.MasterResistor else "ON"))

if __name__ == "__main__":
    try:
        # Open the first device
        device = ics.open_device()
        print("Opened Device {dev_name(device)} (Open Client handles: {device.NumberOfClients})...")
    except ics.RuntimeError as ex:
        print("Failed to open first device: {ex}")
        exit(1)
    print("Reading settings...")
    settings = ics.get_device_settings(device)
    print(settings)
    print("Writing settings...")
    settings.Settings.fire3.lin1.Baudrate = 19200
    settings.Settings.fire3.lin1.MasterResistor = 0
    ics.set_device_settings(device, settings)
    print(settings)
