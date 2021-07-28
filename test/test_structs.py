import unittest
import sys
import os
#print(os.getcwd())
print(os.path.abspath('../'))
sys.path.append('../')

from ics.structures.inner_structure import *
from ics.structures.test_structure import *
from ics.structures.test import *

class TestTestEnum(unittest.TestCase):
    def test_all(self):
        self.assertEqual(test.TestNone, 0)
        self.assertEqual(test.TestA, 1)
        self.assertEqual(test.TestB, 2)
        self.assertEqual(test.TestC, 3)
        self.assertEqual(test.TestD, 4)
        self.assertEqual(test.TestE, 5)

class TestInnerStructure(unittest.TestCase):
    def test_all(self):
        t = inner_structure()
        self.assertTrue(isinstance(t, ctypes.Structure))

        # default init
        self.assertEqual(t.a, b'\x00')
        self.assertEqual(t.b, 0)
        self.assertEqual(t.t, 0)
        t.a = b'Z'
        self.assertEqual(t.a, b'Z')
        self.assertEqual(t.b, 0)
        self.assertEqual(t.t, 0)
        t.a = b'\x00'
        t.b = 10
        self.assertEqual(t.a, b'\x00')
        self.assertEqual(t.b, 10)
        self.assertEqual(t.t, 0)
        t.b = 0
        t.t = test.TestD
        self.assertEqual(t.a, b'\x00')
        self.assertEqual(t.b, 0)
        self.assertEqual(t.t, test.TestD)


