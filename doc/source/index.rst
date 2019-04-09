
============================================================
python_ics
============================================================

Intrepid Control Systems, Inc. open source Python module for interfacing to Intrepid hardware. Basic knowledge of using and installing Python modules is assumed. Please see https://docs.python.org/3/installing/index.html for documentation on how to install Python modules.

============================================================
Versioning Information
============================================================

Minor differences can occur between different icsnVC40.h versions. These differences are usually just structures and constant differences. Below is a list of how the python_ics version correlates to the icsnVC40.h version:

v802
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``pip install 'python_ics>=2.0,<3.0' --force-reinstall``

    **Note:** Refer to platform specific installation if not on Windows

v803
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``pip install 'python_ics>=3.0,<4.0' --force-reinstall``

    **Note:** Refer to platform specific installation if not on Windows

v900
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``pip install 'python_ics>=4.0,<5.0' --force-reinstall``

    **Note:** Refer to platform specific installation if not on Windows


============================================================
Installation on Windows
============================================================

PyPi provides binary packages for Windows. You can simply install the python_ics module by running the following command:

``pip install python_ics``

    **Note:** pip.exe is usually located under the Scripts directory under the Python
    installation directory.

    
Building from source
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Building from source on windows is not usually need so it won't really be covered here in detail. As a starting point you'll need to match the compiler version used to build the official Python binaries (MSVC). If the build environment is setup correctly, you should be able to run ``python setup.py build`` like usual. 

Intrepid icsneo40 Library
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
python_ics module looks for ``icsneo40.dll`` in the normal windows DLL search paths. The module will throw an exception if its not found.



============================================================
Installation on Linux
============================================================
python_ics does not provide binaries for linux distributions so we will have to compile from source. This can be easily achieved by utilzing Python's PIP. First we need to make sure we have some base packages installed.

Fedora Dependencies (FC28)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``sudo dnf install redhat-rpm-config gcc g++ python3-devel``

Debian/Ubuntu Dependencies
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``sudo apt install build-essential python-dev``

Others (Required dependencies)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
- GCC
- G++
- Python Development packages (We Need to link to Python.h)


Installation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

After dependencies are installed we can run the following pip command:

``pip install python_ics``

    **Note:** A lot of distributions have Python 2 and 3 installed side by side. As of this writing without a version suffix the commands still default to version 2 of the Python binaries. In order to utilize the Python 3 binaries you must append a 3 after the binary names (python3 and pip3 instead of just python and pip).

Intrepid libicsneoapi.so Library
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Please see https://github.com/intrepidcs/icsneoapi for more details.


============================================================
Getting Started
============================================================

Please see https://github.com/intrepidcs/python_ics/tree/master/examples for simple examples on how to use this module. Most function documentation has a simple example on how its intended to be used. Every function was designed to be as close as possible to it's C counterpart unless it was deemed to make the function more pythonic in nature. 

For those experienced with the C API ``ics.open_device`` (``icsneoOpenNeoDevice()``) behavior has been changed the most (no parameters makes it auto utilize ``ics.find_devices`` (``icsneoFindNeoDevices()``) and open the first device). Also since python is a object oriented language the module utilizes this and auto cleans up device handles when going out of scope so there is usually no need to call ``ics.close_device()``.


============================================================
Module Function List
============================================================


