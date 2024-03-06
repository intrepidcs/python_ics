import ics

def show_clients():
    for d in ics.find_devices():
        print(d, d.NumberOfClients)

print("Find...")
devices = ics.find_devices()
show_clients()
print("Devices: ", devices)
d = ics.open_device(devices[0])
show_clients()
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