class TestTestStructure(unittest.TestCase):    
    def test_a(self):
        t = A()
        self.assertTrue(isinstance(t, ctypes.Structure))
        # default init
        self.assertEqual(t.a, 0)
        self.assertEqual(t.b, 0)
        self.assertEqual(t.c, 0)
        t.a = 10
        self.assertEqual(t.a, 10)
        self.assertEqual(t.b, 0)
        self.assertEqual(t.c, 0)
        t.a = 0
        t.b = 10
        self.assertEqual(t.a, 0)
        self.assertEqual(t.b, 10)
        self.assertEqual(t.c, 0)
        t.b = 0
        t.c = 10
        self.assertEqual(t.a, 0)
        self.assertEqual(t.b, 0)
        self.assertEqual(t.c, 10)
    
    def test_b(self):
        t = B()
        self.assertTrue(isinstance(t, ctypes.Structure))
        # default init
        self.assertEqual(t.d, 0)
        self.assertEqual(t.e, 0)
        self.assertEqual(t.f, 0)
        t.d = 1
        self.assertEqual(t.d, 1)
        self.assertEqual(t.e, 0)
        self.assertEqual(t.f, 0)
        t.d = 0
        t.e = 1
        self.assertEqual(t.d, 0)
        self.assertEqual(t.e, 1)
        self.assertEqual(t.f, 0)
        t.e = 0
        t.f = 1
        self.assertEqual(t.d, 0)
        self.assertEqual(t.e, 0)
        self.assertEqual(t.f, 1)
    
    def test_c(self):
        t = C()
        self.assertTrue(isinstance(t, ctypes.Union))
        # default init
        self.assertEqual(t.ghi, 0)
        self.assertEqual(t.g, 0)
        self.assertEqual(t.h, 0)
        self.assertEqual(t.i, 0)
        t.g = 1
        self.assertEqual(t.ghi, 0x1)
        self.assertEqual(t.g, 1)
        self.assertEqual(t.h, 0)
        self.assertEqual(t.i, 0)
        t.g = 0
        t.h = 1
        self.assertEqual(t.ghi, 0x10000)
        self.assertEqual(t.g, 0)
        self.assertEqual(t.h, 1)
        self.assertEqual(t.i, 0)
        t.h = 0
        t.i = 1
        self.assertEqual(t.ghi, 0x100000000)
        self.assertEqual(t.g, 0)
        self.assertEqual(t.h, 0)
        self.assertEqual(t.i, 1)
        t.i = 0
        t.ghi = 0x100010001
        self.assertEqual(t.ghi, 0x100010001)
        self.assertEqual(t.g, 1)
        self.assertEqual(t.h, 1)
        self.assertEqual(t.i, 1)

    def test_d(self):
        t = D()
        self.assertTrue(isinstance(t, ctypes.Union))
        # default init
        self.assertEqual(t.jkm, 0)
        self.assertEqual(t.j, 0)
        self.assertEqual(t.k, 0)
        self.assertEqual(t.m, 0)
        t.j = 1
        self.assertEqual(t.jkm, 0x1)
        self.assertEqual(t.j, 1)
        self.assertEqual(t.k, 0)
        self.assertEqual(t.m, 0)
        t.j = 0
        t.k = 1
        self.assertEqual(t.jkm, 0x10000)
        self.assertEqual(t.j, 0)
        self.assertEqual(t.k, 1)
        self.assertEqual(t.m, 0)
        t.k = 0
        t.m = 1
        self.assertEqual(t.jkm, 0x100000000)
        self.assertEqual(t.j, 0)
        self.assertEqual(t.k, 0)
        self.assertEqual(t.m, 1)
        t.m = 0
        t.jkm = 0x100010001
        self.assertEqual(t.jkm, 0x100010001)
        self.assertEqual(t.j, 1)
        self.assertEqual(t.k, 1)
        self.assertEqual(t.m, 1)
    
    def test_e(self):
        t = E()
        self.assertTrue(isinstance(t, ctypes.Structure))
        # default init
        self.assertEqual(t.n, 0)
        self.assertEqual(t.p, 0)
        self.assertEqual(t.q, 0)
        t.n = 1
        self.assertEqual(t.n, 1)
        self.assertEqual(t.p, 0)
        self.assertEqual(t.q, 0)
        t.n = 0
        t.p = 1
        self.assertEqual(t.n, 0)
        self.assertEqual(t.p, 1)
        self.assertEqual(t.q, 0)
        t.p = 0
        t.q = 1
        self.assertEqual(t.n, 0)
        self.assertEqual(t.p, 0)
        self.assertEqual(t.q, 1)
        t.q = 0
        self.assertEqual(t.n, 0)
        self.assertEqual(t.p, 0)
        self.assertEqual(t.q, 0)

    def test_f(self):
        t = F()
        self.assertTrue(isinstance(t, ctypes.Structure))
        # default init
        self.assertEqual(t.r, 0)
        self.assertEqual(t.s, 0)
        self.assertEqual(t.t, 0)
        t.r = 1
        self.assertEqual(t.r, 1)
        self.assertEqual(t.s, 0)
        self.assertEqual(t.t, 0)
        t.r = 0
        t.s = 1
        self.assertEqual(t.r, 0)
        self.assertEqual(t.s, 1)
        self.assertEqual(t.t, 0)
        t.s = 0
        t.t = 1
        self.assertEqual(t.r, 0)
        self.assertEqual(t.s, 0)
        self.assertEqual(t.t, 1)
        t.t = 0
        self.assertEqual(t.r, 0)
        self.assertEqual(t.s, 0)
        self.assertEqual(t.t, 0)
    
    def test_anonymous(self):
        t = test_structure()
        self.assertTrue(isinstance(t, ctypes.Structure))

        # test B
        self.assertTrue(isinstance(t.B, ctypes.Structure))
        # default init
        self.assertEqual(t._def, 0)
        self.assertEqual(t.B.d, 0)
        self.assertEqual(t.B.e, 0)
        self.assertEqual(t.B.f, 0)
        t.B.d = 1
        self.assertEqual(t._def, 0x1)
        self.assertEqual(t.B.d, 1)
        self.assertEqual(t.B.e, 0)
        self.assertEqual(t.B.f, 0)
        t.B.d = 0
        t.B.e = 1
        self.assertEqual(t._def, 0x2)
        self.assertEqual(t.B.d, 0)
        self.assertEqual(t.B.e, 1)
        self.assertEqual(t.B.f, 0)
        t.B.e = 0
        t.B.f = 1
        self.assertEqual(t._def, 0x4)
        self.assertEqual(t.B.d, 0)
        self.assertEqual(t.B.e, 0)
        self.assertEqual(t.B.f, 1)
        t._def = 0x7 
        self.assertEqual(t._def, 0x7)
        self.assertEqual(t.B.d, 1)
        self.assertEqual(t.B.e, 1)
        self.assertEqual(t.B.f, 1)


if __name__ == "__main__":
    try:
        unittest.main()
    except SystemExit as ex:
        print(f'Return code: {int(ex.code)}')
