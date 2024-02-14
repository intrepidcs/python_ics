import ics

# Tells our custom open_device() function to do special behavior
# with neoVI Server enabled so we can successfully open devices
enable_use_server = True


def dev_name(device):
    # Return a friendly name of the device (ie. neoVI FIRE2 CY1234)
    if int("0A0000", 36) <= device.SerialNumber <= int("ZZZZZZ", 36):
        return device.Name + " " + ics.base36enc(device.SerialNumber)
    else:
        return device.Name + " " + str(device.SerialNumber)


def open_device(index=0):
    device = None
    if enable_use_server:
        # ics.open_device() won't open a device if we have handles open already
        # so we need to find them and specify which ones to connect to.
        devices = ics.find_devices()
        print(
            "Opening Device {} (Open Client handles: {})...".format(
                dev_name(devices[index]), devices[index].NumberOfClients
            )
        )
        ics.open_device(devices[index])
        device = devices[index]
    else:
        print("Opening Device...")
        device = ics.open_device()
    print("Opened Device %s." % dev_name(device))
    return device


def transmit_can(device):
    msg = ics.SpyMessage()
    msg.ArbIDOrHeader = 0x01  # CAN Arbitration ID
    msg.Data = (1, 2, 3, 4, 5, 6, 7, 8)  # Data Bytes go here
    msg.NetworkID = ics.NETID_HSCAN  # First channel of CAN on the device

    # msg parameter here can also be a tuple of messages
    ics.transmit_messages(device, msg)


def receive_can(device):
    msgs, error_count = ics.get_messages(device)
    print("Received {} messages with {} errors.".format(len(msgs), error_count))
    for i, m in enumerate(msgs):
        print("Message #{}\t".format(i + 1), end="")
        print("\tArbID: {}\tData: {}".format(hex(m.ArbIDOrHeader), [hex(x) for x in m.Data]))


if __name__ == "__main__":
    import time

    # Lets figure out how many are connected to the PC and display it
    connected_count = len(ics.find_devices())
    print("Found {} connected device(s)...".format(connected_count))

    tx_dev = open_device(0)
    rx_dev = open_device(1)

    transmit_can(tx_dev)
    receive_can(rx_dev)

    print("Finished.")
