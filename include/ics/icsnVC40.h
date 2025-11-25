/*
Copyright (c) 2016 Intrepid Control Systems, Inc.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _ICSNVC40_H
#define _ICSNVC40_H

#if defined(_MSC_VER) && (_MSC_VER <= 1500)
// Visual studio has extremely poor support for C99 pre-2010
typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef __int64 int64_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif

#include "cicsSpyStatusBits.h"

#if defined(_MSC_VER)
#pragma warning(disable : 4200)
#endif

// MSVC++ 10.0 _MSC_VER == 1600 64-bit version doesn't allow multi-line #if directives...
#if defined(_WIN64) || defined(__x86_64__) || defined(__aarch64__) || defined(__x86_64__) || defined(__LP64__) || defined(_M_AMD64) || \
	defined(_M_IA64) || defined(__PPC64__)
#define IS_64BIT_SYSTEM
#endif

//deprecated old definition!  Use either SPY_STATUS2_ISO_RX_TIMEOUT_ERROR or SPY_STATUS2_LIN_RX_TIMEOUT_ERROR!
#define SPY_STATUS2_RX_TIMEOUT_ERROR SPY_STATUS2_ISO_RX_TIMEOUT_ERROR

/* OpenPort "OpenType" Argument Constants -- deprecated, use OpenNeoDevice */
#define NEOVI_COMMTYPE_RS232 0
#define NEOVI_COMMTYPE_USB_BULK 1
#define NEOVI_COMMTYPE_TCPIP 3
#define NEOVI_COMMTYPE_FIRE_USB 5

/* Network IDs -- value of NetworkID member of icsSpyMessage */
#define NETID_DEVICE 0
#define NETID_HSCAN 1
#define NETID_MSCAN 2
#define NETID_SWCAN 3
#define NETID_LSFTCAN 4
#define NETID_FORDSCP 5
#define NETID_J1708 6
#define NETID_AUX 7
#define NETID_JVPW 8
#define NETID_ISO 9
#define NETID_ISOPIC 10
#define NETID_MAIN51 11
#define NETID_RED 12
#define NETID_SCI 13
#define NETID_ISO2 14
#define NETID_ISO14230 15
#define NETID_LIN 16
#define NETID_OP_ETHERNET1 17
#define NETID_OP_ETHERNET2 18
#define NETID_OP_ETHERNET3 19
#define NETID_ISO3 41
#define NETID_HSCAN2 42
#define NETID_HSCAN3 44
#define NETID_OP_ETHERNET4 45
#define NETID_OP_ETHERNET5 46
#define NETID_ISO4 47
#define NETID_LIN2 48
#define NETID_LIN3 49
#define NETID_LIN4 50
#define NETID_MOST 51
#define NETID_RED_APP_ERROR 52
#define NETID_CGI 53
#define NETID_3G_RESET_STATUS 54
#define NETID_3G_FB_STATUS 55
#define NETID_3G_APP_SIGNAL_STATUS 56
#define NETID_3G_READ_DATALINK_CM_TX_MSG 57
#define NETID_3G_READ_DATALINK_CM_RX_MSG 58
#define NETID_3G_LOGGING_OVERFLOW 59
#define NETID_3G_READ_SETTINGS_EX 60
#define NETID_HSCAN4 61
#define NETID_HSCAN5 62
#define NETID_RS232 63
#define NETID_UART 64
#define NETID_UART2 65
#define NETID_UART3 66
#define NETID_UART4 67
#define NETID_SWCAN2 68
#define NETID_ETHERNET_DAQ 69
#define NETID_DATA_TO_HOST 70
#define NETID_TEXTAPI_TO_HOST 71
#define NETID_SPI1 72
#define NETID_OP_ETHERNET6 73
#define NETID_RED_VBAT 74
#define NETID_OP_ETHERNET7 75
#define NETID_OP_ETHERNET8 76
#define NETID_OP_ETHERNET9 77
#define NETID_OP_ETHERNET10 78
#define NETID_OP_ETHERNET11 79
#define NETID_FLEXRAY1A 80
#define NETID_FLEXRAY1B 81
#define NETID_FLEXRAY2A 82
#define NETID_FLEXRAY2B 83
#define NETID_LIN5 84
#define NETID_FLEXRAY 85
#define NETID_FLEXRAY2 86
#define NETID_OP_ETHERNET12 87
#define NETID_I2C1 88
#define NETID_MOST25 90
#define NETID_MOST50 91
#define NETID_MOST150 92
#define NETID_ETHERNET 93
#define NETID_GMFSA 94
#define NETID_TCP 95
#define NETID_HSCAN6 96
#define NETID_HSCAN7 97
#define NETID_LIN6 98
#define NETID_LSFTCAN2 99
/**
 * To the next person to add a network, please make it 523!
 */
#define NETID_HW_COM_LATENCY_TEST 512
#define NETID_DEVICE_STATUS 513
#define NETID_UDP 514
#define NETID_AUTOSAR 515
#define NETID_FORWARDED_MESSAGE 516
#define NETID_I2C2 517
#define NETID_I2C3 518
#define NETID_I2C4 519
#define NETID_ETHERNET2 520
#define NETID_ETHERNET_TX_WRAP 521
#define NETID_A2B_01 522
#define NETID_A2B_02 523
#define NETID_ETHERNET3 524
#define NETID_ISM_LOGGER 525
#define NETID_CAN_SWITCH 526

#define NETID_WBMS 532
#define NETID_WBMS2 533
#define NETID_DWCAN_09 534
#define NETID_DWCAN_10 535
#define NETID_DWCAN_11 536
#define NETID_DWCAN_12 537
#define NETID_DWCAN_13 538
#define NETID_DWCAN_14 539
#define NETID_DWCAN_15 540
#define NETID_DWCAN_16 541
#define NETID_LIN_07 542
#define NETID_LIN_08 543
#define NETID_SPI2 544
#define NETID_MDIO_01 545
#define NETID_MDIO_02 546
#define NETID_MDIO_03 547
#define NETID_MDIO_04 548
#define NETID_MDIO_05 549
#define NETID_MDIO_06 550
#define NETID_MDIO_07 551
#define NETID_MDIO_08 552
#define NETID_OP_ETHERNET13 553
#define NETID_OP_ETHERNET14 554
#define NETID_OP_ETHERNET15 555
#define NETID_OP_ETHERNET16 556
#define NETID_SPI3 557
#define NETID_SPI4 558
#define NETID_SPI5 559
#define NETID_SPI6 560
#define NETID_SPI7 561
#define NETID_SPI8 562
#define NETID_LIN_09 563
#define NETID_LIN_10 564
#define NETID_LIN_11 565
#define NETID_LIN_12 566
#define NETID_LIN_13 567
#define NETID_LIN_14 568
#define NETID_LIN_15 569
#define NETID_LIN_16 570

/* Upper boundry of Network IDs */
#define NETID_MAX 100
#define NETID_INVALID 0xffff

/* Device types -- value of DeviceType of NeoDevice */
/* Older devices have a value on a specific bit. Those values have not changed 
 * to support existing apps using the api. New devices can fill in between the 
 * existing ones. I know it hurts, but it's just a number!
 */
//clang-format off
#define NEODEVICE_UNKNOWN (0x00000000)
#define NEODEVICE_BLUE (0x00000001)
#define NEODEVICE_ECU_AVB_DEPRECATED (0x00000002)
#define NEODEVICE_RADSUPERMOON_DEPRECATED (0x00000003)
#define NEODEVICE_DW_VCAN (0x00000004)
#define NEODEVICE_RADMOON2 (0x00000005)
#define NEODEVICE_RADGIGALOG_DEPRECATED (0x00000006) /* AKA RADMARS */
#define NEODEVICE_VCAN41 (0x00000007)
#define NEODEVICE_FIRE (0x00000008)
#define NEODEVICE_RADPLUTO_DEPRECATED (0x00000009)
#define NEODEVICE_VCAN42_EL (0x0000000a)
#define NEODEVICE_RADIO_CANHUB (0x0000000b)
#define NEODEVICE_NEOECU12 (0x0000000c)
#define NEODEVICE_OBD2_LC (0x0000000d)
#define NEODEVICE_RAD_MOON_DUO_DEPRECATED (0x0000000e)
#define NEODEVICE_FIRE3 (0x0000000f)
#define NEODEVICE_VCAN3 (0x00000010)
#define NEODEVICE_RADJUPITER (0x00000011)
#define NEODEVICE_VCAN4_IND (0x00000012)
#define NEODEVICE_GIGASTAR (0x00000013)
#define NEODEVICE_RED2 (0x00000014)
#define NEODEVICE_FIRE2_REDLINE_DEPRECATED (0x00000015)
#define NEODEVICE_ETHER_BADGE_DEPRECATED (0x00000016)
#define NEODEVICE_RAD_A2B (0x00000017)
#define NEODEVICE_RADEPSILON (0x00000018)
#define NEODEVICE_OBD2_SIM_DOIP_DEPRECATED (0x00000019)
#define NEODEVICE_OBD2_DEV_DEPRECATED (0x0000001a)
#define NEODEVICE_ECU22_DEPRECATED (0x0000001b)
#define NEODEVICE_RADEPSILON_T (0x0000001c)
#define NEODEVICE_RADEPSILON_EXPRESS (0x0000001d)
#define NEODEVICE_RADPROXIMA (0x0000001e)

// I'm not sure what was 0x20 anymore, but we'll skip it to be safe
#define NEODEVICE_RAD_GALAXY_2 (0x00000021)
#define NEODEVICE_RAD_BMS (0x00000022)
#define NEODEVICE_RADMOON3 (0x00000023)
#define NEODEVICE_RADCOMET (0x00000024)
#define NEODEVICE_FIRE3_FLEXRAY (0x00000025)
#define NEODEVICE_NEOVI_CONNECT (0x00000026)
#define NEODEVICE_RADCOMET3 (0x00000027)
#define NEODEVICE_RADMOONT1S (0x00000028)
#define NEODEVICE_GIGASTAR2 (0x00000029)
#define NEODEVICE_FIRE3_T1S_LIN (0x0000002A)
#define NEODEVICE_FIRE3_T1S_SENT (0x0000002B)
#define NEODEVICE_RADGEMINI (0x0000002C)

#define NEODEVICE_RED (0x00000040)
#define NEODEVICE_ECU (0x00000080)
#define NEODEVICE_IEVB_DEPRECATED (0x00000100)
#define NEODEVICE_PENDANT (0x00000200)
#define NEODEVICE_OBD2_PRO_DEPRECATED (0x00000400)
#define NEODEVICE_ECUCHIP_UART_DEPRECATED (0x00000800)
#define NEODEVICE_PLASMA (0x00001000)
#define NEODEVICE_DONT_REUSE0 (0x00002000) //NEODEVICE_FIRE_VNET
#define NEODEVICE_NEOANALOG (0x00004000)
#define NEODEVICE_CT_OBD (0x00008000)
#define NEODEVICE_DONT_REUSE1 (0x00010000) //NEODEVICE_PLASMA_1_12
#define NEODEVICE_DONT_REUSE2 (0x00020000) //NEODEVICE_PLASMA_1_13
#define NEODEVICE_ION (0x00040000)
#define NEODEVICE_RADSTAR_DEPRECATED (0x00080000)
#define NEODEVICE_DONT_REUSE3 (0x00100000) //NEODEVICE_ION3
#define NEODEVICE_VCAN44 (0x00200000)
#define NEODEVICE_VCAN42 (0x00400000)
#define NEODEVICE_CMPROBE_DEPRECATED (0x00800000)
#define NEODEVICE_EEVB_DEPRECATED (0x01000000)
#define NEODEVICE_DONT_REUSE4 (0x02000000)
#define NEODEVICE_FIRE2 (0x04000000)
#define NEODEVICE_FLEX_DEPRECATED (0x08000000)
#define NEODEVICE_RADGALAXY (0x10000000)
#define NEODEVICE_RADSTAR2 (0x20000000)
#define NEODEVICE_VIVIDCAN (0x40000000)
#define NEODEVICE_OBD2_SIM_DEPRECATED (0x80000000)
#define NEODEVICE_ANY_PLASMA (NEODEVICE_PLASMA)
#define NEODEVICE_ANY_ION (NEODEVICE_ION)
#define NEODEVICE_NEOECUCHIP NEODEVICE_IEVB_DEPRECATED
//clang-format on

#define DEVICECOUNT_FOR_EXPLORER (36) //this value will be checked by the NeoViExplorer after #6453!

#define ISO15765_2_NETWORK_HSCAN 0x01
#define ISO15765_2_NETWORK_MSCAN 0x02
#define ISO15765_2_NETWORK_HSCAN2 0x04
#define ISO15765_2_NETWORK_HSCAN3 0x08
#define ISO15765_2_NETWORK_SWCAN 0x10
#define ISO15765_2_NETWORK_HSCAN4 0x14
#define ISO15765_2_NETWORK_HSCAN5 0x18
#define ISO15765_2_NETWORK_HSCAN6 0x1C
#define ISO15765_2_NETWORK_HSCAN7 0x20
#define ISO15765_2_NETWORK_SWCAN2 0x24

#define PLASMA_SLAVE1_OFFSET 100
#define PLASMA_SLAVE2_OFFSET 200
#define PLASMA_SLAVE_NUM 51

#define PLASMA_SLAVE1_OFFSET_RANGE2 4608
#define PLASMA_SLAVE2_OFFSET_RANGE2 8704
#define PLASMA_SLAVE3_OFFSET_RANGE2 12800

#define SCRIPT_STATUS_STOPPED 0
#define SCRIPT_STATUS_RUNNING 1

#define SCRIPT_LOCATION_FLASH_MEM 0
#define SCRIPT_LOCATION_INTERNAL_FLASH 2
#define SCRIPT_LOCATION_SDCARD 1
#define SCRIPT_LOCATION_VCAN3_MEM 4
#define SCRIPT_LOCATION_EMMC 6

/* Protocols -- value of Protocol member of icsSpyMessage */
#define SPY_PROTOCOL_CUSTOM 0
#define SPY_PROTOCOL_CAN 1
#define SPY_PROTOCOL_GMLAN 2
#define SPY_PROTOCOL_J1850VPW 3
#define SPY_PROTOCOL_J1850PWM 4
#define SPY_PROTOCOL_ISO9141 5
#define SPY_PROTOCOL_Keyword2000 6
#define SPY_PROTOCOL_GM_ALDL_UART 7
#define SPY_PROTOCOL_CHRYSLER_CCD 8
#define SPY_PROTOCOL_CHRYSLER_SCI 9
#define SPY_PROTOCOL_FORD_UBP 10
#define SPY_PROTOCOL_BEAN 11
#define SPY_PROTOCOL_LIN 12
#define SPY_PROTOCOL_J1708 13
#define SPY_PROTOCOL_CHRYSLER_JVPW 14
#define SPY_PROTOCOL_J1939 15
#define SPY_PROTOCOL_FLEXRAY 16
#define SPY_PROTOCOL_MOST 17
#define SPY_PROTOCOL_CGI 18
#define SPY_PROTOCOL_GME_CIM_SCL_KLINE 19
#define SPY_PROTOCOL_SPI 20
#define SPY_PROTOCOL_I2C 21
#define SPY_PROTOCOL_GENERIC_UART 22
#define SPY_PROTOCOL_JTAG 23
#define SPY_PROTOCOL_UNIO 24
#define SPY_PROTOCOL_DALLAS_1WIRE 25
#define SPY_PROTOCOL_GENERIC_MANCHSESTER 26
#define SPY_PROTOCOL_SENT_PROTOCOL 27
#define SPY_PROTOCOL_UART 28
#define SPY_PROTOCOL_ETHERNET 29
#define SPY_PROTOCOL_CANFD 30
#define SPY_PROTOCOL_GMFSA 31
#define SPY_PROTOCOL_TCP 32
#define SPY_PROTOCOL_UDP 33
#define SPY_PROTOCOL_AUTOSAR 34
#define SPY_PROTOCOL_A2B 35
#define SPY_PROTOCOL_WBMS 36
#define SPY_PROTOCOL_MDIO 37

/* Configuration Array constants */
/* HSCAN neoVI or ValueCAN */
#define NEO_CFG_MPIC_HS_CAN_CNF1 (512 + 10)
#define NEO_CFG_MPIC_HS_CAN_CNF2 (512 + 9)
#define NEO_CFG_MPIC_HS_CAN_CNF3 (512 + 8)
#define NEO_CFG_MPIC_HS_CAN_MODE (512 + 54)

/* med speed neoVI CAN */
#define NEO_CFG_MPIC_MS_CAN_CNF1 (512 + 22)
#define NEO_CFG_MPIC_MS_CAN_CNF2 (512 + 21)
#define NEO_CFG_MPIC_MS_CAN_CNF3 (512 + 20)

/* med speed neoVI CAN */
#define NEO_CFG_MPIC_SW_CAN_CNF1 (512 + 34)
#define NEO_CFG_MPIC_SW_CAN_CNF2 (512 + 33)
#define NEO_CFG_MPIC_SW_CAN_CNF3 (512 + 32)

/* med speed neoVI CAN */
#define NEO_CFG_MPIC_LSFT_CAN_CNF1 (512 + 46)
#define NEO_CFG_MPIC_LSFT_CAN_CNF2 (512 + 45)
#define NEO_CFG_MPIC_LSFT_CAN_CNF3 (512 + 44)

/* Constants used to calculate timestamps */
#define NEOVI_TIMESTAMP_2 0.1048576
#define NEOVI_TIMESTAMP_1 0.0000016

#define NEOVIPRO_VCAN_TIMESTAMP_2 0.065536
#define NEOVIPRO_VCAN_TIMESTAMP_1 0.000001

#define NEOVI6_VCAN_TIMESTAMP_2 0.065536
#define NEOVI6_VCAN_TIMESTAMP_1 0.000001

#define NEOVI_RED_TIMESTAMP_2_25NS 107.3741824
#define NEOVI_RED_TIMESTAMP_1_25NS 0.000000025

#define NEOVI_RED_TIMESTAMP_2_10NS 429.4967296
#define NEOVI_RED_TIMESTAMP_1_10NS 0.000000010

#define HARDWARE_TIMESTAMP_ID_NONE (unsigned char)0
#define HARDWARE_TIMESTAMP_ID_VSI (unsigned char)1
#define HARDWARE_TIMESTAMP_ID_AVT_716 (unsigned char)2
#define HARDWARE_TIMESTAMP_ID_NI_CAN (unsigned char)3
#define HARDWARE_TIMESTAMP_ID_NEOVI (unsigned char)4
#define HARDWARE_TIMESTAMP_ID_AVT_717 (unsigned char)5
#define HARDWARE_TIMESTAMP_ID_NEOv6_VCAN (unsigned char)6
#define HARDWARE_TIMESTAMP_ID_DOUBLE_SEC (unsigned char)7
#define HARDWARE_TIMESTAMP_ID_NEORED_10US (unsigned char)8
#define HARDWARE_TIMESTAMP_ID_NEORED_25NS (unsigned char)9
#define HARDWARE_TIMESTAMP_ID_NEORED_10NS (unsigned char)10

//flag to indicate if the timestamp is a fixed value, or if it is a timestamp referenced to a network object
//if this flag is NOT set, then the TimeStampHardwareID is a 1-based index for GetHWAt(index)
//see CMessageTimeDecoder::GetSpyTimeType()
//see cicsSpyCE::GetSpyTimeType()
#define HADRWARE_TIMESTAMP_ID_FIXED 0x80

#define FIRE2_REPORT_PERIODIC (0x0001)
#define FIRE2_REPORT_EMISC1_DIGITAL (0x0002)
#define FIRE2_REPORT_EMISC2_DIGITAL (0x0004)
#define FIRE2_REPORT_MISC5_DIGITAL (0x0008)
#define FIRE2_REPORT_MISC6_DIGITAL (0x0010)
#define FIRE2_REPORT_EMISC1_ANALOG (0x0020)
#define FIRE2_REPORT_EMISC2_ANALOG (0x0040)
#define FIRE2_REPORT_VBATT_ANALOG (0x0080)
#define FIRE2_REPORT_TEMP_ANALOG (0x0100)
#define FIRE2_REPORT_PWM_IN (0x0200)
#define FIRE2_REPORT_GPS (0x0400)
#define FIRE3_REPORT_ORIENTATION (0x0800)

typedef struct SExtendedDataFlashHeader
{
	uint16_t version;
	uint16_t chksum;
	uint32_t len;
} ExtendedDataFlashHeader_t;

typedef struct
{
	uint32_t DeviceType;
	int32_t Handle;
	int32_t NumberOfClients;
	int32_t SerialNumber;
	int32_t MaxAllowedClients;

} NeoDevice;

typedef struct _NeoDeviceEx
{
	NeoDevice neoDevice;

	uint32_t FirmwareMajor;
	uint32_t FirmwareMinor;

#define CANNODE_STATUS_COREMINI_IS_RUNNING (0x1)
#define CANNODE_STATUS_IN_BOOTLOADER (0x2)
	uint32_t Status; // Bitfield, see defs above

// Option bit flags
#define MAIN_VNET (0x01)
#define SLAVE_VNET_A (0x02)
#define SLAVE_VNET_B (0x04)
#define WIFI_CONNECTION (0x08)
#define REGISTER_BY_SERIAL (0x10)
#define TCP_SUPPORTED (0x20)
#define DRIVER_MASK (0xC0)
#define DRIVER_USB1 (0x40)
#define DRIVER_USB2 (0x80)
#define DRIVER_USB3 (0xC0)
#define SERVD_DRIVER_MASK  (0xFF00)
#define SERVD_DRIVER_VCP   (0x0100)
#define SERVD_DRIVER_DXX   (0x0200)
#define SERVD_DRIVER_CAB   (0x0400)
#define SERVD_DRIVER_TCP   (0x1000)
	uint32_t Options;

	void* pAvailWIFINetwork;
	void* pWIFIInterfaceInfo;

	int isEthernetDevice;

	uint8_t MACAddress[6];
	uint16_t hardwareRev;
	uint16_t revReserved;
	uint32_t tcpIpAddress[4];
	uint16_t tcpPort;
	uint16_t Reserved0;
	uint32_t Reserved1;

} NeoDeviceEx;

typedef union tagOptionsOpenNeoEx
{
	struct
	{
		int32_t iNetworkID; /* Network ID indicating which CAN network to communicate over */
	} CANOptions;

	uint32_t Reserved[16]; /* may be expanded in future revisions */
} OptionsOpenNeoEx, *POptionsOpenNeoEx;

typedef union tagOptionsFindNeoEx
{
	struct
	{
		int32_t iNetworkID; /* Network ID indicating which CAN network to communicate over */
	} CANOptions;
	uint32_t Reserved[16]; /* may be expanded in future revisions */

} OptionsFindNeoEx, *POptionsFindNeoEx;

typedef struct tagicsneoVICommand
{
	uint8_t CommandType;
	uint8_t CommandByteLength;
	uint8_t Data[14];
} icsneoVICommand;

typedef enum
{
	PHY_88Q211x_Z1 = 0,
	PHY_88Q211x_A0 = 1,
	PHY_88Q211x_A1 = 2,
	PHY_88Q211x_A2 = 3,
	PHY_88Q222xM_A0 = 4,
	PHY_88Q222xM_B0 = 5,
	PHY_88Q222xM_B1 = 6,
	PHY_88Q222xM_B2 = 7,
	PHY_UNKNOWN = 255,
} PhyId;

#pragma pack(push, 1)

typedef struct _stAPIFirmwareInfo
{
	int32_t iType; /* 1,2,3 for Generation of HW */

	/* Date and Time (only valid for type 1 and 2) */
	int32_t iMainFirmDateDay;
	int32_t iMainFirmDateMonth;
	int32_t iMainFirmDateYear;
	int32_t iMainFirmDateHour;
	int32_t iMainFirmDateMin;
	int32_t iMainFirmDateSecond;
	int32_t iMainFirmChkSum;

	/* Version data (only valid for type 3) */
	uint8_t iAppMajor;
	uint8_t iAppMinor;

	uint8_t iManufactureDay;
	uint8_t iManufactureMonth;
	uint16_t iManufactureYear;

	uint8_t iBoardRevMajor;
	uint8_t iBoardRevMinor;

	uint8_t iBootLoaderVersionMajor;
	uint8_t iBootLoaderVersionMinor;
	uint8_t iMainVnetHWrevMajor;
	uint8_t iMainVnetHWrevMinor;
	uint8_t iMainVnetSRAMSize;

	uint8_t iPhySiliconRev;
} stAPIFirmwareInfo;

#pragma pack(pop)

/* Settings structures come are all packed to 2 bytes */
#pragma pack(push, 2)

/* Define number of CMP streams per device*/
#define CMP_STREAMS_FIRE3 (10)
#define CMP_STREAMS_FIRE3FR (10)
#define CMP_STREAMS_FIRE3T1SLIN (10)
#define CMP_STREAMS_RED2 (10)
#define CMP_STREAMS_A2B (3)
#define CMP_STREAMS_GIGASTAR (10)

/* CMP Network Enables */
typedef struct
{
	uint8_t bStreamEnabled : 1;
	uint8_t EthModule : 2;
	uint8_t bControlEnabled : 1;
	uint8_t spare : 4;
	uint8_t streamId;
	uint8_t dstMac[6];
	union
	{
		uint64_t word;
		struct
		{
			uint16_t network_enables;
			uint16_t network_enables_2;
			uint16_t network_enables_3;
			uint16_t network_enables_4;
		};
	} network_enables;
	uint64_t network_enables_2;
} CMP_NETWORK_DATA;

/* Global CMP Data */
typedef struct
{
	uint8_t cmp_enabled : 1;
	uint8_t sparebits : 7;
	uint8_t spare;
	uint16_t cmp_device_id;
} CMP_GLOBAL_DATA;

/* SetBaudrate in CAN_SETTINGS */
enum
{
	AUTO,
	USE_TQ
};

/* Baudrate in CAN_SETTINGS/CANFD_SETTINGS */
enum
{
	BPS20,
	BPS33,
	BPS50,
	BPS62,
	BPS83,
	BPS100,
	BPS125,
	BPS250,
	BPS500,
	BPS800,
	BPS1000,
	BPS666,
	BPS2000,
	BPS4000,
	CAN_BPS5000,
	CAN_BPS6667,
	CAN_BPS8000,
	CAN_BPS10000,
};

/* Mode in CAN_SETTINGS */
enum
{
	NORMAL = 0,
	DISABLE = 1,
	LOOPBACK = 2,
	LISTEN_ONLY = 3,
	LISTEN_ALL = 7
};

typedef struct
{
	uint8_t Mode;
	uint8_t SetBaudrate;
	uint8_t Baudrate;
	uint8_t transceiver_mode;
	uint8_t TqSeg1;
	uint8_t TqSeg2;
	uint8_t TqProp;
	uint8_t TqSync;
	uint16_t BRP;
	uint8_t auto_baud;
	uint8_t innerFrameDelay25us : 4;
	uint8_t : 1;
	uint8_t disableRetransmission : 1;
	uint8_t canClk : 2;
} CAN_SETTINGS;
#define CAN_SETTINGS_SIZE 12

/* FDMode in CANFD_SETTINGS */
enum
{
	NO_CANFD,
	CANFD_ENABLED,
	CANFD_BRS_ENABLED,
	CANFD_ENABLED_ISO,
	CANFD_BRS_ENABLED_ISO
};

