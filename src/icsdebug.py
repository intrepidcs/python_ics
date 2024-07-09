import python_ics

def show_clients():
    for d in python_ics.find_devices():
        print(d, d.NumberOfClients)

print("Find...")
devices = python_ics.find_devices()
show_clients()
print("Devices: ", devices)
d = python_ics.open_device(devices[0])
show_clients()
print("Opened", d)
print("Loading default settings...", d)
python_ics.load_default_settings(d)
print("Closing...")
print(python_ics.close_device(d))
print("Done.")

# New Style
d = devices[0]
d.open(config_read=0)
d.load_default_settings()
d.close()
