import ics
import random
import time

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


def calc_checksum(msg):
    checksum = 0
    for byte in msg.Header[1:] + msg.Data:
        checksum += byte
        if checksum > 255:
            checksum -= 255
    msg.Data += tuple([~checksum & 0xFF])


def transmit_lin(msg):
    calc_checksum(msg)
    msg.NumberBytesHeader = len(msg.Header)
    msg.NumberBytesData = len(msg.Data)
    try:
        ics.transmit_messages(device, msg)
    except ics.RuntimeError as ex:
        print(ex)
        raise ex


def prepare_message(device):
    msg = ics.SpyMessageJ1850()
    msg.StatusBitField = ics.SPY_STATUS_INIT_MESSAGE
    msg.Protocol = ics.SPY_PROTOCOL_LIN
    msg.NetworkID = ics.NETID_LIN
    msg.Header = (0x11, 0x11, 0x22)
    msg.Data = (0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x88)
    transmit_lin(msg)


def receive_lin(device):
    msgs, error_count = ics.get_messages(device)
    print("Received {} messages with {} errors.".format(len(msgs), error_count))
    netids = {ics.NETID_LIN: "LIN 1", ics.NETID_LIN2: "LIN 2"}
    for i, m in enumerate(msgs):
        print("\nMessage #{}: ".format(i + 1), end="")
        netid = netids.get(m.NetworkID)
        if netid is not None:
            print("{}".format(netid), end="")
        if m.StatusBitField & ics.SPY_STATUS_INIT_MESSAGE:
            print(" | Init", end="")
        data_list = []
        for x in m.Header[1:]:
            data_list.append(x)
        for y in m.Data:
            data_list.append(y)
        print("\nID: {} | ".format(hex(m.Header[0])), end="")
        if len(data_list):
            checksum = data_list.pop()
            print("Data: {} | ".format([hex(x) for x in data_list]), end="")
            print("Checksum: {}".format(hex(checksum)))


if __name__ == "__main__":
    import time

    # Lets figure out how many are connected to the PC and display it
    connected_count = len(ics.find_devices())
    print("Found {} connected device(s)...".format(connected_count))
    device = open_device(0)
    prepare_message(device)
    time.sleep(1)
    receive_lin(device)
    print("Finished.")