typedef struct _CANFD_SETTINGS
{
	uint8_t FDMode; /* mode, secondary baudrate for canfd */
	uint8_t FDBaudrate;
	uint8_t FDTqSeg1;
	uint8_t FDTqSeg2;
	uint8_t FDTqProp;
	uint8_t FDTqSync;
	uint16_t FDBRP;
	uint8_t FDTDC;
	uint8_t reserved;
} CANFD_SETTINGS;
#define CANFD_SETTINGS_SIZE 10

/* high_speed_auto_switch in SWCAN_SETTINGS */
enum
{
	SWCAN_AUTOSWITCH_DISABLED,
	SWCAN_AUTOSWITCH_NO_RESISTOR,
	SWCAN_AUTOSWITCH_WITH_RESISTOR,
	SWCAN_AUTOSWITCH_DISABLED_RESISTOR_ENABLED
};

typedef struct
{
	uint8_t Mode;
	uint8_t SetBaudrate;
	uint8_t Baudrate;
	uint8_t transceiver_mode;
	uint8_t TqSeg1;
	uint8_t TqSeg2;
	uint8_t TqProp;
	uint8_t TqSync;
	uint16_t BRP;
	uint16_t high_speed_auto_switch;
	uint8_t auto_baud;
	uint8_t RESERVED;
} SWCAN_SETTINGS;
#define SWCAN_SETTINGS_SIZE 14

/* Baudrate in LIN_SETTINGS / ISO9141_KEYWORD2000_SETTINGS / UART_SETTINGS */
enum
{
	BPS5000,
	BPS10400,
	BPS33333,
	BPS50000,
	BPS62500,
	BPS71429,
	BPS83333,
	BPS100000,
	BPS117647
};

/* MasterResistor in LIN_SETTINGS */
enum
{
	RESISTOR_ON,
	RESISTOR_OFF
};

/* Mode in LIN_SETTINGS */
enum
{
	SLEEP_MODE,
	SLOW_MODE,
	NORMAL_MODE,
	FAST_MODE
};

typedef struct _LIN_SETTINGS
{
	uint32_t Baudrate; /* New products since FIREVNETEP should rely on this only */
	uint16_t spbrg; /* Precompiled to be 40Mhz/Baudrate/16 - 1.  Only used in neoVI FIRE/FIREVNET(4dw) */
	uint8_t brgh; /* Must be zero */
	uint8_t numBitsDelay;
	uint8_t MasterResistor;
	uint8_t Mode;
} LIN_SETTINGS;
#define LIN_SETTINGS_SIZE 10

typedef struct
{
	uint16_t time_500us;
	uint16_t k;
	uint16_t l;
} ISO9141_KEYWORD2000__INIT_STEP;
#define ISO9141_KEYWORD2000__INIT_STEP_SIZE 6

typedef struct
{
	uint32_t Baudrate;
	uint16_t spbrg;
	uint16_t brgh;
	ISO9141_KEYWORD2000__INIT_STEP init_steps[16];
	uint8_t init_step_count;
	uint16_t p2_500us;
	uint16_t p3_500us;
	uint16_t p4_500us;
	uint16_t chksum_enabled;
} ISO9141_KEYWORD2000_SETTINGS;
#define ISO9141_KEYWORD2000_SETTINGS_SIZE 114

typedef struct _UART_SETTINGS
{
	uint16_t Baudrate;
	uint16_t spbrg;
	uint16_t brgh;
	uint16_t parity;
	uint16_t stop_bits;
	uint8_t flow_control; /* 0- off, 1 - Simple CTS RTS */
	uint8_t reserved_1;
	union
	{
		uint32_t bOptions;
		struct
		{
			unsigned invert_tx : 1;
			unsigned invert_rx : 1;
			unsigned half_duplex : 1;
			unsigned reserved_bits : 13;
			unsigned reserved_bits2 : 16;
		};
	};
} UART_SETTINGS;
#define UART_SETTINGS_SIZE 16

typedef struct
{
	uint16_t enable_convert_mode;
} J1708_SETTINGS;
#define J1708_SETTINGS_SIZE 2

typedef struct _SRedSettings
{
	CAN_SETTINGS can1;
	CAN_SETTINGS can2;
	LIN_SETTINGS lin1;
	LIN_SETTINGS lin2;
} SRedSettings;
#define SRedSettings_SIZE 44

typedef struct _STextAPISettings
{
	uint32_t can1_tx_id;
	uint32_t can1_rx_id;
	union
	{
		struct
		{
			unsigned bExtended : 1;
			unsigned : 31;
		};
		uint32_t DWord;
	} can1_options;
	uint32_t can2_tx_id;
	uint32_t can2_rx_id;
	union
	{
		struct
		{
			unsigned bExtended : 1;
			unsigned : 31;
		};
		uint32_t DWord;
	} can2_options;

	uint32_t network_enables;

	uint32_t can3_tx_id;
	uint32_t can3_rx_id;
	union
	{
		struct
		{
			unsigned bExtended : 1;
			unsigned : 31;
		};
		uint32_t DWord;
	} can3_options;

	uint32_t can4_tx_id;
	uint32_t can4_rx_id;
	union
	{
		struct
		{
			unsigned bExtended : 1;
			unsigned : 31;
		};
		uint32_t DWord;
	} can4_options;

	uint32_t reserved[5];

} STextAPISettings;
#define STextAPISettings_SIZE 72

typedef union _stChipVersions
{
	struct
	{
		uint8_t mpic_maj;
		uint8_t mpic_min;
		uint8_t upic_maj;
		uint8_t upic_min;
		uint8_t lpic_maj;
		uint8_t lpic_min;
		uint8_t jpic_maj;
		uint8_t jpic_min;
	} fire_versions;

	struct
	{
		uint8_t mpic_maj;
		uint8_t mpic_min;
		uint8_t core_maj;
		uint8_t core_min;
		uint8_t lpic_maj;
		uint8_t lpic_min;
		uint8_t hid_maj;
		uint8_t hid_min;
	} plasma_fire_vnet;

	struct
	{
		uint8_t mpic_maj;
		uint8_t mpic_min;
	} vcan3_versions;

	struct
	{
		uint8_t zynq_core_major;
		uint8_t zynq_core_minor;
	} radgalaxy_versions;

	struct
	{
		uint8_t zynq_core_major;
		uint8_t zynq_core_minor;
	} radstar2_versions;

	struct
	{
		uint8_t mpic_maj;
		uint8_t mpic_min;
		uint8_t ext_flash_maj;
		uint8_t ext_flash_min;
		uint8_t nrf52_maj;
		uint8_t nrf52_min;
	} vividcan_versions;

	struct
	{
		uint8_t mchip_major;
		uint8_t mchip_minor;
	} vcan41_versions;

	struct
	{
		uint8_t mchip_major;
		uint8_t mchip_minor;
	} vcan42_versions;
	struct
	{
		uint8_t zynq_core_major;
		uint8_t zynq_core_minor;
	} radmoon2_versions;
	struct
	{
		uint8_t zynq_core_major;
		uint8_t zynq_core_minor;
	} radmoon2_z7010_versions;
	struct
	{
		uint8_t mchip_major;
		uint8_t mchip_minor;
	} radmoon3_versions;
	struct
	{
		uint8_t mchip_major;
		uint8_t mchip_minor;
	} radgemini_versions;

	struct
	{
		uint8_t zynq_core_major;
		uint8_t zynq_core_minor;
		uint8_t usb_core_major;
		uint8_t usb_core_minor;
	} radgigastar_versions;

	struct
	{
		uint8_t zynq_core_major;
		uint8_t zynq_core_minor;
	} radGalaxy2_versions;

	struct
	{
		uint8_t mchip_major;
		uint8_t mchip_minor;
		uint8_t schip_major;
		uint8_t schip_minor;
	} obd2lc_versions;
	struct
	{
		uint8_t mchip_major;
		uint8_t mchip_minor;
	} jupiter_versions;

	struct
	{
		uint8_t zchip_major;
		uint8_t zchip_minor;
		uint8_t schip_major;
		uint8_t schip_minor;
	} red2_versions;
	struct
	{
		uint8_t zchip_major;
		uint8_t zchip_minor;
		uint8_t schip_major;
		uint8_t schip_minor;
		uint8_t vem_z_major;
		uint8_t vem_z_minor;
	} fire3_versions;
	struct
	{
		uint8_t zchip_major;
		uint8_t zchip_minor;
		uint8_t schip_major;
		uint8_t schip_minor;
		uint8_t vem_z_major;
		uint8_t vem_z_minor;
		uint8_t vem_f_major;
		uint8_t vem_f_minor;
	} fire3_flexray_versions;

	struct
	{
		uint8_t zchip_major;
		uint8_t zchip_minor;
		uint8_t schip_major;
		uint8_t schip_minor;
		uint8_t vem_z_major;
		uint8_t vem_z_minor;
	} fire3_t1slin_versions;

	struct
	{
		uint8_t zynq_core_major;
		uint8_t zynq_core_minor;
	} rad_a2b_versions;

	struct
	{
		uint8_t mchip_major;
		uint8_t mchip_minor;
	} epsilon_versions;

	struct
	{
		uint8_t mchip_major;
		uint8_t mchip_minor;
		uint8_t wil_major;
		uint8_t wil_minor;	
	} rad_wbms_versions;

	struct
	{
		uint8_t zynq_core_major;
		uint8_t zynq_core_minor;
	} rad_comet_versions;

	struct
	{
		uint8_t zynq_core_major;
		uint8_t zynq_core_minor;
	} rad_comet3_versions;

	struct
	{
		uint8_t zynq_core_major;
		uint8_t zynq_core_minor;
		uint8_t usb_core_major;
		uint8_t usb_core_minor;
	} radgigastar2_versions;

	struct
	{
		uint8_t zynq_core_major;
		uint8_t zynq_core_minor;
	} rad_moont1s_versions;

	struct
	{
		uint8_t zchip_major;
		uint8_t zchip_minor;
	} neovi_connect_versions;

} stChipVersions;

#define stChipVersions_SIZE 8

typedef struct _SNeoMostGatewaySettings
{
	uint16_t netId;
	uint8_t zero0;
	uint8_t Config;
} SNeoMostGatewaySettings;
#define SNeoMostGatewaySettings_SIZE 4

/* ucInterfaceType in OP_ETH_GENERAL_SETTINGS */
enum
{
	OPETH_FUNC_TAP = 0,
	OPETH_FUNC_MEDIACONVERTER,
	OPETH_FUNC_TAP_LOW_LATENCY,
	OPETH_FUNC_RAW_MEDIA_CONVERTER,
	OPETH_FUNC_RAW_MEDIA_CONVERTER2,
	OPETH_FUNC_RAW_MEDIA_CONVERTER2_LOW_LATENCY,
};

typedef struct OP_ETH_GENERAL_SETTINGS_t
{
	uint8_t ucInterfaceType;
	union
	{
		uint8_t tapPairOpt;
		struct
		{
			uint8_t tap1ToVspy : 1;
			uint8_t tap2ToVspy : 1;
			uint8_t tap3ToVspy : 1;
			uint8_t tap4ToVspy : 1;
			uint8_t tap5ToVspy : 1;
			uint8_t tap6ToVspy : 1;
			uint8_t tap7ToVspy : 1;
			uint8_t tap8ToVspy : 1;
		};
	};
	uint8_t reserved0[2];
	uint16_t tapPair0;
	uint16_t tapPair1;
	uint16_t tapPair2;
	uint16_t tapPair3;
	uint16_t tapPair4;
	uint16_t tapPair5;
	union
	{
		struct
		{
			uint32_t bTapEnSwitch : 1;
			uint32_t bTapEnPtp : 1;
			uint32_t bEnReportLinkQuality : 1;
			uint32_t bEnTapTxReceipts : 1;
			uint32_t reserved : 28;
		} flags;
		uint32_t uFlags;
	};
} OP_ETH_GENERAL_SETTINGS;
#define OP_ETH_GENERAL_SETTINGS_SIZE 20

typedef struct SRAD_GPTP_SETTINGS_s
{
	uint32_t neighborPropDelayThresh; //ns
	uint32_t sys_phc_sync_interval; //ns
	int8_t logPDelayReqInterval; // log2ms
	int8_t logSyncInterval; // log2ms
	int8_t logAnnounceInterval; // log2ms
	uint8_t profile;
	uint8_t priority1;
	uint8_t clockclass;
	uint8_t clockaccuracy;
	uint8_t priority2;
	uint16_t offset_scaled_log_variance;
	uint8_t gPTPportRole;
	uint8_t gptpEnabledPort;
	uint8_t enableClockSyntonization;
	uint8_t rsvd_1;
	uint8_t icsGptpDrvVerHeader;
	union {
		uint8_t icsGptpDrvVerMajorMinor;
		struct {
			uint8_t icsGptpDrvVerMajor:4;
			uint8_t icsGptpDrvVerMinor:4;
		};
	};
	union{
		uint32_t multiPortsEnabledForMaster;
		struct {
			uint32_t PORT_AE01:1;	// this is LSB in Little Endian
			uint32_t PORT_AE02:1;
			uint32_t PORT_AE03:1;
			uint32_t PORT_AE04:1;
			uint32_t PORT_AE05:1;
			uint32_t PORT_AE06:1;
			uint32_t PORT_AE07:1;
			uint32_t PORT_AE08:1;
			uint32_t PORT_AE09:1;
			uint32_t PORT_AE10:1;
			uint32_t PORT_AE11:1;
			uint32_t PORT_AE12:1;

			uint32_t PORT_ETH1:1;
			uint32_t PORT_ETH2:1;
			uint32_t PORT_ETH3:1;

			uint32_t PORT_AE13:1;
			uint32_t PORT_AE14:1;
			uint32_t PORT_AE15:1;
			uint32_t PORT_AE16:1;
		};
	};
	uint8_t rsvd_2[8];
} RAD_GPTP_SETTINGS; //36 Bytes
#define RAD_GPTP_SETTINGS_SIZE 36

typedef struct SRAD_GPTP_AND_TAP_SETTINGS_s
{
	RAD_GPTP_SETTINGS gPTP;
	OP_ETH_GENERAL_SETTINGS tap;
} RAD_GPTP_AND_TAP_SETTINGS;
#define RAD_GPTP_AND_TAP_SETTINGS_SIZE 40

/* ucConfigMode in OP_ETH_SETTINGS */
typedef enum _opEthLinkMode
{
	OPETH_LINK_AUTO = 0,
	OPETH_LINK_MASTER,
	OPETH_LINK_SLAVE
} opEthLinkMode;

enum
{
	OPETH_MAC_SPOOF_DST_ADDR = 0,
	OPETH_MAC_SPOOF_SRC_ADDR = 1,
};

typedef struct OP_ETH_SETTINGS_t
{
	uint8_t ucConfigMode;
	uint8_t preemption_en;
	union
	{
		struct
		{
			// Reuse the mac_addr for switch mode if required!
			uint8_t mac_addr1[6]; // Original Addr for spoofing
			uint8_t mac_addr2[6]; // Target Addr for spoofing
			uint16_t mac_spoofing_en : 1;
			uint16_t mac_spoofing_isDstOrSrc : 1;
			uint16_t link_spd : 2;
			uint16_t q2112_phy_mode : 1;
			uint16_t macsec_en : 1; // enable loading MACsec config on boot
			uint16_t compliance_mode_en : 1;
			uint16_t cut_thru_tap : 1;
			uint16_t snf_tap : 1; // store and forward
			uint16_t disable_tap_to_host : 1;
			uint16_t show_tap_tx_receipt : 1;
			uint16_t reserved : 5;
		};
		uint8_t reserved0[14];
	};
} OP_ETH_SETTINGS;
#define OP_ETH_SETTINGS_SIZE 16

typedef struct ETHERNET_SETTINGS_t
{
	uint8_t duplex; /* 0 = half, 1 = full */
	uint8_t link_speed;
	uint8_t auto_neg;
	uint8_t led_mode;
	uint8_t rsvd[4];
} ETHERNET_SETTINGS;
#define ETHERNET_SETTINGS_SIZE 8


#define ETHERNET_SETTINGS2_FLAG_FULL_DUPLEX 0x01
#define ETHERNET_SETTINGS2_FLAG_AUTO_NEG 0x02
#define ETHERNET_SETTINGS2_FLAG_TCPIP_ENABLE 0x04
#define ETHERNET_SETTINGS2_FLAG_RTSP_ENABLE 0x08
#define ETHERNET_SETTINGS2_FLAG_DEVICE_HOSTING_ENABLE 0x10
#define ETHERNET_SETTINGS2_FLAG_CONFIG_NOT_ALLOWED 0x20
#define ETHERNET_SETTINGS2_FLAG_ICS_SFP 0x40
#define ETHERNET_SETTINGS2_FLAG_COMM_IN_USE 0x80

#define ETHERNET_SETTINGS2_FLAG2_LINK_MODE 0x01
#define ETHERNET_SETTINGS2_FLAG2_PHY_MODE 0x02
#define ETHERNET_SETTINGS2_FLAG2_LINK_MODE_AUTO 0x04
#define ETHERNET_SETTINGS2_FLAG2_IP_CONFIG_NOT_ALLOWED 0x08
#define ETHERNET_SETTINGS2_FLAG2_SFP_ID_SHIFT 4
#define ETHERNET_SETTINGS2_FLAG2_SFP_ID_MASK 0xF0
#define ETHERNET_SETTINGS2_FLAG2_CUT_THRU_TAP_ENABLE 0x0100
#define ETHERNET_SETTINGS2_FLAG2_SNF_TAP_ENABLE 0x0200 // store and forward
#define ETHERNET_SETTINGS2_FLAG2_DISABLE_TAP_TO_HOST 0x0400
#define ETHERNET_SETTINGS2_FLAG2_SHOW_TAP_TX_RECEIPT 0x0800
#define ETHERNET_SETTINGS2_FLAG2_TCP_COMM_STATIC_PORT_ENABLE 0x1000
#define ETHERNET_SETTINGS2_FLAG2_TAP_DEST_SHIFT 13
#define ETHERNET_SETTINGS2_FLAG2_TAP_DEST_MASK 0x3
#define ETHERNET_SETTINGS2_FLAG2_TC10_FWD_TAP_ENABLE 0x8000

typedef enum
{
	SFP_ID_UNKNOWN = 0,
	SFP_ID_FINISAR_FCLF8522P2BTL,
	SFP_ID_FS_GB_GE_T,
	SFP_ID_ICS_MV2112A2,
	SFP_ID_ICS_MV2221MB1,
	SFP_ID_ICS_MV3244,
	SFP_ID_ICS_MC8670,
	SFP_ID_ICS_EN11100,
	SFP_ID_ICS_AD1101,
	// add new entries here
	SFP_ID_MAX,
} SfpId;

typedef struct ETHERNET_SETTINGS2_t
{
	/* FLAGS
	 * bit0: 0=half duplex, 1=full duplex
	 * bit1: auto negot
	 * bit2: enable tcp/ip stack
	 * bit3: enable rtsp server
	 * bit4: enable intepid device hosting (go online and log other devices)
	 * bit5: config not allowed
	 * bit6: ICS SFP detected
	 * bit7: comm in use
	 */
	uint8_t flags;
	uint8_t link_speed; // 0=10, 1=100, 2=1000
	uint32_t ip_addr;
	uint32_t netmask;
	uint32_t gateway;
	/* FLAGS2
	 * bit0: Link mode - 0=master, 1=slave
	 * bit1: PHY mode - 0=IEEE, 1=legacy
	 * bit2: auto master/slave
	 * bit3: IP config not allowed
	 * bit4: SFP module ID0
	 * bit5: SFP module ID1
	 * bit6: SFP module ID2
	 * bit7: SFP module ID3
	 * bit8: cut through tap enabled (only TX forwarded from tap partner)
	 * bit9: store and forward tap enabled (forward RX to tap partner)
	 * bit10: disable tap frames to host
	 * bit11: show TX receipt for tap frames
	 * bit12: enable static port for TCP comm
	 */
	uint16_t flags2;
} ETHERNET_SETTINGS2;
#define ETHERNET_SETTINGS2_SIZE 16

#define ETHERNET_SETTINGS10G_FLAG_FULL_DUPLEX 0x00000001
#define ETHERNET_SETTINGS10G_FLAG_AUTO_NEG 0x00000002
#define ETHERNET_SETTINGS10G_FLAG_TCPIP_ENABLE 0x00000004
#define ETHERNET_SETTINGS10G_FLAG_RTSP_ENABLE 0x00000008
#define ETHERNET_SETTINGS10G_FLAG_DEVICE_HOSTING_ENABLE 0x00000010
#define ETHERNET_SETTINGS10G_FLAG_CONFIG_NOT_ALLOWED 0x00000020
#define ETHERNET_SETTINGS10G_FLAG_ICS_SFP 0x00000040
#define ETHERNET_SETTINGS10G_FLAG_LINK_MODE 0x00000080
#define ETHERNET_SETTINGS10G_FLAG_PHY_MODE 0x00000100
#define ETHERNET_SETTINGS10G_FLAG_LINK_MODE_AUTO 0x00000200
#define ETHERNET_SETTINGS10G_FLAG_COMPL_MODE 0x00000400
#define ETHERNET_SETTINGS10G_FLAG_PKT_CHECK 0x00000800
#define ETHERNET_SETTINGS10G_FLAG_PKT_GEN 0x00001000
#define ETHERNET_SETTINGS10G_FLAG_IP_CONFIG_NOT_ALLOWED 0x00002000
#define ETHERNET_SETTINGS10G_FLAG_CUT_THRU_TAP_ENABLE 0x00004000
#define ETHERNET_SETTINGS10G_FLAG_SNF_TAP_ENABLE 0x00008000 // store and forward
#define ETHERNET_SETTINGS10G_FLAG_DISABLE_TAP_TO_HOST 0x00010000
#define ETHERNET_SETTINGS10G_FLAG_MACSEC_ENABLE 0x00020000
#define ETHERNET_SETTINGS10G_FLAG_SHOW_TAP_TX_RECEIPT 0x00040000
#define ETHERNET_SETTINGS10G_FLAG_TCP_COMM_STATIC_PORT_ENABLE 0x00080000
#define ETHERNET_SETTINGS10G_FLAG_COMM_IN_USE 0x80000000

typedef struct ETHERNET10G_SETTINGS_t
{
	/* FLAGS
	 * bit0: 0=half duplex, 1=full duplex
	 * bit1: auto negot
	 * bit2: enable tcp/ip stack
	 * bit3: enable rtsp server
	 * bit4: enable intepid device hosting (go online and log other devices)
	 * bit5: config not allowed
	 * bit6: ICS SFP detected
	 * bit7: link mode - 0=master, 1=slave
	 * bit8: PHY mode - 0=IEEE, 1=legacy
	 * bit9: auto master/slave
	 * bit10: enable compliance test mode (device specific)
	 * bit11: enable packet checker
	 * bit12: enable packet generator
	 * bit13: IP config not allowed
	 * bit14: cut through tap enabled (only TX forwarded from tap partner)
	 * bit15: store and forward tap enabled (forward RX to tap partner)
	 * bit16: disable tap frames to host
	 * bit17: macsec enable
	 * bit18: show TX receipt for tap frames
	 * bit19: enable static port for TCP comm
	 * bit31: comm in use
	 */
	uint32_t flags;
	uint32_t ip_addr;
	uint32_t netmask;
	uint32_t gateway;
	uint8_t link_speed; //0=10, 1=100, 2=1000, 3=2500, 4=5000, 5=10000
	uint8_t compliance_mode;
	uint8_t rsvd2[6];
} ETHERNET10G_SETTINGS;
#define ETHERNET10G_SETTINGS_SIZE 24

typedef struct ETHERNET10T1S_SETTINGS_t
{
	uint8_t max_burst_count;
	uint8_t burst_timer;
	uint8_t max_num_nodes;
	uint8_t local_id;
	uint8_t to_timer;
	uint8_t flags;
	uint8_t local_id_alternate;
	uint8_t rsvd[5];
} ETHERNET10T1S_SETTINGS;
#define ETHERNET10T1S_SETTINGS_SIZE 12

#define ETHERNET10T1S_SETTINGS_FLAG_ENABLE_PLCA 0x01
#define ETHERNET10T1S_SETTINGS_FLAG_TERMINATION 0x02
#define ETHERNET10T1S_SETTINGS_FLAG_BUS_DECODING_BEACONS 0x04
#define ETHERNET10T1S_SETTINGS_FLAG_BUS_DECODING_ALL 0x08
#define ETHERNET10T1S_SETTINGS_FLAG_ENABLE_PLCA_COL_DET 0x10
#define ETHERNET10T1S_SETTINGS_FLAG_ENABLE_CSMA_FALLBACK 0x20
#define ETHERNET10T1S_SETTINGS_FLAG_DISABLE_ALL_DECODING 0x40

typedef struct ETHERNET10T1S_SETTINGS_EXT_t
{
	uint8_t enable_multi_id; // Mask representing whether ID at corresponding bit enabled or not
	uint8_t multi_id[7];
	uint8_t rsvd[8];
} ETHERNET10T1S_SETTINGS_EXT;
#define ETHERNET10T1S_SETTINGS_EXT_SIZE 16

typedef struct ETHERNET10T1L_SETTINGS_t
{
	uint8_t tx_mode;
	uint8_t rsvd[7];
} ETHERNET10T1L_SETTINGS;
#define ETHERNET10T1L_SETTINGS_SIZE 8

/* 
 * START - MACsec Definitions 
 */
/* MACsec Rule */
/**
 * @brief Structure of Vlan tag
 * 
 */
#pragma pack(push, 1)
typedef struct
{
	uint16_t VID; /*!< 12 bits */
	uint8_t PRI_CFI; /*!< PRI - 3 bits, CFI - 1bit */
} MACSEC_VLANTAG_t;
/**
 * @brief Structure of MPLS
 * 
 */
typedef struct
{
	uint32_t MPLS_label; /*!< 20 bits */
	uint8_t exp; /*!< 3 bits */
} MACSEC_MPLS_OUTER_t;
/**
 * @brief Define Encoded Packet Type from the parser
 * 
 */