.. autosummary::
	:nosignatures:

	ics.close_device
	ics.coremini_clear
	ics.coremini_get_fblock_status
	ics.coremini_get_status
	ics.coremini_load
	ics.coremini_read_app_signal
	ics.coremini_read_rx_message
	ics.coremini_read_tx_message
	ics.coremini_start
	ics.coremini_start_fblock
	ics.coremini_stop
	ics.coremini_stop_fblock
	ics.coremini_write_app_signal
	ics.coremini_write_rx_message
	ics.coremini_write_tx_message
	ics.create_neovi_radio_message
	ics.find_devices
	ics.firmware_update_required
	ics.force_firmware_update
	ics.get_active_vnet_channel
	ics.get_backup_power_enabled
	ics.get_backup_power_ready
	ics.get_device_settings
	ics.get_device_status
	ics.get_dll_firmware_info
	ics.get_dll_version
	ics.get_error_messages
	ics.get_hw_firmware_info
	ics.get_last_api_error
	ics.get_library_path
	ics.get_messages
	ics.get_performance_parameters
	ics.get_rtc
	ics.get_script_status
	ics.get_serial_number
	ics.get_timestamp_for_msg
	ics.iso15765_disable_networks
	ics.iso15765_enable_networks
	ics.iso15765_receive_message
	ics.iso15765_transmit_message
	ics.load_default_settings
	ics.open_device
	ics.override_library_name
	ics.read_sdcard
	ics.request_enter_sleep_mode
	ics.set_active_vnet_channel
	ics.set_backup_power_enabled
	ics.set_bit_rate
	ics.set_bit_rate_ex
	ics.set_context
	ics.set_device_settings
	ics.set_fd_bit_rate
	ics.set_reflash_callback
	ics.set_rtc
	ics.transmit_messages
	ics.validate_hobject
	ics.write_sdcard
	ics.ClosePort
	ics.FindNeoDevices
	ics.GetDLLVersion
	ics.GetErrorMessages
	ics.GetHWFirmwareInfo
	ics.GetLastAPIError
	ics.GetMessages
	ics.GetPerformanceParameters
	ics.GetRTC
	ics.GetSerialNumber
	ics.OpenNeoDevice
	ics.RequestEnterSleepMode
	ics.ScriptClear
	ics.ScriptGetFBlockStatus
	ics.ScriptGetScriptStatus
	ics.ScriptLoad
	ics.ScriptReadAppSignal
	ics.ScriptReadRxMessage
	ics.ScriptReadTxMessage
	ics.ScriptStart
	ics.ScriptStartFBlock
	ics.ScriptStop
	ics.ScriptStopFBlock
	ics.ScriptWriteAppSignal
	ics.ScriptWriteRxMessage
	ics.ScriptWriteTxMessage
	ics.SetRTC
	ics.SetReflashDisplayCallback
	ics.TxMessages
	ics.ValidateHObject
	ics.base36enc
	ics.icsneoFirmwareUpdateRequired
	ics.icsneoForceFirmwareUpdate
	ics.icsneoGetActiveVNETChannel
	ics.icsneoGetBackupPowerEnabled
	ics.icsneoGetBackupPowerReady
	ics.icsneoGetDLLFirmwareInfo
	ics.icsneoGetDeviceStatus
	ics.icsneoGetFireSettings
	ics.icsneoGetTimeStampForMsg
	ics.icsneoGetVCAN3Settings
	ics.icsneoISO15765_DisableNetworks
	ics.icsneoISO15765_EnableNetworks
	ics.icsneoISO15765_ReceiveMessage
	ics.icsneoISO15765_TransmitMessage
	ics.icsneoLoadDefaultSettings
	ics.icsneoReadSDCard
	ics.icsneoScriptGetScriptStatusEx
	ics.icsneoSetActiveVNETChannel
	ics.icsneoSetBackupPowerEnabled
	ics.icsneoSetBitRate
	ics.icsneoSetBitRateEx
	ics.icsneoSetContext
	ics.icsneoSetFDBitRate
	ics.icsneoSetFireSettings
	ics.icsneoSetVCAN3Settings
	ics.icsneoWriteSDCard

============================================================
Module Documentation
============================================================
.. automodule:: ics
   :members:
   :show-inheritance:
   :undoc-members:

============================================================
Module Variables
============================================================

.. py:data:: AUTO
	:annotation: = 0
.. py:data:: BPS100
	:annotation: = 5
.. py:data:: BPS1000
	:annotation: = 10
.. py:data:: BPS100000
	:annotation: = 7
.. py:data:: BPS10400
	:annotation: = 1
.. py:data:: BPS117647
	:annotation: = 8
.. py:data:: BPS125
	:annotation: = 6
.. py:data:: BPS20
	:annotation: = 0
.. py:data:: BPS2000
	:annotation: = 12
.. py:data:: BPS250
	:annotation: = 7
.. py:data:: BPS33
	:annotation: = 1
.. py:data:: BPS33333
	:annotation: = 2
.. py:data:: BPS4000
	:annotation: = 13
.. py:data:: BPS50
	:annotation: = 2
.. py:data:: BPS500
	:annotation: = 8
.. py:data:: BPS5000
	:annotation: = 0
.. py:data:: BPS50000
	:annotation: = 3
.. py:data:: BPS62
	:annotation: = 3
.. py:data:: BPS62500
	:annotation: = 4
.. py:data:: BPS666
	:annotation: = 11
.. py:data:: BPS71429
	:annotation: = 5
.. py:data:: BPS800
	:annotation: = 9
.. py:data:: BPS83
	:annotation: = 4
.. py:data:: BPS83333
	:annotation: = 6
.. py:data:: BUILD_DATETIME
	:annotation: = May 29 2018 16:04:26
.. py:data:: CANFD_BRS_ENABLED
	:annotation: = 2
.. py:data:: CANFD_BRS_ENABLED_ISO
	:annotation: = 4
.. py:data:: CANFD_ENABLED
	:annotation: = 1
.. py:data:: CANFD_ENABLED_ISO
	:annotation: = 3
.. py:data:: CANFD_SETTINGS_SIZE
	:annotation: = 10
.. py:data:: CANTERM_SETTINGS_SIZE
	:annotation: = 6
.. py:data:: CAN_BPS10000
	:annotation: = 17
.. py:data:: CAN_BPS5000
	:annotation: = 14
.. py:data:: CAN_BPS6667
	:annotation: = 15
.. py:data:: CAN_BPS8000
	:annotation: = 16
.. py:data:: CAN_SETTINGS_SIZE
	:annotation: = 12
.. py:data:: DISABLE
	:annotation: = 1
.. py:data:: ETHERNET_SETTINGS_SIZE
	:annotation: = 8
.. py:data:: FAST_MODE
	:annotation: = 3
.. py:data:: GLOBAL_SETTINGS_SIZE
	:annotation: = 908
.. py:data:: GS_VERSION
	:annotation: = 5
