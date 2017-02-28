import ics
import unittest
import random
import time
import os

from cmvspy import data

class testCoreMini(unittest.TestCase):
    def _clear_coremini(self):
        if self.dev1.DeviceType == ics.NEODEVICE_VCAN3:
            ics.coremini_clear(self.dev1, ics.SCRIPT_LOCATION_VCAN3_MEM)
        else:
            ics.coremini_clear(self.dev1, ics.SCRIPT_LOCATION_FLASH_MEM)
            ics.coremini_clear(self.dev1, ics.SCRIPT_LOCATION_SDCARD)
        
    @classmethod
    def setUpClass(self):
        #input() # for debugging purposes
        self.dev1 = ics.open_device()
        self._clear_coremini(self)

    @classmethod
    def tearDownClass(self):
        # For some reason tp_dealloc doesn't get called on
        # ics.NeoDevice when initialzed in setUpClass().
        # Lets force it here.
        self._clear_coremini(self)
        del self.dev1

    def testStartStop(self):
        def load_coremini(self, contents, location):
            self.assertFalse(ics.coremini_get_status(self.dev1))
            ics.coremini_load(self.dev1, contents, location)
            ics.coremini_start(self.dev1, location)
            self.assertTrue(ics.coremini_get_status(self.dev1))
            time.sleep(2)
            ics.coremini_clear(self.dev1, location)
            time.sleep(0.1)
            self.assertFalse(ics.coremini_get_status(self.dev1))
        # This allows us to work in other directories and leave the vs3cmb file
        # inside same directory as the script.
        vs3file = os.path.dirname(os.path.realpath(__file__)) + '/cmvspy.vs3cmb'
        if self.dev1.DeviceType == ics.NEODEVICE_VCAN3:
            load_coremini(self, data, ics.SCRIPT_LOCATION_VCAN3_MEM)
            load_coremini(self, vs3file, ics.SCRIPT_LOCATION_VCAN3_MEM)
        elif self.dev1.DeviceType == ics.NEODEVICE_FIRE2:
            load_coremini(self, data, ics.SCRIPT_LOCATION_SDCARD)
            load_coremini(self, vs3file, ics.SCRIPT_LOCATION_SDCARD)
        else:
            load_coremini(self, data, ics.SCRIPT_LOCATION_FLASH_MEM)
            load_coremini(self, data, ics.SCRIPT_LOCATION_SDCARD)
            load_coremini(self, vs3file, ics.SCRIPT_LOCATION_FLASH_MEM)
            load_coremini(self, vs3file, ics.SCRIPT_LOCATION_SDCARD)

    def testFblock(self):
        if self.dev1.DeviceType == ics.NEODEVICE_VCAN3:
            ics.coremini_load(self.dev1, data, ics.SCRIPT_LOCATION_VCAN3_MEM)
        elif self.dev1.DeviceType == ics.NEODEVICE_FIRE2:
            ics.coremini_load(self.dev1, data, ics.SCRIPT_LOCATION_SDCARD)
        else:
            ics.coremini_load(self.dev1, data, ics.SCRIPT_LOCATION_FLASH_MEM)
        self.assertTrue(ics.coremini_get_fblock_status(self.dev1, 0))
        self.assertIsNone(ics.coremini_stop_fblock(self.dev1, 0))
        self.assertFalse(ics.coremini_get_fblock_status(self.dev1, 0))
        time.sleep(2)
        self.assertIsNone(ics.coremini_start_fblock(self.dev1, 0))
        self.assertTrue(ics.coremini_get_fblock_status(self.dev1, 0))
        self._clear_coremini(self)


if __name__ == "__main__":
	unittest.main()