typedef enum
{
	MACSEC_PACKET_NO_VLAN_OR_MPLS = 0,
	MACSEC_PACKET_SINGLE_VLAN = 1,
	MACSEC_PACKET_DUAL_VLAN = 2,
	MACSEC_PACKET_MPLS = 3,
	MACSEC_PACKET_SINGLE_VLAN_FOLLOW_BY_MPLS = 4,
	MACSEC_PACKET_DUAL_VLAN_FOLLOW_BY_MPLS = 5,
	MACSEC_PACKET_UNSUPPORTED_TYPE = 6
} MACSEC_PACKET_TYPE;
#define MACSEC_SETTINGS_RULE_SIZE (88)
typedef union _MACSecRule
{
	struct
	{
		uint8_t index;
		uint8_t key_MAC_DA[6]; /*!< MAC DA field extracted from the packet */
		uint8_t mask_MAC_DA[6]; /*!< Set bits to 1 to mask/exclude corresponding flowid_tcam_data bit from compare */
		uint8_t key_MAC_SA[6]; /*!< MAC SA field extracted from the packet */
		uint8_t mask_MAC_SA[6]; /*!< Set bits to 1 to mask/exclude corresponding flowid_tcam_data bit from compare */
		uint16_t key_Ethertype; /*!< First E-Type found in the packet that doesn't match one of the preconfigured custom tag. */
		uint16_t mask_Ethertype; /*!< Set bits to 1 to mask/exclude corresponding flowid_tcam_data bit from compare */
		MACSEC_VLANTAG_t key_vlantag_outer1; /*!< outermost/1st VLAN ID {8'd0, VLAN_ID[11:0]}, or 20-bit MPLS label. */
		MACSEC_MPLS_OUTER_t key_MPLS_outer1;
		MACSEC_VLANTAG_t mask_vlantag_outer1; /*!< Set bits to 1 to mask/exclude corresponding flowid_tcam_data bit from compare */
		MACSEC_MPLS_OUTER_t mask_MPLS_outer1;
		MACSEC_VLANTAG_t key_vlantag_outer2; /*!< 2nd outermost VLAN ID {8'd0, VLAN_ID[11:0]}, or 20-bit MPLS label. */
		MACSEC_MPLS_OUTER_t key_MPLS_outer2;
		MACSEC_VLANTAG_t mask_vlantag_outer2; /*!< Set bits to 1 to mask/exclude corresponding flowid_tcam_data bit from compare */
		MACSEC_MPLS_OUTER_t mask_MPLS_outer2;
		uint16_t key_bonus_data; /*!< 2 bytes of additional bonus data extracted from one of the custom tags. */
		uint16_t mask_bonus_data; /*!< Set bits to 1 to mask/exclude corresponding flowid_tcam_data bit from compare */
		uint8_t
			key_tag_match_bitmap; /*!< 8 bits total. Maps 1 to 1 bitwise with the set of custom tags. (set bit[N]=1 if check Nth custom tag) */
		uint8_t mask_tag_match_bitmap; /*!< Set bits to 1 to mask/exclude corresponding flowid_tcam_data bit from compare */
		uint8_t key_packet_type; /*!< Encoded Packet Type, see MACSEC_PACKET_TYPE */
		uint8_t mask_packet_type; /*!< Set bits to 1 to mask/exclude corresponding flowid_tcam_data bit from compare */
		uint16_t
			key_inner_vlan_type; /*!< 3 bits total. Encoded value indicating which VLAN TPID value matched for the second outermost VLAN Tag. */
		uint16_t mask_inner_vlan_type; /*!< Set bits to 1 to mask/exclude corresponding flowid_tcam_data bit from compare */
		uint16_t key_outer_vlan_type; /*!< 3 bits total. Encoded value indicating which VLAN TPID value matched for the outermost VLAN Tag. */
		uint16_t mask_outer_vlan_type; /*!< Set bits to 1 to mask/exclude corresponding flowid_tcam_data bit from compare */
		uint8_t
			key_num_tags; /*!< 7 bits total. Number of VLAN/custom tags or MPLS lables detected. Ingress: before SecTag; Egress: total detected. Exclude MCS header tags. i.e. Bit 2: 2 tags/labels before SecTAG...Bit 6: 6 or more tags/labels before SecTAG. */
		uint8_t mask_num_tags; /*!< Set bits to 1 to mask/exclude corresponding flowid_tcam_data bit from compare */
		uint8_t key_express; /*!< 1 bits. Express packet. */
		uint8_t mask_express; /*!< Set bits to 1 to mask/exclude corresponding flowid_tcam_data bit from compare */
		uint8_t isMPLS;
		uint8_t rsvd[5];
		uint8_t enable;
	};
	uint8_t byte[MACSEC_SETTINGS_RULE_SIZE];
} MACSecRule_t;
/* MACsec Map */
#define MACSEC_SETTINGS_MAP_SIZE (20)
typedef union _MACSecMap
{
	struct
	{
		uint8_t index;
		uint64_t sectag_sci; /*!< Identifies the SecTAG SCI for this Flow. */
		uint8_t secYIndex; /*!< index for entry in Egress secY Policy */
		uint8_t isControlPacket; /*!< Identifies all packets matching this index lookup as control packets. */
		uint8_t scIndex; /*!< Identifies the SC for this Flow. */
		uint8_t auxiliary_plcy; /*!< Auxiliary policy bits. */
		uint8_t ruleId; /*!< Identifies the Rule for this Flow. */
		uint8_t rsvd[5];
		uint8_t enable;
	};
	uint8_t byte[MACSEC_SETTINGS_MAP_SIZE];
} MACSecMap_t;
/* MACsec SecY */
/**
 * @brief Define the permit police for frames as defined in 802.1ae
 * 
 */
typedef enum
{
	MACSEC_VF_DISABLED = 0, /*!< Disable validation */
	MACSEC_VF_CHECK = 1, /*!< Enable validation, do not discard invalid frames*/
	MACSEC_VF_STRICT = 2, /*!< Enable validation and discard invalid frames */
	MACSEC_VF_NA = 3 /*!< No processing or accounting */
} MACSEC_VALIDATEFRAME;
/**
 * @brief Define SecTag and ICV configuration.
 * 
 */
typedef enum
{
	MACSEC_SECTAG_ICV_BOTH_STRIP = 0, /*!< Strip both SecTag and ICV from packet */
	MACSEC_SECTAG_ICV_RESERVED = 1,
	MACSEC_SECTAG_ICV_STRIP_ICV_ONLY = 2, /*!< Preserve SecTag, Strip ICV */
	MACSEC_SECTAG_ICV_NO_STRIP = 3 /*!< Preserve both SecTag and ICV */
} MACSEC_STRIP_SECTAG_ICV;
/**
 * @brief Define the cipher suite to use for this SecY
 * 
 */
typedef enum
{
	MACSEC_CIPHER_GCM_AES_128 = 0,
	MACSEC_CIPHER_GCM_AES_256 = 1,
	MACSEC_CIPHER_GCM_AES_128_XPN = 2,
	MACSEC_CIPHER_GCM_AES_256_XPN = 3
} MACSEC_CIPHER_SUITE;
#define MACSEC_SETTINGS_SECY_SIZE (24)
typedef union _MACSecSecY
{
	struct
	{
		uint8_t index; /*!< Identifies the SecY for this Flow. */
		uint8_t controlled_port_enabled; /*!< Enable (or disable) operation of the Controlled port associated with this SecY */
		uint8_t validate_frames; /*!< see MACSEC_VALIDATEFRAME */
		uint8_t strip_sectag_icv; /*!< see MACSEC_STRIP_SECTAG_ICV */
		uint8_t cipher; /*!< Define the cipher suite to use for this SecY see MACSEC_CIPHER_SUITE */
		uint8_t confidential_offset; /*!< Define the number of bytes that are unencrypted following the SecTag. */
		uint8_t icv_includes_da_sa; /*!< When set, the outer DA/SA bytes are included in the authentication GHASH calculation */
		uint8_t replay_protect; /*!< Enables Anti-Replay protection */
		uint32_t replay_window; /*!< Unsigned value indicating the size of the anti-replay window. */
		uint8_t
			protect_frames; /*!< 0 = do not encrypt or authenticate this packet; 1 = always Authenticate frame and if SecTag.TCI.E = 1 encrypt the packet as well. */
		uint8_t
			sectag_offset; /*!< Define the offset in bytes from either the start of the packet or a matching Etype depending on SecTag_Insertion_Mode. */
		uint8_t sectag_tci; /*!< Tag Control Information excluding the AN field which originates from the SA Policy table */
		uint16_t mtu; /*!< Specifies the outgoing MTU for this SecY */
		uint8_t rsvd[6];
		uint8_t enable;
	};
	uint8_t byte[MACSEC_SETTINGS_SECY_SIZE];
} MACSecSecY_t;
/* MACsec SC */
#define MACSEC_SETTINGS_SC_SIZE (24)
typedef union _MACSecSc
{
	struct
	{
		uint8_t index; /*!< SC index. */
		uint8_t secYIndex; /*!< SecY associated with this packet. */
		uint64_t sci; /*!< The Secure Channel Identifier. */
		uint8_t sa_index0; /*!< Define the 1st SA to use */
		uint8_t sa_index1; /*!< Define the 2nd SA to use */
		uint8_t sa_index0_in_use; /*!< Specifies whether 1st SA is in use or not. */
		uint8_t sa_index1_in_use; /*!< Specifies whether 2nd SA is in use or not.  */
		uint8_t enable_auto_rekey; /*!< If enabled, then once the pn_threshold is reached, auto rekey will happen. */
		uint8_t
			isActiveSA1; /*!< If set, then sa_index1 is the currently active SA index. If cleared, the sa_index0 is the currently active SA index). */
		uint8_t rsvd[7];
		uint8_t enable;
	};
	uint8_t byte[MACSEC_SETTINGS_SC_SIZE];
} MACSecSc_t;
/* MACsec SA */
#define MACSEC_SETTINGS_SA_SIZE (80)
typedef union _MACSecSa
{
	struct
	{
		uint8_t index; /*!< SA index */
		uint8_t
			sak[32]; /*!< 256b SAK: Define the encryption key to be used to encrypte this packet. The lower 128 bits are used for 128-bit ciphers. */
		uint8_t hashKey[16]; /*!< 128b Hash Key: Key used for authentication. */
		uint8_t salt[12]; /*!< 96b Salt value: Salt value used in XPN ciphers. */
		uint32_t ssci; /*!< 32b SSCI value: Short Secure Channel Identifier, used in XPN ciphers. */
		uint8_t AN; /*!< 2b SecTag Association Number (AN) */
		uint64_t nextPN; /*!< 64b next_pn value: Next packet number to insert into outgoing packet on a particular SA. */
		uint8_t rsvd[5];
		uint8_t enable;
	};
	uint8_t byte[MACSEC_SETTINGS_SA_SIZE];
} MACSecSa_t;
/* MACsec Flags */
#define MACSEC_SETTINGS_FLAGS_SIZE (4)
typedef union _MACSecFlags
{
	struct
	{
		uint32_t en : 1; // '1' = enable; '0' = disable
		uint32_t reserved : 31;
	};
	uint32_t flags_32b;
} MACSecFlags_t;
/* MACSec Settings for 1 port/phy */
#define MACSEC_NUM_FLAGS_PER_CONFIG (1)
#define MACSEC_NUM_RULES_PER_CONFIG (2)
#define MACSEC_NUM_MAPS_PER_CONFIG (2)
#define MACSEC_NUM_SECY_PER_CONFIG (2)
#define MACSEC_NUM_SC_PER_CONFIG (2)
#define MACSEC_NUM_SA_PER_CONFIG (4)
typedef struct MACSEC_CONFIG_t
{
	MACSecFlags_t flags;
	MACSecRule_t rule[MACSEC_NUM_RULES_PER_CONFIG];
	MACSecMap_t map[MACSEC_NUM_MAPS_PER_CONFIG];
	MACSecSecY_t secy[MACSEC_NUM_SECY_PER_CONFIG];
	MACSecSc_t sc[MACSEC_NUM_SC_PER_CONFIG];
	MACSecSa_t sa[MACSEC_NUM_SA_PER_CONFIG];
} MACSEC_CONFIG;
typedef union _MACSecGlobalFlags
{
	struct
	{
		uint32_t en : 1; // '1' = enable; '0' = disable
		uint32_t nvm : 1; // store macsec config in non-volatile memory
		uint32_t reserved : 30;
	};
	uint32_t flags_32b;
} MACSecGlobalFlags_t;
#define MACSEC_SETTINGS_SIZE (2040) // leave space for expansion and keep nicely aligned for flashing
typedef union _MACSEC_SETTINGS
{
	struct
	{
		MACSecGlobalFlags_t flags;
		MACSEC_CONFIG rx;
		MACSEC_CONFIG tx;
	};
	uint8_t byte[MACSEC_SETTINGS_SIZE];
} MACSEC_SETTINGS;
#pragma pack(pop)
/* 
 * END - MACsec Definitions 
 */

typedef struct LOGGER_SETTINGS_t
{
	/* bit6-0: timeout in seconds
	 * bit7: 1=disable coremini/logging during extraction for timeout
	 */
	uint8_t extraction_timeout;
	uint8_t rsvd[3];
} LOGGER_SETTINGS;
#define LOGGER_SETTINGS_SIZE 4

typedef struct DISK_SETTINGS_t
{
	uint8_t disk_layout; // RAID0, spanned, etc
	uint8_t disk_format; // FAT32
	uint32_t disk_enables; // mask of enabled disks in this layout
	uint8_t rsvd[8];
} DISK_SETTINGS;
#define DISK_SETTINGS_SIZE 14

typedef struct
{
	uint8_t term_enabled;
	uint8_t term_network;
	uint16_t reserved[2];
} CANTERM_SETTINGS;
#define CANTERM_SETTINGS_SIZE 6

typedef struct
{
	uint8_t MasterEnable;
	uint8_t SlaveEnable;
	uint8_t MasterNetwork;
	uint8_t SlaveNetwork;
} TIMESYNC_ICSHARDWARE_SETTINGS;
#define TIMESYNC_ICSHARDWARE_SETTINGS_SIZE 4

typedef enum _EDiskFormat
{
	DiskFormatUnknown = 0,
	DiskFormatFAT32,
	DiskFormatexFAT,
} EDiskFormat;

typedef enum _EDiskLayout
{
	DiskLayoutSpanned = 0,
	DiskLayoutRAID0,
	DiskLayoutRAID1,
	DiskLayoutRAID5,
	DiskLayoutIndividual,
} EDiskLayout;

// Extended Comm structures
#define DISK_STATUS_FLAG_PRESENT 0x01
#define DISK_STATUS_FLAG_INITIALIZED 0x02

typedef struct _SDiskStatus
{
	uint16_t status; // 0x1 = present, 0x2 = initialized
	uint8_t sectors[8];
	uint8_t bytesPerSector[4];
} SDiskStatus;
#define SDiskStatus_SIZE 14

#define DISK_STRUCTURE_FLAG_FULL_FORMAT 0x01

typedef struct _SDiskStructure
{
	DISK_SETTINGS settings;
	uint16_t options; // 0x01 full format
} SDiskStructure;
#define SDiskStructure_SIZE 16

typedef struct _SDiskDetails
{
	SDiskStructure structure;
	SDiskStatus status[12];
} SDiskDetails;
#define SDiskDetails_SIZE 184

typedef struct _SDiskFormatProgress
{
	uint16_t state; // state of formatting (not started, writing file system, formatting, writing VSAs, finished)
	uint8_t sectorsRemaining[8];
} SDiskFormatProgress;
#define SDiskFormatProgress_SIZE 10

typedef struct _StartDHCPServerCommand
{
	uint16_t networkId; // NETID_ of the physical ethernet network on which to start the server
	uint32_t serverIpAddress; // Set as our IP address using LWIP_SetIPAddress
	uint32_t subnetMask; // Subnet mask to advertise - set our subnet to match using LWIP_SetNetmask
	uint32_t gatewayAddress; // Gateway address to advertise on DHCP server offers
	uint32_t startAddress; // Start of IP address range available for the server to offer
	uint32_t endAddress; // End of IP address range available for the server to offer
	uint32_t leaseTime; // Lease time setting for the DHCP server in seconds
	uint32_t overwrite; // flag - set to nonzero if we want to overwrite an already running DHCP server
} StartDHCPServerCommand;

typedef struct _StopDHCPServerCommand
{
	uint16_t networkId; // NETID_ of the network on which to attempt to stop the DHCP server
} StopDHCPServerCommand;

typedef enum _ExtendedResponseCode
{
	EXTENDED_RESPONSE_OK = 0,
	// Unsupported sub command
	EXTENDED_RESPONSE_INVALID_COMMAND = -1,
	// Device is not in the correct state to accept this command
	EXTENDED_RESPONSE_INVALID_STATE = -2,
	// Operation failed
	EXTENDED_RESPONSE_OPERATION_FAILED = -3,
	// Response code for a non-blocking command that is successfully queued but still in progress
	EXTENDED_RESPONSE_OPERATION_PENDING = -4,
	// One or more invalid parameters were supplied
	EXTENDED_RESPONSE_INVALID_PARAMETER = -5,
} ExtendedResponseCode;

typedef struct _ExtendedResponseGeneric
{
	uint16_t commandType; // command type we're responding to
	int32_t returnCode;
} ExtendedResponseGeneric;

typedef struct _GenericAPISelector
{
	uint8_t apiIndex;
	uint8_t instance;
	uint8_t functionID;
} GenericAPISelector;

typedef struct _GenericAPIStatus
{
	GenericAPISelector api;
	uint8_t functionError;
	uint8_t calbackError;
	uint8_t finishedProcessing;
} GenericAPIStatus;

#define GENERIC_API_DATA_BUFFER_SIZE 513

typedef struct _GenericAPIData
{
	uint16_t length;	
	GenericAPISelector api;
	uint8_t bData[GENERIC_API_DATA_BUFFER_SIZE];
} GenericAPIData;

typedef struct _GenericAPIData_OLD
{
	GenericAPISelector api;
	uint8_t bData[GENERIC_API_DATA_BUFFER_SIZE];
	uint16_t length;	
} GenericAPIData_OLD;

typedef struct _wBMSManagerSetLock
{
	uint8_t managerIndex;
	uint8_t setLock;
} wBMSManagerSetLock;

typedef struct _wBMSManagerReset
{
	uint8_t managerIndex;
} wBMSManagerReset;

typedef struct _UartPortData
{
	uint16_t len;
	uint8_t port;
	uint8_t bData[256];
} UartPortData;

typedef struct _UartPortPortBytes
{
	uint16_t len;
	uint8_t port;
	uint8_t flag;
} UartPortPortBytes;

typedef struct _UartPortConfig
{
	uint32_t baudrate;
	uint8_t port;
	uint8_t reserve[7];
} UartPortConfig;
#pragma pack(push, 1)

struct _timestamp
{
	uint16_t seconds_msb;
	uint32_t seconds_lsb;
	uint32_t nanoseconds;
};

typedef uint64_t _clock_identity;

struct port_identity
{
	_clock_identity clock_identity;
	uint16_t port_number;
};
struct _clock_quality
{
	uint8_t clock_class;
	uint8_t clock_accuracy;
	uint16_t offset_scaled_log_variance;
};
struct system_identity
{
	uint8_t priority_1;
	struct _clock_quality clock_quality;
	uint8_t priority_2;
	_clock_identity clock_identity;
};
struct priority_vector
{
	struct system_identity sysid;
	uint16_t steps_removed;
	struct port_identity portid;
	uint16_t port_number;
};
struct _scaled_ns {
	int16_t nanoseconds_msb;
	int64_t nanoseconds_lsb;
	int16_t fractional_nanoseconds;
};

// IEEE 802.1AS-2020 14.3
// This is a read-only data structure
struct _current_ds {
	uint16_t steps_removed;
	int64_t offset_from_master;
	struct _scaled_ns last_gm_phase_change;
	double last_gm_freq_change;
	uint16_t gm_time_base_indicator;
	uint32_t gm_change_count;
	uint32_t time_of_last_gm_change_event;
	uint32_t time_of_last_gm_phase_change_event;
	uint32_t time_of_last_gm_freq_change_event;
};

// IEEE 802.1AS-2020 14.4
// This is a read-only data structure
struct _parent_ds {
	struct port_identity parent_port_identity;
	int32_t cumulative_rate_ratio;
	_clock_identity grandmaster_identity;
	uint8_t gm_clock_quality_clock_class;
	uint8_t gm_clock_quality_clock_accuracy;
	uint16_t gm_clock_quality_offset_scaled_log_variance;
	uint8_t gm_priority1;
	uint8_t gm_priority2;
};

typedef struct _GPTPStatus
{
	struct _timestamp current_time;
	struct priority_vector gm_priority;
	int64_t ms_offset_ns;
	uint8_t is_sync;
	uint8_t link_status;
	int64_t link_delay_ns;
	uint8_t selected_role;
	uint8_t as_capable;
	uint8_t is_syntonized;
	struct _timestamp last_rx_sync_ts; // t2 in IEEE 1588-2019 Figure-16
	struct _current_ds current_ds;
	struct _parent_ds parent_ds;
} GPTPStatus;

typedef struct _GenericBinaryStatus
{
	uint32_t size;
	uint16_t index;
	uint16_t status;
	uint8_t reserved[8];
} GenericBinaryStatus;

//-----------------------------------------------------------------
#define MACADDR_LEN 6
#define MULTI_MACADDR_CNT 32
typedef struct _MacAddrEntry
{
	uint16_t mMacId;
	uint8_t mMacAddr[MACADDR_LEN];
} MacAddrEntry;

typedef struct _MultiMacAddrInfo
{
	uint16_t mAddrCnt;
	MacAddrEntry mMacEntries[MULTI_MACADDR_CNT];
} MultiMacAddrInfo;
//-----------------------------------------------------------------

#define GENERIC_BINARY_STATUS_ERROR_UNKNOWN_BINARY 0x0001
#define GENERIC_BINARY_STATUS_ERROR_OVERSIZE 0x0002
#define GENERIC_BINARY_STATUS_ERROR_BINARY_EMPTY 0x0004
#define GENERIC_BINARY_STATUS_ERROR_ANY_MASK \
	(GENERIC_BINARY_STATUS_ERROR_UNKNOWN_BINARY | GENERIC_BINARY_STATUS_ERROR_OVERSIZE | GENERIC_BINARY_STATUS_ERROR_BINARY_EMPTY)

#pragma pack(pop)

#define SERDESCAM_SETTINGS_FLAG_ENABLE 0x0001
#define SERDESCAM_SETTINGS_FLAG_RTSP_ENABLE 0x0002
#define SERDESCAM_SETTINGS_FLAG_AUTO_DET_RES_ENABLE 0x0004
#define SERDESCAM_SETTINGS_FLAG_CONFIG_ENABLE 0x0008
#define SERDESCAM_SETTINGS_FLAG_LOGGING_ENABLE 0x0010
#define SERDESCAM_SETTINGS_FLAG_TX0_ENABLE 0x0020
#define SERDESCAM_SETTINGS_FLAG_TX1_ENABLE 0x0040
#define SERDESCAM_SETTINGS_FLAG_TX2_ENABLE 0x0080
#define SERDESCAM_SETTINGS_FLAG_TX3_ENABLE 0x0100

/* mode in SERDESCAM_SETTINGS */
enum
{
	SERDESCAM_MODE_TAP_REPEATER = 0,
	SERDESCAM_MODE_SPLITTER,
	SERDESCAM_MODE_LOG_ONLY,
	SERDESCAM_MODE_CUSTOM,
	// NOTE: new entries must be appended to maintain backwards compatibility
	// insert new entries here
	SERDESCAM_MODE_COUNT,
};

/* bitPos in SERDESCAM_SETTINGS */
enum
{
	SERDESCAM_PIXEL_BIT_POS_0 = 0,
	SERDESCAM_PIXEL_BIT_POS_1,
	SERDESCAM_PIXEL_BIT_POS_2,
	SERDESCAM_PIXEL_BIT_POS_3,
};

