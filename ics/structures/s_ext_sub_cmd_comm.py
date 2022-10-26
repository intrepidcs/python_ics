# This file was auto generated; Do not modify, if you value your sanity!
import ctypes
import enum

from ics.structures.extended_response_generic import *
from ics.structures.generic_api_data import *
from ics.structures.generic_api_selector import *
from ics.structures.generic_api_status import *
from ics.structures.get_component_versions import *
from ics.structures.get_component_versions_response import *
from ics.structures.get_supported_features_response import *
from ics.structures.gptp_status import *
from ics.structures.s_disk_details import *
from ics.structures.s_disk_format_progress import *
from ics.structures.s_disk_structure import *
from ics.structures.s_ext_sub_cmd_hdr import *
from ics.structures.software_update_command import *
from ics.structures.start_dhcp_server_command import *
from ics.structures.stop_dhcp_server_command import *
from ics.structures.uart_port_config import *
from ics.structures.uart_port_data import *
from ics.structures.uart_port_port_bytes import *
from ics.structures.w_bms_manager_reset import *
from ics.structures.w_bms_manager_set_lock import *


class extension(ctypes.Union):
    _pack_ = 2
    _fields_ = [
        ('structure', SDiskStructure),
        ('details', SDiskDetails),
        ('progress', SDiskFormatProgress),
        ('startDHCPServer', StartDHCPServerCommand),
        ('stopDHCPServer', StopDHCPServerCommand),
        ('getSupportedFeatures', GetSupportedFeaturesResponse),
        ('genericResponse', ExtendedResponseGeneric),
        ('gptpStatus', GPTPStatus),
        ('apiStatus', GenericAPIStatus),
        ('apiData', GenericAPIData),
        ('apiSelector', GenericAPISelector),
        ('getComponentVersions', GetComponentVersions),
        ('softwareUpdate', SoftwareUpdateCommand),
        ('getComponentVersionsResponse', GetComponentVersionsResponse),
        ('wbmsManagerToLockUnlock', wBMSManagerSetLock),
        ('wbmsManagerToReset', wBMSManagerReset),
        ('uartData', UartPortData),
        ('uartBytesLen', UartPortPortBytes),
        ('uartConfig', UartPortConfig),
    ]



class s_ext_sub_cmd_comm(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('header', SExtSubCmdHdr),
        ('extension', extension),
    ]


_SExtSubCmdComm = s_ext_sub_cmd_comm
SExtSubCmdComm = s_ext_sub_cmd_comm