.. py:data:: ISO15765_2_NETWORK_HSCAN
	:annotation: = 1
.. py:data:: ISO15765_2_NETWORK_HSCAN2
	:annotation: = 4
.. py:data:: ISO15765_2_NETWORK_HSCAN3
	:annotation: = 8
.. py:data:: ISO15765_2_NETWORK_HSCAN4
	:annotation: = 20
.. py:data:: ISO15765_2_NETWORK_HSCAN5
	:annotation: = 24
.. py:data:: ISO15765_2_NETWORK_HSCAN6
	:annotation: = 28
.. py:data:: ISO15765_2_NETWORK_HSCAN7
	:annotation: = 32
.. py:data:: ISO15765_2_NETWORK_MSCAN
	:annotation: = 2
.. py:data:: ISO15765_2_NETWORK_SWCAN
	:annotation: = 16
.. py:data:: ISO15765_2_NETWORK_SWCAN2
	:annotation: = 36
.. py:data:: ISO9141_KEYWORD2000_SETTINGS_SIZE
	:annotation: = 114
.. py:data:: ISO9141_KEYWORD2000__INIT_STEP_SIZE
	:annotation: = 6
.. py:data:: J1708_SETTINGS_SIZE
	:annotation: = 2
.. py:data:: LIN_SETTINGS_SIZE
	:annotation: = 10
.. py:data:: LISTEN_ALL
	:annotation: = 7
.. py:data:: LISTEN_ONLY
	:annotation: = 3
.. py:data:: LOOPBACK
	:annotation: = 2
.. py:data:: NEODEVICE_ALL
	:annotation: = -16385
.. py:data:: NEODEVICE_ANY_ION
	:annotation: = 1310720
.. py:data:: NEODEVICE_ANY_PLASMA
	:annotation: = 208896
.. py:data:: NEODEVICE_BLUE
	:annotation: = 1
.. py:data:: NEODEVICE_CMPROBE
	:annotation: = 8388608
.. py:data:: NEODEVICE_CT_OBD
	:annotation: = 32768
.. py:data:: NEODEVICE_DW_VCAN
	:annotation: = 4
.. py:data:: NEODEVICE_ECU
	:annotation: = 128
.. py:data:: NEODEVICE_ECUCHIP_UART
	:annotation: = 2048
.. py:data:: NEODEVICE_EEVB
	:annotation: = 16777216
.. py:data:: NEODEVICE_FIRE
	:annotation: = 8
.. py:data:: NEODEVICE_FIRE2
	:annotation: = 67108864
.. py:data:: NEODEVICE_FIRE_VNET
	:annotation: = 8192
.. py:data:: NEODEVICE_FLEX
	:annotation: = 134217728
.. py:data:: NEODEVICE_IEVB
	:annotation: = 256
.. py:data:: NEODEVICE_ION_2
	:annotation: = 262144
.. py:data:: NEODEVICE_ION_3
	:annotation: = 1048576
.. py:data:: NEODEVICE_NEOANALOG
	:annotation: = 16384
.. py:data:: NEODEVICE_NEOECUCHIP
	:annotation: = 256
.. py:data:: NEODEVICE_OBD2_PRO
	:annotation: = 1024
.. py:data:: NEODEVICE_OBD2_SIM
	:annotation: = -2147483648
.. py:data:: NEODEVICE_PENDANT
	:annotation: = 512
.. py:data:: NEODEVICE_PLASMA_1_11
	:annotation: = 4096
.. py:data:: NEODEVICE_PLASMA_1_12
	:annotation: = 65536
.. py:data:: NEODEVICE_PLASMA_1_13
	:annotation: = 131072
.. py:data:: NEODEVICE_RADGALAXY
	:annotation: = 268435456
.. py:data:: NEODEVICE_RADSTAR
	:annotation: = 524288
.. py:data:: NEODEVICE_RADSTAR2
	:annotation: = 536870912
.. py:data:: NEODEVICE_RED
	:annotation: = 64
.. py:data:: NEODEVICE_SW_VCAN
	:annotation: = 2
.. py:data:: NEODEVICE_UNKNOWN
	:annotation: = 0
.. py:data:: NEODEVICE_VCAN3
	:annotation: = 16
.. py:data:: NEODEVICE_VCAN4
	:annotation: = 2097152
.. py:data:: NEODEVICE_VCAN4_12
	:annotation: = 4194304
.. py:data:: NEODEVICE_VCANRF
	:annotation: = 33554432
.. py:data:: NEODEVICE_VIVIDCAN
	:annotation: = 1073741824
.. py:data:: NEOVI6_VCAN_TIMESTAMP_1
	:annotation: = 1e-06
.. py:data:: NEOVI6_VCAN_TIMESTAMP_2
	:annotation: = 0.065536
.. py:data:: NEOVIPRO_VCAN_TIMESTAMP_1
	:annotation: = 1e-06
.. py:data:: NEOVIPRO_VCAN_TIMESTAMP_2
	:annotation: = 0.065536
.. py:data:: NEOVI_3G_MAX_SETTINGS_SIZE
	:annotation: = 908
