import python_ics
import unittest
import time
import random


class testneoVIFIRENetworks(unittest.TestCase):
    @classmethod
    def setUpClass(self):
        devices = python_ics.find_devices(python_ics.NEODEVICE_FIRE)
        python_ics.open_device(devices[0])
        python_ics.open_device(devices[1])
        self.dev1 = devices[0]
        self.dev2 = devices[1]

    @classmethod
    def setUp(self):
        python_ics.load_default_settings(self.dev1)
        python_ics.load_default_settings(self.dev2)

        # Make sure we start with a "clean" network
        python_ics.get_error_messages(self.dev1)
        python_ics.get_error_messages(self.dev2)
        python_ics.get_messages(self.dev1, False, 0.1)
        python_ics.get_messages(self.dev2, False, 0.1)

    @classmethod
    def tearDownClass(self):
        # For some reason tp_dealloc doesn't get called on
        # python_ics.NeoDevice when initialzed in setUpClass().
        # Lets force it here.
        del self.dev1
        del self.dev2

    def testCAN(self):
        message = python_ics.SpyMessage()
        message.ArbIDOrHeader = 0xFF
        message.Data = (1, 2, 3, 4, 5, 6, 7, 8)
        for network in (
            python_ics.NETID_HSCAN,
            python_ics.NETID_MSCAN,
            python_ics.NETID_HSCAN2,
            python_ics.NETID_HSCAN3,
            python_ics.NETID_LSFTCAN,
            python_ics.NETID_SWCAN,
        ):
            message.NetworkID = network
            try:
                self.assertTrue(python_ics.transmit_messages(self.dev1, message) == None, network)
            except python_ics.RuntimeError as ex:
                print(ex, network)
                raise ex
            self.assertFalse(python_ics.get_error_messages(self.dev1))
            self.assertFalse(python_ics.get_error_messages(self.dev2))
            messages, error_count = python_ics.get_messages(self.dev1, False, 0.1)
            self.assertEqual(error_count, 0)
            self.assertEqual(len(messages), 1)
            self.assertEqual(message.ArbIDOrHeader, messages[0].ArbIDOrHeader)
            self.assertEqual(message.NetworkID, messages[0].NetworkID)
            self.assertEqual(message.Data, messages[0].Data)
            self.assertFalse(python_ics.get_error_messages(self.dev1))
            self.assertFalse(python_ics.get_error_messages(self.dev2))

    def testLIN(self):
        message = python_ics.SpyMessageJ1850()
        message.Header = (0x3C, 1, 2)
        message.StatusBitField = python_ics.SPY_STATUS_NETWORK_MESSAGE_TYPE | python_ics.SPY_STATUS_LIN_MASTER
        message.Protocol = python_ics.SPY_PROTOCOL_LIN

        for network in (python_ics.NETID_LIN, python_ics.NETID_LIN2, python_ics.NETID_LIN3, python_ics.NETID_LIN4):
            message.NetworkID = network
            message.Data = tuple([random.randint(x, 0xFF) for x in range(6)])
            # Generate the checksum
            checksum = 0
            for byte in message.Data + message.Header[1:3]:
                checksum += byte
                if checksum > 255:
                    checksum -= 255
            message.Data += ((~checksum & 0xFF),)
            self.assertTrue(python_ics.transmit_messages(self.dev1, message) == None)
            self.assertFalse(python_ics.get_error_messages(self.dev1))
            self.assertFalse(python_ics.get_error_messages(self.dev2))
            messages, error_count = python_ics.get_messages(self.dev1, False, 0.1)
            self.assertEqual(error_count, 0)
            self.assertEqual(len(messages), 1)
            self.assertEqual(message.Header, messages[0].Header)
            self.assertEqual(message.NetworkID, messages[0].NetworkID)
            self.assertEqual(message.Data[0:-1], messages[0].Data)
            self.assertFalse(python_ics.get_error_messages(self.dev1))
            self.assertFalse(python_ics.get_error_messages(self.dev2))

    def testMISC(self):
        # dev1 = output, dev2 = input
        def _test_misc(self, state):
            arbs = (0x203, 0x204, 0x205, 0x206, 0x201, 0x202)
            for arb in arbs:
                message = python_ics.SpyMessage()
                message.ArbIDOrHeader = arb
                message.NetworkID = python_ics.NETID_DEVICE
                message.Data = (state,)
                self.assertEqual(python_ics.transmit_messages(self.dev1, message), None)
            # Wait for the report message to get sent
            time.sleep(0.2)
            self.assertFalse(python_ics.get_error_messages(self.dev1))
            self.assertFalse(python_ics.get_error_messages(self.dev2))
            messages, error_count = python_ics.get_messages(self.dev2, False, 0.5)
            self.assertEqual(error_count, 0)
            self.assertNotEqual(len(messages), 0)
            self.assertEqual(messages[-1].ArbIDOrHeader, 0x100)
            for i, arb in enumerate(arbs):
                # print(messages[-1].Data, messages[-1].Data[1]>>i & 1)
                self.assertEqual(messages[-1].Data[1] >> i & 1, state, "MISC%d PIN state is wrong" % (arb - 0x200))
            self.assertFalse(python_ics.get_error_messages(self.dev1))
            self.assertFalse(python_ics.get_error_messages(self.dev2))

        # Change the device settings
        # dev1 = output, dev2 = input
        settings = python_ics.get_device_settings(self.dev1)
        settings.misc_io_initial_ddr = 0x3F
        settings.misc_io_initial_latch = 0x3F
        python_ics.set_device_settings(self.dev1, settings)
        settings = python_ics.get_device_settings(self.dev2)
        settings.misc_io_initial_ddr = 0x0
        settings.misc_io_initial_latch = 0x0
        settings.misc_io_on_report_events = 0x7F
        settings.misc_io_report_period = 100
        python_ics.set_device_settings(self.dev2, settings)
        _test_misc(self, 1)
        _test_misc(self, 0)
