import unittest
import time
import ics

unittest.TestLoader.sortTestMethodsUsing = None


error_flags = {
    ics.SPY_STATUS_GLOBAL_ERR: "SPY_STATUS_GLOBAL_ERR",
    ics.SPY_STATUS_CRC_ERROR: "SPY_STATUS_CRC_ERROR",
    ics.SPY_STATUS_GLOBAL_ERR: "SPY_STATUS_GLOBAL_ERR",
    ics.SPY_STATUS_CRC_ERROR: "SPY_STATUS_CRC_ERROR",
    ics.SPY_STATUS_CAN_ERROR_PASSIVE: "SPY_STATUS_CAN_ERROR_PASSIVE",
    ics.SPY_STATUS_HEADERCRC_ERROR: "SPY_STATUS_HEADERCRC_ERROR",
    ics.SPY_STATUS_INCOMPLETE_FRAME: "SPY_STATUS_INCOMPLETE_FRAME",
    ics.SPY_STATUS_LOST_ARBITRATION: "SPY_STATUS_LOST_ARBITRATION",
    ics.SPY_STATUS_UNDEFINED_ERROR: "SPY_STATUS_UNDEFINED_ERROR",
    ics.SPY_STATUS_CAN_BUS_OFF: "SPY_STATUS_CAN_BUS_OFF",
    ics.SPY_STATUS_BUS_RECOVERED: "SPY_STATUS_BUS_RECOVERED",
    ics.SPY_STATUS_BUS_SHORTED_PLUS: "SPY_STATUS_BUS_SHORTED_PLUS",
    ics.SPY_STATUS_BUS_SHORTED_GND: "SPY_STATUS_BUS_SHORTED_GND",
    ics.SPY_STATUS_CHECKSUM_ERROR: "SPY_STATUS_CHECKSUM_ERROR",
    ics.SPY_STATUS_BAD_MESSAGE_BIT_TIME_ERROR: (
        "SPY_STATUS_BAD_MESSAGE_BIT_TIME_ERROR"
    ),
    ics.SPY_STATUS_TX_NOMATCH: "SPY_STATUS_TX_NOMATCH",
    ics.SPY_STATUS_COMM_IN_OVERFLOW: "SPY_STATUS_COMM_IN_OVERFLOW",
    ics.SPY_STATUS_EXPECTED_LEN_MISMATCH: "SPY_STATUS_EXPECTED_LEN_MISMATCH",
    ics.SPY_STATUS_MSG_NO_MATCH: "SPY_STATUS_MSG_NO_MATCH",
    ics.SPY_STATUS_BREAK: "SPY_STATUS_BREAK",
    ics.SPY_STATUS_AVSI_REC_OVERFLOW: "SPY_STATUS_AVSI_REC_OVERFLOW",
    ics.SPY_STATUS_BREAK: "SPY_STATUS_AVSI_REC_OVERFLOW",
}