.. py:data:: NEOVI_COMMTYPE_FIRE_USB
	:annotation: = 5
.. py:data:: NEOVI_COMMTYPE_RS232
	:annotation: = 0
.. py:data:: NEOVI_COMMTYPE_TCPIP
	:annotation: = 3
.. py:data:: NEOVI_COMMTYPE_USB_BULK
	:annotation: = 1
.. py:data:: NEOVI_RED_TIMESTAMP_1_10NS
	:annotation: = 1e-08
.. py:data:: NEOVI_RED_TIMESTAMP_1_25NS
	:annotation: = 2.5e-08
.. py:data:: NEOVI_RED_TIMESTAMP_2_10NS
	:annotation: = 429.4967296
.. py:data:: NEOVI_RED_TIMESTAMP_2_25NS
	:annotation: = 107.3741824
.. py:data:: NEOVI_TIMESTAMP_1
	:annotation: = 1.6e-06
.. py:data:: NEOVI_TIMESTAMP_2
	:annotation: = 0.1048576
.. py:data:: NEO_CFG_MPIC_HS_CAN_CNF1
	:annotation: = 522
.. py:data:: NEO_CFG_MPIC_HS_CAN_CNF2
	:annotation: = 521
.. py:data:: NEO_CFG_MPIC_HS_CAN_CNF3
	:annotation: = 520
.. py:data:: NEO_CFG_MPIC_HS_CAN_MODE
	:annotation: = 566
.. py:data:: NEO_CFG_MPIC_LSFT_CAN_CNF1
	:annotation: = 558
.. py:data:: NEO_CFG_MPIC_LSFT_CAN_CNF2
	:annotation: = 557
.. py:data:: NEO_CFG_MPIC_LSFT_CAN_CNF3
	:annotation: = 556
.. py:data:: NEO_CFG_MPIC_MS_CAN_CNF1
	:annotation: = 534
.. py:data:: NEO_CFG_MPIC_MS_CAN_CNF2
	:annotation: = 533
.. py:data:: NEO_CFG_MPIC_MS_CAN_CNF3
	:annotation: = 532
.. py:data:: NEO_CFG_MPIC_SW_CAN_CNF1
	:annotation: = 546
.. py:data:: NEO_CFG_MPIC_SW_CAN_CNF2
	:annotation: = 545
.. py:data:: NEO_CFG_MPIC_SW_CAN_CNF3
	:annotation: = 544
.. py:data:: NETID_3G_APP_SIGNAL_STATUS
	:annotation: = 56
.. py:data:: NETID_3G_FB_STATUS
	:annotation: = 55
.. py:data:: NETID_3G_LOGGING_OVERFLOW
	:annotation: = 59
.. py:data:: NETID_3G_READ_DATALINK_CM_RX_MSG
	:annotation: = 58
.. py:data:: NETID_3G_READ_DATALINK_CM_TX_MSG
	:annotation: = 57
.. py:data:: NETID_3G_READ_SETTINGS_EX
	:annotation: = 60
.. py:data:: NETID_3G_RESET_STATUS
	:annotation: = 54
.. py:data:: NETID_AUX
	:annotation: = 7
.. py:data:: NETID_CGI
	:annotation: = 53
.. py:data:: NETID_DATA_TO_HOST
	:annotation: = 70
.. py:data:: NETID_DEVICE
	:annotation: = 0
.. py:data:: NETID_DEVICE_STATUS
	:annotation: = 513
.. py:data:: NETID_ETHERNET
	:annotation: = 93
.. py:data:: NETID_ETHERNET_DAQ
	:annotation: = 69
.. py:data:: NETID_FLEXRAY
	:annotation: = 85
.. py:data:: NETID_FLEXRAY1A
	:annotation: = 80
.. py:data:: NETID_FLEXRAY1B
	:annotation: = 81
.. py:data:: NETID_FLEXRAY2
	:annotation: = 86
.. py:data:: NETID_FLEXRAY2A
	:annotation: = 82
.. py:data:: NETID_FLEXRAY2B
	:annotation: = 83
.. py:data:: NETID_FORDSCP
	:annotation: = 5
.. py:data:: NETID_GMFSA
	:annotation: = 94
.. py:data:: NETID_HSCAN
	:annotation: = 1
.. py:data:: NETID_HSCAN2
	:annotation: = 42
.. py:data:: NETID_HSCAN3
	:annotation: = 44
.. py:data:: NETID_HSCAN4
	:annotation: = 61
.. py:data:: NETID_HSCAN5
	:annotation: = 62
.. py:data:: NETID_HSCAN6
	:annotation: = 96
.. py:data:: NETID_HSCAN7
	:annotation: = 97
.. py:data:: NETID_HW_COM_LATENCY_TEST
	:annotation: = 512
.. py:data:: NETID_I2C1
	:annotation: = 71
.. py:data:: NETID_INVALID
	:annotation: = 65535
.. py:data:: NETID_ISO
	:annotation: = 9
.. py:data:: NETID_ISO14230
	:annotation: = 15
.. py:data:: NETID_ISO2
	:annotation: = 14
.. py:data:: NETID_ISO3
	:annotation: = 41
