import ics
import time
# Tells our custom open_device() function to do special behavior
# with neoVI Server enabled so we can successfully open devices
enable_use_server = True


DATA_BYTES = tuple([x for x in range(64)])

def are_errors_present(msg):
    """Helper function to detect if a message error occurred."""
    error_flags = 0
    error_flags |= ics.SPY_STATUS_GLOBAL_ERR
    error_flags |= ics.SPY_STATUS_CRC_ERROR
    error_flags |= ics.SPY_STATUS_CAN_ERROR_PASSIVE
    error_flags |= ics.SPY_STATUS_HEADERCRC_ERROR
    error_flags |= ics.SPY_STATUS_INCOMPLETE_FRAME
    error_flags |= ics.SPY_STATUS_LOST_ARBITRATION
    error_flags |= ics.SPY_STATUS_UNDEFINED_ERROR
    error_flags |= ics.SPY_STATUS_CAN_BUS_OFF
    error_flags |= ics.SPY_STATUS_BUS_RECOVERED
    error_flags |= ics.SPY_STATUS_BUS_SHORTED_PLUS
    error_flags |= ics.SPY_STATUS_BUS_SHORTED_GND
    error_flags |= ics.SPY_STATUS_CHECKSUM_ERROR
    error_flags |= ics.SPY_STATUS_BAD_MESSAGE_BIT_TIME_ERROR
    error_flags |= ics.SPY_STATUS_TX_NOMATCH
    error_flags |= ics.SPY_STATUS_COMM_IN_OVERFLOW
    error_flags |= ics.SPY_STATUS_EXPECTED_LEN_MISMATCH
    error_flags |= ics.SPY_STATUS_MSG_NO_MATCH
    error_flags |= ics.SPY_STATUS_BREAK
    error_flags |= ics.SPY_STATUS_AVSI_REC_OVERFLOW
    error_flags |= ics.SPY_STATUS_BREAK
    if (msg.StatusBitField & error_flags) != 0:
        return True
    return False


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
        print("Opening Device {} (Open Client handles: {})...".format(
            dev_name(devices[index]), devices[index].NumberOfClients))
        ics.open_device(devices[index])
        device = devices[index]
    else:
        print("Opening Device...")
        device = ics.open_device()
    print("Opened Device %s." % dev_name(device))
    return device


def transmit_ethernet(device):
    netid = ics.NETID_ETHERNET

    msg = ics.SpyMessage()
    msg.NetworkID = netid
    msg.NetworkID2 = netid >> 8
    msg.Protocol = ics.SPY_PROTOCOL_ETHERNET
    # use broadcast in case we are using a switch (First 6 bytes)
    # use ARP packet
    # Gigalog requires this for Ethernet 10G to be detected in Vspy (0x08, 0x06)
    # Last two bytes are the network id
    data = [0x00, 0xFC, 0x70, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0x08, 0x06, netid & 0xFF, (netid >> 8) & 0xFF]
    # Append 62 random bytes on the end.
    data += [x for x in range(62)]
    msg.ExtraDataPtr = tuple(data)
    # Wait for each device to have a link - In a real application we should be checking the neoVI status messages
    time.sleep(3)
    # Clear the receive buffer for later
    _, _ = ics.get_messages(device)
    # msg parameter here can also be a tuple of messages
    ics.transmit_messages(device, msg)
    # Give the bus and buffers time to do their magic. 
    # In a real application we should poll until we find our actual message.
    time.sleep(0.5)
    # get all the messages on this device and print out the transmitted messages
    print("="*80)
    print(f"Transmitted Messages on {dev_name(device)}")
    print("="*80)
    msgs, error_count = ics.get_messages(device)
    for i, m in enumerate(msgs):
        # Only process transmitted messages
        if m.StatusBitField & ics.SPY_STATUS_TX_MSG == ics.SPY_STATUS_TX_MSG:
            print('Message #{}\t'.format(i+1), end='')
            data = m.Data if not m.ExtraDataPtr else m.ExtraDataPtr
            netid = m.NetworkID | (m.NetworkID2 << 8)
            print('NetID: {}\tArbID: {}\tData: {}\tErrors Present: {}'.format(hex(netid), hex(m.ArbIDOrHeader), [hex(x) for x in data], are_errors_present(m)))

def receive_ethernet(device):
    msgs, error_count = ics.get_messages(device)
    print("="*80)
    print(f"Received Messages on {dev_name(device)}")
    print("="*80)
    print("Received {} messages with {} errors.".format(len(msgs), error_count))
    for i, m in enumerate(msgs):
        # Ignore transmitted messages
        if m.StatusBitField & ics.SPY_STATUS_TX_MSG == ics.SPY_STATUS_TX_MSG:
            continue
        print('Message #{}\t'.format(i+1), end='')
        data = m.Data if not m.ExtraDataPtr else m.ExtraDataPtr
        netid = m.NetworkID | (m.NetworkID2 << 8)
        print('NetID: {}\tArbID: {}\tData: {}'.format(hex(netid), hex(m.ArbIDOrHeader), [hex(x) for x in data]))


if __name__ == "__main__":
    # Lets figure out how many are connected to the PC and display it
    connected_count = len(ics.find_devices())
    print("Found {} connected device(s)...".format(connected_count))

    tx_dev = open_device(0)
    rx_dev = open_device(1)

    transmit_ethernet(tx_dev)
    print()
    receive_ethernet(rx_dev)

    print("Finished.")
