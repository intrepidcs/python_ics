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



// MSVC++ 10.0 _MSC_VER == 1600 64-bit version doesn't allow multi-line #if directives...
#if defined(_WIN64) || defined(__x86_64__) || defined(__aarch64__) || defined(__x86_64__) || defined(__LP64__) || defined(_M_AMD64) || \
	defined(_M_IA64) || defined(__PPC64__)
#define IS_64BIT_SYSTEM
#endif

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
#define NEODEVICE_ECU_AVB (0x00000002)
#define NEODEVICE_RADSUPERMOON (0x00000003)
#define NEODEVICE_DW_VCAN (0x00000004)
#define NEODEVICE_RADMOON2 (0x00000005)
#define NEODEVICE_RADGIGALOG (0x00000006) /* AKA RADMARS */
#define NEODEVICE_VCAN41 (0x00000007)
#define NEODEVICE_FIRE (0x00000008)
#define NEODEVICE_RADPLUTO (0x00000009)
#define NEODEVICE_VCAN42_EL (0x0000000a)
#define NEODEVICE_RADIO_CANHUB (0x0000000b)
#define NEODEVICE_NEOECU12 (0x0000000c)
#define NEODEVICE_OBD2_LC (0x0000000d)
#define NEODEVICE_RAD_MOON_DUO (0x0000000e)
#define NEODEVICE_FIRE3 (0x0000000f)
#define NEODEVICE_VCAN3 (0x00000010)
#define NEODEVICE_RADJUPITER (0x00000011)
#define NEODEVICE_VCAN4_IND (0x00000012)
#define NEODEVICE_GIGASTAR (0x00000013)
#define NEODEVICE_RED2 (0x00000014)
#define NEODEVICE_FIRE2_REDLINE (0x00000015)
#define NEODEVICE_ETHER_BADGE (0x00000016)
#define NEODEVICE_RAD_A2B (0x00000017)
#define NEODEVICE_RADEPSILON (0x00000018)
#define NEODEVICE_OBD2_SIM_DOIP (0x00000019)
#define NEODEVICE_OBD2_DEV (0x0000001a)
#define NEODEVICE_ECU22 (0x0000001b)
#define NEODEVICE_RADEPSILON_T (0x0000001c)
#define NEODEVICE_RADEPSILON_EXPRESS (0x0000001d)
#define NEODEVICE_RADPROXIMA (0x0000001e)
#define NEODEVICE_NEW_DEVICE_58 (0x0000001f)
// I'm not sure what was 0x20 anymore, but we'll skip it to be safe
#define NEODEVICE_NEW_DEVICE_59 (0x00000021)
#define NEODEVICE_RAD_BMS (0x00000022)
#define NEODEVICE_RED (0x00000040)
#define NEODEVICE_ECU (0x00000080)
#define NEODEVICE_IEVB (0x00000100)
#define NEODEVICE_PENDANT (0x00000200)
#define NEODEVICE_OBD2_PRO (0x00000400)
#define NEODEVICE_ECUCHIP_UART (0x00000800)
#define NEODEVICE_PLASMA (0x00001000)
#define NEODEVICE_DONT_REUSE0 (0x00002000)//NEODEVICE_FIRE_VNET
#define NEODEVICE_NEOANALOG (0x00004000)
#define NEODEVICE_CT_OBD (0x00008000)
#define NEODEVICE_DONT_REUSE1 (0x00010000)//NEODEVICE_PLASMA_1_12
#define NEODEVICE_DONT_REUSE2 (0x00020000)//NEODEVICE_PLASMA_1_13
#define NEODEVICE_ION (0x00040000)
#define NEODEVICE_RADSTAR (0x00080000)
#define NEODEVICE_DONT_REUSE3 (0x00100000)//NEODEVICE_ION3
#define NEODEVICE_VCAN44 (0x00200000)
#define NEODEVICE_VCAN42 (0x00400000)
#define NEODEVICE_CMPROBE (0x00800000)
#define NEODEVICE_EEVB (0x01000000)
#define NEODEVICE_VCANRF (0x02000000)
#define NEODEVICE_FIRE2 (0x04000000)
#define NEODEVICE_FLEX (0x08000000)
#define NEODEVICE_RADGALAXY (0x10000000)
#define NEODEVICE_RADSTAR2 (0x20000000)
#define NEODEVICE_VIVIDCAN (0x40000000)
#define NEODEVICE_OBD2_SIM (0x80000000)
#define NEODEVICE_ANY_PLASMA (NEODEVICE_PLASMA)
#define NEODEVICE_ANY_ION (NEODEVICE_ION)
#define NEODEVICE_NEOECUCHIP NEODEVICE_IEVB
//clang-format on

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

/* Bitmasks for StatusBitField member of icsSpyMessage */
#define SPY_STATUS_GLOBAL_ERR 0x01
#define SPY_STATUS_TX_MSG 0x02
#define SPY_STATUS_XTD_FRAME 0x04
#define SPY_STATUS_REMOTE_FRAME 0x08
#define SPY_STATUS_CRC_ERROR 0x10
#define SPY_STATUS_CAN_ERROR_PASSIVE 0x20
#define SPY_STATUS_HEADERCRC_ERROR 0x20
#define SPY_STATUS_INCOMPLETE_FRAME 0x40
#define SPY_STATUS_LOST_ARBITRATION 0x80
#define SPY_STATUS_UNDEFINED_ERROR 0x100
#define SPY_STATUS_CAN_BUS_OFF 0x200
#define SPY_STATUS_BUS_RECOVERED 0x400
#define SPY_STATUS_BUS_SHORTED_PLUS 0x800
#define SPY_STATUS_BUS_SHORTED_GND 0x1000
#define SPY_STATUS_CHECKSUM_ERROR 0x2000
#define SPY_STATUS_BAD_MESSAGE_BIT_TIME_ERROR 0x4000
#define SPY_STATUS_TX_NOMATCH 0x8000
#define SPY_STATUS_COMM_IN_OVERFLOW 0x10000
#define SPY_STATUS_EXPECTED_LEN_MISMATCH 0x20000
#define SPY_STATUS_MSG_NO_MATCH 0x40000
#define SPY_STATUS_BREAK 0x80000
#define SPY_STATUS_AVSI_REC_OVERFLOW 0x100000
#define SPY_STATUS_TEST_TRIGGER 0x200000
#define SPY_STATUS_AUDIO_COMMENT 0x400000
#define SPY_STATUS_GPS_DATA 0x800000
#define SPY_STATUS_ANALOG_DIGITAL_INPUT 0x1000000
#define SPY_STATUS_TEXT_COMMENT 0x2000000
#define SPY_STATUS_NETWORK_MESSAGE_TYPE 0x4000000
#define SPY_STATUS_VSI_TX_UNDERRUN 0x8000000
#define SPY_STATUS_VSI_IFR_CRC_BIT 0x10000000
#define SPY_STATUS_INIT_MESSAGE 0x20000000
#define SPY_STATUS_LIN_MASTER 0x20000000
#define SPY_STATUS_CANFD 0x20000000
#define SPY_STATUS_A2B_CONTROL 0x80000
#define SPY_STATUS_A2B_SCF_VALID_WAITING 0x08
#define SPY_STATUS_A2B_MONITOR 0x20000000
#define SPY_STATUS_A2B_UPSTREAM 0x40000000
#define SPY_STATUS_PDU 0x10000000
#define SPY_STATUS_FLEXRAY_PDU SPY_STATUS_PDU
#define SPY_STATUS_HIGH_SPEED 0x40000000
#define SPY_STATUS_EXTENDED 0x80000000 /* if this bit is set than decode StatusBitField3 in AckBytes */
#define SPY_STATUS_FLEXRAY_PDU_UPDATE_BIT_SET 0x40000000
#define SPY_STATUS_FLEXRAY_PDU_NO_UPDATE_BIT 0x08

/* Bitmasks for StatusBitField2 member of icsSpyMessage */
#define SPY_STATUS2_HAS_VALUE 0x1
#define SPY_STATUS2_VALUE_IS_BOOLEAN 0x2
#define SPY_STATUS2_HIGH_VOLTAGE 0x4
#define SPY_STATUS2_LONG_MESSAGE 0x8
#define SPY_STATUS2_GLOBAL_CHANGE 0x10000
#define SPY_STATUS2_ERROR_FRAME 0x20000
#define SPY_STATUS2_END_OF_LONG_MESSAGE 0x100000

/* I2C Specific - check protocol before handling  */
#define SPY_STATUS2_I2C_ERR_TIMEOUT 0x200000
#define SPY_STATUS2_I2C_ERR_NACK 0x400000
#define SPY_STATUS2_I2C_DIR_READ 0x800000

/* LIN/ISO Specific - check protocol before handling  */
#define SPY_STATUS2_LIN_ERR_RX_BREAK_NOT_0 0x200000
#define SPY_STATUS2_LIN_ERR_RX_BREAK_TOO_SHORT 0x400000
#define SPY_STATUS2_LIN_ERR_RX_SYNC_NOT_55 0x800000
#define SPY_STATUS2_LIN_ERR_RX_DATA_GREATER_8 0x1000000
#define SPY_STATUS2_LIN_ERR_TX_RX_MISMATCH 0x2000000
#define SPY_STATUS2_LIN_ERR_MSG_ID_PARITY 0x4000000
#define SPY_STATUS2_ISO_FRAME_ERROR 0x8000000
#define SPY_STATUS2_LIN_SYNC_FRAME_ERROR 0x8000000
#define SPY_STATUS2_ISO_OVERFLOW_ERROR 0x10000000
#define SPY_STATUS2_LIN_ID_FRAME_ERROR 0x10000000
#define SPY_STATUS2_ISO_PARITY_ERROR 0x20000000
#define SPY_STATUS2_LIN_SLAVE_BYTE_ERROR 0x20000000
#define SPY_STATUS2_RX_TIMEOUT_ERROR 0x40000000
#define SPY_STATUS2_LIN_NO_SLAVE_DATA 0x80000000
#define SPY_STATUS3_LIN_JUST_BREAK_SYNC 0x1
#define SPY_STATUS3_LIN_SLAVE_DATA_TOO_SHORT 0x2
#define SPY_STATUS3_LIN_ONLY_UPDATE_SLAVE_TABLE_ONCE 0x4

