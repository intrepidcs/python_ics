# This file was auto generated; Do not modify, if you value your sanity!
import ctypes

try: # 5
    from op_eth_general_settings import op_eth_general_settings
    from op_eth_settings import op_eth_settings
    from s_text_api_settings import s_text_api_settings
    from timesync_icshardware_settings import timesync_icshardware_settings
    from ethernet_settings2 import ethernet_settings2
except:
    from ics.structures.op_eth_general_settings import op_eth_general_settings
    from ics.structures.op_eth_settings import op_eth_settings
    from ics.structures.s_text_api_settings import s_text_api_settings
    from ics.structures.timesync_icshardware_settings import timesync_icshardware_settings
    from ics.structures.ethernet_settings2 import ethernet_settings2

class srad_super_moon_settings(ctypes.Structure):
    _pack_ = 2
    _fields_ = [
        ('perf_en', ctypes.c_uint16), 
        ('opEthGen', op_eth_general_settings), 
        ('opEth1', op_eth_settings), 
        ('network_enables', ctypes.c_uint16), 
        ('network_enables_2', ctypes.c_uint16), 
        ('network_enabled_on_boot', ctypes.c_uint16), 
        ('network_enables_3', ctypes.c_uint16), 
        ('text_api', s_text_api_settings), 
        ('pc_com_mode', ctypes.c_uint16), 
        ('timeSyncSettings', timesync_icshardware_settings), 
        ('hwComLatencyTestEn', ctypes.c_uint16), 
        ('Eth2', ethernet_settings2), 
    ]

# Extra names go here:
SRADSuperMoonSettings = srad_super_moon_settings
# End of extra names