.. py:data:: NETID_ISO4
	:annotation: = 47
.. py:data:: NETID_ISOPIC
	:annotation: = 10
.. py:data:: NETID_J1708
	:annotation: = 6
.. py:data:: NETID_JVPW
	:annotation: = 8
.. py:data:: NETID_LIN
	:annotation: = 16
.. py:data:: NETID_LIN2
	:annotation: = 48
.. py:data:: NETID_LIN3
	:annotation: = 49
.. py:data:: NETID_LIN4
	:annotation: = 50
.. py:data:: NETID_LIN5
	:annotation: = 84
.. py:data:: NETID_LIN6
	:annotation: = 98
.. py:data:: NETID_LSFTCAN
	:annotation: = 4
.. py:data:: NETID_LSFTCAN2
	:annotation: = 99
.. py:data:: NETID_MAIN51
	:annotation: = 11
.. py:data:: NETID_MAX
	:annotation: = 100
.. py:data:: NETID_MOST
	:annotation: = 51
.. py:data:: NETID_MOST150
	:annotation: = 92
.. py:data:: NETID_MOST25
	:annotation: = 90
.. py:data:: NETID_MOST50
	:annotation: = 91
.. py:data:: NETID_MSCAN
	:annotation: = 2
.. py:data:: NETID_OP_ETHERNET1
	:annotation: = 17
.. py:data:: NETID_OP_ETHERNET10
	:annotation: = 78
.. py:data:: NETID_OP_ETHERNET11
	:annotation: = 79
.. py:data:: NETID_OP_ETHERNET12
	:annotation: = 87
.. py:data:: NETID_OP_ETHERNET2
	:annotation: = 18
.. py:data:: NETID_OP_ETHERNET3
	:annotation: = 19
.. py:data:: NETID_OP_ETHERNET4
	:annotation: = 45
.. py:data:: NETID_OP_ETHERNET5
	:annotation: = 46
.. py:data:: NETID_OP_ETHERNET6
	:annotation: = 73
.. py:data:: NETID_OP_ETHERNET7
	:annotation: = 75
.. py:data:: NETID_OP_ETHERNET8
	:annotation: = 76
.. py:data:: NETID_OP_ETHERNET9
	:annotation: = 77
.. py:data:: NETID_RED
	:annotation: = 12
.. py:data:: NETID_RED_APP_ERROR
	:annotation: = 52
.. py:data:: NETID_RED_VBAT
	:annotation: = 74
.. py:data:: NETID_RS232
	:annotation: = 63
.. py:data:: NETID_SCI
	:annotation: = 13
.. py:data:: NETID_SPI1
	:annotation: = 72
.. py:data:: NETID_SWCAN
	:annotation: = 3
.. py:data:: NETID_SWCAN2
	:annotation: = 68
.. py:data:: NETID_TCP
	:annotation: = 95
.. py:data:: NETID_TEXTAPI_TO_HOST
	:annotation: = 71
.. py:data:: NETID_UART
	:annotation: = 64
.. py:data:: NETID_UART2
	:annotation: = 65
.. py:data:: NETID_UART3
	:annotation: = 66
.. py:data:: NETID_UART4
	:annotation: = 67
.. py:data:: NORMAL
	:annotation: = 0
.. py:data:: NORMAL_MODE
	:annotation: = 2
.. py:data:: NO_CANFD
	:annotation: = 0
.. py:data:: OPETH_FUNC_MEDIACONVERTER
	:annotation: = 1
.. py:data:: OPETH_FUNC_TAP
	:annotation: = 0
.. py:data:: OPETH_FUNC_TAP_LOW_LATENCY
	:annotation: = 2
.. py:data:: OPETH_LINK_AUTO
	:annotation: = 0
.. py:data:: OPETH_LINK_MASTER
	:annotation: = 1
.. py:data:: OPETH_LINK_SLAVE
	:annotation: = 2
.. py:data:: OPETH_MAC_SPOOF_DST_ADDR
	:annotation: = 0
.. py:data:: OPETH_MAC_SPOOF_SRC_ADDR
	:annotation: = 1
.. py:data:: OP_ETH_GENERAL_SETTINGS_SIZE
	:annotation: = 20
.. py:data:: OP_ETH_SETTINGS_SIZE
	:annotation: = 16
.. py:data:: PLASMA_SLAVE1_OFFSET
	:annotation: = 100
.. py:data:: PLASMA_SLAVE1_OFFSET_RANGE2
	:annotation: = 4608
.. py:data:: PLASMA_SLAVE2_OFFSET
	:annotation: = 200
.. py:data:: PLASMA_SLAVE2_OFFSET_RANGE2
	:annotation: = 8704
.. py:data:: PLASMA_SLAVE3_OFFSET_RANGE2
	:annotation: = 12800
.. py:data:: PLASMA_SLAVE_NUM
	:annotation: = 51
.. py:data:: REPORT_ON_GPS
	:annotation: = 15
.. py:data:: REPORT_ON_KLINE
	:annotation: = 9
.. py:data:: REPORT_ON_LED1
	:annotation: = 7
.. py:data:: REPORT_ON_LED2
	:annotation: = 8
