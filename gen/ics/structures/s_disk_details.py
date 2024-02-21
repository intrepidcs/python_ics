# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.s_disk_status import *
from ics.structures.s_disk_structure import *


class s_disk_details(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('structure', SDiskStructure),
        ('status', SDiskStatus * 12),
    ]


_SDiskDetails = s_disk_details
SDiskDetails = s_disk_details

