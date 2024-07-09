import python_ics

# Tells our custom open_device() function to do special behavior
# with neoVI Server enabled so we can successfully open devices
enable_use_server = True


def open_device(index=0):
    device = None
    if enable_use_server:
        # python_ics.open_device() won't open a device if we have handles open already
        # so we need to find them and specify which ones to connect to.
        devices = python_ics.find_devices()
        print(
            "Opening Device {} (Open Client handles: {})...".format(
                devices[index], devices[index].NumberOfClients
            )
        )
        python_ics.open_device(devices[index])
        device = devices[index]
    else:
        print("Opening Device...")
        device = python_ics.open_device()
    print("Opened Device %s." % device)
    return device


if __name__ == "__main__":
    # Lets figure out how many are connected to the PC and display it
    connected_count = len(python_ics.find_devices())
    print("Found {} connected device(s)...".format(connected_count))
    for i in range(connected_count):
        # Lets open the device
        device = open_device(i)
        # the device will automatically close here
        # because the device object is going out of
        # scope.
    print("Finished.")