.. py:data:: REPORT_ON_MISC1
	:annotation: = 1
.. py:data:: REPORT_ON_MISC2
	:annotation: = 2
.. py:data:: REPORT_ON_MISC3
	:annotation: = 3
.. py:data:: REPORT_ON_MISC3_AIN
	:annotation: = 10
.. py:data:: REPORT_ON_MISC4
	:annotation: = 4
.. py:data:: REPORT_ON_MISC4_AIN
	:annotation: = 11
.. py:data:: REPORT_ON_MISC5
	:annotation: = 5
.. py:data:: REPORT_ON_MISC5_AIN
	:annotation: = 12
.. py:data:: REPORT_ON_MISC6
	:annotation: = 6
.. py:data:: REPORT_ON_MISC6_AIN
	:annotation: = 13
.. py:data:: REPORT_ON_PERIODIC
	:annotation: = 0
.. py:data:: REPORT_ON_PWM_IN1
	:annotation: = 14
.. py:data:: RESISTOR_OFF
	:annotation: = 1
.. py:data:: RESISTOR_ON
	:annotation: = 0
.. py:data:: SCRIPT_LOCATION_FLASH_MEM
	:annotation: = 0
.. py:data:: SCRIPT_LOCATION_INTERNAL_FLASH
	:annotation: = 2
.. py:data:: SCRIPT_LOCATION_SDCARD
	:annotation: = 1
.. py:data:: SCRIPT_LOCATION_VCAN3_MEM
	:annotation: = 4
.. py:data:: SCRIPT_STATUS_RUNNING
	:annotation: = 1
.. py:data:: SCRIPT_STATUS_STOPPED
	:annotation: = 0
.. py:data:: SLEEP_MODE
	:annotation: = 0
.. py:data:: SLOW_MODE
	:annotation: = 1
.. py:data:: SPY_PROTOCOL_BEAN
	:annotation: = 11
.. py:data:: SPY_PROTOCOL_CAN
	:annotation: = 1
.. py:data:: SPY_PROTOCOL_CANFD
	:annotation: = 30
.. py:data:: SPY_PROTOCOL_CGI
	:annotation: = 18
.. py:data:: SPY_PROTOCOL_CHRYSLER_CCD
	:annotation: = 8
.. py:data:: SPY_PROTOCOL_CHRYSLER_JVPW
	:annotation: = 14
.. py:data:: SPY_PROTOCOL_CHRYSLER_SCI
	:annotation: = 9
.. py:data:: SPY_PROTOCOL_CUSTOM
	:annotation: = 0
.. py:data:: SPY_PROTOCOL_DALLAS_1WIRE
	:annotation: = 25
.. py:data:: SPY_PROTOCOL_ETHERNET
	:annotation: = 29
.. py:data:: SPY_PROTOCOL_FLEXRAY
	:annotation: = 16
.. py:data:: SPY_PROTOCOL_FORD_UBP
	:annotation: = 10
.. py:data:: SPY_PROTOCOL_GENERIC_MANCHSESTER
	:annotation: = 26
.. py:data:: SPY_PROTOCOL_GENERIC_UART
	:annotation: = 22
.. py:data:: SPY_PROTOCOL_GME_CIM_SCL_KLINE
	:annotation: = 19
.. py:data:: SPY_PROTOCOL_GMFSA
	:annotation: = 31
.. py:data:: SPY_PROTOCOL_GMLAN
	:annotation: = 2
.. py:data:: SPY_PROTOCOL_GM_ALDL_UART
	:annotation: = 7
.. py:data:: SPY_PROTOCOL_I2C
	:annotation: = 21
.. py:data:: SPY_PROTOCOL_ISO9141
	:annotation: = 5
.. py:data:: SPY_PROTOCOL_J1708
	:annotation: = 13
.. py:data:: SPY_PROTOCOL_J1850PWM
	:annotation: = 4
.. py:data:: SPY_PROTOCOL_J1850VPW
	:annotation: = 3
.. py:data:: SPY_PROTOCOL_J1939
	:annotation: = 15
.. py:data:: SPY_PROTOCOL_JTAG
	:annotation: = 23
.. py:data:: SPY_PROTOCOL_LIN
	:annotation: = 12
.. py:data:: SPY_PROTOCOL_MOST
	:annotation: = 17
.. py:data:: SPY_PROTOCOL_SENT_PROTOCOL
	:annotation: = 27
.. py:data:: SPY_PROTOCOL_SPI
	:annotation: = 20
.. py:data:: SPY_PROTOCOL_TCP
	:annotation: = 32
.. py:data:: SPY_PROTOCOL_UART
	:annotation: = 28
.. py:data:: SPY_PROTOCOL_UNIO
	:annotation: = 24
.. py:data:: SPY_STATUS2_CAN_HAVE_LINK_DATA
	:annotation: = 4194304
.. py:data:: SPY_STATUS2_CAN_ISO15765_LOGICAL_FRAME
	:annotation: = 2097152
.. py:data:: SPY_STATUS2_END_OF_LONG_MESSAGE
	:annotation: = 1048576
