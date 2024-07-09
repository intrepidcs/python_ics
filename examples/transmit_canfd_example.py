import python_ics
import time

# Tells our custom open_device() function to do special behavior
# with neoVI Server enabled so we can successfully open devices
enable_use_server = True


DATA_BYTES = tuple([x for x in range(64)])


def are_errors_present(msg):
    """Helper function to detect if a message error occurred."""
    error_flags = 0
    error_flags |= python_ics.SPY_STATUS_GLOBAL_ERR
    error_flags |= python_ics.SPY_STATUS_CRC_ERROR
    error_flags |= python_ics.SPY_STATUS_CAN_ERROR_PASSIVE
    error_flags |= python_ics.SPY_STATUS_HEADERCRC_ERROR
    error_flags |= python_ics.SPY_STATUS_INCOMPLETE_FRAME
    error_flags |= python_ics.SPY_STATUS_LOST_ARBITRATION
    error_flags |= python_ics.SPY_STATUS_UNDEFINED_ERROR
    error_flags |= python_ics.SPY_STATUS_CAN_BUS_OFF
    error_flags |= python_ics.SPY_STATUS_BUS_RECOVERED
    error_flags |= python_ics.SPY_STATUS_BUS_SHORTED_PLUS
    error_flags |= python_ics.SPY_STATUS_BUS_SHORTED_GND
    error_flags |= python_ics.SPY_STATUS_CHECKSUM_ERROR
    error_flags |= python_ics.SPY_STATUS_BAD_MESSAGE_BIT_TIME_ERROR
    error_flags |= python_ics.SPY_STATUS_TX_NOMATCH
    error_flags |= python_ics.SPY_STATUS_COMM_IN_OVERFLOW
    error_flags |= python_ics.SPY_STATUS_EXPECTED_LEN_MISMATCH
    error_flags |= python_ics.SPY_STATUS_MSG_NO_MATCH
    error_flags |= python_ics.SPY_STATUS_BREAK
    error_flags |= python_ics.SPY_STATUS_AVSI_REC_OVERFLOW
    error_flags |= python_ics.SPY_STATUS_BREAK
    if (msg.StatusBitField & error_flags) != 0:
        return True
    return False


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


def transmit_can(device):
    msg = python_ics.SpyMessage()
    msg.ArbIDOrHeader = 0x01  # CAN Arbitration ID
    msg.NetworkID = python_ics.NETID_HSCAN  # First channel of CAN on the device
    msg.Protocol = python_ics.SPY_PROTOCOL_CANFD
    msg.StatusBitField = python_ics.SPY_STATUS_CANFD
    msg.StatusBitField3 = python_ics.SPY_STATUS3_CANFD_BRS
    msg.ExtraDataPtr = DATA_BYTES

    # Clear the receive buffer for later
    _, _ = python_ics.get_messages(device)
    # msg parameter here can also be a tuple of messages
    python_ics.transmit_messages(device, msg)
    # Give the bus and buffers time to do their magic.
    # In a real application we should poll until we find our actual message.
    time.sleep(0.5)
    # get all the messages on this device and print out the transmitted messages
    print("=" * 80)
    print(f"Transmitted Messages on {device}")
    print("=" * 80)
    msgs, error_count = python_ics.get_messages(device)
    for i, m in enumerate(msgs):
        # Only process transmitted messages
        if m.StatusBitField & python_ics.SPY_STATUS_TX_MSG == python_ics.SPY_STATUS_TX_MSG:
            print("Message #{}\t".format(i + 1), end="")
            data = m.Data if not m.ExtraDataPtr else m.ExtraDataPtr
            netid = m.NetworkID | (m.NetworkID2 << 8)
            print(
                "NetID: {}\tArbID: {}\tData: {}\tErrors Present: {}".format(
                    hex(netid), hex(m.ArbIDOrHeader), [hex(x) for x in data], are_errors_present(m)
                )
            )


def receive_can(device):
    msgs, error_count = python_ics.get_messages(device)
    print("=" * 80)
    print(f"Received Messages on {device}")
    print("=" * 80)
    print("Received {} messages with {} errors.".format(len(msgs), error_count))
    for i, m in enumerate(msgs):
        # Ignore transmitted messages
        if m.StatusBitField & python_ics.SPY_STATUS_TX_MSG == python_ics.SPY_STATUS_TX_MSG:
            continue
        # if m.Protocol != python_ics.SPY_PROTOCOL_CANFD:
        #    continue
        print("Message #{}\t".format(i + 1), end="")
        data = m.Data if not m.ExtraDataPtr else m.ExtraDataPtr
        netid = m.NetworkID | (m.NetworkID2 << 8)
        print("NetID: {}\tArbID: {}\tData: {}".format(hex(netid), hex(m.ArbIDOrHeader), [hex(x) for x in data]))


if __name__ == "__main__":
    # Lets figure out how many are connected to the PC and display it
    connected_count = len(python_ics.find_devices())
    print("Found {} connected device(s)...".format(connected_count))

    tx_dev = open_device(0)
    rx_dev = open_device(1)

    transmit_can(tx_dev)
    print()
    receive_can(rx_dev)

    print("Finished.")