/* videoFormat in SERDESCAM_SETTINGS */
enum
{
	SERDESCAM_VIDEO_FORMAT_NONE = -1,
	SERDESCAM_VIDEO_FORMAT_UYVY_422_8 = 0, // packed YUV 4:2:2, 16bpp, Cb Y0 Cr Y1
	SERDESCAM_VIDEO_FORMAT_YUYV_422_8, // packed YUV 4:2:2, 16bpp, Y0 Cb Y1 Cr
	SERDESCAM_VIDEO_FORMAT_YVYU_422_8, // packed YUV 4:2:2, 16bpp, Y0 Cr Y1 Cb
	SERDESCAM_VIDEO_FORMAT_VYUY_422_8, // packed YUV 4:2:2, 16bpp, Cr Y0 Cb Y1
	SERDESCAM_VIDEO_FORMAT_BAYER_BGGR_8,
	SERDESCAM_VIDEO_FORMAT_RAW_8, // e.g. bayer 8 bit, gray 8 bit
	SERDESCAM_VIDEO_FORMAT_RAW_10, // e.g. bayer 10 bit, gray 10 bit
	SERDESCAM_VIDEO_FORMAT_RAW_12,
	SERDESCAM_VIDEO_FORMAT_RAW_16, // e.g. planar YUV 4:2:2, 16bpp, 8 bit samples
	SERDESCAM_VIDEO_FORMAT_RAW_20, // e.g. planar YUV 4:2:2, 20bpp, 10 bit samples
	SERDESCAM_VIDEO_FORMAT_RAW_24, // e.g. packed RGB 8:8:8 24bpp, 8 bit samples
	SERDESCAM_VIDEO_FORMAT_RAW_30, // e.g. planar YUV 4:4:4, 30bpp, 10 bit samples
	SERDESCAM_VIDEO_FORMAT_RAW_32, // e.g. packed ARGB 8:8:8:8, 32bpp, 8 bit samples
	SERDESCAM_VIDEO_FORMAT_RAW_36,
	SERDESCAM_VIDEO_FORMAT_RGB888, // packed RGB 8:8:8, 24bpp, RGBRGB...
	SERDESCAM_VIDEO_FORMAT_UYVY_422_10LE_PACKED, // packed YUV 4:2:2, 20bpp, Cb Y0 Cr Y1, bitpacked
	SERDESCAM_VIDEO_FORMAT_YUYV_422_10LE_PACKED, // packed YUV 4:2:2, 20bpp, Y0 Cb Y1 Cr, FOURCC Y210 bitpacked
	SERDESCAM_VIDEO_FORMAT_YVYU_422_10LE_PACKED, // packed YUV 4:2:2, 20bpp, Y0 Cr Y1 Cb, bitpacked
	SERDESCAM_VIDEO_FORMAT_VYUY_422_10LE_PACKED, // packed YUV 4:2:2, 20bpp, Cr Y0 Cb Y1, bitpacked
	SERDESCAM_VIDEO_FORMAT_BAYER_BGGR_10LE_PACKED, // 10-bit samples bitpacked into 40-bits little endian
	SERDESCAM_VIDEO_FORMAT_BAYER_BGGR_12LE_PACKED, // 12-bit samples bitpacked into 24-bits little endian
	SERDESCAM_VIDEO_FORMAT_BAYER_BGGR_16LE, // 16-bit samples little endian
	SERDESCAM_VIDEO_FORMAT_BAYER_BGGR_16BE, // 16-bit samples big endian
	SERDESCAM_VIDEO_FORMAT_JPEG,
	SERDESCAM_VIDEO_FORMAT_UYVY_422_12LE_PACKED, // packed YUV 4:2:2, 24bpp, Cb Y0 Cr Y1, bitpacked
	SERDESCAM_VIDEO_FORMAT_YUYV_422_12LE_PACKED, // packed YUV 4:2:2, 24bpp, Y0 Cb Y1 Cr, bitpacked
	SERDESCAM_VIDEO_FORMAT_YVYU_422_12LE_PACKED, // packed YUV 4:2:2, 24bpp, Y0 Cr Y1 Cb, bitpacked
	SERDESCAM_VIDEO_FORMAT_VYUY_422_12LE_PACKED, // packed YUV 4:2:2, 24bpp, Cr Y0 Cb Y1, bitpacked
	SERDESCAM_VIDEO_FORMAT_YUV422_10LE_PLANAR, // planar YUV 4:2:2, 20bpp, (1 Cr & Cb sample per 2x1 Y samples), little-endian
	SERDESCAM_VIDEO_FORMAT_YUV422_16LE_PLANAR, // planar YUV 4:2:2, 32bpp, (1 Cr & Cb sample per 2x1 Y samples), little-endian
	SERDESCAM_VIDEO_FORMAT_RGB565, // packed RGB 5:6:5, 16bpp, RGBRGB...
	SERDESCAM_VIDEO_FORMAT_RGB666, // packed RGB 6:6:6, 18bpp, RGBRGB...
	SERDESCAM_VIDEO_FORMAT_RAW_11x2,
	SERDESCAM_VIDEO_FORMAT_RAW_12x2,
	SERDESCAM_VIDEO_FORMAT_RAW_14,
	// NOTE: CSI2 formats are only used internal to VSPY
	// Firmware should flag video as CSI2 source types
	// Vspy will then convert formats into the proper CSI2 version
	SERDESCAM_VIDEO_FORMAT_CSI2_UYVY_422_8, // packed YUV 4:2:2, 16bpp, Cb Y0 Cr Y1
	SERDESCAM_VIDEO_FORMAT_CSI2_YUYV_422_8, // packed YUV 4:2:2, 16bpp, Y0 Cb Y1 Cr
	SERDESCAM_VIDEO_FORMAT_CSI2_YVYU_422_8, // packed YUV 4:2:2, 16bpp, Y0 Cr Y1 Cb
	SERDESCAM_VIDEO_FORMAT_CSI2_VYUY_422_8, // packed YUV 4:2:2, 16bpp, Cr Y0 Cb Y1
	SERDESCAM_VIDEO_FORMAT_CSI2_UYVY_422_10LE_PACKED, // packed YUV 4:2:2, 20bpp, Cb Y0 Cr Y1, bitpacked
	SERDESCAM_VIDEO_FORMAT_CSI2_YUYV_422_10LE_PACKED, // packed YUV 4:2:2, 20bpp, Y0 Cb Y1 Cr, FOURCC Y210 bitpacked
	SERDESCAM_VIDEO_FORMAT_CSI2_YVYU_422_10LE_PACKED, // packed YUV 4:2:2, 20bpp, Y0 Cr Y1 Cb, bitpacked
	SERDESCAM_VIDEO_FORMAT_CSI2_VYUY_422_10LE_PACKED, // packed YUV 4:2:2, 20bpp, Cr Y0 Cb Y1, bitpacked
	SERDESCAM_VIDEO_FORMAT_CSI2_UYVY_422_12LE_PACKED, // packed YUV 4:2:2, 24bpp, Cb Y0 Cr Y1, bitpacked
	SERDESCAM_VIDEO_FORMAT_CSI2_YUYV_422_12LE_PACKED, // packed YUV 4:2:2, 24bpp, Y0 Cb Y1 Cr, bitpacked
	SERDESCAM_VIDEO_FORMAT_CSI2_YVYU_422_12LE_PACKED, // packed YUV 4:2:2, 24bpp, Y0 Cr Y1 Cb, bitpacked
	SERDESCAM_VIDEO_FORMAT_CSI2_VYUY_422_12LE_PACKED, // packed YUV 4:2:2, 24bpp, Cr Y0 Cb Y1, bitpacked
	SERDESCAM_VIDEO_FORMAT_CSI2_RGB565, // packed RGB 5:6:5, 16bpp, BGRBGR...
	SERDESCAM_VIDEO_FORMAT_CSI2_RGB666, // packed RGB 6:6:6, 18bpp, BGRBGR...
	SERDESCAM_VIDEO_FORMAT_CSI2_RGB888, // packed RGB 8:8:8, 24bpp, BGRBGR...
	SERDESCAM_VIDEO_FORMAT_CSI2_BAYER_BGGR_8,
	SERDESCAM_VIDEO_FORMAT_CSI2_BAYER_BGGR_10LE_PACKED, // 10-bit samples bitpacked into 40-bits little endian
	SERDESCAM_VIDEO_FORMAT_CSI2_BAYER_BGGR_12LE_PACKED, // 12-bit samples bitpacked into 40-bits little endian
	SERDESCAM_VIDEO_FORMAT_CSI2_RAW_8, // e.g. bayer 8 bit, gray 8 bit
	SERDESCAM_VIDEO_FORMAT_CSI2_RAW_10, // e.g. bayer 10 bit, gray 10 bit
	SERDESCAM_VIDEO_FORMAT_CSI2_RAW_11x2,
	SERDESCAM_VIDEO_FORMAT_CSI2_RAW_12,
	SERDESCAM_VIDEO_FORMAT_CSI2_RAW_12x2,
	SERDESCAM_VIDEO_FORMAT_CSI2_RAW_14,
	SERDESCAM_VIDEO_FORMAT_CSI2_RAW_16, // e.g. planar YUV 4:2:2, 16bpp, 8 bit samples
	SERDESCAM_VIDEO_FORMAT_CSI2_RAW_20, // e.g. planar YUV 4:2:2, 20bpp, 10 bit samples
	SERDESCAM_VIDEO_FORMAT_CSI2_RAW_24, // e.g. packed RGB 8:8:8 24bpp, 8 bit samples
	SERDESCAM_VIDEO_FORMAT_CSI2_RAW_30, // e.g. planar YUV 4:4:4, 30bpp, 10 bit samples
	SERDESCAM_VIDEO_FORMAT_CSI2_RAW_32, // e.g. packed ARGB 8:8:8:8, 32bpp, 8 bit samples
	SERDESCAM_VIDEO_FORMAT_CSI2_RAW_36,

	SERDESCAM_VIDEO_FORMAT_BAYER_RGGB_8,
	SERDESCAM_VIDEO_FORMAT_BAYER_RGGB_10LE_PACKED, // 10-bit samples bitpacked into 40-bits little endian
	SERDESCAM_VIDEO_FORMAT_BAYER_RGGB_12LE_PACKED, // 12-bit samples bitpacked into 24-bits little endian
	SERDESCAM_VIDEO_FORMAT_BAYER_RGGB_16LE, // 16-bit samples little endian
	SERDESCAM_VIDEO_FORMAT_BAYER_RGGB_16BE, // 16-bit samples big endian
	SERDESCAM_VIDEO_FORMAT_CSI2_BAYER_RGGB_8,
	SERDESCAM_VIDEO_FORMAT_CSI2_BAYER_RGGB_10LE_PACKED, // 10-bit samples bitpacked into 40-bits little endian
	SERDESCAM_VIDEO_FORMAT_CSI2_BAYER_RGGB_12LE_PACKED, // 12-bit samples bitpacked into 24-bits little endian

	SERDESCAM_VIDEO_FORMAT_BAYER_GBRG_8,
	SERDESCAM_VIDEO_FORMAT_BAYER_GBRG_10LE_PACKED, // 10-bit samples bitpacked into 40-bits little endian
	SERDESCAM_VIDEO_FORMAT_BAYER_GBRG_12LE_PACKED, // 12-bit samples bitpacked into 24-bits little endian
	SERDESCAM_VIDEO_FORMAT_BAYER_GBRG_16LE, // 16-bit samples little endian
	SERDESCAM_VIDEO_FORMAT_BAYER_GBRG_16BE, // 16-bit samples big endian
	SERDESCAM_VIDEO_FORMAT_CSI2_BAYER_GBRG_8,
	SERDESCAM_VIDEO_FORMAT_CSI2_BAYER_GBRG_10LE_PACKED, // 10-bit samples bitpacked into 40-bits little endian
	SERDESCAM_VIDEO_FORMAT_CSI2_BAYER_GBRG_12LE_PACKED, // 12-bit samples bitpacked into 24-bits little endian

	SERDESCAM_VIDEO_FORMAT_BAYER_GRBG_8,
	SERDESCAM_VIDEO_FORMAT_BAYER_GRBG_10LE_PACKED, // 10-bit samples bitpacked into 40-bits little endian
	SERDESCAM_VIDEO_FORMAT_BAYER_GRBG_12LE_PACKED, // 12-bit samples bitpacked into 24-bits little endian
	SERDESCAM_VIDEO_FORMAT_BAYER_GRBG_16LE, // 16-bit samples little endian
	SERDESCAM_VIDEO_FORMAT_BAYER_GRBG_16BE, // 16-bit samples big endian
	SERDESCAM_VIDEO_FORMAT_CSI2_BAYER_GRBG_8,
	SERDESCAM_VIDEO_FORMAT_CSI2_BAYER_GRBG_10LE_PACKED, // 10-bit samples bitpacked into 40-bits little endian
	SERDESCAM_VIDEO_FORMAT_CSI2_BAYER_GRBG_12LE_PACKED, // 12-bit samples bitpacked into 24-bits little endian
	// NOTE: new entries must be appended to maintain backwards compatibility
	// insert new entries before this
	SERDESCAM_VIDEO_FORMAT_COUNT,
};

typedef struct SERDESCAM_SETTINGS_t
{
	/* 
	 * bit0: enable
	 * bit1: RTSP stream enable
	 * bit2: auto detect resolution
	 * bit3: enable configuration
	 * bit4: enable logging
	 * bit5: forward on port 0
	 * bit6: forward on port 1
	 * bit7: forward on port 2
	 * bit8: forward on port 3
	 */
	uint32_t flags;
	uint8_t mode; // passthrough, tap, etc
	uint8_t rsvd1;
	uint8_t bitPos;
	uint8_t videoFormat; // bytes per pixel
	uint16_t resWidth;
	uint16_t resHeight;
	uint8_t frameSkip; // skip every nth frame
	uint8_t rsvd2[19];
} SERDESCAM_SETTINGS;
#define SERDESCAM_SETTINGS_SIZE 32

#define SERDESPOC_SETTINGS_MODE_DISABLED 0x00
#define SERDESPOC_SETTINGS_MODE_SUPPLY 0x01
#define SERDESPOC_SETTINGS_MODE_SERIALIZER 0x02

typedef struct SERDESPOC_SETTINGS_t
{
	uint8_t mode; // no poc, generated supply, serializer passthrough
	uint8_t rsvd[6];
	uint8_t voltage; // generated voltage
	uint16_t chksum; // checksum to protect settings structure (don't want corrupt voltage settings)
} SERDESPOC_SETTINGS;
#define SERDESPOC_SETTINGS_SIZE 10

enum
{
	SERDESGEN_MOD_ID_NONE = 0,
	SERDESGEN_MOD_ID_FPD3_2x2 = 1,
	SERDESGEN_MOD_ID_GMSL2_2x2 = 2,
	SERDESGEN_MOD_ID_GMSL1_4x4 = 3,
	SERDESGEN_MOD_ID_FPD3_TO_GMSL2_2x2 = 4,
	// new modules go above this line
	SERDESGEN_MOD_ID_UNKNOWN = -1,
};

#define SERDESGEN_SETTINGS_FLAG_TX_PATGEN_ENABLE 0x0001

typedef struct SERDESGEN_SETTINGS_t
{
	/* 
	 * bit0: enable pattern generator
	 */
	uint16_t flags;
	uint8_t rsvd1;
	uint8_t mod_id; // connected module passed back from device
	uint16_t tx_speed; // Mbps per lane, all tx ports
	uint16_t rx_speed; // Mbps per lane, all rx ports
	// reserved space for the future
	// maybe pattern generator settings
	uint8_t rsvd2[24];
} SERDESGEN_SETTINGS;
#define SERDESGEN_SETTINGS_SIZE 32

// clang-format off
#define RAD_REPORTING_SETTINGS_FLAG_TEMP_ENABLE               0x00000001
#define RAD_REPORTING_SETTINGS_FLAG_MIC2_GPS_ENABLE           0x00000002 // USB port 1
#define RAD_REPORTING_SETTINGS_FLAG_INT_GPS_ENABLE            0x00000004
#define RAD_REPORTING_SETTINGS_FLAG_MIC2_GPS_ENABLE2          0x00000008 // USB port 2
#define RAD_REPORTING_SETTINGS_FLAG_MISC1_DIN                 0x00000010
#define RAD_REPORTING_SETTINGS_FLAG_MISC2_DIN                 0x00000020
#define RAD_REPORTING_SETTINGS_FLAG_MISC1_PWMIN               0x00000040
#define RAD_REPORTING_SETTINGS_FLAG_MISC2_PWMIN               0x00000080
#define RAD_REPORTING_SETTINGS_FLAG_AIN1                      0x00000100
#define RAD_REPORTING_SETTINGS_FLAG_SERDES_ENABLE             0x00000200
#define RAD_REPORTING_SETTINGS_FLAG_FAN_SPEED_ENABLE          0x00000400
#define RAD_REPORTING_SETTINGS_FLAG_REPORT_ORIENTATION_ENABLE 0x00000800
// clang-format on

typedef struct RAD_REPORTING_SETTINGS_t
{
	uint32_t flags;
	uint16_t temp_interval_ms;
	uint16_t gps_interval_ms;
	uint16_t serdes_interval_ms;
	uint16_t io_interval_ms;
	uint16_t fan_speed_interval_ms;
	uint8_t rsvd[2];
} RAD_REPORTING_SETTINGS;
#define RAD_REPORTING_SETTINGS_SIZE 16

/* These are bit positions for misc_io_on_report_eventsin SFireSettings */
enum
{
	REPORT_ON_PERIODIC,
	REPORT_ON_MISC1,
	REPORT_ON_MISC2,
	REPORT_ON_MISC3,
	REPORT_ON_MISC4,
	REPORT_ON_MISC5,
	REPORT_ON_MISC6,
	REPORT_ON_LED1,
	REPORT_ON_LED2,
	REPORT_ON_KLINE,
	REPORT_ON_MISC3_AIN,
	REPORT_ON_MISC4_AIN,
	REPORT_ON_MISC5_AIN,
	REPORT_ON_MISC6_AIN,
	REPORT_ON_PWM_IN1, /* send PWM 0x101 on change */
	REPORT_ON_GPS, /* send GPS 0x110-0x116 on change */
};

typedef struct _SFireSettings
{
	CAN_SETTINGS can1;
	CAN_SETTINGS can2;
	CAN_SETTINGS can3;
	CAN_SETTINGS can4;

	SWCAN_SETTINGS swcan;
	CAN_SETTINGS lsftcan;

	LIN_SETTINGS lin1;
	LIN_SETTINGS lin2;
	LIN_SETTINGS lin3;
	LIN_SETTINGS lin4;

	uint16_t cgi_enable_reserved;
	uint16_t cgi_baud;
	uint16_t cgi_tx_ifs_bit_times;
	uint16_t cgi_rx_ifs_bit_times;
	uint16_t cgi_chksum_enable;

	uint16_t network_enables;
	uint16_t network_enabled_on_boot;

	uint32_t pwm_man_timeout;
	uint16_t pwr_man_enable;

	uint16_t misc_io_initial_ddr;
	uint16_t misc_io_initial_latch;

	uint16_t misc_io_analog_enable;
	uint16_t misc_io_report_period;
	uint16_t misc_io_on_report_events;
	uint16_t ain_sample_period;
	uint16_t ain_threshold;

	uint16_t iso15765_separation_time_offset;

	uint16_t iso9141_kwp_enable_reserved;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings;

	uint16_t perf_en;

	/* ISO9141: iso_parity 0 - no parity, 1 - event, 2 - odd; iso_msg_termination 0 - use inner frame time, 1 - GME CIM-SCL */

	uint16_t iso_parity;
	uint16_t iso_msg_termination;
	uint16_t iso_tester_pullup_enable;

	uint16_t network_enables_2;

	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_2;
	uint16_t iso_parity_2;
	uint16_t iso_msg_termination_2;

	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_3;
	uint16_t iso_parity_3;
	uint16_t iso_msg_termination_3;

	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_4;
	uint16_t iso_parity_4;
	uint16_t iso_msg_termination_4;

	uint16_t fast_init_network_enables_1;
	uint16_t fast_init_network_enables_2;

	UART_SETTINGS uart;
	UART_SETTINGS uart2;

	STextAPISettings text_api;

	SNeoMostGatewaySettings neoMostGateway;

#define VNETBITS_FEATURE_ANDROID_MSGS (1)
	/**
	 * Unfortuntely I haven't gone thru the trouble
	 * of splitting the FIRE VNET and FIRE settings
	 * structures. So until I can do so and reserve
	 * some time to test it, add a member that only
	 * VNET looks at for VNET features (like
	 * Android CoreMiniMsg pump).
	 * Defaults to zero.
	 * @see VNETBITS_FEATURE_ANDROID_MSGS
	 */
	uint16_t vnetBits;
} SFireSettings;
#define SFireSettings_SIZE 744

typedef struct _SFireVnetSettings
{
	CAN_SETTINGS can1;
	CAN_SETTINGS can2;
	CAN_SETTINGS can3;
	CAN_SETTINGS can4;

	SWCAN_SETTINGS swcan;
	CAN_SETTINGS lsftcan;

	LIN_SETTINGS lin1;
	LIN_SETTINGS lin2;
	LIN_SETTINGS lin3;
	LIN_SETTINGS lin4;

	uint16_t cgi_enable_reserved;
	uint16_t cgi_baud;
	uint16_t cgi_tx_ifs_bit_times;
	uint16_t cgi_rx_ifs_bit_times;
	uint16_t cgi_chksum_enable;

	uint16_t network_enables;
	uint16_t network_enabled_on_boot;

	uint32_t pwm_man_timeout;
	uint16_t pwr_man_enable; /* 0 - off, 1 - sleep enabled, 2- idle enabled (fast wakeup) */

	uint16_t misc_io_initial_ddr;
	uint16_t misc_io_initial_latch;
	uint16_t misc_io_analog_enable;
	uint16_t misc_io_report_period;
	uint16_t misc_io_on_report_events;
	uint16_t ain_sample_period;
	uint16_t ain_threshold;

	uint16_t iso15765_separation_time_offset;

	uint16_t iso9141_kwp_enable_reserved;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings;

	uint16_t perf_en;

	/* ISO9141: iso_parity 0 - no parity, 1 - event, 2 - odd; iso_msg_termination 0 - use inner frame time, 1 - GME CIM-SCL */

	uint16_t iso_parity;
	uint16_t iso_msg_termination;
	uint16_t iso_tester_pullup_enable;

	uint16_t network_enables_2;

	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_2;
	uint16_t iso_parity_2;
	uint16_t iso_msg_termination_2;

	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_3;
	uint16_t iso_parity_3;
	uint16_t iso_msg_termination_3;

	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_4;
	uint16_t iso_parity_4;
	uint16_t iso_msg_termination_4;

	uint16_t fast_init_network_enables_1;
	uint16_t fast_init_network_enables_2;

	UART_SETTINGS uart;
	UART_SETTINGS uart2;

	STextAPISettings text_api;

	SNeoMostGatewaySettings neoMostGateway;

#define VNETBITS_FEATURE_ANDROID_MSGS (1)
#define VNETBITS_FEATURE_DISABLE_USB_CHECK (2)
	/**
	 * VNET options bitfield.
	 * Defaults to zero.
	 * @see VNETBITS_FEATURE_ANDROID_MSGS
	 */
	uint16_t vnetBits;

	CAN_SETTINGS can5;
	CAN_SETTINGS can6;
	LIN_SETTINGS lin5;
	SWCAN_SETTINGS swcan2;
} SFireVnetSettings;
#define SFireVnetSettings_SIZE 792

typedef struct _SCyanSettings
{
	uint16_t perf_en;

	CAN_SETTINGS can1;
	CANFD_SETTINGS canfd1;
	CAN_SETTINGS can2;
	CANFD_SETTINGS canfd2;
	CAN_SETTINGS can3;
	CANFD_SETTINGS canfd3;
	CAN_SETTINGS can4;
	CANFD_SETTINGS canfd4;
	CAN_SETTINGS can5;
	CANFD_SETTINGS canfd5;
	CAN_SETTINGS can6;
	CANFD_SETTINGS canfd6;
	CAN_SETTINGS can7;
	CANFD_SETTINGS canfd7;
	CAN_SETTINGS can8;
	CANFD_SETTINGS canfd8;

	/* Native CAN are either LS1/LS2 or SW1/SW2 */
	SWCAN_SETTINGS swcan1;
	uint16_t network_enables;
	SWCAN_SETTINGS swcan2;
	uint16_t network_enables_2;

	CAN_SETTINGS lsftcan1;
	CAN_SETTINGS lsftcan2;

	LIN_SETTINGS lin1;
	uint16_t misc_io_initial_ddr;
	LIN_SETTINGS lin2;
	uint16_t misc_io_initial_latch;
	LIN_SETTINGS lin3;
	uint16_t misc_io_report_period;
	LIN_SETTINGS lin4;
	uint16_t misc_io_on_report_events;
	LIN_SETTINGS lin5;
	uint16_t misc_io_analog_enable;
	uint16_t ain_sample_period;
	uint16_t ain_threshold;

	uint32_t pwr_man_timeout;
	uint16_t pwr_man_enable;

	uint16_t network_enabled_on_boot;

	uint16_t iso15765_separation_time_offset;

	uint16_t iso_9141_kwp_enable_reserved;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_1;
	uint16_t iso_parity_1;

	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_2;
	uint16_t iso_parity_2;

	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_3;
	uint16_t iso_parity_3;

	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_4;
	uint16_t iso_parity_4;

	uint16_t iso_msg_termination_1;
	uint16_t iso_msg_termination_2;
	uint16_t iso_msg_termination_3;
	uint16_t iso_msg_termination_4;

	uint16_t idle_wakeup_network_enables_1;
	uint16_t idle_wakeup_network_enables_2;

	/* reserved for HSCAN6/7, LSFT2, etc.. */
	uint16_t network_enables_3;
	uint16_t idle_wakeup_network_enables_3;

	uint16_t can_switch_mode;
	STextAPISettings text_api;
	uint64_t termination_enables;
	LIN_SETTINGS lin6;
	ETHERNET_SETTINGS ethernet;
	uint16_t slaveVnetA;
	uint16_t slaveVnetB;
	struct
	{
		uint32_t disableUsbCheckOnBoot : 1;
		uint32_t enableLatencyTest : 1;
		uint32_t busMessagesToAndroid : 1;
		uint32_t enablePcEthernetComm : 1;
		uint32_t enableDefaultLogger : 1;
		uint32_t enableDefaultUpload : 1;
		uint32_t reserved : 26;
	} flags;
	uint16_t digitalIoThresholdTicks;
	uint16_t digitalIoThresholdEnable;
	TIMESYNC_ICSHARDWARE_SETTINGS timeSync;
	DISK_SETTINGS disk;
	ETHERNET_SETTINGS2 ethernet2; // supercedes ethernet settings
} SCyanSettings;
#define SCyanSettings_SIZE 936

typedef SCyanSettings SFire2Settings;

typedef struct _SVCAN3Settings
{
	CAN_SETTINGS can1;
	CAN_SETTINGS can2;

	uint16_t network_enables;
	uint16_t network_enabled_on_boot;

	uint16_t iso15765_separation_time_offset;

	uint16_t perf_en;

	uint16_t misc_io_initial_ddr;
	uint16_t misc_io_initial_latch;
	uint16_t misc_io_report_period;
	uint16_t misc_io_on_report_events;
} SVCAN3Settings;
#define SVCAN3Settings_SIZE 40

typedef struct _SVCAN4Settings
{
	uint16_t perf_en;
	CAN_SETTINGS can1;
	CANFD_SETTINGS canfd1;
	CAN_SETTINGS can2;
	CANFD_SETTINGS canfd2;
	CAN_SETTINGS can3;
	CANFD_SETTINGS canfd3;
	CAN_SETTINGS can4;
	CANFD_SETTINGS canfd4;
	uint16_t network_enables;
	uint16_t network_enables_2;
	LIN_SETTINGS lin1;
	uint16_t network_enabled_on_boot;
	int16_t iso15765_separation_time_offset;
	uint16_t iso_9141_kwp_enable_reserved;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_1;
	uint16_t iso_parity_1;
	uint16_t iso_msg_termination_1;
	uint16_t network_enables_3;
	STextAPISettings text_api;
	uint64_t termination_enables;
	ETHERNET_SETTINGS ethernet;
	struct
	{
		uint32_t enableLatencyTest : 1;
		uint32_t enablePcEthernetComm : 1;
		uint32_t reserved : 30;
	} flags;
	uint16_t pwr_man_enable;
	uint16_t pwr_man_timeout;
	ETHERNET_SETTINGS2 ethernet2;
} SVCAN4Settings;
#define SVCAN4Settings_SIZE 342

typedef struct _SECUSettings
{
	/* ECU ID used in CAN communications.
	 * TX ID = ECU ID with bit28 cleared,
	 * RX ID = ECUID with bit28 set,
	 * ECU ID = 0 implies ECU ID = serial no with bit 27 set\
	*/
	uint32_t ecu_id;

	uint16_t selected_network; // not supported yet - default to HSCAN

	CAN_SETTINGS can1;
	CAN_SETTINGS can2;

	LIN_SETTINGS lin1;
	LIN_SETTINGS lin2;

	uint16_t iso15765_separation_time_offset;

	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings;
	uint16_t iso_parity;
	uint16_t iso_msg_termination;

	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_2;
	uint16_t iso_parity_2;
	uint16_t iso_msg_termination_2;

	uint16_t network_enables;
	uint16_t network_enables_2;
	uint16_t network_enabled_on_boot;

	uint32_t pwr_man_timeout;
	uint16_t pwr_man_enable;

	uint16_t misc_io_initial_ddr;
	uint16_t misc_io_initial_latch;
	uint16_t misc_io_analog_enable;
	uint16_t misc_io_report_period;
	uint16_t misc_io_on_report_events;
	uint16_t ain_sample_period;
	uint16_t ain_threshold;

	SWCAN_SETTINGS swcan;
	SWCAN_SETTINGS swcan2;
	CAN_SETTINGS lsftcan;
	CAN_SETTINGS lsftcan2;

	UART_SETTINGS uart;
	UART_SETTINGS uart2;

	STextAPISettings text_api;
} SECUSettings;
#define SECUSettings_SIZE 470

typedef struct _SPendantSettings
{
	/* see SECUSettings */
	uint32_t ecu_id;

	uint16_t selected_network; /* not supported yet - default to HSCAN */

	CAN_SETTINGS can1;
	CAN_SETTINGS can2;

	LIN_SETTINGS lin1;
	LIN_SETTINGS lin2;

	uint16_t iso15765_separation_time_offset;

	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings;
	uint16_t iso_parity;
	uint16_t iso_msg_termination;

	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_2;
	uint16_t iso_parity_2;
	uint16_t iso_msg_termination_2;

	uint16_t network_enables;
	uint16_t network_enables_2;
	uint16_t network_enabled_on_boot;

	uint32_t pwr_man_timeout;
	uint16_t pwr_man_enable;

	uint16_t misc_io_initial_ddr;
	uint16_t misc_io_initial_latch;
	uint16_t misc_io_analog_enable;
	uint16_t misc_io_report_period;
	uint16_t misc_io_on_report_events;
	uint16_t ain_sample_period;
	uint16_t ain_threshold;

	SWCAN_SETTINGS swcan;
	SWCAN_SETTINGS swcan2;
	CAN_SETTINGS lsftcan;
	CAN_SETTINGS lsftcan2;

	UART_SETTINGS uart;
	UART_SETTINGS uart2;

	STextAPISettings text_api;
} SPendantSettings;
#define SPendantSettings_SIZE 470

