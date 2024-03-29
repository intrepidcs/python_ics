import os
print(os.getpid())

import ics
devices = ics.find_devices()
print(f"Found {len(devices)} devices...")
for device in devices:
    print(device)
    ics.open_device(device)
    ics.close_device(device)

print("Done.")