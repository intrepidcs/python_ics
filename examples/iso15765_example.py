import ics

enable_print_message = False
enable_use_server = True

# Helper Functions ##########################################################
def dev_name(device):
    if int("AA0000", 36) < device.SerialNumber < int("ZZZZZZ", 36):
        return device.Name + " " + ics.base36enc(device.SerialNumber)
    else:
        return device.Name + " " + str(device.SerialNumber)

def print_message(msg):
    if not enable_print_message:
        if isinstance(msg, ics.SpyMessage):
            print('\tArbID: {}\tData: {}'.format(hex(msg.ArbIDOrHeader), [hex(x) for x in msg.Data]))
        return
    print('\t' + str(type(msg)))
    for attribute in dir(msg):
        if attribute.startswith("_"):
            continue
        length = len(attribute)
        if attribute == 'data':
            print("\t\t{}:{}{}".format(attribute, " "*(30-length), msg.data[:msg.num_bytes]))
        else:
            value = getattr(msg, attribute)
            try:
                value = hex(value)
            except:
                pass
            print("\t\t{}:{}{}".format(attribute, " "*(30-length), value))
    print()

def open_device(index=0):
    device = None
    if enable_use_server:
        # ics.open_device() won't open a device if we have handles open already
        # so we need to find them and specify which ones to connect to.
        devices = ics.find_devices()
        print("Opening Device {} (Open Client handles: {})...".format(dev_name(devices[index]), devices[index].NumberOfClients))
        ics.open_device(devices[index])
        device = devices[index]
    else:
        print("Opening Device...")
        device = ics.open_device()
    print("Opened Device %s." % dev_name(device))
    return device

# Iso15765 Fuctions #########################################################
def transmit_iso15765_msg(device, netid=ics.NETID_HSCAN, is_canfd=False):
    number_of_bytes = 64
    msg = ics.CmISO157652TxMessage()
    msg.id = 0x7E0
    msg.vs_netid = netid
    msg.num_bytes = number_of_bytes
    msg.padding = 0xAA
    # Flow Control
    msg.fc_id = 0x7E8
    msg.fc_id_mask = 0xFFF
    msg.flowControlExtendedAddress = 0xFE
    msg.fs_timeout = 0x10 # ms
    msg.fs_wait = 0x3000 # ms
    msg.blockSize = 0
    msg.stMin = 0
    # CmISO157652TxMessage.flags bitfield union isn't implemented as of 2.12, we need to do it manually.
    msg.flags = 0
    # paddingEnable
    msg.flags |= (1 << 6)
    # CANFD: Enable + BRS
    if is_canfd:
        msg.flags |= (1 << 7) | (1 << 8)
    # tx_dl
    msg.flags |= (8 << 24)
    # Data
    msg.data = [x for x in range(number_of_bytes)]

    # Transmit the message
    print("Transmitting iso15765 message on {}...".format(dev_name(device)))
    ics.iso15765_transmit_message(device, netid, msg, 3000)
    # Wait for the messages to be transmitted, this can be calculated a lot better but works here.
    time.sleep((((number_of_bytes/8)*msg.fs_timeout)/1000.0)+0.5)
    #print_message(msg)
    print("Transmitted iso15765 message on {}.".format(dev_name(device)))

def setup_rx_iso15765_msg(device, netid=ics.NETID_HSCAN, is_canfd=False):
    msg = ics.CmISO157652RxMessage()

    msg.id = 0x7E0
    msg.vs_netid = netid
    msg.padding = 0xAA
    msg.id_mask = 0xFFF
    msg.fc_id = 0x7E8
    msg.blockSize = 100
    msg.stMin = 10
    msg.cf_timeout = 1000
    # CmISO157652RxMessage.flags bitfield union isn't implemented as of 2.12, we need to do it manually.
    msg.flags = 0
    # enableFlowControlTransmission = 1
    msg.flags |= (1 << 4)
    # paddingEnable
    msg.flags |= (1 << 5)
    # CANFD: Enable + BRS
    if is_canfd:
        msg.flags |= (1 << 6) | (1 << 7)

    print_message(msg)
    print("Setting up iso15765 message on {}...".format(dev_name(device)))
    ics.iso15765_receive_message(device, netid, msg)
    print("Setup iso15765 message on {}.".format(dev_name(device)))
    

def get_iso15765_msgs(device):
    msgs, error_count = ics.get_messages(device)
    print("Received {} messages with {} errors.".format(len(msgs), error_count))
    for i, m in enumerate(msgs):
        print('Message #{}\t'.format(i+1), end='')
        print_message(m)
    
if __name__ == "__main__":
    import time
    netid = ics.NETID_HSCAN
    
    tx_device = open_device(0)
    rx_device = open_device(1)
    
    ics.iso15765_enable_networks(tx_device, netid)
    ics.iso15765_enable_networks(rx_device, netid)
    setup_rx_iso15765_msg(rx_device)
    transmit_iso15765_msg(tx_device)
    get_iso15765_msgs(rx_device)
    
    ics.iso15765_disable_networks(tx_device)
    ics.iso15765_disable_networks(rx_device)