/* MOST Specific - check protocol before handling */
#define SPY_STATUS2_MOST_PACKET_DATA 0x200000
#define SPY_STATUS2_MOST_STATUS 0x400000 /* reflects changes in light/lock/MPR/SBC/etc... */
#define SPY_STATUS2_MOST_LOW_LEVEL 0x800000 /* MOST low level message, allocs, deallocs, remote requests...*/
#define SPY_STATUS2_MOST_CONTROL_DATA 0x1000000
#define SPY_STATUS2_MOST_MHP_USER_DATA 0x2000000 /* MOST HIGH User Data Frame */
#define SPY_STATUS2_MOST_MHP_CONTROL_DATA 0x4000000 /* MOST HIGH Control Data */
#define SPY_STATUS2_MOST_I2S_DUMP 0x8000000
#define SPY_STATUS2_MOST_TOO_SHORT 0x10000000
#define SPY_STATUS2_MOST_MOST50 0x20000000 /* absence of MOST50 and MOST150 implies it's MOST25 */
#define SPY_STATUS2_MOST_MOST150 0x40000000
#define SPY_STATUS2_MOST_CHANGED_PAR 0x80000000 /* first byte in ack reflects what changed. */

/* Ethernet Specific - check protocol before handling */
#define SPY_STATUS2_ETHERNET_CRC_ERROR 0x200000
#define SPY_STATUS2_ETHERNET_FRAME_TOO_SHORT 0x400000
#define SPY_STATUS2_ETHERNET_FCS_AVAILABLE \
	0x800000 /* This frame contains FCS (4 bytes) obtained from ICS Ethernet hardware (ex. RAD-STAR) */
#define SPY_STATUS2_ETHERNET_NO_PADDING 0x1000000
#define SPY_STATUS2_ETHERNET_PREEMPTION_ENABLED 0x2000000
#define SPY_STATUS2_ETHERNET_UPDATE_CHECKSUMS 0x4000000
#define SPY_STATUS2_ETHERNET_MANUALFCS_ENABLED 0x8000000
#define SPY_STATUS2_ETHERNET_FCS_VERIFIED 0x10000000

/* FlexRay Specific - check protocol before handling */
#define SPY_STATUS2_FLEXRAY_TX_AB 0x200000
#define SPY_STATUS2_FLEXRAY_TX_AB_NO_A 0x400000
#define SPY_STATUS2_FLEXRAY_TX_AB_NO_B 0x800000
#define SPY_STATUS2_FLEXRAY_TX_AB_NO_MATCH 0x1000000
#define SPY_STATUS2_FLEXRAY_NO_CRC 0x2000000
#define SPY_STATUS2_FLEXRAY_NO_HEADERCRC 0x4000000

/* CAN/CAN-FD Specific - check protocol before handling */
#define SPY_STATUS2_CAN_ISO15765_LOGICAL_FRAME 0x200000
#define SPY_STATUS2_CAN_HAVE_LINK_DATA 0x400000

/* CAN-FD Specific - check protocol before handling */
#define SPY_STATUS3_CANFD_ESI 0x01
#define SPY_STATUS3_CANFD_IDE 0x02
#define SPY_STATUS3_CANFD_RTR 0x04
#define SPY_STATUS3_CANFD_FDF 0x08
#define SPY_STATUS3_CANFD_BRS 0x10

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
	uint32_t Status;// Bitfield, see defs above

// Option bit flags
#define MAIN_VNET (0x01)
#define SLAVE_VNET_A (0x02)
#define SLAVE_VNET_B (0x04)
#define WIFI_CONNECTION (0x08)
#define REGISTER_BY_SERIAL (0x10)
	uint32_t Options;

	void* pAvailWIFINetwork;
	void* pWIFIInterfaceInfo;

	int isEthernetDevice;

	uint8_t MACAddress[6];
	uint16_t hardwareRev;
	uint16_t revReserved;
	uint32_t Reserved[6];// may be expanded in future revisions

} NeoDeviceEx;

typedef union tagOptionsOpenNeoEx {
	struct
	{
		int32_t iNetworkID; /* Network ID indicating which CAN network to communicate over */
	} CANOptions;

	uint32_t Reserved[16]; /* may be expanded in future revisions */
} OptionsOpenNeoEx, *POptionsOpenNeoEx;

typedef union tagOptionsFindNeoEx {
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
	uint8_t innerFrameDelay25us;
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
	union {
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
	union {
		struct
		{
			unsigned bExtended : 1;
			unsigned : 31;
		};
		uint32_t DWord;
	} can1_options;
	uint32_t can2_tx_id;
	uint32_t can2_rx_id;
	union {
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
	union {
		struct
		{
			unsigned bExtended : 1;
			unsigned : 31;
		};
		uint32_t DWord;
	} can3_options;

	uint32_t can4_tx_id;
	uint32_t can4_rx_id;
	union {
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

typedef union _stChipVersions {
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
		uint8_t mpic_maj;
		uint8_t mpic_min;
	} vcanrf_versions;

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
		uint8_t zynq_core_major;
		uint8_t zynq_core_minor;
	} cmprobe_versions;

	struct
	{
		uint8_t mchip_major;
		uint8_t mchip_minor;
		uint8_t schip_major;
		uint8_t schip_minor;
		uint8_t core_major;
		uint8_t core_minor;
	} obd2pro_versions;

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
		uint8_t mchip_major;
		uint8_t mchip_minor;
	} neoecu_avb_versions;
	struct
	{
		uint8_t zynq_core_major;
		uint8_t zynq_core_minor;
	} radsupermoon_versions;
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
	} pluto_versions;
	struct
	{
		uint8_t zynq_core_major;
		uint8_t zynq_core_minor;
	} radgigalog_versions;

	struct
	{
		uint8_t zynq_core_major;
		uint8_t zynq_core_minor;
	} radgigalog3_versions;

	struct
	{
		uint8_t zynq_core_major;
		uint8_t zynq_core_minor;
	} radgigastar_versions;

	struct
	{
		uint8_t zynq_core_major;
		uint8_t zynq_core_minor;
	} radgigastar_usbz_versions;

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
	} fire3_versions;

	struct
	{
		uint8_t mchip_major;
		uint8_t mchip_minor;
	} rad_moon_duo_versions;

	struct
	{
		uint8_t mchip_major;
		uint8_t mchip_minor;
		uint8_t schip_major;
		uint8_t schip_minor;
	} obd2dev_versions;

	struct
	{
		uint8_t mchip_major;
		uint8_t mchip_minor;
	} ether_badge_versions;

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
	uint8_t reserved0[3];
	uint16_t tapPair0;
	uint16_t tapPair1;
	uint16_t tapPair2;
	uint16_t tapPair3;
	uint16_t tapPair4;
	uint16_t tapPair5;
	union {
		struct
		{
			unsigned bTapEnSwitch : 1;
			unsigned bTapEnPtp : 1;
			unsigned bEnReportLinkQuality : 1;
		} flags;
		unsigned uFlags;
	};
} OP_ETH_GENERAL_SETTINGS;
#define OP_ETH_GENERAL_SETTINGS_SIZE 20

typedef struct SRAD_GPTP_SETTINGS_s
{
	uint32_t neighborPropDelayThresh;//ns
	uint32_t sys_phc_sync_interval;//ns
	int8_t logPDelayReqInterval;// log2ms
	int8_t logSyncInterval;// log2ms
	int8_t logAnnounceInterval;// log2ms
	uint8_t profile;
	uint8_t priority1;
	uint8_t clockclass;
	uint8_t clockaccuracy;
	uint8_t priority2;
	uint16_t offset_scaled_log_variance;
	uint8_t gPTPportRole;
	uint8_t gptpEnabledPort;
	uint8_t enableClockSyntonization;
	uint8_t rsvd[15];
} RAD_GPTP_SETTINGS; //36 Bytes
#define RAD_GPTP_SETTINGS_SIZE 36

typedef struct SRAD_GPTP_AND_TAP_SETTINGS_s
{
	RAD_GPTP_SETTINGS gPTP;
    OP_ETH_GENERAL_SETTINGS tap;
} RAD_GPTP_AND_TAP_SETTINGS;
#define RAD_GPTP_AND_TAP_SETTINGS_SIZE 40

