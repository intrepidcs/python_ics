# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.s_ext_sub_cmd_hdr import *
from ics.structures.s_disk_details import *
from ics.structures.s_disk_structure import *
from ics.structures.s_disk_format_progress import *


class nameless42136(ctypes.Union):
    _pack_ = 2
    _fields_ = [
        ('structure', SDiskStructure),
        ('details', SDiskDetails),
        ('progress', SDiskFormatProgress),
    ]



class s_ext_sub_cmd_comm(ctypes.Structure):
    _pack_ = 2
    _anonymous_  = ('nameless42136',)
    _fields_ = [
        ('hdr', SExtSubCmdHdr),
        ('nameless42136', nameless42136),
    ]


_SExtSubCmdComm = s_ext_sub_cmd_comm
SExtSubCmdComm = s_ext_sub_cmd_comm

