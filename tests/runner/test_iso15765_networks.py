# ruff: noqa: E501
import ctypes
import datetime
import unittest
import time
import ics

unittest.TestLoader.sortTestMethodsUsing = None


def print_message(msg):
    if isinstance(msg, ics.st_cm_iso157652_rx_message.st_cm_iso157652_rx_message):
        print("\tArbID: {}\tData: {}".format(hex(msg.id), [hex(x) for x in msg.Data]))
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


class BaseTests:
    """Base classes. These are isolated and won't be run/discovered. Used for inheritance"""

    class TestISO15765(unittest.TestCase):
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
                ics.load_default_settings(device)

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
            
            netid = ics.NETID_HSCAN

            tx_device = tx_device
            rx_device = rx_devices[0]

            ics.iso15765_enable_networks(tx_device, netid)
            ics.iso15765_enable_networks(rx_device, netid)
            self.setup_rx_iso15765_msg(rx_device)
            self.transmit_iso15765_msg(tx_device)
            self.get_iso15765_msgs(rx_device)

            ics.iso15765_disable_networks(tx_device)
            ics.iso15765_disable_networks(rx_device)
            
            # tx_msg = ics.SpyMessage()
            # tx_msg.ArbIDOrHeader = 0x01
            # tx_msg.NetworkID = self.netid
            # tx_msg.Protocol = ics.SPY_PROTOCOL_CANFD
            # tx_msg.StatusBitField = ics.SPY_STATUS_CANFD
            # tx_msg.StatusBitField3 = ics.SPY_STATUS3_CANFD_BRS
            # tx_msg.ExtraDataPtr = tuple([x for x in range(64)])
            # # tx HSCAN msg
            # ics.transmit_messages(tx_device, tx_msg)
            # # CAN ACK timeout in firmware is 200ms, so wait 300ms for ACK
            # time.sleep(0.3)

            # # rx HSCAN msg
            # for device in rx_devices:
            #     rx_messages, error_count = ics.get_messages(device, False, 1)
            #     self.assertEqual(error_count, 0, str(device))
            #     self.assertEqual(
            #         len(rx_messages),
            #         1,
            #         f"Device {str(device)} didnt find 1 msg but {len(rx_messages)} msgs",
            #     )
            #     for rx_msg in rx_messages:
            #         if rx_msg.NetworkID == tx_msg.NetworkID:
            #             if rx_msg.ArbIDOrHeader == tx_msg.ArbIDOrHeader:
            #                 self.assertEqual(rx_msg.ExtraDataPtr, tx_msg.ExtraDataPtr)
            #                 self.assertFalse(
            #                     are_errors_present(rx_msg),
            #                     f"Device {str(device)} rx msg error: {hex(rx_msg.StatusBitField)}",
            #                 )
            #                 datetime.datetime.fromtimestamp(rx_msg.TimeHardware)
            #                 self.assertGreater(rx_msg.TimeSystem, 0)
            #                 self.assertEqual(rx_msg.TimeStampHardwareID, 9)
            #                 self.assertEqual(rx_msg.TimeStampSystemID, 1)

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
        
        def setup_rx_iso15765_msg(self, device, netid=ics.NETID_HSCAN, is_canfd=False):
            msg = ics.st_cm_iso157652_rx_message.st_cm_iso157652_rx_message()

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
            # print_message(msg)
            print("Setting up iso15765 message on {}...".format(device))
            ics.iso15765_receive_message(device, netid, msg)
            print("Setup iso15765 message on {}.".format(device))
        
        def transmit_iso15765_msg(self, device, netid=ics.NETID_HSCAN, is_canfd=False):
            number_of_bytes = 64
            msg = ics.st_cm_iso157652_tx_message.st_cm_iso157652_tx_message()
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
            ics.iso15765_transmit_message(device, netid, msg, 3000)
            time.sleep(0.5)
            print_message(msg)
            print("Transmitted iso15765 message on {}.".format(device))

        def get_iso15765_msgs(self, device):
            msgs, error_count = ics.get_messages(device, False, 1)
            print("Received {} messages with {} errors.".format(len(msgs), error_count))
            for i, m in enumerate(msgs):
                print("Message #{}\t".format(i + 1), end="")
                print_message(m)


class TestHSCAN1(BaseTests.TestISO15765):
    @classmethod
    def setUpClass(cls):
        cls.netid = ics.NETID_HSCAN


if __name__ == "__main__":
    unittest.main()