typedef struct HW_ETH_SETTINGS_t
{
	OP_ETH_GENERAL_SETTINGS General_Settings;
} HW_ETH_SETTINGS;
#define HW_ETH_SETTINGS_SIZE 20

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
	unsigned char preemption_en;
	union {
		struct
		{
			// Reuse the mac_addr for switch mode if required!
			unsigned char mac_addr1[6];// Original Addr for spoofing
			unsigned char mac_addr2[6];// Target Addr for spoofing
			unsigned short mac_spoofing_en : 1;
			unsigned short mac_spoofing_isDstOrSrc : 1;
			unsigned short link_spd : 2;
			unsigned short q2112_phy_mode : 1;
			unsigned short reserved : 11;
		};
		unsigned char reserved0[14];
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


#define ETHERNET_SETTINGS2_FLAG_FULL_DUPLEX  0x01
#define ETHERNET_SETTINGS2_FLAG_AUTO_NEG     0x02
#define ETHERNET_SETTINGS2_FLAG_TCPIP_ENABLE 0x04
#define ETHERNET_SETTINGS2_FLAG_RTSP_ENABLE  0x08
#define ETHERNET_SETTINGS2_FLAG_DEVICE_HOSTING_ENABLE  0x10
#define ETHERNET_SETTINGS2_FLAG_CONFIG_NOT_ALLOWED 0x20
#define ETHERNET_SETTINGS2_FLAG_COMM_IN_USE  0x80

typedef struct ETHERNET_SETTINGS2_t
{
	/* bit0: 0=half duplex, 1=full duplex
	 * bit1: auto negot
	 * bit2: enable tcp/ip stack
	 * bit3: enable rtsp server
	 * bit4: enable intepid device hosting (go online and log other devices)
	 * bit5: config not allowed
	 */
	uint8_t flags;
	uint8_t link_speed;//0=10, 1=100, 2=1000
	uint32_t ip_addr;
	uint32_t netmask;
	uint32_t gateway;
	uint8_t rsvd[2];
} ETHERNET_SETTINGS2;
#define ETHERNET_SETTINGS2_SIZE 16

/* ETHERNET_SETTINGS2 link speed, duplex options */
enum
{
	LINK_SPEED_AUTO_NEGOTIATION = 0,
	LINK_SPEED_1GBPS_FULL_DUPLEX,
	LINK_SPEED_1GBPS_HALF_DUPLEX,
	LINK_SPEED_100MBPS_FULL_DUPLEX,
	LINK_SPEED_100MBPS_HALF_DUPLEX,
	LINK_SPEED_10MBPS_FULL_DUPLEX,
	LINK_SPEED_10MBPS_HALF_DUPLEX,
	// NOTE: new entries must be appended to maintain backwards compatibility
	// insert new entries here
	LINK_SPEED_COUNT,
};

#define ETHERNET_SETTINGS10G_FLAG_FULL_DUPLEX  0x01
#define ETHERNET_SETTINGS10G_FLAG_AUTO_NEG     0x02
#define ETHERNET_SETTINGS10G_FLAG_TCPIP_ENABLE 0x04
#define ETHERNET_SETTINGS10G_FLAG_RTSP_ENABLE  0x08
#define ETHERNET_SETTINGS10G_FLAG_DEVICE_HOSTING_ENABLE  0x10
#define ETHERNET_SETTINGS10G_FLAG_COMM_IN_USE  0x80000000

typedef struct ETHERNET10G_SETTINGS_t
{
	/* bit0: 0=half duplex, 1=full duplex
	 * bit1: auto negot
	 * bit2: enable tcp/ip stack
	 * bit3: enable rtsp server
	 * bit4: enable intepid device hosting (go online and log other devices)
	 * bit31: comm in use
	 */
	uint32_t flags;
	uint32_t ip_addr;
	uint32_t netmask;
	uint32_t gateway;
	uint8_t link_speed;//0=10, 1=100, 2=1000, 3=2500, 4=5000, 5=10000
	uint8_t rsvd2[7];
} ETHERNET10G_SETTINGS;
#define ETHERNET10G_SETTINGS_SIZE 24

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
	uint8_t disk_layout;// RAID0, spanned, etc
	uint8_t disk_format;// FAT32
	uint32_t disk_enables;// mask of enabled disks in this layout
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
	uint16_t status;// 0x1 = present, 0x2 = initialized
	uint8_t sectors[8];
	uint8_t bytesPerSector[4];
} SDiskStatus;
#define SDiskStatus_SIZE 14

#define DISK_STRUCTURE_FLAG_FULL_FORMAT 0x01

typedef struct _SDiskStructure
{
	DISK_SETTINGS settings;
	uint16_t options;// 0x01 full format
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
	uint16_t state;// state of formatting (not started, writing file system, formatting, writing VSAs, finished)
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
} ExtendedResponseCode;

typedef struct _ExtendedResponseGeneric
{
	uint16_t commandType; // command type we're responding to
	int32_t returnCode;
} ExtendedResponseGeneric;

#define GET_SUPPORTED_FEATURES_COMMAND_VERSION (1)
typedef struct
{
	uint16_t cmdVersion;
	uint16_t numValidBits;
	uint32_t featureBitfields[0];
} GetSupportedFeaturesResponse;

typedef struct _SExtSubCmdHdr
{
	uint16_t command;
	uint16_t length;
} SExtSubCmdHdr;
#define SExtSubCmdHdr_SIZE 4

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
	uint8_t reserved[8];
} GPTPStatus;

#pragma pack(pop)

typedef struct _SExtSubCmdComm
{
	SExtSubCmdHdr header;
	union {
		SDiskStructure structure;
		SDiskDetails details;
		SDiskFormatProgress progress;
		StartDHCPServerCommand startDHCPServer;
		StopDHCPServerCommand stopDHCPServer;
		GetSupportedFeaturesResponse getSupportedFeatures;
		ExtendedResponseGeneric genericResponse;
		GPTPStatus gptpStatus;
		// Add additional extension commands to this union as needed.
	} extension;
} SExtSubCmdComm;
#define SExtSubCmdComm_SIZE 188

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
	SERDESCAM_VIDEO_FORMAT_RAW_8,  // e.g. bayer 8 bit, gray 8 bit
	SERDESCAM_VIDEO_FORMAT_RAW_10, // e.g. bayer 10 bit, gray 10 bit
	SERDESCAM_VIDEO_FORMAT_RAW_12,
	SERDESCAM_VIDEO_FORMAT_RAW_16, // e.g. planar YUV 4:2:2, 16bpp, 8 bit samples
	SERDESCAM_VIDEO_FORMAT_RAW_20, // e.g. planar YUV 4:2:2, 20bpp, 10 bit samples
	SERDESCAM_VIDEO_FORMAT_RAW_24, // e.g. packed RGB 8:8:8 24bpp, 8 bit samples
	SERDESCAM_VIDEO_FORMAT_RAW_30, // e.g. planar YUV 4:4:4, 30bpp, 10 bit samples
	SERDESCAM_VIDEO_FORMAT_RAW_32, // e.g. packed ARGB 8:8:8:8, 32bpp, 8 bit samples
	SERDESCAM_VIDEO_FORMAT_RAW_36,
	SERDESCAM_VIDEO_FORMAT_RGB888, // packed RGB 8:8:8, 24bpp, RGBRGB...
	SERDESCAM_VIDEO_FORMAT_UYVY_422_10LE_PACKED,// packed YUV 4:2:2, 20bpp, Cb Y0 Cr Y1, bitpacked
	SERDESCAM_VIDEO_FORMAT_YUYV_422_10LE_PACKED,// packed YUV 4:2:2, 20bpp, Y0 Cb Y1 Cr, FOURCC Y210 bitpacked
	SERDESCAM_VIDEO_FORMAT_YVYU_422_10LE_PACKED,// packed YUV 4:2:2, 20bpp, Y0 Cr Y1 Cb, bitpacked
	SERDESCAM_VIDEO_FORMAT_VYUY_422_10LE_PACKED,// packed YUV 4:2:2, 20bpp, Cr Y0 Cb Y1, bitpacked
	SERDESCAM_VIDEO_FORMAT_BAYER_BGGR_10LE_PACKED,// 10-bit samples bitpacked into 40-bits little endian
	SERDESCAM_VIDEO_FORMAT_BAYER_BGGR_12LE_PACKED,// 12-bit samples bitpacked into 24-bits little endian
	SERDESCAM_VIDEO_FORMAT_BAYER_BGGR_16LE,// 16-bit samples little endian
	SERDESCAM_VIDEO_FORMAT_BAYER_BGGR_16BE,// 16-bit samples big endian
	SERDESCAM_VIDEO_FORMAT_JPEG,
	SERDESCAM_VIDEO_FORMAT_UYVY_422_12LE_PACKED,// packed YUV 4:2:2, 24bpp, Cb Y0 Cr Y1, bitpacked
	SERDESCAM_VIDEO_FORMAT_YUYV_422_12LE_PACKED,// packed YUV 4:2:2, 24bpp, Y0 Cb Y1 Cr, bitpacked
	SERDESCAM_VIDEO_FORMAT_YVYU_422_12LE_PACKED,// packed YUV 4:2:2, 24bpp, Y0 Cr Y1 Cb, bitpacked
	SERDESCAM_VIDEO_FORMAT_VYUY_422_12LE_PACKED,// packed YUV 4:2:2, 24bpp, Cr Y0 Cb Y1, bitpacked
	SERDESCAM_VIDEO_FORMAT_YUV422_10LE_PLANAR,// planar YUV 4:2:2, 20bpp, (1 Cr & Cb sample per 2x1 Y samples), little-endian
	SERDESCAM_VIDEO_FORMAT_YUV422_16LE_PLANAR,// planar YUV 4:2:2, 32bpp, (1 Cr & Cb sample per 2x1 Y samples), little-endian
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
	SERDESCAM_VIDEO_FORMAT_CSI2_UYVY_422_10LE_PACKED,// packed YUV 4:2:2, 20bpp, Cb Y0 Cr Y1, bitpacked
	SERDESCAM_VIDEO_FORMAT_CSI2_YUYV_422_10LE_PACKED,// packed YUV 4:2:2, 20bpp, Y0 Cb Y1 Cr, FOURCC Y210 bitpacked
	SERDESCAM_VIDEO_FORMAT_CSI2_YVYU_422_10LE_PACKED,// packed YUV 4:2:2, 20bpp, Y0 Cr Y1 Cb, bitpacked
	SERDESCAM_VIDEO_FORMAT_CSI2_VYUY_422_10LE_PACKED,// packed YUV 4:2:2, 20bpp, Cr Y0 Cb Y1, bitpacked
	SERDESCAM_VIDEO_FORMAT_CSI2_UYVY_422_12LE_PACKED,// packed YUV 4:2:2, 24bpp, Cb Y0 Cr Y1, bitpacked
	SERDESCAM_VIDEO_FORMAT_CSI2_YUYV_422_12LE_PACKED,// packed YUV 4:2:2, 24bpp, Y0 Cb Y1 Cr, bitpacked
	SERDESCAM_VIDEO_FORMAT_CSI2_YVYU_422_12LE_PACKED,// packed YUV 4:2:2, 24bpp, Y0 Cr Y1 Cb, bitpacked
	SERDESCAM_VIDEO_FORMAT_CSI2_VYUY_422_12LE_PACKED,// packed YUV 4:2:2, 24bpp, Cr Y0 Cb Y1, bitpacked
	SERDESCAM_VIDEO_FORMAT_CSI2_RGB565, // packed RGB 5:6:5, 16bpp, BGRBGR...
	SERDESCAM_VIDEO_FORMAT_CSI2_RGB666, // packed RGB 6:6:6, 18bpp, BGRBGR...
	SERDESCAM_VIDEO_FORMAT_CSI2_RGB888, // packed RGB 8:8:8, 24bpp, BGRBGR...
	SERDESCAM_VIDEO_FORMAT_CSI2_BAYER_BGGR_8,
	SERDESCAM_VIDEO_FORMAT_CSI2_BAYER_BGGR_10LE_PACKED,// 10-bit samples bitpacked into 40-bits little endian
	SERDESCAM_VIDEO_FORMAT_CSI2_BAYER_BGGR_12LE_PACKED,// 12-bit samples bitpacked into 40-bits little endian
	SERDESCAM_VIDEO_FORMAT_CSI2_RAW_8,  // e.g. bayer 8 bit, gray 8 bit
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
	SERDESCAM_VIDEO_FORMAT_BAYER_RGGB_10LE_PACKED,// 10-bit samples bitpacked into 40-bits little endian
	SERDESCAM_VIDEO_FORMAT_BAYER_RGGB_12LE_PACKED,// 12-bit samples bitpacked into 24-bits little endian
	SERDESCAM_VIDEO_FORMAT_BAYER_RGGB_16LE,// 16-bit samples little endian
	SERDESCAM_VIDEO_FORMAT_BAYER_RGGB_16BE,// 16-bit samples big endian
	SERDESCAM_VIDEO_FORMAT_CSI2_BAYER_RGGB_8,
	SERDESCAM_VIDEO_FORMAT_CSI2_BAYER_RGGB_10LE_PACKED,// 10-bit samples bitpacked into 40-bits little endian
	SERDESCAM_VIDEO_FORMAT_CSI2_BAYER_RGGB_12LE_PACKED,// 12-bit samples bitpacked into 24-bits little endian

	SERDESCAM_VIDEO_FORMAT_BAYER_GBRG_8,
	SERDESCAM_VIDEO_FORMAT_BAYER_GBRG_10LE_PACKED,// 10-bit samples bitpacked into 40-bits little endian
	SERDESCAM_VIDEO_FORMAT_BAYER_GBRG_12LE_PACKED,// 12-bit samples bitpacked into 24-bits little endian
	SERDESCAM_VIDEO_FORMAT_BAYER_GBRG_16LE,// 16-bit samples little endian
	SERDESCAM_VIDEO_FORMAT_BAYER_GBRG_16BE,// 16-bit samples big endian
	SERDESCAM_VIDEO_FORMAT_CSI2_BAYER_GBRG_8,
	SERDESCAM_VIDEO_FORMAT_CSI2_BAYER_GBRG_10LE_PACKED,// 10-bit samples bitpacked into 40-bits little endian
	SERDESCAM_VIDEO_FORMAT_CSI2_BAYER_GBRG_12LE_PACKED,// 12-bit samples bitpacked into 24-bits little endian
	
	SERDESCAM_VIDEO_FORMAT_BAYER_GRBG_8,
	SERDESCAM_VIDEO_FORMAT_BAYER_GRBG_10LE_PACKED,// 10-bit samples bitpacked into 40-bits little endian
	SERDESCAM_VIDEO_FORMAT_BAYER_GRBG_12LE_PACKED,// 12-bit samples bitpacked into 24-bits little endian
	SERDESCAM_VIDEO_FORMAT_BAYER_GRBG_16LE,// 16-bit samples little endian
	SERDESCAM_VIDEO_FORMAT_BAYER_GRBG_16BE,// 16-bit samples big endian
	SERDESCAM_VIDEO_FORMAT_CSI2_BAYER_GRBG_8,
	SERDESCAM_VIDEO_FORMAT_CSI2_BAYER_GRBG_10LE_PACKED,// 10-bit samples bitpacked into 40-bits little endian
	SERDESCAM_VIDEO_FORMAT_CSI2_BAYER_GRBG_12LE_PACKED,// 12-bit samples bitpacked into 24-bits little endian
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
	uint8_t mode;// passthrough, tap, etc
	uint8_t rsvd1;
	uint8_t bitPos;
	uint8_t videoFormat;// bytes per pixel
	uint16_t resWidth;
	uint16_t resHeight;
	uint8_t frameSkip;// skip every nth frame
	uint8_t rsvd2[19];
} SERDESCAM_SETTINGS;
#define SERDESCAM_SETTINGS_SIZE 32