.. py:data:: SPY_STATUS2_ERROR_FRAME
	:annotation: = 131072
.. py:data:: SPY_STATUS2_ETHERNET_CRC_ERROR
	:annotation: = 2097152
.. py:data:: SPY_STATUS2_ETHERNET_FCS_AVAILABLE
	:annotation: = 8388608
.. py:data:: SPY_STATUS2_ETHERNET_FRAME_TOO_SHORT
	:annotation: = 4194304
.. py:data:: SPY_STATUS2_ETHERNET_NO_PADDING
	:annotation: = 16777216
.. py:data:: SPY_STATUS2_ETHERNET_PREEMPTION_ENABLED
	:annotation: = 33554432
.. py:data:: SPY_STATUS2_FLEXRAY_NO_CRC
	:annotation: = 33554432
.. py:data:: SPY_STATUS2_FLEXRAY_NO_HEADERCRC
	:annotation: = 67108864
.. py:data:: SPY_STATUS2_FLEXRAY_TX_AB
	:annotation: = 2097152
.. py:data:: SPY_STATUS2_FLEXRAY_TX_AB_NO_A
	:annotation: = 4194304
.. py:data:: SPY_STATUS2_FLEXRAY_TX_AB_NO_B
	:annotation: = 8388608
.. py:data:: SPY_STATUS2_FLEXRAY_TX_AB_NO_MATCH
	:annotation: = 16777216
.. py:data:: SPY_STATUS2_GLOBAL_CHANGE
	:annotation: = 65536
.. py:data:: SPY_STATUS2_HAS_VALUE
	:annotation: = 1
.. py:data:: SPY_STATUS2_HIGH_VOLTAGE
	:annotation: = 4
.. py:data:: SPY_STATUS2_ISO_FRAME_ERROR
	:annotation: = 134217728
.. py:data:: SPY_STATUS2_ISO_OVERFLOW_ERROR
	:annotation: = 268435456
.. py:data:: SPY_STATUS2_ISO_PARITY_ERROR
	:annotation: = 536870912
.. py:data:: SPY_STATUS2_LIN_ERR_MSG_ID_PARITY
	:annotation: = 67108864
.. py:data:: SPY_STATUS2_LIN_ERR_RX_BREAK_NOT_0
	:annotation: = 2097152
.. py:data:: SPY_STATUS2_LIN_ERR_RX_BREAK_TOO_SHORT
	:annotation: = 4194304
.. py:data:: SPY_STATUS2_LIN_ERR_RX_DATA_GREATER_8
	:annotation: = 16777216
.. py:data:: SPY_STATUS2_LIN_ERR_RX_SYNC_NOT_55
	:annotation: = 8388608
.. py:data:: SPY_STATUS2_LIN_ERR_TX_RX_MISMATCH
	:annotation: = 33554432
.. py:data:: SPY_STATUS2_LIN_ID_FRAME_ERROR
	:annotation: = 268435456
.. py:data:: SPY_STATUS2_LIN_NO_SLAVE_DATA
	:annotation: = -2147483648
.. py:data:: SPY_STATUS2_LIN_SLAVE_BYTE_ERROR
	:annotation: = 536870912
.. py:data:: SPY_STATUS2_LIN_SYNC_FRAME_ERROR
	:annotation: = 134217728
.. py:data:: SPY_STATUS2_LONG_MESSAGE
	:annotation: = 8
.. py:data:: SPY_STATUS2_MOST_CHANGED_PAR
	:annotation: = -2147483648
.. py:data:: SPY_STATUS2_MOST_CONTROL_DATA
	:annotation: = 16777216
.. py:data:: SPY_STATUS2_MOST_I2S_DUMP
	:annotation: = 134217728
.. py:data:: SPY_STATUS2_MOST_LOW_LEVEL
	:annotation: = 8388608
.. py:data:: SPY_STATUS2_MOST_MHP_CONTROL_DATA
	:annotation: = 67108864
.. py:data:: SPY_STATUS2_MOST_MHP_USER_DATA
	:annotation: = 33554432
.. py:data:: SPY_STATUS2_MOST_MOST150
	:annotation: = 1073741824
.. py:data:: SPY_STATUS2_MOST_MOST50
	:annotation: = 536870912
.. py:data:: SPY_STATUS2_MOST_PACKET_DATA
	:annotation: = 2097152
.. py:data:: SPY_STATUS2_MOST_TOO_SHORT
	:annotation: = 268435456
.. py:data:: SPY_STATUS2_RX_TIMEOUT_ERROR
	:annotation: = 1073741824
.. py:data:: SPY_STATUS2_VALUE_IS_BOOLEAN
	:annotation: = 2
.. py:data:: SPY_STATUS3_CANFD_BRS
	:annotation: = 16
.. py:data:: SPY_STATUS3_CANFD_ESI
	:annotation: = 1
.. py:data:: SPY_STATUS3_CANFD_FDF
	:annotation: = 8
.. py:data:: SPY_STATUS3_CANFD_IDE
	:annotation: = 2
.. py:data:: SPY_STATUS3_CANFD_RTR
	:annotation: = 4
.. py:data:: SPY_STATUS3_LIN_JUST_BREAK_SYNC
	:annotation: = 1