class BaseTests:
    """Base classes. These are isolated and won't be run/discovered. Used for inheritance"""

    class TestCAN(unittest.TestCase):
        @classmethod
        def setUp(self):
            self.fire2 = ics.find_devices([ics.NEODEVICE_FIRE2])[0]
            self.fire3 = ics.find_devices([ics.NEODEVICE_FIRE3])[0]
            self.devices = [self.fire2, self.fire3]
            for device in self.devices:
                ics.open_device(device)
                ics.load_default_settings(device)
                _, _ = ics.get_messages(device, False, 1)

        @classmethod
        def tearDown(self):
            for device in self.devices:
                _, _ = ics.get_messages(device, False, 1)
                ics.close_device(device)

        def _check_ethernet_link(self, toggle_com, device, netid):
            # Enable network comm to push status message and clear previous messages
            if toggle_com:
                ics.enable_network_com(device, False)
                _, _ = ics.get_messages(device, False, 0.5)
                ics.enable_network_com(device, True)
            # Search for neoVI ethernet status msg and check for link up
            netid_lower = netid & 0xFF
            netid_upper = (netid & 0xFF00) >> 8
            msgs, _ = ics.get_messages(device, False, 1)
            for msg in msgs:
                if msg.NetworkID == ics.NETID_DEVICE and msg.ArbIDOrHeader == 0x162:
                    if (
                        msg.Data[0] == 1
                        and msg.Data[3] == netid_lower
                        and msg.Data[4] == netid_upper
                    ):
                        return True
            return False

        def _test_tx_rx(self, tx_dev, rx_dev, tx_msg, rx_netid):
            # clear buffers
            _, _ = ics.get_messages(tx_dev, False, 1)
            _, _ = ics.get_messages(rx_dev, False, 1)
            found = False
            # Transmit message, We aren't guarenteed to receive ethernet on the other side so we "have" to transmit more
            # than one message and hope at least one gets through.
            for _ in range(20):
                if found:
                    break
                ics.transmit_messages(tx_dev, tx_msg)
                time.sleep(0.1)
                _, _ = ics.get_messages(tx_dev, False, 0)
                # Process the messages
                rx_msgs, errors = ics.get_messages(rx_dev, False, 2)
                for rx_msg in rx_msgs:
                    # Fire2 eth1 <-> Fire3 eth3
                    netid = (rx_msg.NetworkID2 << 8) | rx_msg.NetworkID
                    if netid == rx_netid:
                        if tx_msg.Protocol == rx_msg.Protocol:
                            if tx_msg.ExtraDataPtr == rx_msg.ExtraDataPtr[:-4]:
                                # We found the message, lets make sure there are no errors present.
                                if rx_msg.StatusBitField in error_flags.keys():
                                    raise Exception(
                                        f"{rx_dev} rx msg error: {error_flags[rx_msg.StatusBitField]}"
                                    )
                                else:
                                    found = True
                                    break

            if not found:
                raise Exception(f"Failed to find tx msg on {rx_dev}")

        def test_ethernet_fire2(self):
            start_time = time.time()
            toggle_com = True
            while not self._check_ethernet_link(
                toggle_com, self.fire2, self.fire2_netid
            ):
                toggle_com = False
                if time.time() - start_time > 10.0:
                    raise TimeoutError(
                        f"Failed to establish link in 10sec on {self.fire2}"
                    )
            time.sleep(1)

            # Create SpyMessage for transmission
            ics_mac_address = (0x00, 0xFC, 0x70, 0xFF, 0xDE, 0xAD)
            ether_type = (0xFF, 0xFF)
            payload_size = 64
            tx_msg = ics.SpyMessage()
            tx_msg.NetworkID = self.fire2_netid & 0xFF
            tx_msg.NetworkID2 = (self.fire2_netid >> 8) & 0xFF
            tx_msg.Protocol = ics.SPY_PROTOCOL_ETHERNET
            tx_msg.ExtraDataPtr = (
                (self.fire2_netid,)
                + ics_mac_address
                + ics_mac_address
                + ether_type
                + tuple([x & 0xFF for x in range(payload_size)])
            )

            self._test_tx_rx(self.fire2, self.fire3, tx_msg, self.fire3_netid)

        def test_ethernet_fire3(self):
            start_time = time.time()
            toggle_com = True
            while not self._check_ethernet_link(
                toggle_com, self.fire3, self.fire3_netid
            ):
                toggle_com = False
                if time.time() - start_time > 10.0:
                    raise TimeoutError(
                        f"Failed to establish link in 10sec on {self.fire3}"
                    )
            time.sleep(1)

            # Create SpyMessage for transmission
            ics_mac_address = (0x00, 0xFC, 0x70, 0xFF, 0xDE, 0xAD)
            ether_type = (0xFF, 0xFF)
            payload_size = 64
            tx_msg = ics.SpyMessage()
            tx_msg.NetworkID = self.fire3_netid & 0xFF
            tx_msg.NetworkID2 = (self.fire3_netid >> 8) & 0xFF
            tx_msg.Protocol = ics.SPY_PROTOCOL_ETHERNET
            tx_msg.ExtraDataPtr = (
                (self.fire3_netid,)
                + ics_mac_address
                + ics_mac_address
                + ether_type
                + tuple([x & 0xFF for x in range(payload_size)])
            )

            self._test_tx_rx(self.fire3, self.fire2, tx_msg, self.fire2_netid)


class TestEthernet(BaseTests.TestCAN):
    @classmethod
    def setUpClass(cls):
        # fire3 ethernet2 <-> fire2 ethernet1
        # fire3 VEM IS NEEDED!
        cls.fire3_netid = ics.NETID_ETHERNET3
        cls.fire2_netid = ics.NETID_ETHERNET


if __name__ == "__main__":
    unittest.main()