#define SERDESPOC_SETTINGS_MODE_DISABLED 0x00
#define SERDESPOC_SETTINGS_MODE_SUPPLY 0x01
#define SERDESPOC_SETTINGS_MODE_SERIALIZER 0x02

typedef struct SERDESPOC_SETTINGS_t
{
	uint8_t mode;// no poc, generated supply, serializer passthrough
	uint8_t rsvd[6];
	uint8_t voltage;// generated voltage
	uint16_t chksum;// checksum to protect settings structure (don't want corrupt voltage settings)
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
	uint16_t tx_speed;// Mbps per lane, all tx ports
	uint16_t rx_speed;// Mbps per lane, all rx ports
	// reserved space for the future
	// maybe pattern generator settings
	uint8_t rsvd2[24];
} SERDESGEN_SETTINGS;
#define SERDESGEN_SETTINGS_SIZE 32

typedef struct _RadMoonDuoConverterSettings
{
	// OPETH_LINK_AUTO/MASTER/SLAVE
	uint8_t linkMode0;
	uint8_t linkMode1;
	// USB/CM or RJ45 selection
	uint8_t converter1Mode;
	// IP Settings if converter is hooked up to Coremini
	uint32_t ipAddress;
	uint32_t ipMask;
	uint32_t ipGateway;
} RadMoonDuoConverterSettings;
#define RADMOONDUO_CONVERTER_SETTINGS_SIZE (16)

// clang-format off
#define RAD_REPORTING_SETTINGS_FLAG_TEMP_ENABLE 		0x00000001
#define RAD_REPORTING_SETTINGS_FLAG_MIC2_GPS_ENABLE 	0x00000002 // USB port 1
#define RAD_REPORTING_SETTINGS_FLAG_INT_GPS_ENABLE 		0x00000004
#define RAD_REPORTING_SETTINGS_FLAG_MIC2_GPS_ENABLE2 	0x00000008 // USB port 2
#define RAD_REPORTING_SETTINGS_FLAG_MISC1_DIN 			0x00000010
#define RAD_REPORTING_SETTINGS_FLAG_MISC2_DIN 			0x00000020
#define RAD_REPORTING_SETTINGS_FLAG_MISC1_PWMIN 		0x00000040
#define RAD_REPORTING_SETTINGS_FLAG_MISC2_PWMIN 		0x00000080
#define RAD_REPORTING_SETTINGS_FLAG_AIN1 				0x00000100
#define RAD_REPORTING_SETTINGS_FLAG_SERDES_ENABLE 		0x00000200
#define RAD_REPORTING_SETTINGS_FLAG_FAN_SPEED_ENABLE	0x00000400
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

typedef struct _SVCANRFSettings
{
	CAN_SETTINGS can1;
	CAN_SETTINGS can2;
	CAN_SETTINGS can3;
	CAN_SETTINGS can4;

	LIN_SETTINGS lin1;
	LIN_SETTINGS lin2;

	uint16_t network_enables;
	uint16_t network_enabled_on_boot;

	uint32_t pwr_man_timeout;
	uint16_t pwr_man_enable;

	uint16_t misc_io_initial_ddr;
	uint16_t misc_io_initial_latch;
	uint16_t misc_io_analog_enable;
	uint16_t misc_io_report_period;
	uint16_t misc_io_on_report_events;

	uint16_t iso15765_separation_time_offset;

	uint16_t iso9141_kwp_enable_reserved;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings;

	uint16_t perf_en;

	uint16_t iso_parity;
	uint16_t iso_msg_termination;
	uint16_t iso_tester_pullup_enable;
	uint16_t network_enables_2;

	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_2;
	uint16_t iso_parity_2;
	uint16_t iso_msg_termination_2;

	uint16_t idle_wakeup_network_enables_1;
	uint16_t idle_wakeup_network_enables_2;

	uint16_t disableFwLEDs : 1;
	uint16_t reservedZero : 15;
} SVCANRFSettings;
#define SVCANRFSettings_SIZE 340

typedef struct _SECUSettings
{
	/* ECU ID used in CAN communications.
	 * TX ID = ECU ID with bit28 cleared,
	 * RX ID = ECUID with bit28 set,
	 * ECU ID = 0 implies ECU ID = serial no with bit 27 set\
	*/
	uint32_t ecu_id;

	uint16_t selected_network;// not supported yet - default to HSCAN

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

typedef struct _SIEVBSettings
{
	/* see SECUSettings */
	uint32_t ecu_id;

	uint16_t selected_network; /* not supported yet - default to HSCAN */

	CAN_SETTINGS can1;
	LIN_SETTINGS lin1;

	uint16_t network_enables;
	uint16_t network_enables_2;
	uint16_t network_enabled_on_boot;

	uint16_t misc_io_initial_ddr;
	uint16_t misc_io_initial_latch;
	uint16_t misc_io_analog_enable;
	uint16_t misc_io_report_period;
	uint16_t misc_io_on_report_events;
	uint16_t ain_sample_period;
	uint16_t ain_threshold;

	uint16_t iso15765_separation_time_offset;

	CAN_SETTINGS can2;
	LIN_SETTINGS lin2;

	UART_SETTINGS uart;
	UART_SETTINGS uart2;

	STextAPISettings text_api;

	uint32_t reserved_1;
	uint32_t reserved_2;

	uint32_t pwr_man_timeout;
	uint16_t pwr_man_enable;

	uint16_t idle_wakeup_network_enables_1;
	uint16_t idle_wakeup_network_enables_2;

	uint16_t misc_io_analog_enable_2;

	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings;
	uint16_t iso_parity;
	uint16_t iso_msg_termination;
	uint16_t iso_tester_pullup_enable;

	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_2;
	uint16_t iso_parity_2;
	uint16_t iso_msg_termination_2;

} SIEVBSettings;
#define SIEVBSettings_SIZE 434

typedef struct _SEEVBSettings
{
	uint32_t ecu_id;

	CAN_SETTINGS can1;

	uint16_t network_enables;
	uint16_t network_enabled_on_boot;

	uint16_t iso15765_separation_time_offset;

	uint16_t perf_en;

	uint16_t ain_sample_period;
	uint16_t ain_threshold;

	uint32_t rsvd;
} SEEVBSettings;
#define SEEVBSettings_SIZE 32

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
};

/* GPTP port role options */
enum eGPTPRole
{
	eRoleDisabled = 0,
	eRolePassive = 1,
	eRoleMaster = 2,
	eRoleSlave = 3,
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

