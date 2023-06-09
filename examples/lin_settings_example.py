import ics
import random
import time

#ics.override_library_name("/home/kyle/Code/libicsneo/build/libicsneolegacy.so")

def dev_name(device):
    # Return a friendly name of the device (ie. neoVI FIRE2 CY1234)
    if int("AA0000", 36) <= device.SerialNumber <= int("ZZZZZZ", 36):
        return device.Name + " " + ics.base36enc(device.SerialNumber)
    else:
        return device.Name + " " + str(device.SerialNumber)
    
def open_new_device():
    devices = ics.find_devices()
    if(devices):
        print("Opening Device {} (Open Client handles: {})...".format(dev_name(devices[0]), devices[0].NumberOfClients))
        dev = ics.open_device(devices[0])
        return dev
    else:
        print("No devices found...")

#red2 should be defined, but is not at the moment
#fire3 is close enough to red2 to proceed
def get_device_settings(device):
    settings = ics.get_device_settings(device)
    if(settings):
        print("Settings successfully retreived from device!")
        print("LIN 1 Baudrate:" + str(settings.Settings.fire3.lin1.Baudrate))
        print("LIN 1 Master resistor:" + ("OFF" if settings.Settings.fire3.lin1.MasterResistor else "ON"))
        print("LIN 2 Baudrate:" + str(settings.Settings.fire3.lin2.Baudrate))
        print("LIN 2 Master resistor:" + ("OFF" if settings.Settings.fire3.lin2.MasterResistor else "ON"))
        return settings

    else:
        print("Settings not read!")
        return None

def set_settings(device, settings):
    if(settings is not None):
        settings.Settings.fire3.lin1.Baudrate = 19200
        settings.Settings.fire3.lin1.MasterResistor = 0
        ics.set_device_settings(device, settings)
        get_device_settings(device)
        print("Settings successfully updated!")
    else:
        print("Settings could not be set!")

if __name__ == "__main__":
    device = open_new_device()
    dev_settings = get_device_settings(device)
    set_settings(device, dev_settings)
    
