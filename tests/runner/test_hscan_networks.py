# ruff: noqa: E501
import datetime
import unittest
import time
import ics

unittest.TestLoader.sortTestMethodsUsing = None


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


class BaseTests:
    """Base classes. These are isolated and won't be run/discovered. Used for inheritance"""

    class TestCAN(unittest.TestCase):
        @classmethod
        def setUpClass(cls):
            cls.netid = None

        @classmethod
        def setUp(self):
            self.vcan42 = ics.find_devices([ics.NEODEVICE_VCAN42])[0]
            self.fire2 = ics.find_devices([ics.NEODEVICE_FIRE2])[0]
            self.fire3 = ics.find_devices([ics.NEODEVICE_FIRE3])[0]
            self.devices = [self.vcan42, self.fire2, self.fire3]
            for device in self.devices:
                ics.open_device(device)
                # ics.load_default_settings(device)

        @classmethod
        def tearDown(self):
            for device in self.devices:
                ics.close_device(device)
            del self.devices

        def _prepare_devices(self):
            for device in self.devices:
                # Clear any messages in the buffer
                _, _ = ics.get_messages(device, False, 1)
                _ = ics.get_error_messages(
                    device
                )  # Documentation is wrong -- says it can take 3 args but only takes 1
                # may need more clearing of errors here

        def _tx_rx_devices(self, tx_device, rx_devices: list):
            self._prepare_devices()
            tx_msg = ics.SpyMessage()
            tx_msg.ArbIDOrHeader = 0x01
            tx_msg.NetworkID = self.netid
            tx_msg.Protocol = ics.SPY_PROTOCOL_CANFD
            tx_msg.StatusBitField = ics.SPY_STATUS_CANFD
            tx_msg.StatusBitField3 = ics.SPY_STATUS3_CANFD_BRS
            tx_msg.ExtraDataPtr = tuple([x for x in range(64)])
            # tx HSCAN msg
            ics.transmit_messages(tx_device, tx_msg)
            # CAN ACK timeout in firmware is 200ms, so wait 300ms for ACK
            time.sleep(1)
            

            # rx HSCAN msg
            for device in rx_devices:
                # rx_messages, error_count = ics.get_messages(device, False, .01)
                # time.sleep(0.3)
                rx_messages, error_count = ics.get_messages(device, False, .01)
                self.assertEqual(error_count, 0, str(device))
                # self.assertEqual(
                #     len(rx_messages),
                #     1,
                #     f"Device {str(device)} didnt find 1 msg but {len(rx_messages)} msgs",
                # )
                for rx_msg in rx_messages:
                    if rx_msg.NetworkID == tx_msg.NetworkID:
                        if rx_msg.ArbIDOrHeader == tx_msg.ArbIDOrHeader:
                            self.assertEqual(rx_msg.ExtraDataPtr, tx_msg.ExtraDataPtr)
                            self.assertFalse(
                                are_errors_present(rx_msg),
                                f"Device {str(device)} rx msg error: {hex(rx_msg.StatusBitField)}",
                            )
                            datetime.datetime.fromtimestamp(rx_msg.TimeHardware)
                            self.assertGreater(rx_msg.TimeSystem, 0)
                            self.assertEqual(rx_msg.TimeStampHardwareID, 9)
                            self.assertEqual(rx_msg.TimeStampSystemID, 1)

            for device in self.devices:
                self.assertFalse(ics.get_error_messages(device))

        def test_vcan42_transmit(self):
            self._tx_rx_devices(self.vcan42, self.devices[1:])  # rx on fire2 and fire3

        def test_fire2_transmit(self):
            self._tx_rx_devices(
                self.fire2, [self.devices[0], self.devices[-1]]
            )  # rx on vcan42 and fire3

        def test_fire3_transmit(self):
            self._tx_rx_devices(self.fire3, self.devices[:-1])  # rx on vcan42 and fire2

        def test_spy_message(self):
            msg = ics.SpyMessage()
            with self.assertRaises(TypeError):
                msg.ArbIDOrHeader = "a"
            msg.NetworkID = 255
            with self.assertRaises(AttributeError):
                msg.Data = [x for x in range(8)]
            msg.Data = tuple([x for x in range(8)])
            self.assertTrue(msg.NumberBytesData == 8)
            msg.Data = tuple([x for x in range(16)])
            # Data gets truncated and overflow goes into ExtraDataPtr but is it correct???
            self.assertTrue(msg.NumberBytesData == 16)
            self.assertTrue(msg.Data == tuple([x for x in range(8)]))
            msg.ExtraDataPtr = tuple([x for x in range(255)])
            self.assertTrue(len(msg.ExtraDataPtr) == 255)
            msg.ExtraDataPtr = tuple([x for x in range(256)])
            self.assertIsNone(msg.ExtraDataPtr)

            msg.Data = ()
            msg.ExtraDataPtr = tuple([x for x in range(8)])
            self.assertTrue(msg.Data == msg.ExtraDataPtr)
            self.assertTrue(msg.NumberBytesData == 8)
            msg.Data = ()
            self.assertIsNone(msg.ExtraDataPtr)

            msg.ExtraDataPtr = tuple([x for x in range(16)])
            self.assertTrue(msg.Data == tuple([x for x in range(8)]))
            self.assertTrue(msg.Data == msg.ExtraDataPtr[:8])
            self.assertTrue(msg.NumberBytesData == 16)

            msg.ExtraDataPtr = ()
            self.assertTrue(msg.Data == ())

            msg.ExtraDataPtr = tuple([x for x in range(16)])
            self.assertTrue(
                msg.Data == msg.ExtraDataPtr[:8]
            )  # This looks like an error... but its fixed now???


class TestHSCAN1(BaseTests.TestCAN):
    @classmethod
    def setUpClass(cls):
        cls.netid = ics.NETID_HSCAN


class TestHSCAN2(BaseTests.TestCAN):
    @classmethod
    def setUpClass(cls):
        cls.netid = ics.NETID_HSCAN2

class TestHSCAN3(BaseTests.TestCAN):
    @classmethod
    def setUpClass(cls):
        cls.netid = ics.NETID_HSCAN3

class TestMSCAN(BaseTests.TestCAN):
    @classmethod
    def setUpClass(cls):
        cls.netid = ics.NETID_MSCAN

class TestLSFTCAN(BaseTests.TestCAN):
    @classmethod
    def setUpClass(cls):
        cls.netid = ics.NETID_LSFTCAN

class TestSWCAN(BaseTests.TestCAN):
    @classmethod
    def setUpClass(cls):
        cls.netid = ics.NETID_SWCAN


if __name__ == "__main__":
    unittest.main()