	ETHERNET_SETTINGS2 ethernet1;// DAQ port on label, NETID_ETHERNET
	ETHERNET_SETTINGS2 ethernet2;// LAN port on label, NETID_ETHERNET2
	uint16_t network_enables_4;
	
	RAD_GPTP_SETTINGS gPTP;
} SRADGalaxySettings;
#define SRADGalaxySettings_SIZE 768

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
	uint16_t hwComLatencyTestEn;
	RAD_REPORTING_SETTINGS reporting;
	ETHERNET_SETTINGS2 ethernet;
	
	RAD_GPTP_SETTINGS gPTP;
} SRADStar2Settings;

#define SRADStar2Settings_SIZE 414

typedef struct _SRADSuperMoonSettings
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

	ETHERNET_SETTINGS2 Eth2;
	
	RAD_GPTP_SETTINGS gPTP;
} SRADSuperMoonSettings;

#define SRADSuperMoonSettings_SIZE 178

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
	// TODO!!!!
	uint16_t perf_en;
	struct
	{
		uint16_t hwComLatencyTestEn : 1;
		uint16_t : 15;
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
} SRADA2BSettings;

#define SRADA2BSettings_SIZE 274

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
} SRADMoon2Settings;

#define SRADMoon2Settings_SIZE 162

typedef struct _SRADGigalogSettings
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
	CAN_SETTINGS can7;
	CANFD_SETTINGS canfd7;
	CAN_SETTINGS can8;
	CANFD_SETTINGS canfd8;

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
	uint8_t rsvd1[8];// previously ETHERNET_SETTINGS
	uint8_t rsvd2[8];// previously ETHERNET10G_SETTINGS

	DISK_SETTINGS disk;

	TIMESYNC_ICSHARDWARE_SETTINGS timeSyncSettings;
	struct
	{
		uint16_t hwComLatencyTestEn : 1;
		uint16_t disableUsbCheckOnBoot : 1;
		uint16_t reserved : 14;
	} flags;
	ETHERNET_SETTINGS2 ethernet;

	SERDESCAM_SETTINGS serdescam1;
	ETHERNET10G_SETTINGS ethernet10g;

	LIN_SETTINGS lin1;

	SERDESPOC_SETTINGS serdespoc;
	LOGGER_SETTINGS logger;
	SERDESCAM_SETTINGS serdescam2;
	SERDESCAM_SETTINGS serdescam3;
	SERDESCAM_SETTINGS serdescam4;

	ETHERNET_SETTINGS2 ethernet2;
	uint16_t network_enables_4;
	RAD_REPORTING_SETTINGS reporting;
	SERDESGEN_SETTINGS serdesgen;

} SRADGigalogSettings;

#define SRADGigalogSettings_SIZE 698

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
} SRADGigastarSettings;

#define SRADGigastarSettings_SIZE 702

typedef struct _SVividCANSettings
{
	uint32_t ecu_id;

	CAN_SETTINGS can1;// 12 bytes
	SWCAN_SETTINGS swcan1;// 14 bytes
	CAN_SETTINGS lsftcan1;// 12 bytes

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

typedef struct _SOBD2SimSettings
{
	CAN_SETTINGS can1;
	CAN_SETTINGS can2;
	CANFD_SETTINGS canfd1;
	CANFD_SETTINGS canfd2;

	uint64_t network_enables;
	uint16_t network_enabled_on_boot;

	int16_t iso15765_separation_time_offset;

	uint16_t perf_en;

	uint16_t misc_io_initial_ddr;
	uint16_t misc_io_initial_latch;
	uint16_t misc_io_report_period;
	uint16_t misc_io_on_report_events;
	uint16_t misc_io_analog_enable;
	uint16_t ain_sample_period;
	uint16_t ain_threshold;

	struct
	{
		uint32_t : 1;
		uint32_t enableLatencyTest : 1;
		uint32_t reserved : 30;
	} flags;

	STextAPISettings text_api;
} SOBD2SimSettings;
#define SOBD2SimSettings_SIZE 148

typedef struct _CmProbeSettings
{
	//	uint16_t        perf_en;

	//	ETHERNET_SETTINGS eth1;  // 16 bytes
	//	OP_ETH_SETTINGS opEth1;

	uint16_t network_enables;

	//	uint16_t        misc_io_initial_ddr;
	//	uint16_t        misc_io_initial_latch;
	//	uint16_t        misc_io_report_period;
	//	uint16_t        misc_io_on_report_events;
	//	uint16_t        misc_io_analog_enable;
	//	uint16_t        ain_sample_period;
	//	uint16_t        ain_threshold;
	//
	//	uint32_t        pwr_man_timeout;
	//	uint16_t        pwr_man_enable;
	//
	uint16_t network_enabled_on_boot;
	//
	//	uint16_t        idle_wakeup_network_enables_1;

} CmProbeSettings, SCmProbeSettings;
#define CmProbeSettings_SIZE 4

typedef struct _OBD2ProSettings
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
	LIN_SETTINGS lin2;

	ETHERNET_SETTINGS ethernet;

	/* ISO9141 - Keyword */
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_1;
	uint16_t iso_parity_1;
	uint16_t iso_msg_termination_1;

	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_2;
	uint16_t iso_parity_2;
	uint16_t iso_msg_termination_2;

	uint64_t network_enables;

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
	uint16_t can_switch_mode;

	uint16_t misc_io_analog_enable;
	ETHERNET_SETTINGS2 ethernet2;
} OBD2ProSettings, SOBD2ProSettings;
#define OBD2ProSettings_SIZE 482

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

typedef struct _neoECU_AVBSettings
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
} ECU_AVBSettings, SECU_AVBSettings;
#define ECU_AVBSettings_SIZE 148

#define PLUTO_NUM_PORTS 5
#define PLUTO_NUM_PRIORITY 8
#define PLUTO_MAX_L2_POLICING 45
#define PLUTO_MAX_L2_ADDRESS_LOOKUP 1024
#define PLUTO_MAX_VLAN_LOOKUP 4096
#define PLUTO_MAX_FORWARDING_ENTRIES 13
#define PLUTO_MAX_MAC_CONFIG_ENTRIES 5
#define PLUTO_MAX_RETAGGING_ENTRIES 32
#define MAX_VL_POLICING_ENTRIES 1024
#define MAX_VL_FORWARDING_ENTRIES 1024

typedef struct SPluto_L2AddressLookupEntry_s
{
	uint16_t index;
	uint16_t vlanID;
	uint8_t macaddr[6];
	uint8_t destports;
	uint8_t enfport;
	uint8_t learnedEntry;
	uint8_t pad1;
	uint8_t pad2;
	uint8_t pad3;
} SPluto_L2AddressLookupEntry;//16

typedef struct SPluto_L2AddressLookupParams_s
{
	uint16_t maxage;
	uint8_t dyn_tbsz;
	uint8_t poly;
	uint8_t shared_learn;
	uint8_t no_enf_hostprt;
	uint8_t no_mgmt_learn;
	uint8_t pad;
} SPluto_L2AddressLookupParams;//8

typedef struct SPluto_L2ForwardingParams_s
{
	uint16_t part_spc[PLUTO_NUM_PRIORITY];
	uint8_t max_dynp;
	uint8_t pad;
} SPluto_L2ForwardingParams;//18

typedef struct SPluto_L2ForwardingEntry_s
{
	uint8_t vlan_pmap[PLUTO_NUM_PRIORITY];
	uint8_t bc_domain;
	uint8_t reach_port;
	uint8_t fl_domain;
	uint8_t pad;
} SPluto_L2ForwardingEntry;//12

typedef struct SPluto_L2Policing_s
{
	uint16_t smax;
	uint16_t rate;
	uint16_t maxlen;
	uint8_t sharindx;
	uint8_t partition;
} SPluto_L2Policing;//8

typedef struct SPluto_VlanLookup_s
{
	uint16_t vlanid;
	uint8_t ving_mirr;
	uint8_t vegr_mirr;
	uint8_t vmemb_port;
	uint8_t vlan_bc;
	uint8_t tag_port;
	uint8_t pad;
} SPluto_VlanLookup;//8

typedef struct SPluto_MacConfig_s
{
	uint16_t top[PLUTO_NUM_PRIORITY];
	uint16_t base[PLUTO_NUM_PRIORITY];
	uint16_t tp_delin;
	uint16_t tp_delout;
	uint16_t vlanid;
	uint8_t enabled[PLUTO_NUM_PRIORITY];
	uint8_t ifg;
	uint8_t speed;
	uint8_t maxage;
	uint8_t vlanprio;
	uint8_t ing_mirr;
	uint8_t egr_mirr;
	uint8_t drpnona664;
	uint8_t drpdtag;
	uint8_t drpuntag;
	uint8_t retag;
	uint8_t dyn_learn;
	uint8_t egress;
	uint8_t ingress;
	uint8_t pad;
} SPluto_MacConfig;//60

typedef struct SPluto_RetaggingEntry_s
{
	uint16_t vlan_egr;
	uint16_t vlan_ing;
	uint8_t egr_port;
	uint8_t ing_port;
	uint8_t do_not_learn;
	uint8_t use_dest_ports;
	uint8_t destports;
	uint8_t pad;
} SPluto_RetaggingEntry;//10

typedef struct SPluto_GeneralParams_s
{
	uint64_t mac_fltres1;
	uint64_t mac_fltres0;
	uint64_t mac_flt1;
	uint64_t mac_flt0;
	uint32_t vlmarker;
	uint32_t vlmask;
	uint16_t tpid;
	uint16_t tpid2;
	uint8_t vllupformat;
	uint8_t mirr_ptacu;
	uint8_t switchid;
	uint8_t hostprio;
	uint8_t incl_srcpt1;
	uint8_t incl_srcpt0;
	uint8_t send_meta1;
	uint8_t send_meta0;
	uint8_t casc_port;
	uint8_t host_port;
	uint8_t mirr_port;
	uint8_t ignore2stf;
} SPluto_GeneralParams;//60