/* GPTP portEnable options */
enum eGPTPPort
{
	ePortDisabled = 0,
	ePortOpEth1 = 1,
	ePortOpEth2 = 2,
	ePortOpEth3 = 3,
	ePortOpEth4 = 4,
	ePortOpEth5 = 5,
	ePortOpEth6 = 6,
	ePortOpEth7 = 7,
	ePortOpEth8 = 8,
	ePortOpEth9 = 9,
	ePortOpEth10 = 10,
	ePortOpEth11 = 11,
	ePortOpEth12 = 12,

	ePortStdEth1 = 13,
	ePortStdEth2 = 14,
	ePortStdEth3 = 15,

	ePortOpEth13 = 16,
	ePortOpEth14 = 17,
	ePortOpEth15 = 18,
	ePortOpEth16 = 19,
};

/* GPTP port role options */
enum eGPTPRole
{
	eRoleDisabled = 0,
	eRolePassive = 1,
	eRoleMaster = 2,
	eRoleSlave = 3,
};

enum eGPTPProfile
{
	eGPTP_PROFILE_STANDARD = 0,
	eGPTP_PROFILE_AUTOMOTIVE = 1,
};

typedef struct _SRADGalaxySettings
{
	uint16_t perf_en;

	OP_ETH_GENERAL_SETTINGS opEthGen;
	OP_ETH_SETTINGS opEth1;
	OP_ETH_SETTINGS opEth2;
	OP_ETH_SETTINGS opEth3;
	OP_ETH_SETTINGS opEth4;
	OP_ETH_SETTINGS opEth5;
	OP_ETH_SETTINGS opEth6;
	OP_ETH_SETTINGS opEth7;
	OP_ETH_SETTINGS opEth8;
	OP_ETH_SETTINGS opEth9;
	OP_ETH_SETTINGS opEth10;
	OP_ETH_SETTINGS opEth11;
	OP_ETH_SETTINGS opEth12;

	CAN_SETTINGS can1;
	CANFD_SETTINGS canfd1;
	CAN_SETTINGS can2;
	CANFD_SETTINGS canfd2;
	CAN_SETTINGS can3;
	CANFD_SETTINGS canfd3;
	CAN_SETTINGS can4;
	CANFD_SETTINGS canfd4;
	CAN_SETTINGS can5;
	CANFD_SETTINGS canfd5;
	CAN_SETTINGS can6;
	CANFD_SETTINGS canfd6;
	CAN_SETTINGS can7;
	CANFD_SETTINGS canfd7;
	CAN_SETTINGS can8;
	CANFD_SETTINGS canfd8;

	/* Native CAN are either LS1/LS2 or SW1/SW2 */
	SWCAN_SETTINGS swcan1;
	uint16_t network_enables;
	SWCAN_SETTINGS swcan2;
	uint16_t network_enables_2;

	LIN_SETTINGS lin1;
	uint16_t misc_io_initial_ddr;
	uint16_t misc_io_initial_latch;
	uint16_t misc_io_report_period;
	uint16_t misc_io_on_report_events;
	uint16_t misc_io_analog_enable;
	uint16_t ain_sample_period;
	uint16_t ain_threshold;

	uint32_t pwr_man_timeout;
	uint16_t pwr_man_enable;

	uint16_t network_enabled_on_boot;

	uint16_t iso15765_separation_time_offset;

	uint16_t iso_9141_kwp_enable_reserved;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_1;
	uint16_t iso_parity_1;

	uint16_t iso_msg_termination_1;

	uint16_t idle_wakeup_network_enables_1;
	uint16_t idle_wakeup_network_enables_2;

	uint16_t network_enables_3;
	uint16_t idle_wakeup_network_enables_3;

	uint16_t can_switch_mode;
	STextAPISettings text_api;
	TIMESYNC_ICSHARDWARE_SETTINGS timeSyncSettings;
	uint16_t hwComLatencyTestEn;
	RAD_REPORTING_SETTINGS reporting;
	DISK_SETTINGS disk;
	LOGGER_SETTINGS logger;

	ETHERNET_SETTINGS2 ethernet1; // DAQ port on label, NETID_ETHERNET
	ETHERNET_SETTINGS2 ethernet2; // LAN port on label, NETID_ETHERNET2
	uint16_t network_enables_4;

	RAD_GPTP_SETTINGS gPTP;
	uint64_t network_enables_5;
} SRADGalaxySettings;
#define SRADGalaxySettings_SIZE 776

typedef struct _SRADStar2Settings
{
	uint16_t perf_en;

	OP_ETH_GENERAL_SETTINGS opEthGen;
	OP_ETH_SETTINGS opEth1;
	OP_ETH_SETTINGS opEth2;

	CAN_SETTINGS can1;
	CANFD_SETTINGS canfd1;
	CAN_SETTINGS can2;
	CANFD_SETTINGS canfd2;

	uint16_t network_enables;
	uint16_t network_enables_2;

	LIN_SETTINGS lin1;
	uint16_t misc_io_initial_ddr;
	uint16_t misc_io_initial_latch;
	uint16_t misc_io_report_period;
	uint16_t misc_io_on_report_events;
	uint16_t misc_io_analog_enable;
	uint16_t ain_sample_period;
	uint16_t ain_threshold;

	uint32_t pwr_man_timeout;
	uint16_t pwr_man_enable;

	uint16_t network_enabled_on_boot;

	uint16_t iso15765_separation_time_offset;

	uint16_t iso_9141_kwp_enable_reserved;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_1;
	uint16_t iso_parity_1;

	uint16_t iso_msg_termination_1;

	uint16_t idle_wakeup_network_enables_1;
	uint16_t idle_wakeup_network_enables_2;

	uint16_t network_enables_3;
	uint16_t idle_wakeup_network_enables_3;

	uint16_t can_switch_mode;
	STextAPISettings text_api;
	uint16_t pc_com_mode;
	TIMESYNC_ICSHARDWARE_SETTINGS timeSyncSettings;
	struct
	{
		uint16_t hwComLatencyTestEn : 1;
		uint16_t disableUsbCheckOnBoot : 1;
		uint16_t reserved : 14;
	} flags;
	RAD_REPORTING_SETTINGS reporting;
	ETHERNET_SETTINGS2 ethernet;

	RAD_GPTP_SETTINGS gPTP;
	uint64_t network_enables_5;
} SRADStar2Settings;

#define SRADStar2Settings_SIZE 422

typedef enum
{
	tdmModeTDM2 = 0,
	tdmModeTDM4,
	tdmModeTDM8,
	tdmModeTDM12,
	tdmModeTDM16,
	tdmModeTDM20,
	tdmModeTDM24,
	tdmModeTDM32,
} A2BTDMMode;

typedef enum
{
	a2bNodeTypeMonitor = 0,
	a2bNodeTypeMaster,
	a2bNodeTypeSlave,
} A2BNodeType;

#define A2B_SETTINGS_FLAG_16BIT 0x01

typedef struct
{
	uint8_t tdmMode; // see enum A2BTDMMode
	uint8_t upstreamChannelOffset;
	uint8_t downstreamChannelOffset;
	uint8_t nodeType; // see enum A2BNodeType
	/* 
	 * bit0: 16-bit channel width
	 */
	uint8_t flags;
	uint8_t reserved[15];
} A2BMonitorSettings;
#define A2BMonitorSettings_SIZE 20

typedef struct _SRADA2BSettings
{
	uint16_t perf_en;
	struct
	{
		uint16_t hwComLatencyTestEn : 1;
		uint16_t disableUsbCheckOnBoot : 1;
		uint16_t : 14;
	} flags;
	uint16_t network_enabled_on_boot;
	CAN_SETTINGS can1;
	CANFD_SETTINGS canfd1;
	CAN_SETTINGS can2;
	CANFD_SETTINGS canfd2;
	LIN_SETTINGS lin1;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_1;
	uint16_t iso_parity_1;
	uint16_t iso_msg_termination_1;
	uint64_t network_enables;		
	uint64_t termination_enables;
	TIMESYNC_ICSHARDWARE_SETTINGS timeSyncSettings;
	RAD_REPORTING_SETTINGS reporting;
	DISK_SETTINGS disk;
	LOGGER_SETTINGS logger;
	int16_t iso15765_separation_time_offset;
	A2BMonitorSettings a2b_monitor;
	A2BMonitorSettings a2b_node;
	uint32_t pwr_man_timeout;
	uint16_t pwr_man_enable;
	ETHERNET_SETTINGS2 ethernet;
	RAD_GPTP_SETTINGS gPTP;
	uint64_t network_enables_5;
	CMP_GLOBAL_DATA cmp_global_data;
	CMP_NETWORK_DATA cmp_stream_data[CMP_STREAMS_A2B];
} SRADA2BSettings;

#define SRADA2BSettings_SIZE 416

typedef struct _SRADMoon2Settings
{
	uint16_t perf_en;

	OP_ETH_GENERAL_SETTINGS opEthGen;
	OP_ETH_SETTINGS opEth1;

	uint16_t network_enables;
	uint16_t network_enables_2;
	uint16_t network_enabled_on_boot;
	uint16_t network_enables_3;

	STextAPISettings text_api;

	uint16_t pc_com_mode;
	TIMESYNC_ICSHARDWARE_SETTINGS timeSyncSettings;
	uint16_t hwComLatencyTestEn;

	RAD_GPTP_SETTINGS gPTP;
	uint64_t network_enables_5;
} SRADMoon2Settings;

#define SRADMoon2Settings_SIZE 170

typedef struct _SRADMoon3Settings
{
	uint16_t perf_en; // 2

	ETHERNET10G_SETTINGS autoEth10g; // 24
	ETHERNET10G_SETTINGS eth10g; // 24

	uint16_t network_enables; // 2
	uint16_t network_enables_2; // 2
	uint16_t network_enabled_on_boot; // 2
	uint16_t network_enables_3; // 2

	struct
	{
		uint16_t enableLatencyTest : 1;
		uint16_t reserved : 15;
	} flags; // 2
	uint64_t network_enables_5;
} SRADMoon3Settings;

#define SRADMoon3Settings_SIZE 68

typedef struct _SRADGeminiSettings
{
	uint16_t perf_en; // 2

	ETHERNET_SETTINGS2 ethernet1; // 16
	ETHERNET_SETTINGS2 ethernet2; // 16
	ETHERNET_SETTINGS2 autoEthernet1; // 16
	ETHERNET_SETTINGS2 autoEthernet2; // 16

	uint16_t network_enabled_on_boot; // 2
	uint16_t network_enables; // 2
	uint16_t network_enables_2; // 2
	uint16_t network_enables_3; // 2
	uint16_t network_enables_4; // 2
	uint64_t network_enables_5; // 8

	struct
	{
		uint16_t enableLatencyTest : 1;
		uint16_t reserved : 15;
	} flags; // 2
} SRADGeminiSettings;

#define SRADGeminiSettings_SIZE 86

typedef struct _SRADGigastarSettings
{
	uint32_t ecu_id;

	uint16_t perf_en;

	CAN_SETTINGS can1;
	CANFD_SETTINGS canfd1;
	CAN_SETTINGS can2;
	CANFD_SETTINGS canfd2;
	CAN_SETTINGS can3;
	CANFD_SETTINGS canfd3;
	CAN_SETTINGS can4;
	CANFD_SETTINGS canfd4;
	CAN_SETTINGS can5;
	CANFD_SETTINGS canfd5;
	CAN_SETTINGS can6;
	CANFD_SETTINGS canfd6;

	uint16_t network_enables;
	uint16_t network_enables_2;

	uint32_t pwr_man_timeout;
	uint16_t pwr_man_enable;

	uint16_t network_enabled_on_boot;

	uint16_t iso15765_separation_time_offset;

	uint16_t iso_9141_kwp_enable_reserved;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_1;
	uint16_t iso_parity_1;

	uint16_t iso_msg_termination_1;

	uint16_t idle_wakeup_network_enables_1;
	uint16_t idle_wakeup_network_enables_2;

	uint16_t network_enables_3;
	uint16_t idle_wakeup_network_enables_3;

	STextAPISettings text_api;
	uint64_t termination_enables;

	DISK_SETTINGS disk;

	TIMESYNC_ICSHARDWARE_SETTINGS timeSyncSettings;
	struct
	{
		uint16_t hwComLatencyTestEn : 1;
		uint16_t disableUsbCheckOnBoot : 1;
		uint16_t reserved : 14;
	} flags;
	ETHERNET_SETTINGS2 ethernet1;
	ETHERNET_SETTINGS2 ethernet2;

	LIN_SETTINGS lin1;

	OP_ETH_GENERAL_SETTINGS opEthGen;
	OP_ETH_SETTINGS opEth1;
	OP_ETH_SETTINGS opEth2;

	SERDESCAM_SETTINGS serdescam1;
	SERDESPOC_SETTINGS serdespoc;
	LOGGER_SETTINGS logger;
	SERDESCAM_SETTINGS serdescam2;
	SERDESCAM_SETTINGS serdescam3;
	SERDESCAM_SETTINGS serdescam4;
	RAD_REPORTING_SETTINGS reporting;
	uint16_t network_enables_4;
	SERDESGEN_SETTINGS serdesgen;

	RAD_GPTP_SETTINGS gPTP;
	uint64_t network_enables_5;
	// SFP T1S
	ETHERNET10T1S_SETTINGS sfp_t1s_1;
	ETHERNET10T1S_SETTINGS_EXT sfp_t1s_ext_1;
	ETHERNET10T1S_SETTINGS sfp_t1s_2;
	ETHERNET10T1S_SETTINGS_EXT sfp_t1s_ext_2;

	CMP_GLOBAL_DATA cmp_global_data;
	CMP_NETWORK_DATA cmp_stream_data[CMP_STREAMS_GIGASTAR];
	// SFP T1L
	ETHERNET10T1L_SETTINGS sfp_t1l_1;
	ETHERNET10T1L_SETTINGS sfp_t1l_2;
} SRADGigastarSettings;

#define SRADGigastarSettings_SIZE 1026

typedef struct _SRADGalaxy2Settings
{
	uint32_t ecu_id;
	uint16_t perf_en;

	/* CAN */
	CAN_SETTINGS can1;
	CANFD_SETTINGS canfd1;
	CAN_SETTINGS can2;
	CANFD_SETTINGS canfd2;
	CAN_SETTINGS can3;
	CANFD_SETTINGS canfd3;
	CAN_SETTINGS can4;
	CANFD_SETTINGS canfd4;
	CAN_SETTINGS can5;
	CANFD_SETTINGS canfd5;
	CAN_SETTINGS can6;
	CANFD_SETTINGS canfd6;
	CAN_SETTINGS can7;
	CANFD_SETTINGS canfd7;
	CAN_SETTINGS can8;
	CANFD_SETTINGS canfd8;

	// SWCAN_SETTINGS swcan1;	G2 does not have SWCAN.
	uint16_t network_enables;
	// SWCAN_SETTINGS swcan2;	G2 does not have SWCAN.
	uint16_t network_enables_2;

	uint32_t pwr_man_timeout;
	uint16_t pwr_man_enable;

	uint16_t network_enabled_on_boot;

	/* ISO15765-2 Transport Layer */
	uint16_t iso15765_separation_time_offset;

	/* ISO9141 - Keyword */
	uint16_t iso_9141_kwp_enable_reserved;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_1;
	uint16_t iso_parity_1;
	uint16_t iso_msg_termination_1;

	uint16_t idle_wakeup_network_enables_1;
	uint16_t idle_wakeup_network_enables_2;

	/* reserved for T1 networks such as BR1, BR2, etc.. */
	uint16_t network_enables_3;
	uint16_t idle_wakeup_network_enables_3;

	STextAPISettings text_api;

	uint64_t termination_enables; // New feature unlike Galaxy.

	TIMESYNC_ICSHARDWARE_SETTINGS timeSyncSettings;
	struct
	{
		uint16_t hwComLatencyTestEn : 1;
		uint16_t hwFramePackerEn : 1;
		uint16_t reserved : 14;
	} flags;

	LIN_SETTINGS lin1;

	OP_ETH_GENERAL_SETTINGS opEthGen;
	OP_ETH_SETTINGS opEth1;
	OP_ETH_SETTINGS opEth2;
	OP_ETH_SETTINGS opEth3;
	OP_ETH_SETTINGS opEth4;
	OP_ETH_SETTINGS opEth5;
	OP_ETH_SETTINGS opEth6;
	OP_ETH_SETTINGS opEth7;
	OP_ETH_SETTINGS opEth8;
	OP_ETH_SETTINGS opEth9;
	OP_ETH_SETTINGS opEth10;
	OP_ETH_SETTINGS opEth11;
	OP_ETH_SETTINGS opEth12;
	OP_ETH_SETTINGS opEth13;
	OP_ETH_SETTINGS opEth14;
	OP_ETH_SETTINGS opEth15;
	OP_ETH_SETTINGS opEth16;

	ETHERNET10G_SETTINGS ethernet10g_3;
	ETHERNET10G_SETTINGS ethernet10g;
	ETHERNET10G_SETTINGS ethernet10g_2;

	uint16_t network_enables_4;
	RAD_REPORTING_SETTINGS reporting;
	RAD_GPTP_SETTINGS gPTP;
	uint64_t network_enables_5;

	LIN_SETTINGS lin2;
	uint16_t iso_9141_kwp_enable_reserved_2;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_2;
	uint16_t iso_parity_2;
	uint16_t iso_msg_termination_2;

} SRADGalaxy2Settings;
#define SRADGalaxy2Settings_SIZE 960

typedef struct _SVividCANSettings
{
	uint32_t ecu_id;

	CAN_SETTINGS can1; // 12 bytes
	SWCAN_SETTINGS swcan1; // 14 bytes
	CAN_SETTINGS lsftcan1; // 12 bytes

	uint16_t network_enables;
	uint16_t network_enabled_on_boot;

	uint16_t iso15765_separation_time_offset;

	uint16_t perf_en;

	uint32_t pwr_man_timeout;
	uint16_t pwr_man_enable;

	uint16_t can_switch_mode;
	uint16_t termination_enables;

	struct
	{
		uint32_t disableUsbCheckOnBoot : 1;
		uint32_t enableLatencyTest : 1;
		uint32_t reserved : 30;
	} flags;
} SVividCANSettings;
#define SVividCANSettings_SIZE 64

typedef struct _VCAN412Settings
{
	/* Performance Test */
	uint16_t perf_en;

	CAN_SETTINGS can1;
	CANFD_SETTINGS canfd1;
	CAN_SETTINGS can2;
	CANFD_SETTINGS canfd2;

	uint64_t network_enables;
	uint64_t termination_enables;

	uint32_t pwr_man_timeout;
	uint16_t pwr_man_enable;

	uint16_t network_enabled_on_boot;

	/* ISO15765-2 Transport Layer */
	int16_t iso15765_separation_time_offset;

	STextAPISettings text_api;
	struct
	{
		uint32_t disableUsbCheckOnBoot : 1;
		uint32_t enableLatencyTest : 1;
		uint32_t reserved : 30;
	} flags;
} VCAN412Settings, SVCAN412Settings;
#define VCAN412Settings_SIZE 148
#define SVCAN412Settings_SIZE VCAN412Settings_SIZE

#define gPTP_ROLE_DISABLED 0
#define gPTP_ROLE_PASSIVE 1
#define gPTP_ROLE_MASTER 2
#define gPTP_ROLE_SLAVE 3

#define gPTP_PROFILE_STANDARD 0
#define gPTP_PROFILE_AUTOMOTIVE 1

#define gPTP_PORT_DISABLED 0
#define gPTP_PORT_ENABLED 1

typedef union
{
	uint32_t word;
	struct
	{
		unsigned can_sleep_command_id : 29;
		unsigned can_sleep_command_isExtended : 1;
		unsigned reserved : 2;
	} id;
} SCANSleepID;
typedef struct
{
	CAN_SETTINGS can1;
	CANFD_SETTINGS canfd1;
	uint64_t network_enables;
	uint64_t termination_enables;
	uint32_t pwr_man_timeout;
	uint16_t pwr_man_enable;
	uint16_t network_enabled_on_boot;
	int16_t iso15765_separation_time_offset;
	uint32_t ecu_id;
	SCANSleepID sleep_id;
} CANHubSettings, SCANHubSettings;
#define CANHubSettings_SIZE 56

typedef struct _SFlexVnetzSettings
{
	uint16_t perf_en;
	uint16_t network_enabled_on_boot;
	uint16_t misc_io_on_report_events;
	uint16_t pwr_man_enable;
	int16_t iso15765_separation_time_offset;
	uint16_t flex_mode;
	uint16_t flex_termination;
	uint16_t slaveVnetA;
	uint64_t termination_enables;
	union
	{
		uint64_t word;
		struct
		{
			uint16_t network_enables;
			uint16_t network_enables_2;
			uint16_t network_enables_3;
		};
	} network_enables;
	uint32_t pwr_man_timeout;
	uint16_t slaveVnetB;
	CAN_SETTINGS can1;
	CANFD_SETTINGS canfd1;
	CAN_SETTINGS can2;
	CANFD_SETTINGS canfd2;
	CAN_SETTINGS can3;
	CANFD_SETTINGS canfd3;
	CAN_SETTINGS can4;
	CANFD_SETTINGS canfd4;
	CAN_SETTINGS can5;
	CANFD_SETTINGS canfd5;
	CAN_SETTINGS can6;
	CANFD_SETTINGS canfd6;
	CAN_SETTINGS can7;
	CANFD_SETTINGS canfd7;
	ETHERNET_SETTINGS ethernet;
	TIMESYNC_ICSHARDWARE_SETTINGS timeSync;
	STextAPISettings text_api;
	struct
	{
		uint32_t disableUsbCheckOnBoot : 1;
		uint32_t enableLatencyTest : 1;
		uint32_t busMessagesToAndroid : 1;
		uint32_t enablePcEthernetComm : 1;
		uint32_t enableDefaultLogger : 1;
		uint32_t enableDefaultUpload : 1;
		uint32_t reserved : 26;
	} flags;
	DISK_SETTINGS disk;
	ETHERNET_SETTINGS2 ethernet2;
} SFlexVnetzSettings;
#define SFlexVnetzSettings_Size (310)

typedef enum _flexVnetMode
{
	flexVnetModeDisabled,
	flexVnetModeOneSingle,
	flexVnetModeOneDual,
	flexVnetModeTwoSingle,
	flexVnetModeColdStart
} flexVnetMode;

typedef struct _NeoECU12Settings
{
	uint32_t ecu_id;
	CAN_SETTINGS can1;
	CANFD_SETTINGS canfd1;
	CAN_SETTINGS can2;
	CANFD_SETTINGS canfd2;
	SWCAN_SETTINGS swcan1;
	SWCAN_SETTINGS swcan2;
	CAN_SETTINGS lsftcan1;
	CAN_SETTINGS lsftcan2;
	LIN_SETTINGS lin1;

	uint64_t network_enables;
	uint16_t network_enabled_on_boot;

	uint64_t termination_enables;
	uint16_t can_switch_mode;

	/* ISO9141 - Keyword */
	uint16_t iso_9141_kwp_enable_reserved;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings;
	uint16_t iso_parity;
	uint16_t iso_msg_termination;

	uint32_t pwr_man_timeout;
	uint16_t pwr_man_enable;
	uint16_t perf_en;
	uint16_t misc_io_initial_ddr;
	uint16_t misc_io_initial_latch;
	uint16_t misc_io_analog_enable;
	uint16_t misc_io_report_period;
	uint16_t misc_io_on_report_events;
	uint16_t ain_sample_period;
	uint16_t ain_threshold;
	int16_t iso15765_separation_time_offset;
	STextAPISettings text_api;
	struct
	{
		uint32_t disableUsbCheckOnBoot : 1;
		uint32_t enableLatencyTest : 1;
		uint32_t reserved : 30;
	} flags;
	uint32_t reserved_field[2]; //#3166 reserved field for downgrade support
} SNeoECU12Settings;
#define SNeoECU12Settings_SIZE 358

typedef struct _VCAN4IndSettings
{
	CAN_SETTINGS can1;
	CANFD_SETTINGS canfd1;
	CAN_SETTINGS can2;
	CANFD_SETTINGS canfd2;
	ETHERNET_SETTINGS ethernet;
	LIN_SETTINGS lin1;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings;
	uint16_t iso_parity;
	uint16_t iso_msg_termination;

	uint32_t pwr_man_timeout;
	uint16_t pwr_man_enable;
	uint16_t perf_en;
	int16_t iso15765_separation_time_offset;
	uint16_t network_enabled_on_boot;

	union
	{
		uint64_t word;
		struct
		{
			uint16_t network_enables;
			uint16_t network_enables_2;
			uint16_t network_enables_3;
		};
	} network_enables;
	uint64_t termination_enables;
	struct
	{
		uint32_t disableUsbCheckOnBoot : 1;
		uint32_t enableLatencyTest : 1;
		uint32_t busMessagesToAndroid : 1;
		uint32_t enablePcEthernetComm : 1;
		uint32_t reserved : 28;
	} flags;
	ETHERNET_SETTINGS2 ethernet2;
} VCAN4IndSettings, SVCAN4IndSettings;
#define VCAN4IndSettings_SIZE (228)

typedef struct _SOBD2LCSettings
{
	/* Performance Test */
	uint16_t perf_en;
	CAN_SETTINGS can1;
	CANFD_SETTINGS canfd1;
	CAN_SETTINGS can2;
	CANFD_SETTINGS canfd2;
	CAN_SETTINGS can3;
	CANFD_SETTINGS canfd3;
	CAN_SETTINGS can4;
	CANFD_SETTINGS canfd4;
	SWCAN_SETTINGS swcan1;
	LIN_SETTINGS lin1;
	/* ISO9141 - Keyword */
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings;
	uint16_t iso_parity;
	uint16_t iso_msg_termination;
	union
	{
		uint64_t word;
		struct
		{
			uint16_t network_enables;
			uint16_t network_enables_2;
			uint16_t network_enables_3;
		};
	} network_enables;
	uint32_t pwr_man_timeout;
	uint16_t pwr_man_enable;
	uint16_t network_enabled_on_boot;
	/* ISO15765-2 Transport Layer */
	int16_t iso15765_separation_time_offset;
	STextAPISettings text_api;
	struct
	{
		uint32_t disableUsbCheckOnBoot : 1;
		uint32_t enableLatencyTest : 1;
		uint32_t busMessagesToAndroid : 1;
		uint32_t enablePcEthernetComm : 1;
		uint32_t enableDefaultLogger : 1;
		uint32_t enableDefaultUpload : 1;
		uint32_t reserved : 26;
	} flags;
	uint16_t can_switch_mode;
	uint16_t misc_io_on_report_events;
	DISK_SETTINGS disk;
	ETHERNET_SETTINGS ethernet;
	ETHERNET_SETTINGS2 ethernet2; // supercedes ethernet settings
	uint16_t iso_tester_pullup_enable;
} OBD2LCSettings, SOBD2LCSettings;
#define OBD2LCSettings_SIZE 370

#define RADJUPITER_NUM_PORTS 8

