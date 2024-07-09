import python_ics

if __name__ == "__main__":
    # Create a CAN Message like normal but set the StatusBitFields
    msg = python_ics.SpyMessage()
    msg.ArbIDOrHeader = 0x01
    msg.NetworkID = python_ics.NETID_HSCAN
    msg.Protocol = python_ics.SPY_PROTOCOL_CANFD
    msg.StatusBitField = python_ics.SPY_STATUS_CANFD
    msg.StatusBitField3 = python_ics.SPY_STATUS3_CANFD_BRS
    msg.ExtraDataPtr = tuple([x for x in range(64)])

    # Open Device and transmit the message
    device = python_ics.open_device()
    python_ics.transmit_messages(device, msg)
