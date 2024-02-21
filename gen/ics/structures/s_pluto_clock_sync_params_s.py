# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum



class s_pluto_clock_sync_params_s(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('etssrcpcf', ctypes.c_uint64),
        ('wfintmout', ctypes.c_uint32),
        ('maxtranspclk', ctypes.c_uint32),
        ('listentmout', ctypes.c_uint32),
        ('intcydur', ctypes.c_uint32),
        ('caentmout', ctypes.c_uint32),
        ('pcfsze', ctypes.c_uint16),
        ('obvwinsz', ctypes.c_uint16),
        ('vlidout', ctypes.c_uint16),
        ('vlidimnmin', ctypes.c_uint16),
        ('vlidinmax', ctypes.c_uint16),
        ('accdevwin', ctypes.c_uint16),
        ('srcport', ctypes.c_uint8 * 8),
        ('waitthsync', ctypes.c_uint8),
        ('unsytotsyth', ctypes.c_uint8),
        ('unsytosyth', ctypes.c_uint8),
        ('tsytosyth', ctypes.c_uint8),
        ('tsyth', ctypes.c_uint8),
        ('tsytousyth', ctypes.c_uint8),
        ('syth', ctypes.c_uint8),
        ('sytousyth', ctypes.c_uint8),
        ('sypriority', ctypes.c_uint8),
        ('sydomain', ctypes.c_uint8),
        ('stth', ctypes.c_uint8),
        ('sttointth', ctypes.c_uint8),
        ('pcfpriority', ctypes.c_uint8),
        ('numunstbcy', ctypes.c_uint8),
        ('numstbcy', ctypes.c_uint8),
        ('maxintegcy', ctypes.c_uint8),
        ('inttotentth', ctypes.c_uint8),
        ('inttosyncth', ctypes.c_uint8),
        ('vlidselect', ctypes.c_uint8),
        ('tentsyrelen', ctypes.c_uint8),
        ('asytensyen', ctypes.c_uint8),
        ('sytostben', ctypes.c_uint8),
        ('syrelen', ctypes.c_uint8),
        ('sysyen', ctypes.c_uint8),
        ('syasyen', ctypes.c_uint8),
        ('ipcframesy', ctypes.c_uint8),
        ('stabasyen', ctypes.c_uint8),
        ('swmaster', ctypes.c_uint8),
        ('fullcbg', ctypes.c_uint8),
        ('pad1', ctypes.c_uint8),
        ('pad2', ctypes.c_uint8),
        ('pad3', ctypes.c_uint8),
    ]


SPluto_ClockSyncParams_s = s_pluto_clock_sync_params_s
SPluto_ClockSyncParams = s_pluto_clock_sync_params_s