.. py:data:: SPY_STATUS3_LIN_ONLY_UPDATE_SLAVE_TABLE_ONCE
	:annotation: = 4
.. py:data:: SPY_STATUS3_LIN_SLAVE_DATA_TOO_SHORT
	:annotation: = 2
.. py:data:: SPY_STATUS_ANALOG_DIGITAL_INPUT
	:annotation: = 16777216
.. py:data:: SPY_STATUS_AUDIO_COMMENT
	:annotation: = 4194304
.. py:data:: SPY_STATUS_AVSI_REC_OVERFLOW
	:annotation: = 1048576
.. py:data:: SPY_STATUS_BAD_MESSAGE_BIT_TIME_ERROR
	:annotation: = 16384
.. py:data:: SPY_STATUS_BREAK
	:annotation: = 524288
.. py:data:: SPY_STATUS_BUS_RECOVERED
	:annotation: = 1024
.. py:data:: SPY_STATUS_BUS_SHORTED_GND
	:annotation: = 4096
.. py:data:: SPY_STATUS_BUS_SHORTED_PLUS
	:annotation: = 2048
.. py:data:: SPY_STATUS_CANFD
	:annotation: = 536870912
.. py:data:: SPY_STATUS_CAN_BUS_OFF
	:annotation: = 512
.. py:data:: SPY_STATUS_CAN_ERROR_PASSIVE
	:annotation: = 32
.. py:data:: SPY_STATUS_CHECKSUM_ERROR
	:annotation: = 8192
.. py:data:: SPY_STATUS_COMM_IN_OVERFLOW
	:annotation: = 65536
.. py:data:: SPY_STATUS_CRC_ERROR
	:annotation: = 16
.. py:data:: SPY_STATUS_EXPECTED_LEN_MISMATCH
	:annotation: = 131072
.. py:data:: SPY_STATUS_EXTENDED
	:annotation: = -2147483648
.. py:data:: SPY_STATUS_FLEXRAY_PDU
	:annotation: = 536870912
.. py:data:: SPY_STATUS_FLEXRAY_PDU_NO_UPDATE_BIT
	:annotation: = 8
.. py:data:: SPY_STATUS_FLEXRAY_PDU_UPDATE_BIT_SET
	:annotation: = 1073741824
.. py:data:: SPY_STATUS_GLOBAL_ERR
	:annotation: = 1
.. py:data:: SPY_STATUS_GPS_DATA
	:annotation: = 8388608
.. py:data:: SPY_STATUS_HEADERCRC_ERROR
	:annotation: = 32
.. py:data:: SPY_STATUS_HIGH_SPEED
	:annotation: = 1073741824
.. py:data:: SPY_STATUS_INCOMPLETE_FRAME
	:annotation: = 64
.. py:data:: SPY_STATUS_INIT_MESSAGE
	:annotation: = 536870912
.. py:data:: SPY_STATUS_LIN_MASTER
	:annotation: = 536870912
.. py:data:: SPY_STATUS_LOST_ARBITRATION
	:annotation: = 128
.. py:data:: SPY_STATUS_MSG_NO_MATCH
	:annotation: = 262144
.. py:data:: SPY_STATUS_NETWORK_MESSAGE_TYPE
	:annotation: = 67108864
.. py:data:: SPY_STATUS_PDU
	:annotation: = 536870912
.. py:data:: SPY_STATUS_REMOTE_FRAME
	:annotation: = 8
.. py:data:: SPY_STATUS_TEST_TRIGGER
	:annotation: = 2097152
.. py:data:: SPY_STATUS_TEXT_COMMENT
	:annotation: = 33554432
.. py:data:: SPY_STATUS_TX_MSG
	:annotation: = 2
.. py:data:: SPY_STATUS_TX_NOMATCH
	:annotation: = 32768
.. py:data:: SPY_STATUS_UNDEFINED_ERROR
	:annotation: = 256
.. py:data:: SPY_STATUS_VSI_IFR_CRC_BIT
	:annotation: = 268435456
.. py:data:: SPY_STATUS_VSI_TX_UNDERRUN
	:annotation: = 134217728
.. py:data:: SPY_STATUS_XTD_FRAME
	:annotation: = 4
.. py:data:: SWCAN_AUTOSWITCH_DISABLED
	:annotation: = 0
.. py:data:: SWCAN_AUTOSWITCH_DISABLED_RESISTOR_ENABLED
	:annotation: = 3
.. py:data:: SWCAN_AUTOSWITCH_NO_RESISTOR
	:annotation: = 1
.. py:data:: SWCAN_AUTOSWITCH_WITH_RESISTOR
	:annotation: = 2
.. py:data:: SWCAN_SETTINGS_SIZE
	:annotation: = 14
.. py:data:: UART_SETTINGS_SIZE
	:annotation: = 16
.. py:data:: USE_TQ
	:annotation: = 1
.. py:data:: VNETBITS_FEATURE_ANDROID_MSGS
	:annotation: = 1
.. py:data:: VNETBITS_FEATURE_DISABLE_USB_CHECK
	:annotation: = 2
