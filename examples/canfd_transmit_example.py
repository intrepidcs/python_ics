import ics 

if __name__ == "__main__":
    # Create a CAN Message like normal but set the StatusBitFields
    msg = ics.SpyMessage()
    msg.ArbIDOrHeader = 0x01
    msg.NetworkID = ics.NETID_HSCAN
    msg.Protocol = ics.SPY_PROTOCOL_CANFD
    msg.StatusBitField = ics.SPY_STATUS_CANFD
    msg.StatusBitField3 = ics.SPY_STATUS3_CANFD_BRS
    msg.ExtraDataPtr = tuple([x for x in range(64)]) 

    # Open Device and transmit the message
    device = ics.open_device()
    ics.transmit_messages(device, msg)