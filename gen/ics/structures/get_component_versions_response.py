# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.version_report import *


class get_component_versions_response(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('numVersions', ctypes.c_uint16),
        ('versions', VersionReport * 16),
    ]


_ExtendedGetVersionsResponse = get_component_versions_response
GetComponentVersionsResponse = get_component_versions_response