typedef struct SPluto_VlLookupEntry_s
{
	union {
		/* format == 0 */
		struct
		{
			uint64_t macaddr;
			uint16_t vlanid;
			uint8_t destports;
			uint8_t iscritical;
			uint8_t port;
			uint8_t vlanprior;
		} vllupformat0;//14
		/* format == 1 */
		struct
		{
			uint16_t vlid;
			uint8_t egrmirr;
			uint8_t ingrmirr;
			uint8_t port;
		} vllupformat1;//5
	};
} SPluto_VlLookupEntry;//14

typedef struct SPluto_VlPolicingEntry_s
{
	uint64_t type;
	uint64_t maxlen;
	uint64_t sharindx;
	uint64_t bag;
	uint64_t jitter;
} SPluto_VlPolicingEntry;//40

typedef struct SPluto_VlForwardingParams_s
{
	uint16_t partspc[PLUTO_NUM_PRIORITY];
	uint8_t debugen;
	uint8_t pad;
} SPluto_VlForwardingParams;//18

typedef struct SPluto_VlForwardingEntry_s
{
	uint8_t type;
	uint8_t priority;
	uint8_t partition;
	uint8_t destports;
} SPluto_VlForwardingEntry;//4

typedef struct SPluto_AVBParams_s
{
	uint64_t destmeta;
	uint64_t srcmeta;
} SPluto_AVBParams;//16

typedef struct SPluto_ClockSyncParams_s
{
	uint64_t etssrcpcf;
	uint32_t wfintmout;
	uint32_t maxtranspclk;
	uint32_t listentmout;
	uint32_t intcydur;
	uint32_t caentmout;
	uint16_t pcfsze;
	uint16_t obvwinsz;
	uint16_t vlidout;
	uint16_t vlidimnmin;
	uint16_t vlidinmax;
	uint16_t accdevwin;
	uint8_t srcport[8];
	uint8_t waitthsync;
	uint8_t unsytotsyth;
	uint8_t unsytosyth;
	uint8_t tsytosyth;
	uint8_t tsyth;
	uint8_t tsytousyth;
	uint8_t syth;
	uint8_t sytousyth;
	uint8_t sypriority;
	uint8_t sydomain;
	uint8_t stth;
	uint8_t sttointth;
	uint8_t pcfpriority;
	uint8_t numunstbcy;
	uint8_t numstbcy;
	uint8_t maxintegcy;
	uint8_t inttotentth;
	uint8_t inttosyncth;
	uint8_t vlidselect;
	uint8_t tentsyrelen;
	uint8_t asytensyen;
	uint8_t sytostben;
	uint8_t syrelen;
	uint8_t sysyen;
	uint8_t syasyen;
	uint8_t ipcframesy;
	uint8_t stabasyen;
	uint8_t swmaster;
	uint8_t fullcbg;
	uint8_t pad1;
	uint8_t pad2;
	uint8_t pad3;
} SPluto_ClockSyncParams;//80

#define gPTP_ROLE_DISABLED 0
#define gPTP_ROLE_PASSIVE 1
#define gPTP_ROLE_MASTER 2
#define gPTP_ROLE_SLAVE 3

#define gPTP_PROFILE_STANDARD 0
#define gPTP_PROFILE_AUTOMOTIVE 1

#define gPTP_PORT_DISABLED 0
#define gPTP_PORT_ENABLED 1

typedef struct SPlutoPtpParams_s
{
	uint32_t neighborPropDelayThresh;//ns
	uint32_t sys_phc_sync_interval;//ns
	int8_t logPDelayReqInterval;// log2ms
	int8_t logSyncInterval;// log2ms
	int8_t logAnnounceInterval;// log2ms
	uint8_t profile;
	uint8_t priority1;
	uint8_t clockclass;
	uint8_t clockaccuracy;
	uint8_t priority2;
	uint16_t offset_scaled_log_variance;
	uint8_t gPTPportRole[PLUTO_NUM_PORTS - 1];// the 5th port is used for SAM
	uint8_t portEnable[PLUTO_NUM_PORTS - 1];// the 5th port is used for SAM
} PlutoPtpParams_t;//26

typedef struct SPluto_CustomParams_s
{
	uint8_t mode[PLUTO_MAX_MAC_CONFIG_ENTRIES];
	uint8_t speed[PLUTO_MAX_MAC_CONFIG_ENTRIES];
	uint8_t enablePhy[PLUTO_MAX_MAC_CONFIG_ENTRIES];
	uint8_t ae1Select;
	uint8_t usbSelect;
	uint8_t pad;
	PlutoPtpParams_t ptpParams;
} SPluto_CustomParams;//44

typedef struct SPlutoSwitchSettings_s
{
	ExtendedDataFlashHeader_t flashHeader;//all extended data must start with this header //8
	SPluto_L2AddressLookupParams l2_addressLookupParams;// 8
	SPluto_L2AddressLookupEntry l2_addressLookupEntries[PLUTO_MAX_L2_ADDRESS_LOOKUP];// 16 * 1024
	SPluto_L2Policing l2_policing[PLUTO_MAX_L2_POLICING];// 8 * 45
	SPluto_L2ForwardingParams l2_forwardingParams;// 18
	SPluto_L2ForwardingEntry l2_ForwardingEntries[PLUTO_MAX_FORWARDING_ENTRIES];// 12 * 13
	SPluto_VlanLookup vlan_LookupEntries[PLUTO_MAX_VLAN_LOOKUP];// 8 * 4096
	SPluto_MacConfig macConfig[PLUTO_MAX_MAC_CONFIG_ENTRIES];// 60  * 5
	SPluto_GeneralParams generalParams;// 60
	SPluto_RetaggingEntry retagging[PLUTO_MAX_RETAGGING_ENTRIES];// 10 * 32
#if 0
	SPluto_VlPolicingEntry vl_policing[MAX_VL_POLICING_ENTRIES];
	SPluto_VlForwardingParams vl_forwardingParams;
	SPluto_VlForwardingEntry vl_forwardingEntries[MAX_VL_FORWARDING_ENTRIES];
	SPluto_AVBParams avbParams;
	SPluto_ClockSyncParams clkSyncParams;
#endif
} SPlutoSwitchSettings;
#define SPlutoSwitchSettings_SIZE 50378

typedef struct _RADPlutoSettings
{
	/* Performance Test */
	uint16_t perf_en;//2

	CAN_SETTINGS can1;//12
	CANFD_SETTINGS canfd1;//10
	CAN_SETTINGS can2;//12
	CANFD_SETTINGS canfd2;//10
	LIN_SETTINGS lin1;//10

	uint16_t network_enables;//2
	uint16_t network_enables_2;//2
	uint16_t network_enables_3;//2
	uint64_t termination_enables;//8
	uint16_t misc_io_analog_enable;//2

	uint32_t pwr_man_timeout;//4
	uint16_t pwr_man_enable;//2

	uint16_t network_enabled_on_boot;//2

	/* ISO15765-2 Transport Layer */
	int16_t iso15765_separation_time_offset;//2
	uint16_t iso9141_kwp_enable_reserved;//2
	uint16_t iso_tester_pullup_enable;//2
	uint16_t iso_parity;//2
	uint16_t iso_msg_termination;//2
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings;//114
	ETHERNET_SETTINGS ethernet;//8

	STextAPISettings text_api;//72
	struct
	{
		uint32_t disableUsbCheckOnBoot : 1;
		uint32_t enableLatencyTest : 1;
		uint32_t enablePcEthernetComm : 1;
		uint32_t reserved : 29;
	} flags;//4

	SPluto_CustomParams custom;//44
	ETHERNET_SETTINGS2 ethernet2;//16
} SRADPlutoSettings;
#define SRADPlutoSettings_SIZE 348