typedef struct SJupiterPtpParams_s
{
	uint32_t neighborPropDelay; //ns
	int8_t initLogPDelayReqInterval; // log2ms
	int8_t initLogSyncInterval; // log2ms
	int8_t operationLogPDelayReqInterval; // log2ms
	int8_t operationLogSyncInterval; // log2ms
	uint8_t gPTPportRole[RADJUPITER_NUM_PORTS]; // the 6th port is used for SAM
} JupiterPtpParams_t; //16

typedef struct _SRADJupiterSwitchSettings
{
	uint8_t phyMode[RADJUPITER_NUM_PORTS]; //8
	uint8_t enablePhy[RADJUPITER_NUM_PORTS]; //8
	uint8_t port7Select; //1
	uint8_t port8Select; //1
	uint8_t port8Speed;
	uint8_t port8Legacy;
	uint8_t spoofMacFlag;
	uint8_t spoofedMac[6];
	uint8_t pad;
	JupiterPtpParams_t ptpParams_unused; //16
} SRADJupiterSwitchSettings; //44

typedef struct _SRADJupiterSettings
{
	/* Performance Test */
	uint16_t perf_en; //2

	CAN_SETTINGS can1; //12
	CANFD_SETTINGS canfd1; //10
	CAN_SETTINGS can2; //12
	CANFD_SETTINGS canfd2; //10
	LIN_SETTINGS lin1; //10

	uint16_t network_enables; //2
	uint16_t network_enables_2; //2
	uint16_t network_enables_3; //2
	uint64_t termination_enables; //8
	uint16_t misc_io_analog_enable; //2

	uint32_t pwr_man_timeout; //4
	uint16_t pwr_man_enable; //2

	uint16_t network_enabled_on_boot; //2

	/* ISO15765-2 Transport Layer */
	int16_t iso15765_separation_time_offset; //2
	uint16_t iso9141_kwp_enable_reserved; //2
	uint16_t iso_tester_pullup_enable; //2
	uint16_t iso_parity; //2
	uint16_t iso_msg_termination; //2
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings; //114
	ETHERNET_SETTINGS ethernet; //8

	STextAPISettings text_api; //72

	struct
	{
		uint32_t disableUsbCheckOnBoot : 1;
		uint32_t enableLatencyTest : 1;
		uint32_t enablePcEthernetComm : 1;
		uint32_t reserved : 29;
	} flags; //4

	SRADJupiterSwitchSettings switchSettings; //44
	ETHERNET_SETTINGS2 ethernet2;
} SRADJupiterSettings; //348

#define SRADJupiterSettings_SIZE 348

#define LINUX_BOOT_ALLOWED (1)

#define WIFI_ANTENNA_INTERNAL (0)
#define WIFI_ANTENNA_EXTERNAL (1)

#define LINUX_CONFIG_PORT_NONE (0)
#define LINUX_CONFIG_PORT_ETH_01 (1)
#define LINUX_CONFIG_PORT_ETH_02 (2)
typedef struct
{
	uint8_t allowBoot; // 0 - disable booting Linux, 1 - enable booting Linux, Others - Disable booting linux
	uint8_t useExternalWifiAntenna; // 0 for internal, 1 for external, Others - Internal
	uint8_t
		ethConfigurationPort; // 0 - both ports used by logger, 1 - ETH 01 for Linux Configuration, 2 - ETH 02 for Linux Configuration, Others - both ports used by logger
	uint8_t reserved[5];
} Fire3LinuxSettings;

enum
{
	NETWORK_TIMESYNC_OFF,
	NETWORK_TIMESYNC_AUTO,
	NETWORK_TIMESYNC_NTP_ONLY,
	NETWORK_TIMESYNC_GPS_ONLY
};

typedef struct _SRed2Settings
{
	uint16_t perf_en;
	uint16_t network_enabled_on_boot;
	uint16_t misc_io_on_report_events;
	uint16_t pwr_man_enable;
	int16_t iso15765_separation_time_offset;
	uint16_t slaveVnetA;
	uint32_t reserved;
	uint64_t termination_enables;
	union
	{
		uint64_t word;
		struct
		{
			uint16_t network_enables;
			uint16_t network_enables_2;
			uint16_t network_enables_3;
			uint16_t network_enables_4;
		};
	} network_enables;
	uint32_t pwr_man_timeout;
	CAN_SETTINGS can1;
	CANFD_SETTINGS canfd1;
	CAN_SETTINGS can2;
	CANFD_SETTINGS canfd2;
	CAN_SETTINGS can3;
	CANFD_SETTINGS canfd3;
	CAN_SETTINGS can4;
	CANFD_SETTINGS canfd4;
	CAN_SETTINGS can5;
	CANFD_SETTINGS canfd5;
	CAN_SETTINGS can6;
	CANFD_SETTINGS canfd6;
	CAN_SETTINGS can7;
	CANFD_SETTINGS canfd7;
	CAN_SETTINGS can8;
	CANFD_SETTINGS canfd8;
	LIN_SETTINGS lin1;
	LIN_SETTINGS lin2;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_1;
	uint16_t iso_parity_1;
	uint16_t iso_msg_termination_1;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_2;
	uint16_t iso_parity_2;
	uint16_t iso_msg_termination_2;
	ETHERNET_SETTINGS ethernet_1;
	TIMESYNC_ICSHARDWARE_SETTINGS timeSync;
	STextAPISettings text_api;
	struct
	{
		uint32_t disableUsbCheckOnBoot : 1;
		uint32_t enableLatencyTest : 1;
		uint32_t busMessagesToAndroid : 1;
		uint32_t enablePcEthernetComm : 1;
		uint32_t enableDefaultLogger : 1;
		uint32_t enableDefaultUpload : 1;
		uint32_t reserved : 26;
	} flags;
	DISK_SETTINGS disk;
	uint16_t misc_io_report_period;
	uint16_t ain_threshold;
	uint16_t misc_io_analog_enable;
	uint16_t digitalIoThresholdTicks;
	uint16_t digitalIoThresholdEnable;
	uint16_t misc_io_initial_ddr;
	uint16_t misc_io_initial_latch;
	ETHERNET_SETTINGS2 ethernet2_1;
	ETHERNET_SETTINGS ethernet_2;
	ETHERNET_SETTINGS2 ethernet2_2;
	Fire3LinuxSettings os_settings;
	RAD_GPTP_SETTINGS gPTP;
	uint16_t iso_tester_pullup_enable;
	CMP_GLOBAL_DATA cmp_global_data;
	CMP_NETWORK_DATA cmp_stream_data[CMP_STREAMS_RED2];
	uint32_t networkTimeSync;
} SRed2Settings;
#define SRed2Settings_SIZE (918)

typedef struct _SFire3Settings
{
	uint16_t perf_en;
	uint16_t network_enabled_on_boot;
	uint16_t misc_io_on_report_events;
	uint16_t pwr_man_enable;
	int16_t iso15765_separation_time_offset;
	uint16_t slaveVnetA;
	uint32_t reserved;
	uint64_t termination_enables_1;
	uint64_t network_enables;
	uint32_t pwr_man_timeout;
	CAN_SETTINGS can1;
	CANFD_SETTINGS canfd1;
	CAN_SETTINGS can2;
	CANFD_SETTINGS canfd2;
	CAN_SETTINGS can3;
	CANFD_SETTINGS canfd3;
	CAN_SETTINGS can4;
	CANFD_SETTINGS canfd4;
	CAN_SETTINGS can5;
	CANFD_SETTINGS canfd5;
	CAN_SETTINGS can6;
	CANFD_SETTINGS canfd6;
	CAN_SETTINGS can7;
	CANFD_SETTINGS canfd7;
	CAN_SETTINGS can8;
	CANFD_SETTINGS canfd8;
	LIN_SETTINGS lin1;
	LIN_SETTINGS lin2;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_1;
	uint16_t iso_parity_1;
	uint16_t iso_msg_termination_1;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_2;
	uint16_t iso_parity_2;
	uint16_t iso_msg_termination_2;
	ETHERNET_SETTINGS ethernet_1;
	TIMESYNC_ICSHARDWARE_SETTINGS timeSync;
	STextAPISettings text_api;
	struct
	{
		uint32_t disableUsbCheckOnBoot : 1;
		uint32_t enableLatencyTest : 1;
		uint32_t busMessagesToAndroid : 1;
		uint32_t enablePcEthernetComm : 1;
		uint32_t enableDefaultLogger : 1;
		uint32_t enableDefaultUpload : 1;
		uint32_t reserved : 26;
	} flags;
	DISK_SETTINGS disk;
	uint16_t misc_io_report_period;
	uint16_t ain_threshold;
	uint16_t misc_io_analog_enable;
	uint16_t digitalIoThresholdTicks;
	uint16_t digitalIoThresholdEnable;
	uint16_t misc_io_initial_ddr;
	uint16_t misc_io_initial_latch;
	ETHERNET_SETTINGS2 ethernet2_1;
	ETHERNET_SETTINGS ethernet_2;
	ETHERNET_SETTINGS2 ethernet2_2;
	Fire3LinuxSettings os_settings;
	RAD_GPTP_SETTINGS gPTP;
	CAN_SETTINGS can9;
	CANFD_SETTINGS canfd9;
	CAN_SETTINGS can10;
	CANFD_SETTINGS canfd10;
	CAN_SETTINGS can11;
	CANFD_SETTINGS canfd11;
	CAN_SETTINGS can12;
	CANFD_SETTINGS canfd12;
	CAN_SETTINGS can13;
	CANFD_SETTINGS canfd13;
	CAN_SETTINGS can14;
	CANFD_SETTINGS canfd14;
	CAN_SETTINGS can15;
	CANFD_SETTINGS canfd15;
	CAN_SETTINGS can16;
	CANFD_SETTINGS canfd16;
	SWCAN_SETTINGS swcan1;
	SWCAN_SETTINGS swcan2;
	CAN_SETTINGS lsftcan1;
	CAN_SETTINGS lsftcan2;
	ETHERNET_SETTINGS ethernet_3;
	ETHERNET_SETTINGS2 ethernet2_3;
	LIN_SETTINGS lin3;
	LIN_SETTINGS lin4;
	LIN_SETTINGS lin5;
	LIN_SETTINGS lin6;
	LIN_SETTINGS lin7;
	LIN_SETTINGS lin8;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_3;
	uint16_t iso_parity_3;
	uint16_t iso_msg_termination_3;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_4;
	uint16_t iso_parity_4;
	uint16_t iso_msg_termination_4;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_5;
	uint16_t iso_parity_5;
	uint16_t iso_msg_termination_5;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_6;
	uint16_t iso_parity_6;
	uint16_t iso_msg_termination_6;
	uint16_t selectable_network_1;
	uint16_t selectable_network_2;
	uint64_t network_enables_2;
	uint64_t termination_enables_2;
	uint16_t iso_tester_pullup_enable;
	CMP_GLOBAL_DATA cmp_global_data;
	CMP_NETWORK_DATA cmp_stream_data[CMP_STREAMS_FIRE3];
	uint32_t networkTimeSync;
} SFire3Settings;
#define SFire3Settings_SIZE (1722)


typedef struct _SFire3FlexraySettings
{
	uint16_t perf_en;
	uint16_t network_enabled_on_boot;
	uint16_t misc_io_on_report_events;
	uint16_t pwr_man_enable;
	int16_t iso15765_separation_time_offset;
	uint16_t slaveVnetA;
	uint32_t reserved;
	uint64_t termination_enables_1;
	uint64_t network_enables;
	uint32_t pwr_man_timeout;
	CAN_SETTINGS can1;
	CANFD_SETTINGS canfd1;
	CAN_SETTINGS can2;
	CANFD_SETTINGS canfd2;
	CAN_SETTINGS can3;
	CANFD_SETTINGS canfd3;
	CAN_SETTINGS can4;
	CANFD_SETTINGS canfd4;
	CAN_SETTINGS can5;
	CANFD_SETTINGS canfd5;
	CAN_SETTINGS can6;
	CANFD_SETTINGS canfd6;
	CAN_SETTINGS can7;
	CANFD_SETTINGS canfd7;
	CAN_SETTINGS can8;
	CANFD_SETTINGS canfd8;
	LIN_SETTINGS lin1;
	LIN_SETTINGS lin2;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_1;
	uint16_t iso_parity_1;
	uint16_t iso_msg_termination_1;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_2;
	uint16_t iso_parity_2;
	uint16_t iso_msg_termination_2;
	ETHERNET_SETTINGS ethernet_1;
	TIMESYNC_ICSHARDWARE_SETTINGS timeSync;
	STextAPISettings text_api;
	struct
	{
		uint32_t disableUsbCheckOnBoot : 1;
		uint32_t enableLatencyTest : 1;
		uint32_t busMessagesToAndroid : 1;
		uint32_t reserved1 : 1;
		uint32_t enableDefaultLogger : 1;
		uint32_t enableDefaultUpload : 1;
		uint32_t reserved : 26;
	} flags;
	DISK_SETTINGS disk;
	uint16_t misc_io_report_period;
	uint16_t ain_threshold;
	uint16_t misc_io_analog_enable;
	uint16_t digitalIoThresholdTicks;
	uint16_t digitalIoThresholdEnable;
	uint16_t misc_io_initial_ddr;
	uint16_t misc_io_initial_latch;
	ETHERNET_SETTINGS2 ethernet2_1;
	ETHERNET_SETTINGS ethernet_2;
	ETHERNET_SETTINGS2 ethernet2_2;
	Fire3LinuxSettings os_settings;
	RAD_GPTP_SETTINGS gPTP;
	CAN_SETTINGS can9;
	CANFD_SETTINGS canfd9;
	CAN_SETTINGS can10;
	CANFD_SETTINGS canfd10;
	CAN_SETTINGS can11;
	CANFD_SETTINGS canfd11;
	CAN_SETTINGS can12;
	CANFD_SETTINGS canfd12;
	CAN_SETTINGS can13;
	CANFD_SETTINGS canfd13;
	CAN_SETTINGS can14;
	CANFD_SETTINGS canfd14;
	CAN_SETTINGS can15;
	CANFD_SETTINGS canfd15;
	ETHERNET_SETTINGS ethernet_3;
	ETHERNET_SETTINGS2 ethernet2_3;
	LIN_SETTINGS lin3;
	LIN_SETTINGS lin4;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_3;
	uint16_t iso_parity_3;
	uint16_t iso_msg_termination_3;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_4;
	uint16_t iso_parity_4;
	uint16_t iso_msg_termination_4;
	uint64_t network_enables_2;
	uint64_t termination_enables_2;
	uint16_t flex_mode;
	uint16_t flex_termination;
	uint16_t iso_tester_pullup_enable;
	CMP_GLOBAL_DATA cmp_global_data;
	CMP_NETWORK_DATA cmp_stream_data[CMP_STREAMS_FIRE3FR];
	uint32_t networkTimeSync;
} SFire3FlexraySettings;
#define SFire3FlexraySettings_SIZE (1372)

typedef struct _SFire3T1SLINSettings
{
	uint16_t perf_en;
	uint16_t network_enabled_on_boot;
	uint16_t misc_io_on_report_events;
	uint16_t pwr_man_enable;
	int16_t iso15765_separation_time_offset;
	uint16_t slaveVnetA;
	uint32_t reserved;
	uint64_t termination_enables_1;
	uint64_t network_enables;
	uint32_t pwr_man_timeout;
	CAN_SETTINGS can1;
	CANFD_SETTINGS canfd1;
	CAN_SETTINGS can2;
	CANFD_SETTINGS canfd2;
	CAN_SETTINGS can3;
	CANFD_SETTINGS canfd3;
	CAN_SETTINGS can4;
	CANFD_SETTINGS canfd4;
	CAN_SETTINGS can5;
	CANFD_SETTINGS canfd5;
	CAN_SETTINGS can6;
	CANFD_SETTINGS canfd6;
	CAN_SETTINGS can7;
	CANFD_SETTINGS canfd7;
	CAN_SETTINGS can8;
	CANFD_SETTINGS canfd8;
	LIN_SETTINGS lin1;
	LIN_SETTINGS lin2;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_1;
	uint16_t iso_parity_1;
	uint16_t iso_msg_termination_1;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_2;
	uint16_t iso_parity_2;
	uint16_t iso_msg_termination_2;
	ETHERNET_SETTINGS ethernet_1;
	TIMESYNC_ICSHARDWARE_SETTINGS timeSync;
	STextAPISettings text_api;
	struct
	{
		uint32_t disableUsbCheckOnBoot : 1;
		uint32_t enableLatencyTest : 1;
		uint32_t busMessagesToAndroid : 1;
		uint32_t reserved1 : 1;
		uint32_t enableDefaultLogger : 1;
		uint32_t enableDefaultUpload : 1;
		uint32_t reserved : 26;
	} flags;
	DISK_SETTINGS disk;
	uint16_t misc_io_report_period;
	uint16_t ain_threshold;
	uint16_t misc_io_analog_enable;
	uint16_t digitalIoThresholdTicks;
	uint16_t digitalIoThresholdEnable;
	uint16_t misc_io_initial_ddr;
	uint16_t misc_io_initial_latch;
	ETHERNET_SETTINGS2 ethernet2_1;
	ETHERNET_SETTINGS ethernet_2;
	ETHERNET_SETTINGS2 ethernet2_2;
	Fire3LinuxSettings os_settings;
	RAD_GPTP_SETTINGS gPTP;

	/* VEM */
	// 10T1S
	ETHERNET_SETTINGS2 ethT1s1;
	ETHERNET10T1S_SETTINGS t1s1;
	ETHERNET10T1S_SETTINGS_EXT t1s1Ext;
	// 10T1S
	ETHERNET_SETTINGS2 ethT1s2;
	ETHERNET10T1S_SETTINGS t1s2;
	ETHERNET10T1S_SETTINGS_EXT t1s2Ext;
	// 10T1S
	ETHERNET_SETTINGS2 ethT1s3;
	ETHERNET10T1S_SETTINGS t1s3;
	ETHERNET10T1S_SETTINGS_EXT t1s3Ext;
	// 10T1S
	ETHERNET_SETTINGS2 ethT1s4;
	ETHERNET10T1S_SETTINGS t1s4;
	ETHERNET10T1S_SETTINGS_EXT t1s4Ext;
	// 10T1S
	ETHERNET_SETTINGS2 ethT1s5;
	ETHERNET10T1S_SETTINGS t1s5;
	ETHERNET10T1S_SETTINGS_EXT t1s5Ext;
	// 10T1S
	ETHERNET_SETTINGS2 ethT1s6;
	ETHERNET10T1S_SETTINGS t1s6;
	ETHERNET10T1S_SETTINGS_EXT t1s6Ext;
	// 10T1S
	ETHERNET_SETTINGS2 ethT1s7;
	ETHERNET10T1S_SETTINGS t1s7;
	ETHERNET10T1S_SETTINGS_EXT t1s7Ext;
	// 10T1S
	ETHERNET_SETTINGS2 ethT1s8;
	ETHERNET10T1S_SETTINGS t1s8;
	ETHERNET10T1S_SETTINGS_EXT t1s8Ext;

	LIN_SETTINGS lin3;
	LIN_SETTINGS lin4;
	LIN_SETTINGS lin5;
	LIN_SETTINGS lin6;
	LIN_SETTINGS lin7;
	LIN_SETTINGS lin8;
	LIN_SETTINGS lin9;
	LIN_SETTINGS lin10;

	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_3;
	uint16_t iso_parity_3;
	uint16_t iso_msg_termination_3;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_4;
	uint16_t iso_parity_4;
	uint16_t iso_msg_termination_4;

	uint16_t iso_tester_pullup_enable;

	uint64_t network_enables_5;

	CMP_GLOBAL_DATA cmp_global_data;
	CMP_NETWORK_DATA cmp_stream_data[CMP_STREAMS_FIRE3T1SLIN];
	uint32_t networkTimeSync;
} SFire3T1sLinSettings;
#define SFire3T1sLinSettings_SIZE (1594)

#define RADEPSILON_NUM_PORTS 18 // ATSAM + PHYs
#define RADEPSILON_MAX_PHY 18
#define EPSILON_88Q6113_SWITCH_A 1
#define EPSILON_88Q6113_SWITCH_B 2
#define EPSILON_88Q6113_SWITCH_AB 3
typedef enum
{
	EPSILON_10G_PHY1 = (1 << 0),
	EPSILON_10G_PHY2 = (1 << 1),
} Epsilon_10G_PHY_select;

typedef struct _SRADEpsilonSwitchSettings
{
	uint8_t phyMode[RADEPSILON_MAX_PHY];
	uint8_t enablePhy[RADEPSILON_MAX_PHY];
	uint8_t speed[RADEPSILON_MAX_PHY];
	uint8_t legacy[RADEPSILON_MAX_PHY];
	uint8_t spoofedMac[6];
	uint8_t spoofMacFlag;
	uint8_t pad;
} SRADEpsilonSwitchSettings; //80

typedef struct _SRADEpsilonSettings
{
	/* Performance Test */
	uint16_t perf_en; //2

	CAN_SETTINGS can1; //12
	CANFD_SETTINGS canfd1; //10
	CAN_SETTINGS can2; //12
	CANFD_SETTINGS canfd2; //10
	LIN_SETTINGS lin1; //10

	uint16_t network_enables; //2
	uint16_t network_enables_2; //2
	uint16_t network_enables_3; //2
	uint64_t termination_enables; //8
	uint16_t misc_io_analog_enable; //2

	uint32_t pwr_man_timeout; //4
	uint16_t pwr_man_enable; //2

	uint16_t network_enabled_on_boot; //2

	/* ISO15765-2 Transport Layer */
	int16_t iso15765_separation_time_offset; //2
	uint16_t iso9141_kwp_enable_reserved; //2
	uint16_t iso_tester_pullup_enable; //2
	uint16_t iso_parity; //2
	uint16_t iso_msg_termination; //2
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings; //114
	ETHERNET_SETTINGS ethernet; //8

	STextAPISettings text_api; //72

	struct
	{
		uint32_t disableUsbCheckOnBoot : 1;
		uint32_t enableLatencyTest : 1;
		uint32_t enablePcEthernetComm : 1;
		uint32_t reserved : 29;
	} flags; //4

	SRADEpsilonSwitchSettings switchSettings; //80
	ETHERNET_SETTINGS2 ethernet2; //16
	uint16_t misc_io_on_report_events; //2
	DISK_SETTINGS disk; //14

} SRADEpsilonSettings; //400
#define SRADEpsilonSettings_SIZE 400

typedef struct
{
	uint8_t wBMSDeviceID;
	uint8_t enabled;
} sWIL_FAULT_SERVICING_SETTINGS; //2

typedef struct
{
	uint8_t enabled;
} sWIL_NETWORK_DATA_CAPTURE_SETTINGS;   //1

typedef struct _sWIL_CONNECTION_SETTINGS
{
	uint8_t using_port_a; //1
	uint8_t using_port_b; //1
	uint8_t attemptConnect; //1
	sWIL_FAULT_SERVICING_SETTINGS fault_servicing_config; //2
	sWIL_NETWORK_DATA_CAPTURE_SETTINGS network_data_capture_config; //1
	uint16_t sensor_buffer_size; //2
} sWIL_CONNECTION_SETTINGS;

enum
{	
	enumWILPortConfig_Single_Port_A = 0,
	enumWILPortConfig_Single_Port_B,
	enumWILPortConfig_Dual_Port_A_And_B,
	enumWILPortConfig_Single_Port_A_And_B,
	_enumWILPortConfig_Total,	
};

enum
{
	SPI_PORT_ONBOARD = 0,
	SPI_PORT_EXTERNAL,
};

enum
{
	SPI_TYPE_WIL = 0,
	SPI_TYPE_RAW,
};

enum
{
	SPI_MODE_MASTER,
	SPI_MODE_SLAVE,
	SPI_MODE_PMS_EMULATION,
};

typedef union
{
	uint64_t dword;
	struct
	{
		uint64_t can_id : 29;
		uint64_t can_id_isExtended : 1;
		uint64_t tcp_port : 16;
		uint64_t reserved : 18;
	} config;
} sWILBridgeConfig;


typedef union
{
	uint8_t byte;
	struct
	{
		uint8_t onboard_external : 1;
		uint8_t type : 1;
		uint8_t mode: 3;
		uint8_t reserved : 3;
	} config;
} sSPI_PORT_SETTING;

typedef struct
{
	sSPI_PORT_SETTING port_a; //1
	sSPI_PORT_SETTING port_b; //1
} sSPI_PORT_SETTINGS;

// clang-format off
#define WBMS_GATEWAY_NETWORK_NONE			(0)
#define WBMS_GATEWAY_NETWORK_DWCAN_01		(1)
#define WBMS_GATEWAY_NETWORK_DWCAN_02		(2)
#define WBMS_GATEWAY_NETWORK_UDP_MULTICAST	(3)
// clang-format on

typedef struct
{
	uint8_t wbms1_network;
	uint8_t wbms1_canfd_enable;
	uint8_t wbms2_network;
	uint8_t wbms2_canfd_enable;
	uint16_t reserved[6];
} WBMSGatewaySettings; //16

typedef struct _SRADBMSSettings
{
	/* Performance Test */
	uint16_t perf_en; //2

	uint64_t termination_enables; //8

	CAN_SETTINGS can1; //12
	CANFD_SETTINGS canfd1; //10

	CAN_SETTINGS can2; //12
	CANFD_SETTINGS canfd2; //10

	uint16_t network_enables; //2
	uint16_t network_enables_2; //2
	uint16_t network_enables_3; //2

	/* ISO15765-2 Transport Layer */
	int16_t iso15765_separation_time_offset; //2

	struct
	{
		uint32_t disableUsbCheckOnBoot : 1;
		uint32_t enableLatencyTest : 1;
		uint32_t enablePcEthernetComm : 1;
		uint32_t reserved : 29;
	} flags; //4

	ETHERNET_SETTINGS ethernet; //8
	ETHERNET_SETTINGS2 ethernet2; //16

	uint32_t pwr_man_timeout; // 4
	uint16_t pwr_man_enable; //2
	uint16_t network_enabled_on_boot; //2

	uint8_t rsvd[10]; //Was sWILBridgeConfig

	sSPI_PORT_SETTINGS spi_config; //2

	sWIL_CONNECTION_SETTINGS wbms_wil_1; //8
	sWIL_CONNECTION_SETTINGS wbms_wil_2; //8

	uint16_t wil1_nwk_metadata_buff_count; //2
	uint16_t wil2_nwk_metadata_buff_count; //2

	WBMSGatewaySettings gateway; //16

	uint16_t network_enables_4; //2
	uint64_t network_enables_5; //8
}SRADBMSSettings;
#define SRADBMSSettings_SIZE 156

