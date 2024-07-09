import python_ics
import ctypes

enable_print_message = False
enable_use_server = True


# Helper Functions ##########################################################

def print_message(msg):
    if not enable_print_message:
        if isinstance(msg, python_ics.SpyMessage):
            print("\tArbID: {}\tData: {}".format(hex(msg.ArbIDOrHeader), [hex(x) for x in msg.Data]))
        return
    print("\t" + str(type(msg)))
    for attribute in dir(msg):
        if attribute.startswith("_"):
            continue
        length = len(attribute)
        if attribute == "data":
            print("\t\t{}:{}{}".format(attribute, " " * (30 - length), msg.data[: msg.num_bytes]))
        else:
            value = getattr(msg, attribute)
            try:
                value = hex(value)
            except:
                pass
            print("\t\t{}:{}{}".format(attribute, " " * (30 - length), value))
    print()


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
    print(f"Opened Device {device}.")
    return device


# Iso15765 Fuctions #########################################################
def transmit_iso15765_msg(device, netid=python_ics.NETID_HSCAN, is_canfd=False):
    number_of_bytes = 64
    msg = python_ics.st_cm_iso157652_tx_message.st_cm_iso157652_tx_message()
    msg.id = 0x7E0
    msg.vs_netid = netid
    msg.num_bytes = number_of_bytes
    msg.padding = 0xAA
    # Flow Control
    msg.fc_id = 0x7E8
    msg.fc_id_mask = 0xFFF
    msg.flowControlExtendedAddress = 0xFE
    msg.fs_timeout = 0x10  # ms
    msg.fs_wait = 0x3000  # ms
    msg.blockSize = 0
    msg.stMin = 0
    # paddingEnable
    msg.paddingEnable = 1
    # CANFD: Enable + BRS
    if is_canfd:
        msg.iscanFD = 1
        msg.isBRSEnabled = 1
    # tx_dl
    msg.tx_dl = 1
    # Data
    my_data = [x for x in range(number_of_bytes)]
    msg.data = (ctypes.c_ubyte * len(msg.data))(*my_data)

    # Transmit the message
    print("Transmitting iso15765 message on {}...".format(device))
    python_ics.iso15765_transmit_message(device, netid, msg, 3000)
    # Wait for the messages to be transmitted, this can be calculated a lot better but works here.
    time.sleep((((number_of_bytes / 8) * msg.fs_timeout) / 1000.0) + 0.5)
    # print_message(msg)
    print("Transmitted iso15765 message on {}.".format(device))


def setup_rx_iso15765_msg(device, netid=python_ics.NETID_HSCAN, is_canfd=False):
    msg = python_ics.st_cm_iso157652_rx_message.st_cm_iso157652_rx_message()

    msg.id = 0x7E0
    msg.vs_netid = netid
    msg.padding = 0xAA
    msg.id_mask = 0xFFF
    msg.fc_id = 0x7E8
    msg.blockSize = 100
    msg.stMin = 10
    msg.cf_timeout = 1000
    # enableFlowControlTransmission = 1
    msg.enableFlowControlTransmission = 1
    # paddingEnable
    msg.paddingEnable = 1
    # CANFD: Enable + BRS
    if is_canfd:
        msg.iscanFD = 1
        msg.isBRSEnabled = 1
    print_message(msg)
    print("Setting up iso15765 message on {}...".format(dev_name(device)))
    python_ics.iso15765_receive_message(device, netid, msg)
    print("Setup iso15765 message on {}.".format(dev_name(device)))


def get_iso15765_msgs(device):
    msgs, error_count = python_ics.get_messages(device)
    print("Received {} messages with {} errors.".format(len(msgs), error_count))
    for i, m in enumerate(msgs):
        print("Message #{}\t".format(i + 1), end="")
        print_message(m)


if __name__ == "__main__":
    import time

    netid = python_ics.NETID_HSCAN

    tx_device = open_device(0)
    rx_device = open_device(1)

    python_ics.iso15765_enable_networks(tx_device, netid)
    python_ics.iso15765_enable_networks(rx_device, netid)
    setup_rx_iso15765_msg(rx_device)
    transmit_iso15765_msg(tx_device)
    get_iso15765_msgs(rx_device)

    python_ics.iso15765_disable_networks(tx_device)
    python_ics.iso15765_disable_networks(rx_device)
