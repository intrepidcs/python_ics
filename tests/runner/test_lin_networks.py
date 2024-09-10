# ruff: noqa: E501
import unittest
import time
import ics

unittest.TestLoader.sortTestMethodsUsing = None


class BaseTests:
    """Base classes. These are isolated and won't be run/discovered. Used for inheritance"""

    class TestCAN(unittest.TestCase):
        @classmethod
        def setUpClass(cls):
            cls.netid = None

        @classmethod
        def setUp(self):
            self.fire2 = ics.find_devices([ics.NEODEVICE_FIRE2])[0]
            self.fire3 = ics.find_devices([ics.NEODEVICE_FIRE3])[0]
            self.devices = [self.fire2, self.fire3]
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
                _ = ics.get_error_messages(device)  # Documentation is wrong -- says it can take 3 args but only takes 1
                # may need more clearing of errors here
        
        def _tx_rx_lin_devices(self, master_dev, slave_dev):
            self._prepare_devices()
            
            master_msg = ics.SpyMessageJ1850()
            master_msg.Header = (0xC1,)
            master_msg.NetworkID = ics.NETID_LIN
            master_msg.Data = ()
            master_msg.StatusBitField = ics.SPY_STATUS_LIN_MASTER
            
            slave_msg = ics.SpyMessageJ1850()
            slave_msg.Header = (0xC1,)
            slave_msg.NetworkID = self.netid
            slave_msg.Data = tuple([x for x in range(8)])
            slave_msg.Protocol = ics.SPY_PROTOCOL_LIN
            checksum = 0
            for byte in slave_msg.Data + slave_msg.Header[1:3]:
                checksum += byte
                if checksum > 255:
                    checksum -= 255
            slave_msg.Data += ((~checksum & 0xFF),)
            
            # transmit slave msg first
            ics.transmit_messages(slave_dev, slave_msg)
            time.sleep(0.5)
            
            # transmit master msg
            ics.transmit_messages(master_dev, master_msg)
            time.sleep(0.5)
            
            # find msg
            rx_msgs, errors = ics.get_messages(slave_dev, False, 1)
            self.assertFalse(errors)
            # Should only see 1 msg but sometimes we get 2
            self.assertTrue(len(rx_msgs) == 1 or len(rx_msgs) == 2)
            for msg in rx_msgs:
                if msg.NetworkID == master_msg.NetworkID:
                    if msg.ArbIDOrHeader == master_msg.Header:
                        if msg.Data == master_msg.Data:
                            break
            
            for device in self.devices:
                self.assertFalse(ics.get_error_messages(device))
        
        def test_fire2_master_tx(self):
            self._tx_rx_lin_devices(self.fire2, self.fire3)
        
        def test_fire3_master_tx(self):
            self._tx_rx_lin_devices(self.fire3, self.fire2)


class TestLIN1(BaseTests.TestCAN):
    @classmethod
    def setUpClass(cls):
        cls.netid = ics.NETID_LIN


class TestLIN2(BaseTests.TestCAN):
    @classmethod
    def setUpClass(cls):
        cls.netid = ics.NETID_LIN2

class TestLIN3(BaseTests.TestCAN):
    @classmethod
    def setUpClass(cls):
        cls.netid = ics.NETID_LIN3

class TestLIN4(BaseTests.TestCAN):
    @classmethod
    def setUpClass(cls):
        cls.netid = ics.NETID_LIN4

if __name__ == "__main__":
    unittest.main()
