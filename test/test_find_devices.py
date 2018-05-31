import timeit
import unittest
import ics
# This test requries 2 devices attached, one neoVI FIRE2s and one ValueCAN3

_DEBUG = False

class TestFindDevicesLegacy(unittest.TestCase):
    @classmethod
    def setUpClass(self):
        ics.override_library_name(r"C:\Windows\SysWOW64\icsneo40-legacy.dll")
        if _DEBUG:
            import os
            input("Pause... " + str(os.getpid()))
        
    def test_default_parameters(self):
        devices = ics.find_devices()
        self.assertTrue(len(devices) == 2)
    
    def test_default_parameters_time(self):
        if not _DEBUG:
            self.assertTrue((timeit.timeit("ics.find_devices()", setup="import ics", number=1000)) <= 5.0)

    def test_find_fire2(self):
        devices = ics.find_devices(ics.NEODEVICE_FIRE2)
        self.assertTrue(len(devices) == 1)
    
    def test_find_vcan3(self):
        devices = ics.find_devices(ics.NEODEVICE_VCAN3)
        self.assertTrue(len(devices) == 1)
    
    def test_find_fire2_and_vcan3(self):
        devices = ics.find_devices(ics.NEODEVICE_FIRE2 | ics.NEODEVICE_VCAN3)
        self.assertTrue(len(devices) == 2)
        
class TestFindDevicesNewStyle(unittest.TestCase):
    @classmethod
    def setUpClass(self):
        ics.override_library_name(r"C:\Windows\SysWOW64\icsneo40.dll")
        if _DEBUG:
            import os
            input("Pause... " + str(os.getpid()))
        
    def test_default_parameters(self):
        devices = ics.find_devices()
        self.assertTrue(len(devices) == 2)
    
    def test_default_parameters_time(self):
        if not _DEBUG:
            self.assertTrue((timeit.timeit("ics.find_devices()", setup="import ics", number=1000)) <= 5.0)

    def test_find_fire2(self):
        devices = ics.find_devices([ics.NEODEVICE_FIRE2,])
        self.assertTrue(len(devices) == 1)
    
    def test_find_vcan3(self):
        devices = ics.find_devices([ics.NEODEVICE_VCAN3,])
        self.assertTrue(len(devices) == 1)
    
    def test_find_fire2_and_vcan3(self):
        devices = ics.find_devices([ics.NEODEVICE_FIRE2, ics.NEODEVICE_VCAN3])
        self.assertTrue(len(devices) == 2)


class TestFindDevicesNewStyleWithLegacyDLL(unittest.TestCase):
    @classmethod
    def setUpClass(self):
        import ics
        ics.override_library_name(r"C:\Windows\SysWOW64\icsneo40-legacy.dll")
        if _DEBUG:
            import os
            input("Pause... " + str(os.getpid()))
        
    def test_default_parameters(self):
        devices = ics.find_devices()
        self.assertTrue(len(devices) == 2)
    
    def test_default_parameters_time(self):
        self.assertTrue((timeit.timeit("ics.find_devices()", setup="import ics", number=1000)) <= 5.0)

    def test_find_fire2(self):
        devices = ics.find_devices([ics.NEODEVICE_FIRE2,])
        self.assertTrue(len(devices) == 2)
    
    def test_find_vcan3(self):
        devices = ics.find_devices([ics.NEODEVICE_VCAN3,])
        self.assertTrue(len(devices) == 2)
    
    def test_find_fire2_and_vcan3(self):
        devices = ics.find_devices([ics.NEODEVICE_FIRE2, ics.NEODEVICE_VCAN3])
        self.assertTrue(len(devices) == 2)


if __name__ == "__main__":
    if _DEBUG:
        import os
        input("Pause... " + str(os.getpid()))
    unittest.main()