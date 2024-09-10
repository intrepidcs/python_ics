import unittest
import time
import ics

unittest.TestLoader.sortTestMethodsUsing = None


def __spy_status_validate_errors(status_bit_field: int, msg: str) -> tuple[bool, str]:
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
        ics.SPY_STATUS_BAD_MESSAGE_BIT_TIME_ERROR: ("SPY_STATUS_BAD_MESSAGE_BIT_TIME_ERROR"),
        ics.SPY_STATUS_TX_NOMATCH: "SPY_STATUS_TX_NOMATCH",
        ics.SPY_STATUS_COMM_IN_OVERFLOW: "SPY_STATUS_COMM_IN_OVERFLOW",
        ics.SPY_STATUS_EXPECTED_LEN_MISMATCH: "SPY_STATUS_EXPECTED_LEN_MISMATCH",
        ics.SPY_STATUS_MSG_NO_MATCH: "SPY_STATUS_MSG_NO_MATCH",
        ics.SPY_STATUS_BREAK: "SPY_STATUS_BREAK",
        ics.SPY_STATUS_AVSI_REC_OVERFLOW: "SPY_STATUS_AVSI_REC_OVERFLOW",
        ics.SPY_STATUS_BREAK: "SPY_STATUS_AVSI_REC_OVERFLOW",
    }
    if status_bit_field in error_flags.keys():
        return False, error_flags[status_bit_field]
    return True, msg

class BaseTests:
    """Base classes. These are isolated and won't be run/discovered. Used for inheritance"""

    class TestCAN(unittest.TestCase):
        @classmethod
        def setUpClass(cls):
            cls.netid = None

        @classmethod
        def setUp(self):
            self.devices = ics.find_devices([ics.NEODEVICE_FIRE2, ics.NEODEVICE_FIRE3])
            for device in self.devices:
                ics.open_device(device)
                ics.load_default_settings(device)
                _, _ = ics.get_messages(device, False, 1)

        @classmethod
        def tearDown(self):
            for device in self.devices:
                _, _ = ics.get_messages(device, False, 1)
                ics.close_device(device)

        def _check_ethernet_link(self, toggle_com, device):
            # Enable network comm to push status message and clear previous messages
            if toggle_com:
                ics.enable_network_com(device, False)
                _, _ = ics.get_messages(device, False, 0.5)
                ics.enable_network_com(device, True)
            # Search for neoVI ethernet status msg and check for link up
            netid_lower = self.netid & 0xFF
            netid_upper = (self.netid & 0xFF00) >> 8
            msgs, _ = ics.get_messages(device, False, 1)
            for msg in msgs:
                if msg.NetworkID == ics.NETID_DEVICE and msg.ArbIDOrHeader == 0x162:
                    if msg.Data[0] == 1 and msg.Data[3] == netid_lower and msg.Data[4] == netid_upper:
                        return True
            return False
        
        def _test_tx_rx(self, tx_dev, rx_dev, tx_msg):
            # clear buffers
            _, _ = ics.get_messages(tx_dev, False, 1)
            _, _ = ics.get_messages(rx_dev, False, 1)
            found = False
            # Transmit message, We aren't guarenteed to receive ethernet on the other side so we "have" to transmit more
            # than one message and hope at least one gets through.
            for _ in range(20):
                ics.transmit_messages(tx_dev, tx_msg)
                time.sleep(0.1)
                _tx_msgs = ics.get_messages(tx_dev, False, 0)
                # Process the messages
                rx_msgs, errors = ics.get_messages(rx_dev, False, 2)
                print(f"Processing {len(rx_msgs)} received messages...")
                for rx_msg in rx_msgs:
                    if tx_msg.NetworkID == rx_msg.NetworkID:
                        if tx_msg.Protocol == rx_msg.Protocol:
                            if tx_msg.ExtraDataPtr == rx_msg.ExtraDataPtr:
                                # We found the message, lets make sure there are no errors present.
                                success, info = __spy_status_validate_errors(rx_msg.StatusBitField, "")
                                if success:
                                    found = True
                                    break
                                else:
                                    raise Exception(f"{rx_dev} rx msg error: {info}")
            if not found:
                raise Exception(f"Failed to find tx msg on {rx_dev}")
        
        def test_tx_rx_ethernet(self):
            dev1 = self.devices[0]
            dev2 = self.devices[1]
            start_time = time.time()
            toggle_com = True
            while not self._check_ethernet_link(toggle_com, dev1):
                toggle_com = False
                if time.time() - start_time > 10.0:
                    raise TimeoutError(f"Failed to establish link in 10sec on {dev1}")
            print(f"Link established on {dev1}")
            time.sleep(1)
            
            # Create a Raw ethernet frame SpyMessage for transmission
            ics_mac_address = (0x00, 0xFC, 0x70, 0xFF, 0xDE, 0xAD)
            ether_type = (0xFF, 0xFF)
            tx_msg = ics.SpyMessage()
            tx_msg.NetworkID = self.netid & 0xFF
            tx_msg.Protocol = ics.SPY_PROTOCOL_ETHERNET
            tx_msg.ExtraDataPtr = (self.netid,) + ics_mac_address + ics_mac_address + ether_type + tuple([x & 0xFF for x in range(100)])

            self._test_tx_rx(dev1, dev2, tx_msg)
            self._test_tx_rx(dev2, dev1, tx_msg)
            


class TestEthernet(BaseTests.TestCAN):
    @classmethod
    def setUpClass(cls):
        cls.netid = ics.NETID_ETHERNET


if __name__ == "__main__":
    unittest.main()
