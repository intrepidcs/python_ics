import ics
import unittest
import time

class testneoVIFIRENetworks(unittest.TestCase):
    @classmethod
    def setUpClass(self):
        self.devices = ics.find_devices()
        
    @classmethod
    def setUp(self):
        pass #time.sleep(2)

    @classmethod
    def tearDownClass(self):
        # For some reason tp_dealloc doesn't get called on
        # ics.NeoDevice when initialzed in setUpClass().
        # Lets force it here.
        del self.devices
        
    def testAutoClose(self):
        devices = ics.find_devices()
        for device in devices:
            ics.open_device(device)
        del devices # emulate NeoDevice list going out of scope
        devices = ics.find_devices()
        for device in devices:
            ics.open_device(device)
        
    def testOpenCloseByFind(self):
        # Open by ics.NeoDevice
        for device in self.devices:
            ics.open_device(device)
            ics.close_device(device)
    
    def testOpenCloseBySerial(self):
        # Open by serial number
        for device in self.devices:
            d = ics.open_device(device.SerialNumber)
            ics.close_device(d)
    
    def testOpenCloseByFirstFound(self):
        # Open by first found
        first_devices = []
        for x in range(len(self.devices)):
            first_devices.append(ics.open_device())
        # Close by API
        for device in first_devices:
            ics.close_device(device)
    
    def testOpenClose100Times(self):
        for x in range(100):
            ics.open_device(self.devices[0])
            ics.close_device(self.devices[0])
