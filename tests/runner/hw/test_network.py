import unittest
import time
import python_ics
from python_ics.py_neo_device_ex import PyNeoDeviceEx
from python_ics.structures.e_device_settings_type import e_device_settings_type

unittest.TestLoader.sortTestMethodsUsing = None


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


class BaseTests:
    """Base classes. These are isolated and won't be run/discovered. Used for inheritance"""

    class TestCAN(unittest.TestCase):
        @classmethod
        def setUpClass(cls):
            cls.netid = None

        @classmethod
        def setUp(self):
            self.devices = python_ics.find_devices()
            for device in self.devices:
                device.open()
                device.load_default_settings()

        @classmethod
        def tearDown(self):
            for device in self.devices:
                device.close()

        def test_get_messages(self):
            for device in self.devices:
                messages, error_count = device.get_messages()

        def test_transmit(self):
            data = tuple([x for x in range(64)])
            tx_msg = python_ics.SpyMessage()
            tx_msg.ArbIDOrHeader = 0x01
            tx_msg.NetworkID = self.netid
            tx_msg.Protocol = python_ics.SPY_PROTOCOL_CANFD
            tx_msg.StatusBitField = python_ics.SPY_STATUS_CANFD | python_ics.SPY_STATUS_NETWORK_MESSAGE_TYPE
            tx_msg.StatusBitField3 = python_ics.SPY_STATUS3_CANFD_BRS | python_ics.SPY_STATUS3_CANFD_FDF
            tx_msg.ExtraDataPtr = data
            for device in self.devices:
                # Clear any messages in the buffer
                _, __ = device.get_messages()
                device.transmit_messages(tx_msg)
                # CAN ACK timeout in firmware is 200ms, so wait 300ms for ACK
                time.sleep(0.3)
                start = time.time()
                messages, error_count = device.get_messages(False, 1)
                elapsed = time.time() - start
                print(f"Elapsed time rx: {elapsed:.4f}s")
                self.assertEqual(error_count, 0, str(device))
                self.assertTrue(len(messages) > 0, str(device))
                # Find the transmit message
                tx_messages = []
                for message in messages:
                    if message.StatusBitField & python_ics.SPY_STATUS_TX_MSG == python_ics.SPY_STATUS_TX_MSG:
                        tx_messages.append(message)
                self.assertEqual(len(tx_messages), 1, str(device))
                for message in tx_messages:
                    # We should only have one transmit message in the buffer
                    self.assertEqual(tx_msg.ArbIDOrHeader, message.ArbIDOrHeader, str(device))
                    self.assertEqual(tx_msg.NetworkID, message.NetworkID, str(device))
                    self.assertEqual(tx_msg.ExtraDataPtr, message.ExtraDataPtr, str(device))
                    self.assertFalse(are_errors_present(message), f"{str(device)} {hex(message.StatusBitField)}")
                    self.assertEqual(
                        tx_msg.StatusBitField | python_ics.SPY_STATUS_TX_MSG,
                        message.StatusBitField,
                        f"{str(device)} {hex(tx_msg.StatusBitField| python_ics.SPY_STATUS_TX_MSG)} {hex(message.StatusBitField)}",
                    )
                    self.assertEqual(
                        tx_msg.StatusBitField3, message.StatusBitField3, f"{str(device)} {hex(message.StatusBitField3)}"
                    )


class TestHSCAN1(BaseTests.TestCAN):
    @classmethod
    def setUpClass(cls):
        cls.netid = python_ics.NETID_HSCAN


class TestHSCAN2(BaseTests.TestCAN):
    @classmethod
    def setUpClass(cls):
        cls.netid = python_ics.NETID_HSCAN2


if __name__ == "__main__":
    unittest.main()