typedef struct _SRADCometSettings
{
	// ECU ID used in CAN communications.
	// TX ID = ECU ID with bit28 cleared,
	// RX ID = ECUID with bit28 set,
	// ECU ID = 0 implies ECU ID = serial no with bit 27 set
	uint32_t ecu_id;
	uint16_t perf_en;
	struct
	{
		uint16_t hwComLatencyTestEn : 1;
		uint16_t disableUsbCheckOnBoot : 1;
		uint16_t reserved : 14;
	} flags;
	uint16_t network_enabled_on_boot;
	CAN_SETTINGS can1;
	CANFD_SETTINGS canfd1;
	CAN_SETTINGS can2;
	CANFD_SETTINGS canfd2;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_1;
	uint16_t iso_parity_1;
	uint16_t iso_msg_termination_1;
	union
	{
		uint64_t word;
		struct
		{
			uint16_t network_enables;
			uint16_t network_enables_2;
			uint16_t network_enables_3;
			uint16_t network_enables_4;
		};
	} network_enables;
	uint64_t termination_enables;
	TIMESYNC_ICSHARDWARE_SETTINGS timeSyncSettings;
	RAD_REPORTING_SETTINGS reporting;
	int16_t iso15765_separation_time_offset;
	uint32_t pwr_man_timeout;
	uint16_t pwr_man_enable;
	RAD_GPTP_SETTINGS gPTP;
	STextAPISettings text_api;
	// Ethernet 10/100/1000
	ETHERNET_SETTINGS2 ethernet;
	// Ethernet General
	OP_ETH_GENERAL_SETTINGS opEthGen;
	// 100/1000T1
	ETHERNET_SETTINGS2 ethT1;
	OP_ETH_SETTINGS opEth1;
	// 10T1S
	ETHERNET_SETTINGS2 ethT1s1;
	ETHERNET10T1S_SETTINGS t1s1;
	// 10T1S
	ETHERNET_SETTINGS2 ethT1s2;
	ETHERNET10T1S_SETTINGS t1s2;
	uint64_t network_enables_5;
	LIN_SETTINGS lin1;
	// 10T1S Extended settings
	ETHERNET10T1S_SETTINGS_EXT t1s1Ext;
	ETHERNET10T1S_SETTINGS_EXT t1s2Ext;
} SRADCometSettings;
#define SRADCometSettings_SIZE 498

typedef struct _SRADComet3Settings
{
	// ECU ID used in CAN communications.
	// TX ID = ECU ID with bit28 cleared,
	// RX ID = ECUID with bit28 set,
	// ECU ID = 0 implies ECU ID = serial no with bit 27 set
	uint32_t ecu_id;
	uint16_t perf_en;
	struct
	{
		uint16_t hwComLatencyTestEn : 1;
		uint16_t disableUsbCheckOnBoot : 1;
		uint16_t reserved : 14;
	} flags;
	uint16_t network_enabled_on_boot;
	CAN_SETTINGS can1;
	CANFD_SETTINGS canfd1;
	CAN_SETTINGS can2;
	CANFD_SETTINGS canfd2;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_1;
	uint16_t iso_parity_1;
	uint16_t iso_msg_termination_1;
	uint64_t network_enables;
	uint64_t network_enables_2;
	uint64_t termination_enables;
	TIMESYNC_ICSHARDWARE_SETTINGS timeSyncSettings;
	RAD_REPORTING_SETTINGS reporting;
	int16_t iso15765_separation_time_offset;
	uint32_t pwr_man_timeout;
	uint16_t pwr_man_enable;
	RAD_GPTP_SETTINGS gPTP;
	STextAPISettings text_api;
	// Ethernet 10/100/1000
	ETHERNET_SETTINGS2 ethernet;
	// Ethernet General
	OP_ETH_GENERAL_SETTINGS opEthGen;
	// 100/1000T1
	ETHERNET_SETTINGS2 ethT1;
	OP_ETH_SETTINGS opEth1;
	// 10T1S
	ETHERNET_SETTINGS2 ethT1s1;
	ETHERNET10T1S_SETTINGS t1s1;
	// 10T1S
	ETHERNET_SETTINGS2 ethT1s2;
	ETHERNET10T1S_SETTINGS t1s2;
	// 10T1S
	ETHERNET_SETTINGS2 ethT1s3;
	ETHERNET10T1S_SETTINGS t1s3;
	// 10T1S
	ETHERNET_SETTINGS2 ethT1s4;
	ETHERNET10T1S_SETTINGS t1s4;
	// 10T1S
	ETHERNET_SETTINGS2 ethT1s5;
	ETHERNET10T1S_SETTINGS t1s5;
	// 10T1S
	ETHERNET_SETTINGS2 ethT1s6;
	ETHERNET10T1S_SETTINGS t1s6;
	LIN_SETTINGS lin1;
	// 10T1S Extended Settings
	ETHERNET10T1S_SETTINGS_EXT t1s1Ext;
	ETHERNET10T1S_SETTINGS_EXT t1s2Ext;
	ETHERNET10T1S_SETTINGS_EXT t1s3Ext;
	ETHERNET10T1S_SETTINGS_EXT t1s4Ext;
	ETHERNET10T1S_SETTINGS_EXT t1s5Ext;
	ETHERNET10T1S_SETTINGS_EXT t1s6Ext;
} SRADComet3Settings;
#define SRADComet3Settings_SIZE 674

typedef struct _SRADGigaStar2Settings
{
	// ECU ID used in CAN communications.
	// TX ID = ECU ID with bit28 cleared,
	// RX ID = ECUID with bit28 set,
	// ECU ID = 0 implies ECU ID = serial no with bit 27 set
	uint32_t ecu_id;
	uint16_t perf_en;
	struct
	{
		uint16_t hwComLatencyTestEn : 1;
		uint16_t disableUsbCheckOnBoot : 1;
		uint16_t reserved : 14;
	} flags;
	uint16_t network_enabled_on_boot;
	CAN_SETTINGS can1;
	CANFD_SETTINGS canfd1;
	CAN_SETTINGS can2;
	CANFD_SETTINGS canfd2;
	CAN_SETTINGS can3;
	CANFD_SETTINGS canfd3;
	CAN_SETTINGS can4;
	CANFD_SETTINGS canfd4;

	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_1;
	uint16_t iso_parity_1;
	uint16_t iso_msg_termination_1;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_2;
	uint16_t iso_parity_2;
	uint16_t iso_msg_termination_2;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_3;
	uint16_t iso_parity_3;
	uint16_t iso_msg_termination_3;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_4;
	uint16_t iso_parity_4;
	uint16_t iso_msg_termination_4;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_5;
	uint16_t iso_parity_5;
	uint16_t iso_msg_termination_5;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_6;
	uint16_t iso_parity_6;
	uint16_t iso_msg_termination_6;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_7;
	uint16_t iso_parity_7;
	uint16_t iso_msg_termination_7;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_8;
	uint16_t iso_parity_8;
	uint16_t iso_msg_termination_8;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_9;
	uint16_t iso_parity_9;
	uint16_t iso_msg_termination_9;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_10;
	uint16_t iso_parity_10;
	uint16_t iso_msg_termination_10;
	uint64_t network_enables;
	uint64_t network_enables_2;
	uint64_t termination_enables;
	TIMESYNC_ICSHARDWARE_SETTINGS timeSyncSettings;
	RAD_REPORTING_SETTINGS reporting;
	int16_t iso15765_separation_time_offset;
	uint32_t pwr_man_timeout;
	uint16_t pwr_man_enable;
	RAD_GPTP_SETTINGS gPTP;
	STextAPISettings text_api;
	DISK_SETTINGS disk;
	LOGGER_SETTINGS logger;
	LIN_SETTINGS lin1;
	LIN_SETTINGS lin2;
	LIN_SETTINGS lin3;
	LIN_SETTINGS lin4;
	LIN_SETTINGS lin5;
	LIN_SETTINGS lin6;
	LIN_SETTINGS lin7;
	LIN_SETTINGS lin8;
	LIN_SETTINGS lin9;
	LIN_SETTINGS lin10;
	// TODO more LIN
	// Ethernet SFP
	ETHERNET_SETTINGS2 ethernet1;
	ETHERNET_SETTINGS2 ethernet2;
	// Ethernet General
	OP_ETH_GENERAL_SETTINGS opEthGen;
	// 100/1000T1
	ETHERNET_SETTINGS2 ethT1;
	OP_ETH_SETTINGS opEth1;
	ETHERNET_SETTINGS2 ethT12;
	OP_ETH_SETTINGS opEth2;
	// 10T1S
	ETHERNET_SETTINGS2 ethT1s1;
	ETHERNET10T1S_SETTINGS t1s1;
	ETHERNET10T1S_SETTINGS_EXT t1s1Ext;
	// 10T1S
	ETHERNET_SETTINGS2 ethT1s2;
	ETHERNET10T1S_SETTINGS t1s2;
	ETHERNET10T1S_SETTINGS_EXT t1s2Ext;
	// 10T1S
	ETHERNET_SETTINGS2 ethT1s3;
	ETHERNET10T1S_SETTINGS t1s3;
	ETHERNET10T1S_SETTINGS_EXT t1s3Ext;
	// 10T1S
	ETHERNET_SETTINGS2 ethT1s4;
	ETHERNET10T1S_SETTINGS t1s4;
	ETHERNET10T1S_SETTINGS_EXT t1s4Ext;
	// 10T1S
	ETHERNET_SETTINGS2 ethT1s5;
	ETHERNET10T1S_SETTINGS t1s5;
	ETHERNET10T1S_SETTINGS_EXT t1s5Ext;
	// 10T1S
	ETHERNET_SETTINGS2 ethT1s6;
	ETHERNET10T1S_SETTINGS t1s6;
	ETHERNET10T1S_SETTINGS_EXT t1s6Ext;
	// 10T1S
	ETHERNET_SETTINGS2 ethT1s7;
	ETHERNET10T1S_SETTINGS t1s7;
	ETHERNET10T1S_SETTINGS_EXT t1s7Ext;
	// 10T1S
	ETHERNET_SETTINGS2 ethT1s8;
	ETHERNET10T1S_SETTINGS t1s8;
	ETHERNET10T1S_SETTINGS_EXT t1s8Ext;
	// SFP T1S
	ETHERNET10T1S_SETTINGS sfp_t1s_1;
	ETHERNET10T1S_SETTINGS_EXT sfp_t1s_ext_1;
	ETHERNET10T1S_SETTINGS sfp_t1s_2;
	ETHERNET10T1S_SETTINGS_EXT sfp_t1s_ext_2;
	LIN_SETTINGS lin11;
	LIN_SETTINGS lin12;
	LIN_SETTINGS lin13;
	LIN_SETTINGS lin14;
	LIN_SETTINGS lin15;
	LIN_SETTINGS lin16;
	// SFP T1L
	ETHERNET10T1L_SETTINGS sfp_t1l_1;
	ETHERNET10T1L_SETTINGS sfp_t1l_2;
} SRADGigastar2Settings;
#define SRADGigastar2Settings_SIZE 2156

// variants to be used with icsneoSetFirmwareVariant
enum Gigastar2FwVariants
{
	GIGASTAR2_FW_VARIANT_6T1S_1CAN_16LIN = 0,
	GIGASTAR2_FW_VARIANT_8T1S_4CAN_6LIN = 1,
	GIGASTAR2_FW_VARIANT_COUNT,
};

typedef struct _SRADMoonT1SSettings
{
	uint16_t perf_en;
	struct
	{
		uint16_t hwComLatencyTestEn : 1;
		uint16_t disableUsbCheckOnBoot : 1;
		uint16_t reserved : 14;
	} flags;
	uint16_t network_enabled_on_boot;
	uint64_t network_enables;
	uint64_t network_enables_2;
	RAD_REPORTING_SETTINGS reporting;
	uint32_t pwr_man_timeout;
	uint16_t pwr_man_enable;
	// Ethernet 10/100/1000
	ETHERNET_SETTINGS2 ethernet;
	// Ethernet General
	OP_ETH_GENERAL_SETTINGS opEthGen;
	// 10T1S
	ETHERNET_SETTINGS2 ethT1s;
	ETHERNET10T1S_SETTINGS t1s;
	// 10T1S Extended Settings
	ETHERNET10T1S_SETTINGS_EXT t1sExt;
	RAD_GPTP_SETTINGS gPTP;
} SRADMoonT1SSettings;
#define SRADMoonT1SSettings_SIZE 160

typedef struct _SNeoVIConnectSettings
{
	uint16_t perf_en;
	uint16_t network_enabled_on_boot;
	uint16_t misc_io_on_report_events;
	uint16_t pwr_man_enable;
	int16_t iso15765_separation_time_offset;
	uint16_t reservedA;
	uint32_t pwr_man_timeout;
	union
	{
		uint64_t word;
		struct
		{
			uint16_t network_enables;
			uint16_t network_enables_2;
			uint16_t network_enables_3;
			uint16_t network_enables_4;
		};
	} network_enables;
	CAN_SETTINGS can1;
	CANFD_SETTINGS canfd1;
	CAN_SETTINGS can2;
	CANFD_SETTINGS canfd2;
	CAN_SETTINGS can3;
	CANFD_SETTINGS canfd3;
	CAN_SETTINGS can4;
	CANFD_SETTINGS canfd4;
	CAN_SETTINGS can5;
	CANFD_SETTINGS canfd5;
	CAN_SETTINGS can6;
	CANFD_SETTINGS canfd6;
	CAN_SETTINGS can7;
	CANFD_SETTINGS canfd7;
	CAN_SETTINGS can8;
	CANFD_SETTINGS canfd8;
	LIN_SETTINGS lin1;
	LIN_SETTINGS lin2;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_1;
	uint16_t iso_parity_1;
	uint16_t iso_msg_termination_1;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_2;
	uint16_t iso_parity_2;
	uint16_t iso_msg_termination_2;
	ETHERNET_SETTINGS ethernet_1;
	ETHERNET_SETTINGS2 ethernet2_1;
	STextAPISettings text_api;
	DISK_SETTINGS disk;
	uint16_t misc_io_report_period;
	uint16_t ain_threshold;
	uint16_t misc_io_analog_enable;
	uint16_t digitalIoThresholdTicks;
	uint16_t digitalIoThresholdEnable;
	uint16_t misc_io_initial_ddr;
	uint16_t misc_io_initial_latch;
	Fire3LinuxSettings os_settings;
	RAD_GPTP_SETTINGS gPTP;
	struct
	{
		uint32_t disableUsbCheckOnBoot : 1;
		uint32_t enableLatencyTest : 1;
		uint32_t enableDefaultLogger : 1;
		uint32_t enableDefaultUpload : 1;
		uint32_t reserved3 : 28;
	} flags;
} SNeoVIConnectSettings;
#define SNeoVIConnectSettings_SIZE (628)

#define GS_VERSION 5
typedef struct _GLOBAL_SETTINGS
{
	uint16_t version;
	uint16_t len;
	uint16_t chksum;
	union
	{
		SRedSettings red;
		SFireSettings fire;
		SFireVnetSettings firevnet;
		SCyanSettings cyan;
		SVCAN3Settings vcan3;
		SVCAN4Settings vcan4;
		SECUSettings ecu;
		SPendantSettings pendant;
		SRADGalaxySettings radgalaxy;
		SRADStar2Settings radstar2;
		SVCAN412Settings vcan412;
		SVCAN412Settings vcan4_12; // backwards compatibility with older code
		SRADMoon2Settings radmoon2;
		SCANHubSettings canhub;
		SNeoECU12Settings neoecu12;
		SFlexVnetzSettings flexvnetz;
		SVividCANSettings vividcan;
		SVCAN4IndSettings vcan4_ind;
		SOBD2LCSettings obd2lc;
		SRADGigastarSettings radgigastar;
		SRADGalaxy2Settings radGalaxy2;
		SRADJupiterSettings jupiter;
		SRed2Settings red2;
		SFire3Settings fire3;
		SFire3FlexraySettings fire3fr;
		SFire3T1sLinSettings fire3t1slin;
		SRADA2BSettings rad_a2b;
		SRADEpsilonSettings epsilon;
		SRADBMSSettings rad_bms;
		SRADMoon3Settings radmoon3;
		SRADGeminiSettings radgemini;
		SRADCometSettings radcomet;
		SRADComet3Settings radcomet3;
		SRADGigastar2Settings radgigastar2;
		SRADMoonT1SSettings radmoont1s;
		SNeoVIConnectSettings neovi_connect;
		// Make sure SDeviceSettings matches this
	};
} GLOBAL_SETTINGS;
#define GLOBAL_SETTINGS_SIZE (SRADGigastar2Settings_SIZE + 6)

#define NEOVI_3G_MAX_SETTINGS_SIZE sizeof(GLOBAL_SETTINGS)

typedef enum _EDeviceSettingsType
{
	DeviceFireSettingsType,
	DeviceFireVnetSettingsType,
	DeviceFire2SettingsType,
	DeviceVCAN3SettingsType,
	DeviceRADGalaxySettingsType,
	DeviceRADStar2SettingsType,
	DeviceVCAN4SettingsType,
	DeviceVCAN412SettingsType,
	DeviceVividCANSettingsType,
	DeviceECU_AVBSettingsTypeDeprecated,
	DeviceRADSuperMoonSettingsTypeDeprecated,
	DeviceRADMoon2SettingsType,
	DeviceRADPlutoSettingsTypeDeprecated,
	DeviceRADGigalogSettingsTypeDeprecated,
	DeviceDeprecatedType,
	DeviceEEVBSettingsTypeDeprecated,
	DeviceVCAN4IndSettingsType,
	DeviceNeoECU12SettingsType,
	DeviceFlexVnetzSettingsType,
	DeviceCANHUBSettingsType,
	DeviceIEVBSettingsTypeDeprecated,
	DeviceOBD2SimSettingsTypeDeprecated,
	DeviceCMProbeSettingsTypeDeprecated,
	DeviceOBD2ProSettingsTypeDeprecated,
	DeviceRedSettingsType,
	DeviceRADPlutoSwitchSettingsTypeDeprecated,
	DeviceRADGigastarSettingsType,
	DeviceRADJupiterSettingsType,
	DeviceRed2SettingsType,
	DeviceRadMoonDuoSettingsTypeDeprecated,
	DeviceEtherBadgeSettingsTypeDeprecated,
	DeviceRADA2BSettingsType,
	DeviceRADEpsilonSettingsType,
	DeviceOBD2LCSettingsType,
	DeviceRADBMSSettingsType,
	DeviceRADMoon3SettingsType,
	DeviceFire3SettingsType,
	DeviceFire3FlexraySettingsType,
	DeviceRADCometSettingsType,
	DeviceNeoVIConnectSettingsType,
	DeviceRADComet3SettingsType,
	DeviceRADGalaxy2SettingsType,
	DeviceRADGigastar2SettingsType,
	DeviceRADMoonT1SSettingsType,
	DeviceRADGeminiSettingsType,
	DeviceFire3T1sLinSettingsType,
	// add new settings type here
	// Also add to map inside cicsneoVI::Init()
	DeviceSettingsTypeMax,
	DeviceSettingsNone = 0xFFFFFFFF // just wanted to reserve this
} EDeviceSettingsType;

typedef struct _SDeviceSettings
{
	EDeviceSettingsType DeviceSettingType;
	union
	{
		SRedSettings red;
		SFireSettings fire;
		SFireVnetSettings firevnet;
		SCyanSettings cyan;
		SVCAN3Settings vcan3;
		SVCAN4Settings vcan4;
		SECUSettings ecu;
		SPendantSettings pendant;
		SRADGalaxySettings radgalaxy;
		SRADStar2Settings radstar2;
		SVCAN412Settings vcan412;
		SVCAN412Settings vcan4_12; // backwards compatibility with older code
		SRADMoon2Settings radmoon2;
		SCANHubSettings canhub;
		SNeoECU12Settings neoecu12;
		SFlexVnetzSettings flexvnetz;
		SVividCANSettings vividcan;
		SVCAN4IndSettings vcan4_ind;
		SOBD2LCSettings obd2lc;
		SRADGigastarSettings radgigastar;
		SRADGalaxy2Settings radGalaxy2;
		SRADJupiterSettings jupiter;
		SFire3Settings fire3;
		SRed2Settings red2;
		SRADA2BSettings rad_a2b;
		SRADEpsilonSettings epsilon;
		SRADBMSSettings rad_bms;
		SRADMoon3Settings radmoon3;
		SRADGeminiSettings radgemini;
		SFire3FlexraySettings fire3Flexray;
		SFire3T1sLinSettings fire3t1slin;
		SRADCometSettings radcomet;
		SRADComet3Settings radcomet3;
		SRADGigastar2Settings radgigastar2;
		SRADMoonT1SSettings radmoont1s;
		SNeoVIConnectSettings neovi_connect;
		// Make sure GLOBAL_SETTINGS matches this
		// NOTE: When adding new structures here implement inside icsneoGetDeviceSettings and icsneoSetDeviceSettings also.	} Settings;
	} Settings;
} SDeviceSettings;


typedef enum _EPlasmaIonVnetChannel_t
{
	PlasmaIonVnetChannelMain, // PLASMA = SLOT 2, ION = VNET2
	PlasmaIonVnetChannelA, // PLASMA = SLOT 1, ION = VNET1
	PlasmaIonVnetChannelB, // PLASMA = SLOT 3, ION = NA
	eSoftCore,
	eFpgaStatusResp,
} EPlasmaIonVnetChannel_t;

typedef enum _EwBMSManagerPort_t
{
	eManagerPortA = 0,
	eManagerPortB,
} EwBMSManagerPort_t;

typedef enum _EwBMSManagerLockState_t
{
	eLockManager = 0,
	eUnlockManager,
} EwBMSManagerLockState_t;

typedef enum _EUartPort_t
{
	eUART0 = 0,
	eUART1,
} EUartPort_t;

typedef enum _eGenericAPIOptions
{
	eGENERIC_API = 0,
	eADI_WIL_API = 1,
} eGenericAPIOptions;

typedef enum _EwBMSInstance_t
{
	ewBMSInstance0 = 0,
	ewBMSInstance1,
} EwBMSInstance_t;

typedef struct _stCM_ISO157652_TxMessage
{
	uint16_t vs_netid; /* The netid of the message (determines which network to transmit on),  not supported */

	uint8_t padding; /* The padding byte to use to fill the unused portion of
								 * transmitted CAN frames (single frame, first frame, consecutive frame) */
	uint8_t tx_index;

	uint32_t id; /* arbId of transmitted frames (CAN id to transmit to) */
	uint32_t fc_id; /* flow control arb id filter value (response id from receiver) */
	uint32_t fc_id_mask; /* The flow control arb filter mask (response id from receiver) */

	uint8_t stMin; /* Overrides the stMin that the receiver reports, see overrideSTmin. Set to J2534's STMIN_TX if <= 0xFF */
	uint8_t blockSize; /* Overrides the block size that the receiver reports, see overrideBlockSize.   Set to J2534's BS_TX if <= 0xFF */
	uint8_t
		flowControlExtendedAddress; /* Expected Extended Address byte of response from receiver.  see fc_ext_address_enable, not supported */
	uint8_t extendedAddress; /* Extended Address byte of transmitter. see ext_address_enable, not supported */

	uint16_t fs_timeout; /* max timeout (ms) for waiting on flow control respons. Set this to N_BS_MAX's value if J2534 */
	uint16_t fs_wait; /* max timeout (ms) for waiting on flow control response after receiving flow control
									 * with flow status set to WAIT.   Set this to N_BS_MAX's value if J2534. */

	uint8_t data[4 * 1024]; /* The data */

	uint32_t num_bytes; /* Number of data bytes */

	union
	{
		struct
		{
			unsigned
				id_29_bit_enable : 1; /* Enables 29 bit arbId for transmitted frames.  Set to 1 so transmitted frames use 29 bit ids, not supported */
			unsigned
				fc_id_29_bit_enable : 1; /* Enables 29 bit arbId for Flow Control filter.  Set to 1 if receiver response uses 29 bit ids, not supported */
			unsigned
				ext_address_enable : 1; /* Enables Extended Addressing, Set to 1 if transmitted frames should have extended addres byte, not supported */
			unsigned
				fc_ext_address_enable : 1; /* Enables Extended Addressing for Flow Control filter.  Set to 1 if receiver responds with extended address byte, not supported */

			unsigned overrideSTmin : 1; /* Uses member stMin and not receiver's flow control's stMin */
			unsigned overrideBlockSize : 1; /* Uses member BlockSize and not receiver's flow control's BlockSize */
			unsigned paddingEnable : 1; /* Enables padding */
			unsigned iscanFD : 1;
			unsigned isBRSEnabled : 1;
			unsigned : 15;
			unsigned tx_dl : 8;
		};
		uint32_t flags;
	};
} stCM_ISO157652_TxMessage;
#define stCM_ISO157652_TxMessage_SIZE 4128

typedef struct
{
	uint16_t vs_netid; /* network id for transmitted/received frames */
	uint8_t padding; /* if paddingEnable is set, frames will be padded to full length (see tx_dl) with this byte */

	uint8_t tx_index; /* identifier for this transmit message */

	uint32_t id; /* ArbID of transmitted frames, see id_29_bit_enable */
	uint32_t fc_id; /* Flow control response ArbID Value, see fc_id_29_bit_enable */
	uint32_t fc_id_mask; /* Flow control response ArbID mask */

	uint8_t stMin; /* If overrideSTmin is set, this value supercedes the value in the flow control responses */
	uint8_t blockSize; /* if overrideBlockSize is ser, this value supercedes the value in the flow control responses */

	uint8_t flowControlExtendedAddress; /* Expected EA from the receiver, see fc_ext_address_enable */
	uint8_t extendedAddress; /* EA for transmitted frames, see ext_address_enable */

	uint16_t fs_timeout; /* timeout in milliseconds for waiting on flow control response */
	uint16_t
		fs_wait; /* timeout in milliseconds for waiting on another flow control response after receiving flow control with status set to WAIT */

	uint8_t* data; /* pointer to the data bytes, this needs to by dynamically allocated in the application */
	uint32_t
		num_bytes; /* number of data bytes, 0-4294967295. As of 06-22-2017, the embedded side has about 60MB of memory available to hold this data */

	uint8_t tx_dl; /* Maximum CAN(FD) protocol length for transmitted frames. Valid values are 8, 12, 16, 20, 24, 32, 48, 64 */

	union
	{
		struct
		{
			uint16_t id_29_bit_enable : 1;
			uint16_t fc_id_29_bit_enable : 1;
			uint16_t ext_address_enable : 1;
			uint16_t fc_ext_address_enable : 1;
			uint16_t overrideSTmin : 1;
			uint16_t overrideBlockSize : 1;
			uint16_t paddingEnable : 1;
			uint16_t iscanFD : 1;
			uint16_t isBRSEnabled : 1;
			uint16_t : 7;
		};
		uint16_t flags;
	};
} ISO15765_2015_TxMessage;
#define ISO15765_2015_TxMessage_SIZE (32 + sizeof(uint8_t*))

