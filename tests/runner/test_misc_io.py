def testMISC(self):
    # dev1 = output, dev2 = input
    def _test_misc(self, state):
        arbs = (0x203, 0x204, 0x205, 0x206, 0x201, 0x202)
        for arb in arbs:
            message = ics.SpyMessage()
            message.ArbIDOrHeader = arb
            message.NetworkID = ics.NETID_DEVICE
            message.Data = (state,)
            self.assertEqual(ics.transmit_messages(self.dev1, message), None)
        # Wait for the report message to get sent
        time.sleep(0.2)
        self.assertFalse(ics.get_error_messages(self.dev1))
        self.assertFalse(ics.get_error_messages(self.dev2))
        messages, error_count = ics.get_messages(self.dev2, False, 0.5)
        self.assertEqual(error_count, 0)
        self.assertNotEqual(len(messages), 0)
        self.assertEqual(messages[-1].ArbIDOrHeader, 0x100)
        for i, arb in enumerate(arbs):
            # print(messages[-1].Data, messages[-1].Data[1]>>i & 1)
            self.assertEqual(messages[-1].Data[1] >> i & 1, state, "MISC%d PIN state is wrong" % (arb - 0x200))
        self.assertFalse(ics.get_error_messages(self.dev1))
        self.assertFalse(ics.get_error_messages(self.dev2))

    # Change the device settings
    # dev1 = output, dev2 = input
    settings = ics.get_device_settings(self.dev1)
    settings.misc_io_initial_ddr = 0x3F
    settings.misc_io_initial_latch = 0x3F
    ics.set_device_settings(self.dev1, settings)
    settings = ics.get_device_settings(self.dev2)
    settings.misc_io_initial_ddr = 0x0
    settings.misc_io_initial_latch = 0x0
    settings.misc_io_on_report_events = 0x7F
    settings.misc_io_report_period = 100
    ics.set_device_settings(self.dev2, settings)
    _test_misc(self, 1)
    _test_misc(self, 0)