typedef union {
	uint32_t word;
	struct
	{
		unsigned can_sleep_command_id:29;
		unsigned can_sleep_command_isExtended:1;
		unsigned reserved:2;
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
	union {
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

	union {
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
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_1;
	uint16_t iso_parity_1;
	uint16_t iso_msg_termination_1;
	union {
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
} OBD2LCSettings, SOBD2LCSettings;
#define OBD2LCSettings_SIZE 360

#define RADJUPITER_NUM_PORTS 8

#define JUPITER_PTP_ROLE_DISABLED 0
#define JUPITER_PTP_ROLE_MASTER 1
#define JUPITER_PTP_ROLE_SLAVE 2
typedef struct SJupiterPtpParams_s
{
	uint32_t neighborPropDelay;//ns
	int8_t initLogPDelayReqInterval;// log2ms
	int8_t initLogSyncInterval;// log2ms
	int8_t operationLogPDelayReqInterval;// log2ms
	int8_t operationLogSyncInterval;// log2ms
	uint8_t gPTPportRole[RADJUPITER_NUM_PORTS];// the 6th port is used for SAM
} JupiterPtpParams_t;//16

typedef struct _SRADJupiterSwitchSettings
{
	uint8_t phyMode[RADJUPITER_NUM_PORTS]; //8
	uint8_t enablePhy[RADJUPITER_NUM_PORTS];//8
	uint8_t port7Select; //1
	uint8_t port8Select; //1
	uint8_t port8Speed;
	uint8_t port8Legacy;
	uint8_t spoofMacFlag;
	uint8_t spoofedMac[6];
	uint8_t pad;
	JupiterPtpParams_t ptpParams;//16
} SRADJupiterSwitchSettings;//44

typedef struct _SRADJupiterSettings
{
	/* Performance Test */
	uint16_t perf_en;//2

	CAN_SETTINGS can1;//12
	CANFD_SETTINGS canfd1;//10
	CAN_SETTINGS can2;//12
	CANFD_SETTINGS canfd2;//10
	LIN_SETTINGS lin1;//10

	uint16_t network_enables;//2
	uint16_t network_enables_2;//2
	uint16_t network_enables_3;//2
	uint64_t termination_enables;//8
	uint16_t misc_io_analog_enable;//2

	uint32_t pwr_man_timeout;//4
	uint16_t pwr_man_enable;//2

	uint16_t network_enabled_on_boot;//2

	/* ISO15765-2 Transport Layer */
	int16_t iso15765_separation_time_offset;//2
	uint16_t iso9141_kwp_enable_reserved;//2
	uint16_t iso_tester_pullup_enable;//2
	uint16_t iso_parity;//2
	uint16_t iso_msg_termination;//2
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings;//114
	ETHERNET_SETTINGS ethernet;//8

	STextAPISettings text_api;//72

	struct
	{
		uint32_t disableUsbCheckOnBoot : 1;
		uint32_t enableLatencyTest : 1;
		uint32_t enablePcEthernetComm : 1;
		uint32_t reserved : 29;
	} flags;//4

	SRADJupiterSwitchSettings switchSettings;//44
	ETHERNET_SETTINGS2 ethernet2;
} SRADJupiterSettings;//348

#define SRADJupiterSettings_SIZE 348

typedef struct _SFire3Settings
{
	uint16_t perf_en;
	uint16_t network_enabled_on_boot;
	uint16_t misc_io_on_report_events;
	uint16_t pwr_man_enable;
	int16_t iso15765_separation_time_offset;
	uint16_t slaveVnetA;
	uint32_t reserved;
	uint64_t termination_enables;
	union {
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
}SFire3Settings;
#define SFire3Settings_SIZE (624)

typedef struct
{
	uint16_t perf_en;
	uint16_t network_enabled_on_boot;
	uint32_t pwr_man_timeout;
	uint16_t pwr_man_enable;
	RadMoonDuoConverterSettings converter;
	uint64_t network_enables;
	struct
	{
		uint32_t disableUsbCheckOnBoot : 1;
		uint32_t enableLatencyTest : 1;
		uint32_t reserved : 30;
	} flags;
} RadMoonDuoSettings, SRadMoonDuoSettings;
#define RadMoonDuoSettings_SIZE 38

typedef struct _SEtherBadgeSettings
{
	/* Performance Test */
	uint16_t perf_en;//2

	CAN_SETTINGS can1;//12
	CANFD_SETTINGS canfd1;//10
	CAN_SETTINGS can2;//12
	CANFD_SETTINGS canfd2;//10
	LIN_SETTINGS lin1;//10

	uint16_t network_enables;//2
	uint16_t network_enables_2;//2
	uint16_t network_enables_3;//2
	uint64_t termination_enables;//8

	uint32_t pwr_man_timeout;//4
	uint16_t pwr_man_enable;//2

	uint16_t network_enabled_on_boot;//2

	/* ISO15765-2 Transport Layer */
	int16_t iso15765_separation_time_offset;//2
	uint16_t iso9141_kwp_enable_reserved;//2
	uint16_t iso_tester_pullup_enable;//2
	uint16_t iso_parity;//2
	uint16_t iso_msg_termination;//2
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings;//114
	ETHERNET_SETTINGS ethernet;//8

	uint16_t misc_io_initial_ddr;//2
	uint16_t misc_io_initial_latch;//2
	uint16_t misc_io_report_period;//2
	uint16_t misc_io_on_report_events;//2
	uint16_t misc_io_analog_enable;//2
	uint16_t ain_sample_period;//2
	uint16_t ain_threshold;//2

	STextAPISettings text_api;//72

	struct
	{
		uint32_t disableUsbCheckOnBoot : 1;
		uint32_t enableLatencyTest : 1;
		uint32_t enablePcEthernetComm : 1;
		uint32_t reserved : 29;
	} flags;//4

	ETHERNET_SETTINGS2 ethernet2;//16
} SEtherBadgeSettings;//316

#define SEtherBadgeSettings_SIZE 316

#define RADEPSILON_MAX_PHY 18

typedef struct _SRADEpsilonSwitchSettings
{
	uint8_t phyMode[RADEPSILON_MAX_PHY];
	uint8_t enablePhy[RADEPSILON_MAX_PHY];
	uint8_t speed[RADEPSILON_MAX_PHY];
	uint8_t legacy[RADEPSILON_MAX_PHY];
	uint8_t spoofedMac[6];
	uint8_t spoofMacFlag;
	uint8_t pad;
}SRADEpsilonSwitchSettings;//80

typedef struct _SRADEpsilonSettings
{
	/* Performance Test */
	uint16_t perf_en;//2

	CAN_SETTINGS can1;//12
	CANFD_SETTINGS canfd1;//10
	CAN_SETTINGS can2;//12
	CANFD_SETTINGS canfd2;//10
	LIN_SETTINGS lin1;//10

	uint16_t network_enables;//2
	uint16_t network_enables_2;//2
	uint16_t network_enables_3;//2
	uint64_t termination_enables;//8
	uint16_t misc_io_analog_enable;//2

	uint32_t pwr_man_timeout;//4
	uint16_t pwr_man_enable;//2

	uint16_t network_enabled_on_boot;//2

	/* ISO15765-2 Transport Layer */
	int16_t iso15765_separation_time_offset;//2
	uint16_t iso9141_kwp_enable_reserved;//2
	uint16_t iso_tester_pullup_enable;//2
	uint16_t iso_parity;//2
	uint16_t iso_msg_termination;//2
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings;//114
	ETHERNET_SETTINGS ethernet;//8

	STextAPISettings text_api;//72

	struct
	{
		uint32_t disableUsbCheckOnBoot : 1;
		uint32_t enableLatencyTest : 1;
		uint32_t enablePcEthernetComm : 1;
		uint32_t reserved : 29;
	} flags;//4

	SRADEpsilonSwitchSettings switchSettings;//80
	ETHERNET_SETTINGS2 ethernet2;//16
}SRADEpsilonSettings;//384
#define SRADEpsilonSettings_SIZE 384

typedef union
{
	uint64_t dword;
	struct
	{
		unsigned can_id:29;
		unsigned can_id_isExtended:1;
		uint16_t tcp_port;
		unsigned reserved:18;
	}config;
} SWILBridgeConfig;

typedef struct _SRADBMSSettings
{
        /* Performance Test */
	uint16_t perf_en;//2

	uint64_t termination_enables;

	CAN_SETTINGS can1;
    CANFD_SETTINGS canfd1;

    CAN_SETTINGS can2;
    CANFD_SETTINGS canfd2;

	uint16_t network_enables;
	uint16_t network_enables_2;
	uint16_t network_enables_3;

	/* ISO15765-2 Transport Layer */
	int16_t iso15765_separation_time_offset;//2

    struct
	{
		uint32_t disableUsbCheckOnBoot : 1;
		uint32_t enableLatencyTest : 1;
		uint32_t enablePcEthernetComm : 1;
		uint32_t reserved : 29;
	} flags;//4

	ETHERNET_SETTINGS ethernet;
	ETHERNET_SETTINGS2 ethernet2;

	uint32_t pwr_man_timeout;
	uint16_t pwr_man_enable;
	uint16_t network_enabled_on_boot;

	//WIL wrapped CAN and ETHERNET
	SWILBridgeConfig wil_config;
} SRADBMSSettings;
#define SRADBMSSettings_SIZE 108

#define GS_VERSION 5
typedef struct _GLOBAL_SETTINGS
{
	uint16_t version;
	uint16_t len;
	uint16_t chksum;
	union {
		SRedSettings red;
		SFireSettings fire;
		SFireVnetSettings firevnet;
		SCyanSettings cyan;
		SVCAN3Settings vcan3;
		SVCAN4Settings vcan4;
		SECUSettings ecu;
		SIEVBSettings ievb;
		SPendantSettings pendant;
		SRADGalaxySettings radgalaxy;
		SRADStar2Settings radstar2;
		SOBD2SimSettings neoobd2_sim;
		SCmProbeSettings cmprobe;
		SOBD2ProSettings obd2pro;
		SVCAN412Settings vcan412;
		SVCAN412Settings vcan4_12;// backwards compatibility with older code
		SECU_AVBSettings neoecu_avb;
		SRADSuperMoonSettings radsupermoon;
		SRADMoon2Settings radmoon2;
		SRADPlutoSettings pluto;
		SRADGigalogSettings radgigalog;
		SCANHubSettings canhub;
		SNeoECU12Settings neoecu12;
		SVCANRFSettings vcanrf;
		SEEVBSettings eevb;
		SFlexVnetzSettings flexvnetz;
		SVividCANSettings vividcan;
		SVCAN4IndSettings vcan4_ind;
		SRADGigastarSettings radgigastar;
		SRADJupiterSettings jupiter;
		SFire3Settings fire3;
		SRadMoonDuoSettings radmoonduo;
		SEtherBadgeSettings etherBadge;
		SRADA2BSettings rad_a2b;
		SRADEpsilonSettings epsilon;
		SOBD2LCSettings obd2lc;
		SRADBMSSettings rad_bms;
		// Make sure SDeviceSettings matches this
	};
} GLOBAL_SETTINGS;
#define GLOBAL_SETTINGS_SIZE (SCyanSettings_SIZE + 6)

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
	DeviceECU_AVBSettingsType,
	DeviceRADSuperMoonSettingsType,
	DeviceRADMoon2SettingsType,
	DeviceRADPlutoSettingsType,
	DeviceRADGigalogSettingsType,
	DeviceVCANRFSettingsType,
	DeviceEEVBSettingsType,
	DeviceVCAN4IndSettingsType,
	DeviceNeoECU12SettingsType,
	DeviceFlexVnetzSettingsType,
	DeviceCANHUBSettingsType,
	DeviceIEVBSettingsType,
	DeviceOBD2SimSettingsType,
	DeviceCMProbeSettingsType,
	DeviceOBD2ProSettingsType,
	DeviceRedSettingsType,
	DeviceRADPlutoSwitchSettingsType,
	DeviceRADGigastarSettingsType,
	DeviceRADJupiterSettingsType,
	DeviceFire3SettingsType,
	DeviceRadMoonDuoSettingsType,
	DeviceEtherBadgeSettingsType,
	DeviceRADA2BSettingsType,
	DeviceRADEpsilonSettingsType,
	DeviceOBD2LCSettingsType,
	DeviceRADBMSSettingsType,
	// add new settings type here
	// Also add to map inside cicsneoVI::Init()
	DeviceSettingsTypeMax,
	DeviceSettingsNone = 0xFFFFFFFF// just wanted to reserve this
} EDeviceSettingsType;

typedef struct _SDeviceSettings
{
	EDeviceSettingsType DeviceSettingType;
	union {
		SRedSettings red;
		SFireSettings fire;
		SFireVnetSettings firevnet;
		SCyanSettings cyan;
		SVCAN3Settings vcan3;
		SVCAN4Settings vcan4;
		SECUSettings ecu;
		SIEVBSettings ievb;
		SPendantSettings pendant;
		SRADGalaxySettings radgalaxy;
		SRADStar2Settings radstar2;
		SOBD2SimSettings neoobd2_sim;
		SCmProbeSettings cmprobe;
		SOBD2ProSettings obd2pro;
		SVCAN412Settings vcan412;
		SVCAN412Settings vcan4_12;// backwards compatibility with older code
		SECU_AVBSettings neoecu_avb;
		SRADSuperMoonSettings radsupermoon;
		SRADMoon2Settings radmoon2;
		SRADPlutoSettings pluto;
		SPlutoSwitchSettings plutoswitch;
		SRADGigalogSettings radgigalog;
		SCANHubSettings canhub;
		SNeoECU12Settings neoecu12;
		SVCANRFSettings vcanrf;
		SEEVBSettings eevb;
		SFlexVnetzSettings flexvnetz;
		SVividCANSettings vividcan;
		SVCAN4IndSettings vcan4_ind;
		SOBD2LCSettings obd2lc;
		SRADGigastarSettings radgigastar;
		SRADJupiterSettings jupiter;
		SFire3Settings fire3;
		SRadMoonDuoSettings radmoon_duo;
		SEtherBadgeSettings etherBadge;
		SRADA2BSettings rad_a2b;
		SRADEpsilonSettings epsilon;
		SRADBMSSettings rad_bms;
		// Make sure GLOBAL_SETTINGS matches this
		// NOTE: When adding new structures here implement inside icsneoGetDeviceSettings and icsneoSetDeviceSettings also.	} Settings;
	} Settings;
} SDeviceSettings;


typedef enum _EPlasmaIonVnetChannel_t
{
	PlasmaIonVnetChannelMain,// PLASMA = SLOT 2, ION = VNET2
	PlasmaIonVnetChannelA,// PLASMA = SLOT 1, ION = VNET1
	PlasmaIonVnetChannelB,// PLASMA = SLOT 3, ION = NA
	eSoftCore,
	eFpgaStatusResp,
} EPlasmaIonVnetChannel_t;

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

	union {
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

	union {
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

	union {
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

#if !defined(VSPY3_GUI) && !defined(WIVI_EXPORT) && !defined(VS4A) && !defined(CORELIB_CMAKE)
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
	union {
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
	union {
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
	union {
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

#if defined(VSPY3_GUI) || defined(WIVI_EXPORT) || defined(VS4A) || defined(CORELIB_CMAKE)
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
	union {
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
	union {
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
	union {
		struct
		{
			uint32_t StatusBitField3;
			uint32_t StatusBitField4;
		};
		uint8_t AckBytes[8];
	};
	uint32_t ExtraDataPtr;
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

#pragma pack(push)
#pragma pack(4)

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
	ethernetNetworkStatus_t ethernetStatus;
	uint8_t unused;
} icsFire3DeviceStatus;

typedef struct
{
	ethernetNetworkStatus_t ethernetStatus[4];
} icsRadMoonDuoDeviceStatus;

typedef struct
{
	ethernetNetworkStatus_t ethernetStatus[RADJUPITER_NUM_PORTS-1];
} icsRadJupiterDeviceStatus;

typedef struct
{
	ethernetNetworkStatus_t ethernetStatus;
} icsOBD2ProDeviceStatus;

typedef struct
{
	ethernetNetworkStatus_t ethernetStatus[4];
} icsRadPlutoDeviceStatus;

typedef struct
{
	ethernetNetworkStatus_t ethernetStatus;
} icsVcan4IndustrialDeviceStatus;

typedef struct
{
	ethernetNetworkStatus_t ethernetStatus;
} icsRadEpsilonDeviceStatus;

typedef struct
{
	ethernetNetworkStatus_t ethernetStatus;
} icsRadBMSDeviceStatus;

typedef union {
	icsFire2DeviceStatus fire2Status;
	icsVcan4DeviceStatus vcan4Status;
	icsFlexVnetzDeviceStatus flexVnetzStatus;
	icsFire3DeviceStatus fire3Status;
	icsRadMoonDuoDeviceStatus radMoonDuoStatus;
	icsRadJupiterDeviceStatus jupiterStatus;
	icsOBD2ProDeviceStatus obd2proStatus;
	icsRadPlutoDeviceStatus plutoStatus;
	icsVcan4IndustrialDeviceStatus vcan4indStatus;
	icsRadBMSDeviceStatus radBMSStatus;
} icsDeviceStatus;

#pragma pack(pop)

typedef struct
{
	char szName[128];//Adaptor name -  ASCII Null terminated
	char szDeviceName[64];//Device name	- ASCII Null terminated
	unsigned long Status;//Adaptor Status, 0 for disabled, 1 for enabled
	unsigned char
		bMAC_Address[6];// The Media Access Control (MAC) Address  of the Network interface in the PC that is to be connected to the vehicle.
	unsigned char bIPV6_Address
		[16];//The Ipv6 address assigned to the Network interface. No compressed or short form notation// If not available, all bytes are set to zero to imply the absence of an address.
	unsigned char bIPV4_Address[4];// The Ipv4 address assigned to the Network interface. If not available, all bytes are set to zero.
	unsigned long EthernetPinConfig;
} NDIS_ADAPTER_INFORMATION;

#define MAX_PHY_REG_PKT_ENTRIES 128
#define PHY_REG_PKT_VERSION 1
typedef struct SPhyRegPktHdr
{
	uint16_t numEntries;
	uint8_t version;
	uint8_t entryBytes;
}PhyRegPktHdr_t;

#define MAX_PHY_SETTINGS_STRUCT	128
#define MAX_NUMBYTES_PHYSETTINGS MAX_PHY_SETTINGS_STRUCT*sizeof(PhyRegPktHdr_t)

typedef struct SPhyRegPktClause22Mess
{
	uint8_t phyAddr; //5 bits
	uint8_t page;//8 bits
	uint16_t regAddr; //5 bits
	uint16_t regVal;
}PhyRegPktClause22Mess_t; //6 bytes

typedef struct SPhyRegPktClause45Mess
{
	uint8_t port; //5 bits    uint8_t device; //5 bits
	uint8_t device; //5 bits
	uint16_t regAddr;
	uint16_t regVal;
}PhyRegPktClause45Mess_t; //6 bytes

typedef enum SPhyRegPktStatus
{
	PHYREG_SUCCESS = 0,
	PHYREG_FAILURE,
	PHYREG_INVALID_MDIO_BUS_INDEX,
	PHYREG_INVALID_PHY_ADDR,
	PHYREG_RESERVED0,
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
		struct{
			uint16_t Enabled:1;
			uint16_t WriteEnable:1;
			uint16_t Clause45Enable:1;
			uint16_t status:2;
			uint16_t reserved:3;
			uint16_t BusIndex:4;
			uint16_t version:4;
		};
		uint16_t flags;
	};

	union
	{
		PhyRegPktClause22Mess_t clause22;
		PhyRegPktClause45Mess_t clause45;
	};
}PhyRegPkt_t;


#ifndef INTREPID_NO_CHECK_STRUCT_SIZE

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
CHECK_STRUCT_SIZE(SVCANRFSettings);
CHECK_STRUCT_SIZE(SECUSettings);
CHECK_STRUCT_SIZE(SPendantSettings);
CHECK_STRUCT_SIZE(SIEVBSettings);
CHECK_STRUCT_SIZE(SEEVBSettings);
CHECK_STRUCT_SIZE(SRADGalaxySettings);
CHECK_STRUCT_SIZE(SRADStar2Settings);
CHECK_STRUCT_SIZE(SOBD2SimSettings)
CHECK_STRUCT_SIZE(CmProbeSettings);
CHECK_STRUCT_SIZE(GLOBAL_SETTINGS);
CHECK_STRUCT_SIZE(stCM_ISO157652_TxMessage);
CHECK_STRUCT_SIZE(stCM_ISO157652_RxMessage);
CHECK_STRUCT_SIZE(spyFilterLong);
CHECK_STRUCT_SIZE(icsSpyMessage);
CHECK_STRUCT_SIZE(icsSpyMessageLong);
CHECK_STRUCT_SIZE(icsSpyMessageJ1850);
CHECK_STRUCT_SIZE(icsSpyMessageVSB);
CHECK_STRUCT_SIZE(OBD2ProSettings);
CHECK_STRUCT_SIZE(ISO15765_2015_TxMessage);
CHECK_STRUCT_SIZE(TIMESYNC_ICSHARDWARE_SETTINGS);
CHECK_STRUCT_SIZE(SRADSuperMoonSettings);
CHECK_STRUCT_SIZE(SRADMoon2Settings);
CHECK_STRUCT_SIZE(SRADGigalogSettings);
CHECK_STRUCT_SIZE(SRADGigastarSettings);
CHECK_STRUCT_SIZE(SExtSubCmdHdr);
CHECK_STRUCT_SIZE(SDiskStructure);
CHECK_STRUCT_SIZE(SDiskFormatProgress);
CHECK_STRUCT_SIZE(SDiskStatus);
CHECK_STRUCT_SIZE(SExtSubCmdComm);
CHECK_STRUCT_SIZE(SRADPlutoSettings);
CHECK_STRUCT_SIZE(CANHubSettings);
CHECK_STRUCT_SIZE(SNeoECU12Settings);
CHECK_STRUCT_SIZE(SPlutoSwitchSettings);
CHECK_STRUCT_SIZE(VCAN4IndSettings);
CHECK_STRUCT_SIZE(SRADJupiterSettings);
CHECK_STRUCT_SIZE(RadMoonDuoSettings);
CHECK_STRUCT_SIZE(SFire3Settings);
CHECK_STRUCT_SIZE(SEtherBadgeSettings);
CHECK_STRUCT_SIZE(SRADA2BSettings);
CHECK_STRUCT_SIZE(A2BMonitorSettings);
CHECK_STRUCT_SIZE(SRADEpsilonSettings);
CHECK_STRUCT_SIZE(RAD_GPTP_SETTINGS);
CHECK_STRUCT_SIZE(SRADBMSSettings);
#endif /* INTREPID_NO_CHECK_STRUCT_SIZE */

#endif /* _ICSNVC40_H */