typedef struct _stCM_ISO157652_RxMessage
{
	uint16_t vs_netid; /* The netid of the message (determines which network to decode receives),  not supported */

	uint8_t padding; /* The padding byte to use to fill the unused portion of
								 * transmitted CAN frames (flow control), see paddingEnable. */


	uint32_t id; /* ArbId filter value for frames from transmitter (from ECU to neoVI) */
	uint32_t id_mask; /* ArbId filter mask for frames from transmitter (from ECU to neoVI) */
	uint32_t fc_id; /* flow control arbId to transmit in flow control (from neoVI to ECU) */

	uint8_t flowControlExtendedAddress; /* Extended Address byte used in flow control (from neoVI to ECU). see fc_ext_address_enable */
	uint8_t extendedAddress; /* Expected Extended Address byte of frames sent by transmitter (from ECU to neoVI).  see ext_address_enable */

	uint8_t blockSize; /* Block Size to report in flow control response */
	uint8_t stMin; /* Minimum seperation time (between consecutive frames) to report in flow control response */

	uint16_t cf_timeout; /* max timeout (ms) for waiting on consecutive frame.  Set this to N_CR_MAX's value in J2534 */

	union
	{
		struct
		{
			unsigned id_29_bit_enable : 1; /* Enables 29 bit arbId filter for frames (from ECU to neoVI) */
			unsigned fc_id_29_bit_enable : 1; /* Enables 29 bit arbId for Flow Control (from neoVI to ECU) */
			unsigned ext_address_enable : 1; /* Enables Extended Addressing (from ECU to neoVI) */
			unsigned fc_ext_address_enable : 1; /* Enables Extended Addressing (from neoVI to ECU) */
			unsigned enableFlowControlTransmission : 1; /*< Enables Flow Control frame transmission (from neoVI to ECU) */
			unsigned paddingEnable : 1; /* Enables padding */
			unsigned iscanFD : 1;
			unsigned isBRSEnabled : 1;
		};
		uint32_t flags;
	};
	uint8_t reserved[16];
} stCM_ISO157652_RxMessage;
#define stCM_ISO157652_RxMessage_SIZE 42

#pragma pack(pop)

typedef struct
{
	uint32_t StatusValue;
	uint32_t StatusMask;
	uint32_t Status2Value;
	uint32_t Status2Mask;
	uint32_t Header;
	uint32_t HeaderMask;
	uint32_t MiscData;
	uint32_t MiscDataMask;
	uint32_t ByteDataMSB;
	uint32_t ByteDataLSB;
	uint32_t ByteDataMaskMSB;
	uint32_t ByteDataMaskLSB;
	uint32_t HeaderLength;
	uint32_t ByteDataLength;
	uint32_t NetworkID;
	uint16_t FrameMaster;
	uint8_t bUseArbIdRangeFilter;
	uint8_t bStuff2;
	uint32_t ExpectedLength;
	uint32_t NodeID;
} spyFilterLong;
#define spyFilterLong_SIZE 72

#if !defined(VSPY3_GUI) && !defined(WIVI_EXPORT) && !defined(VS4A) && !defined(CORELIB_CMAKE) && !defined(NEOVI3GEXPLORER)
typedef int16_t descIdType;
#else
typedef uint32_t descIdType;
#endif

typedef struct _icsSpyMessage
{
	uint32_t StatusBitField;
	uint32_t StatusBitField2;
	uint32_t TimeHardware;
	uint32_t TimeHardware2;
	uint32_t TimeSystem;
	uint32_t TimeSystem2;
	uint8_t TimeStampHardwareID;
	uint8_t TimeStampSystemID;
	uint8_t NetworkID;
	uint8_t NodeID;
	uint8_t Protocol;
	uint8_t MessagePieceID;
	uint8_t ExtraDataPtrEnabled;
	uint8_t NumberBytesHeader;
	uint8_t NumberBytesData;
	uint8_t NetworkID2;
	descIdType DescriptionID;
	uint32_t ArbIDOrHeader;
	uint8_t Data[8];
	union
	{
		struct
		{
			uint32_t StatusBitField3;
			uint32_t StatusBitField4;
		};
		uint8_t AckBytes[8];
	};
	void* ExtraDataPtr;
	uint8_t MiscData;
	uint8_t Reserved[3];
} icsSpyMessage;

typedef struct _icsSpyMessageFlexRay
{
	uint32_t StatusBitField;
	uint32_t StatusBitField2;
	uint32_t TimeHardware;
	uint32_t TimeHardware2;
	uint32_t TimeSystem;
	uint32_t TimeSystem2;
	uint8_t TimeStampHardwareID;
	uint8_t TimeStampSystemID;
	uint8_t NetworkID;
	uint8_t NodeID;
	uint8_t Protocol;
	uint8_t MessagePieceID;
	uint8_t ExtraDataPtrEnabled;
	uint8_t NumberBytesHeader;
	uint8_t NumberBytesData;
	uint8_t NetworkID2;
	descIdType DescriptionID;
	union
	{
		uint32_t ArbIDOrHeader;
		struct
		{
			uint32_t id : 12;
			uint32_t res1 : 4;
			uint32_t cycle : 6;
			uint32_t chA : 1;
			uint32_t chB : 1;
			uint32_t startup : 1;
			uint32_t sync : 1;
			uint32_t null_frame : 1;
			uint32_t payload_preamble : 1;
			uint32_t frame_reserved : 1;
			uint32_t dynamic : 1;
		};
	};
	uint8_t Data[8];
	union
	{
		struct
		{
			uint32_t StatusBitField3;
			uint32_t StatusBitField4;
		};
		uint8_t AckBytes[8];
		struct
		{
			uint32_t hcrc_msbs : 3;
			uint32_t res2 : 5;
			uint32_t hcrc_lsbs : 8;
			uint32_t frame_len_12_5ns : 16;
			uint32_t fcrc0 : 8;
			uint32_t fcrc1 : 8;
			uint32_t fcrc2 : 8;
			uint32_t tss_len_12_5ns : 8;
		};
	};
	void* ExtraDataPtr;
	uint8_t MiscData;
	uint8_t Reserved[3];
} icsSpyMessageFlexRay;

typedef struct _icsSpyMessageMdio
{
	uint32_t StatusBitField;
	uint32_t StatusBitField2;
	uint32_t TimeHardware;
	uint32_t TimeHardware2;
	uint32_t TimeSystem;
	uint32_t TimeSystem2;
	uint8_t TimeStampHardwareID;
	uint8_t TimeStampSystemID;
	uint8_t NetworkID;
	uint8_t NodeID;
	uint8_t Protocol;
	uint8_t MessagePieceID;
	uint8_t ExtraDataPtrEnabled;
	uint8_t NumberBytesHeader;
	uint8_t NumberBytesData;
	uint8_t NetworkID2;
	descIdType DescriptionID;
	union
	{
		uint32_t ArbIDOrHeader;
		struct
		{
			uint32_t RegAddr : 16;
			uint32_t PhyAddr : 5;
			uint32_t DevType : 5;
			uint32_t : 6;
		};
	};
	uint8_t Data[8];
	union
	{
		struct
		{
			uint32_t StatusBitField3;
			uint32_t StatusBitField4;
		};
		uint8_t AckBytes[8];
	};
	void* ExtraDataPtr;
	uint8_t MiscData;
	uint8_t Reserved[3];
} icsSpyMessageMdio;

typedef struct _icsSpyMessagewBMS
{
	uint32_t StatusBitField;
	uint32_t StatusBitField2;
	uint32_t TimeHardware;
	uint32_t TimeHardware2;
	uint32_t TimeSystem;
	uint32_t TimeSystem2;
	uint8_t TimeStampHardwareID;
	uint8_t TimeStampSystemID;
	uint8_t NetworkID;
	uint8_t NodeID;
	uint8_t Protocol;
	uint8_t MessagePieceID;
	uint8_t ExtraDataPtrEnabled;
	uint8_t NumberBytesHeader;
	uint8_t NumberBytesData;
	uint8_t NetworkID2;
	descIdType DescriptionID;
	union
	{
		uint32_t ArbIDOrHeader;
		struct
		{
			uint32_t : 8;
			uint32_t PacketType : 8;
			uint32_t PacketID : 8;
			uint32_t PacketSource : 8;
		};
	};
	uint8_t Data[8];
	union
	{
		struct
		{
			union
			{
				uint32_t StatusBitField3;
				struct
				{
					uint32_t APICode : 8;
					uint32_t : 24;
				};
			};
			uint32_t StatusBitField4;
		};
		uint8_t AckBytes[8];
	};
	void* ExtraDataPtr;
	uint8_t MiscData;
	uint8_t Reserved[3];
} icsSpyMessagewBMS;

#if defined(VSPY3_GUI) || defined(WIVI_EXPORT) || defined(VS4A) || defined(CORELIB_CMAKE) || defined(NEOVI3GEXPLORER)
#if defined(IS_64BIT_SYSTEM)
#define icsSpyMessage_SIZE 80
#else
#define icsSpyMessage_SIZE 68
#endif
#else
#if defined(IS_64BIT_SYSTEM)
#define icsSpyMessage_SIZE 72
#else
#define icsSpyMessage_SIZE 64
#endif
#endif

typedef struct _icsSpyMessageLong
{
	uint32_t StatusBitField;
	uint32_t StatusBitField2;
	uint32_t TimeHardware;
	uint32_t TimeHardware2;
	uint32_t TimeSystem;
	uint32_t TimeSystem2;
	uint8_t TimeStampHardwareID;
	uint8_t TimeStampSystemID;
	uint8_t NetworkID;
	uint8_t NodeID;
	uint8_t Protocol;
	uint8_t MessagePieceID;
	uint8_t ExtraDataPtrEnabled;
	uint8_t NumberBytesHeader;
	uint8_t NumberBytesData;
	uint8_t NetworkID2;
	descIdType DescriptionID;
	uint32_t ArbIDOrHeader;
	uint32_t DataMsb;
	uint32_t DataLsb;
	union
	{
		struct
		{
			uint32_t StatusBitField3;
			uint32_t StatusBitField4;
		};
		uint8_t AckBytes[8];
	};
	void* ExtraDataPtr;
	uint8_t MiscData;
	uint8_t Reserved[3];
} icsSpyMessageLong;
#define icsSpyMessageLong_SIZE icsSpyMessage_SIZE

typedef struct _icsSpyMessageJ1850
{
	uint32_t StatusBitField;
	uint32_t StatusBitField2;
	uint32_t TimeHardware;
	uint32_t TimeHardware2;
	uint32_t TimeSystem;
	uint32_t TimeSystem2;
	uint8_t TimeStampHardwareID;
	uint8_t TimeStampSystemID;
	uint8_t NetworkID;
	uint8_t NodeID;
	uint8_t Protocol;
	uint8_t MessagePieceID;
	uint8_t ExtraDataPtrEnabled;
	uint8_t NumberBytesHeader;
	uint8_t NumberBytesData;
	uint8_t NetworkID2;
	descIdType DescriptionID;
	uint8_t Header[4];
	uint8_t Data[8];
	union
	{
		struct
		{
			uint32_t StatusBitField3;
			uint32_t StatusBitField4;
		};
		uint8_t AckBytes[8];
	};
	void* ExtraDataPtr;
	uint8_t MiscData;
	uint8_t Reserved[3];
} icsSpyMessageJ1850;
#define icsSpyMessageJ1850_SIZE icsSpyMessage_SIZE

typedef struct _icsSpyMessageVSB
{
	uint32_t StatusBitField;
	uint32_t StatusBitField2;
	uint32_t TimeHardware;
	uint32_t TimeHardware2;
	uint32_t TimeSystem;
	uint32_t TimeSystem2;
	uint8_t TimeStampHardwareID;
	uint8_t TimeStampSystemID;
	uint8_t NetworkID;
	uint8_t NodeID;
	uint8_t Protocol;
	uint8_t MessagePieceID;
	uint8_t ExtraDataPtrEnabled;
	uint8_t NumberBytesHeader;
	uint8_t NumberBytesData;
	uint8_t NetworkID2;
	int16_t DescriptionID;
	uint32_t ArbIDOrHeader;
	uint8_t Data[8];
	union
	{
		struct
		{
			uint32_t StatusBitField3;
			uint32_t StatusBitField4;
		};
		uint8_t AckBytes[8];
	};
	uint32_t ExtraDataPtr; //in the context of a vsb file, this is a size, not a pointer
	uint8_t MiscData;
	uint8_t Reserved[3];
} icsSpyMessageVSB;
#define icsSpyMessageVSB_SIZE 64

/**
  * The network of a message is a combination of both NetworkID and NetworkID2.
  * Be sure to use ICS_GET_NETWORKID and ICS_SET_NETWORKID, especially for slave VNETs.
  */

#define ICS_GET_NETWORKID(m) ((((unsigned int)m.NetworkID2) << 8) | m.NetworkID)
#define ICS_SET_NETWORKID(m, X) \
	do                          \
	{                           \
		m.NetworkID = X;        \
		m.NetworkID2 = X >> 8;  \
	} while (0)


#pragma pack(push)
#pragma pack(1)
typedef struct _ethernetNetworkStatus_t
{
	uint16_t networkId;
	uint8_t linkStatus;
	uint8_t linkFullDuplex;
	uint8_t linkSpeed; // see ethLinkSpeed
	uint8_t linkMode; // for automotive networks - see opEthLinkMode
} ethernetNetworkStatus_t;
#pragma pack(pop)

typedef struct
{
	uint8_t backupPowerGood;
	uint8_t backupPowerEnabled;
	uint8_t usbHostPowerEnabled;
	uint8_t ethernetActivationLineEnabled;
	ethernetNetworkStatus_t ethernetStatus;
} icsFire2DeviceStatus;

typedef struct
{
	uint8_t ethernetActivationLineEnabled;
	ethernetNetworkStatus_t ethernetStatus;
	uint8_t unused;
} icsFire2VnetDeviceStatus;

typedef struct
{
	uint8_t ethernetActivationLineEnabled;
	ethernetNetworkStatus_t ethernetStatus;
	uint8_t unused;
} icsVcan4DeviceStatus;

typedef struct
{
	uint8_t ethernetActivationLineEnabled;
	ethernetNetworkStatus_t ethernetStatus;
	uint8_t unused;
} icsFlexVnetzDeviceStatus;

typedef struct
{
	uint8_t ethernetActivationLineEnabled;
	ethernetNetworkStatus_t ethernetStatus[16];
	uint8_t numNetworks;
	uint8_t reserved;
	uint8_t ethernetActivationLineEnabled_2;
} icsFire3DeviceStatus;

typedef struct
{
	ethernetNetworkStatus_t ethernetStatus[RADJUPITER_NUM_PORTS - 1];
} icsRadJupiterDeviceStatus;

typedef struct
{
	ethernetNetworkStatus_t ethernetStatus;
} icsVcan4IndustrialDeviceStatus;

typedef struct
{
	ethernetNetworkStatus_t ethernetStatus[RADEPSILON_NUM_PORTS];
} icsRadEpsilonDeviceStatus;

typedef struct
{
	ethernetNetworkStatus_t ethernetStatus;
} icsRadBMSDeviceStatus;

#pragma pack(push)
#pragma pack(4)

typedef union
{
	icsFire2DeviceStatus fire2Status;
	icsVcan4DeviceStatus vcan4Status;
	icsFlexVnetzDeviceStatus flexVnetzStatus;
	icsFire3DeviceStatus fire3Status;
	icsRadJupiterDeviceStatus jupiterStatus;
	icsRadEpsilonDeviceStatus epsilonStatus;
	icsVcan4IndustrialDeviceStatus vcan4indStatus;
	icsRadBMSDeviceStatus radBMSStatus;
} icsDeviceStatus;

#pragma pack(pop)

typedef struct
{
	char szName[128]; //Adaptor name -  ASCII Null terminated
	char szDeviceName[64]; //Device name	- ASCII Null terminated
	unsigned long Status; //Adaptor Status, 0 for disabled, 1 for enabled
	unsigned char
		bMAC_Address[6]; // The Media Access Control (MAC) Address  of the Network interface in the PC that is to be connected to the vehicle.
	unsigned char bIPV6_Address
		[16]; //The Ipv6 address assigned to the Network interface. No compressed or short form notation// If not available, all bytes are set to zero to imply the absence of an address.
	unsigned char bIPV4_Address[4]; // The Ipv4 address assigned to the Network interface. If not available, all bytes are set to zero.
	unsigned long EthernetPinConfig;
} NDIS_ADAPTER_INFORMATION;

#define MAX_PHY_REG_PKT_ENTRIES 128
#define PHY_REG_PKT_VERSION 1
typedef struct SPhyRegPktHdr
{
	uint16_t numEntries;
	uint8_t version;
	uint8_t entryBytes;
} PhyRegPktHdr_t;

#define MAX_PHY_SETTINGS_STRUCT 128
#define MAX_NUMBYTES_PHYSETTINGS MAX_PHY_SETTINGS_STRUCT * sizeof(PhyRegPktHdr_t)

typedef struct SPhyRegPktClause22Mess
{
	uint8_t phyAddr; //5 bits
	uint8_t page; //8 bits
	uint16_t regAddr; //5 bits
	uint16_t regVal;
} PhyRegPktClause22Mess_t; //6 bytes

typedef struct SPhyRegPktClause45Mess
{
	uint8_t port; //5 bits    uint8_t device; //5 bits
	uint8_t device; //5 bits
	uint16_t regAddr;
	uint16_t regVal;
} PhyRegPktClause45Mess_t; //6 bytes

typedef enum SPhyRegPktStatus
{
	PHYREG_SUCCESS = 0,
	PHYREG_FAILURE,
	PHYREG_INVALID_MDIO_BUS_INDEX,
	PHYREG_INVALID_PHY_ADDR,
	PHYREG_UNSUPPORTED_MDIO_CLAUSE,
	PHYREG_RESERVED1,
	PHYREG_RESERVED2,
	PHYREG_RESERVED3
} PhyRegPktStatus_t;

typedef enum SPhyRegPktRw
{
	PHYREG_READ = 0,
	PHYREG_WRITE,
	PHYREG_BOTH
} PhyRegPktRw_t;

typedef struct SPhyRegPkt
{
	union
	{
		struct
		{
			uint16_t Enabled : 1;
			uint16_t WriteEnable : 1;
			uint16_t Clause45Enable : 1;
			uint16_t status : 3;
			uint16_t reserved : 2;
			uint16_t BusIndex : 4;
			uint16_t version : 4;
		};
		uint16_t flags;
	};

	union
	{
		PhyRegPktClause22Mess_t clause22;
		PhyRegPktClause45Mess_t clause45;
	};
} PhyRegPkt_t;

typedef enum
{
	networkDWCAN01,
	networkDWCAN02,
	networkDWCAN03,
	networkDWCAN04,
	networkDWCAN05,
	networkDWCAN06,
	networkDWCAN07,
	networkDWCAN08,
	networkTerminationDWCAN01,
	networkTerminationDWCAN02,
	networkTerminationDWCAN03,
	networkTerminationDWCAN04,
	networkTerminationDWCAN05,
	networkTerminationDWCAN06,
	networkTerminationDWCAN07,
	networkTerminationDWCAN08,
	enhancedFlashDriver,
	rtcCalibration,
	rtcClosedLoopCalibration,
	cmp,
	NUM_VALID_DEVICE_FEATURES,
	supportedFeatureMax = 0xFFFF,
} DeviceFeature;

typedef enum AccessoryErrorType
{
	AccessoryOperationError = 0,
	AccessoryOperationSuccess = 1,
	AccessoryFlashingInitError = 2,
	AccessoryFlashingEraseError = 3,
	AccessoryFlashingWriteError = 4,
	AccessoryFlashingReadError = 5,
	AccessoryFlashingVerifyError = 6,
	AccessoryFlashingDeinitError = 7,
	AccessoryFlashingInvalidHardware = 8,
	AccessoryFlashingInvalidDataFile = 9,
	AccessoryGetVersionError = 10,
	AccessoryIndexError = 11,
	AccessoryParamApiVersionError = 12,
	AccessoryParamSizeMismatchError = 13,
	AccessoryParameterNull = 14,
} AccessoryOperationErrorType;

typedef enum _EDevNameType
{
	EDevNameTypeDefault,
	EDevNameTypeNoSerial,
	EDevNameTypeTCP,
	EDevNameTypeTCPShort,
} EDevNameType;

#pragma pack(push, 1)
typedef struct _FlashAccessoryFirmwareParams
{
	// set to FlashAccessoryFirmwareAPIVersion - This should increment anytime there is a breakage of ABI / API.
	uint32_t apiVersion;
	// sizeof(FlashAccessoryFirmwareParams)
	uint32_t size;
	// Device specific Index - we should have an enum/preprocess define for all of these
	uint8_t index;
	// firmware data
	uint8_t* data;
	// size of firmware data
	uint32_t dataSize;
} FlashAccessoryFirmwareParams;
#pragma pack(pop)
#if defined(IS_64BIT_SYSTEM)
#define FlashAccessoryFirmwareParams_SIZE (21)
#else
#define FlashAccessoryFirmwareParams_SIZE (17)
#endif


typedef enum _flashAccessoryIndex
{
	FLASH_ACCESSORY_EPSILON_10G_PHY1,
	FLASH_ACCESSORY_EPSILON_10G_PHY2,
	FLASH_ACCESSORY_EPSILON_SWITCH_A,
	FLASH_ACCESSORY_EPSILON_SWITCH_B,
} flashAccessoryIndex;

typedef enum _epsilon10GPHYFW
{
	FLASH_ACCESSORY_EPSILON_10G_PHY_FW_0_3_7_0
} epsilon10GPHYFW;

// Update this assert when we add features to this enum
//static_assert(NUM_VALID_DEVICE_FEATURES == (networkTerminationDWCAN08 + 1));
//static_assert(NUM_VALID_DEVICE_FEATURES <= supportedFeatureMax);
#define NUM_DEVICE_FEATURE_BITFIELDS ((NUM_VALID_DEVICE_FEATURES + 31) / 32)


#if !defined(INTREPID_NO_CHECK_STRUCT_SIZE) && !defined(ics_static_assert)

#if (defined(__cplusplus) && (__cplusplus > 199711L))
#define ics_static_assert(e, msg) static_assert(e, msg)
#define CHECK_STRUCT_SIZE(X) ics_static_assert(sizeof(X) == X##_SIZE, #X " is the wrong size");
#else
#define ASSERT_CONCAT_(a, b) a##b
#define ASSERT_CONCAT(a, b) ASSERT_CONCAT_(a, b)
#define ics_static_assert(e, msg)                                \
	enum                                                         \
	{                                                            \
		ASSERT_CONCAT(assert_line_, __LINE__) = 1 / (int)(!!(e)) \
	}
#define CHECK_STRUCT_SIZE(X) ics_static_assert(sizeof(X) == X##_SIZE, #X " is the wrong size");
#endif


CHECK_STRUCT_SIZE(CAN_SETTINGS);
CHECK_STRUCT_SIZE(CANFD_SETTINGS);
CHECK_STRUCT_SIZE(SWCAN_SETTINGS);
CHECK_STRUCT_SIZE(LIN_SETTINGS);
CHECK_STRUCT_SIZE(ISO9141_KEYWORD2000__INIT_STEP);
CHECK_STRUCT_SIZE(ISO9141_KEYWORD2000_SETTINGS);
CHECK_STRUCT_SIZE(UART_SETTINGS);
CHECK_STRUCT_SIZE(J1708_SETTINGS);
CHECK_STRUCT_SIZE(SRedSettings);
CHECK_STRUCT_SIZE(STextAPISettings);
CHECK_STRUCT_SIZE(stChipVersions);
CHECK_STRUCT_SIZE(SNeoMostGatewaySettings);
CHECK_STRUCT_SIZE(OP_ETH_GENERAL_SETTINGS);
CHECK_STRUCT_SIZE(OP_ETH_SETTINGS);
CHECK_STRUCT_SIZE(ETHERNET_SETTINGS);
CHECK_STRUCT_SIZE(ETHERNET_SETTINGS2);
CHECK_STRUCT_SIZE(ETHERNET10G_SETTINGS);
CHECK_STRUCT_SIZE(ETHERNET10T1S_SETTINGS);
CHECK_STRUCT_SIZE(ETHERNET10T1S_SETTINGS_EXT);
CHECK_STRUCT_SIZE(ETHERNET10T1L_SETTINGS);
CHECK_STRUCT_SIZE(MACSEC_SETTINGS);
CHECK_STRUCT_SIZE(LOGGER_SETTINGS);
CHECK_STRUCT_SIZE(DISK_SETTINGS);
CHECK_STRUCT_SIZE(SERDESCAM_SETTINGS);
CHECK_STRUCT_SIZE(SERDESPOC_SETTINGS);
CHECK_STRUCT_SIZE(SERDESGEN_SETTINGS);
CHECK_STRUCT_SIZE(RAD_REPORTING_SETTINGS);
CHECK_STRUCT_SIZE(CANTERM_SETTINGS);
CHECK_STRUCT_SIZE(SFireSettings);
CHECK_STRUCT_SIZE(SFireVnetSettings);
CHECK_STRUCT_SIZE(SCyanSettings);
CHECK_STRUCT_SIZE(SVCAN3Settings);
CHECK_STRUCT_SIZE(SVCAN4Settings);
CHECK_STRUCT_SIZE(SECUSettings);
CHECK_STRUCT_SIZE(SPendantSettings);
CHECK_STRUCT_SIZE(SRADGalaxySettings);
CHECK_STRUCT_SIZE(SRADStar2Settings);
CHECK_STRUCT_SIZE(GLOBAL_SETTINGS);
CHECK_STRUCT_SIZE(stCM_ISO157652_TxMessage);
CHECK_STRUCT_SIZE(stCM_ISO157652_RxMessage);
CHECK_STRUCT_SIZE(spyFilterLong);
CHECK_STRUCT_SIZE(icsSpyMessage);
CHECK_STRUCT_SIZE(icsSpyMessageLong);
CHECK_STRUCT_SIZE(icsSpyMessageJ1850);
CHECK_STRUCT_SIZE(icsSpyMessageVSB);
CHECK_STRUCT_SIZE(ISO15765_2015_TxMessage);
CHECK_STRUCT_SIZE(TIMESYNC_ICSHARDWARE_SETTINGS);
CHECK_STRUCT_SIZE(SRADMoon2Settings);
CHECK_STRUCT_SIZE(SRADGigastarSettings);
CHECK_STRUCT_SIZE(SRADGalaxy2Settings);
CHECK_STRUCT_SIZE(SDiskStructure);
CHECK_STRUCT_SIZE(SDiskFormatProgress);
CHECK_STRUCT_SIZE(SDiskStatus);
CHECK_STRUCT_SIZE(CANHubSettings);
CHECK_STRUCT_SIZE(SNeoECU12Settings);
CHECK_STRUCT_SIZE(VCAN4IndSettings);
CHECK_STRUCT_SIZE(SRADJupiterSettings);
CHECK_STRUCT_SIZE(SFire3Settings);
CHECK_STRUCT_SIZE(SRed2Settings);
CHECK_STRUCT_SIZE(SRADA2BSettings);
CHECK_STRUCT_SIZE(A2BMonitorSettings);
CHECK_STRUCT_SIZE(SRADEpsilonSettings);
CHECK_STRUCT_SIZE(RAD_GPTP_SETTINGS);
CHECK_STRUCT_SIZE(SRADBMSSettings);
CHECK_STRUCT_SIZE(SRADMoon3Settings);
CHECK_STRUCT_SIZE(SRADGeminiSettings);
CHECK_STRUCT_SIZE(SFire3FlexraySettings);
CHECK_STRUCT_SIZE(SFire3T1sLinSettings);
CHECK_STRUCT_SIZE(CANHubSettings);
CHECK_STRUCT_SIZE(SRADCometSettings);
CHECK_STRUCT_SIZE(SRADComet3Settings);
CHECK_STRUCT_SIZE(SRADGigastar2Settings);
CHECK_STRUCT_SIZE(SRADMoonT1SSettings);
CHECK_STRUCT_SIZE(SNeoVIConnectSettings);
CHECK_STRUCT_SIZE(FlashAccessoryFirmwareParams);

#endif /* INTREPID_NO_CHECK_STRUCT_SIZE */

#endif /* _ICSNVC40_H */
