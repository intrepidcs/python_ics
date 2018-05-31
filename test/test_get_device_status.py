import ics
import time

def print_device_status(s):
    for attr_name in dir(s):
        if attr_name.startswith('_'):
            continue
        print(attr_name, " "*(35-len(attr_name)), getattr(s, attr_name))
        if attr_name.upper() in ('FIRE2STATUS', 'VCAN4STATUS'):
            print()
            print_device_status(getattr(s, attr_name))
            print()

d = ics.open_device()
time.sleep(0.250) # Give the device time to send the frame
s = ics.get_device_status(d)
print_device_status(s)
