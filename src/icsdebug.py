import ics

print("Find...")
devices = ics.find_devices()
print("Devices: ", devices)
d = ics.open_device(devices[0])
print("Opened", d)
print("Loading default settings...", d)
ics.load_default_settings(d)
print("Closing...")
print(ics.close_device(d))
print("Done.")

# New Style
d = devices[0]
d.open(config_read=0)
d.load_default_settings()
d.close()
