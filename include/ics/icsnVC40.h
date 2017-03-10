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
#define NETID_I2C1 71
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
 * To the next person to add a network, please make it 512!
 */
#define NETID_HW_COM_LATENCY_TEST 512

/* Upper boundry of Network IDs */
#define NETID_MAX 100
#define NETID_INVALID 0xffff

/* Device types -- value of DeviceType of NeoDevice */
#define NEODEVICE_UNKNOWN 0
#define NEODEVICE_BLUE 1
#define NEODEVICE_SW_VCAN 2
#define NEODEVICE_DW_VCAN 4
#define NEODEVICE_FIRE 8
#define NEODEVICE_VCAN3 16
#define NEODEVICE_RED 64
#define NEODEVICE_ECU 128
#define NEODEVICE_IEVB 256
#define NEODEVICE_PENDANT 512
#define NEODEVICE_VIRTUAL_NEOVI 1024
#define NEODEVICE_ECUCHIP_UART 2048
#define NEODEVICE_PLASMA_1_11 0x1000
#define NEODEVICE_FIRE_VNET 0x2000
#define NEODEVICE_NEOANALOG 0x4000
#define NEODEVICE_CT_OBD 0x8000
#define NEODEVICE_PLASMA_1_12 0x10000
#define NEODEVICE_PLASMA_1_13 0x20000
#define NEODEVICE_ION_2 0x40000
#define NEODEVICE_RADSTAR 0x80000
#define NEODEVICE_ION_3 0x100000
#define NEODEVICE_VCAN4 0x200000
#define NEODEVICE_ECU15 0x400000
#define NEODEVICE_ECU25 0x800000
#define NEODEVICE_EEVB 0x1000000
#define NEODEVICE_VCANRF 0x2000000
#define NEODEVICE_FIRE2 0x4000000
#define NEODEVICE_FLEX 0x8000000
#define NEODEVICE_RADGALAXY 0x10000000
#define NEODEVICE_RADSTAR2 0x20000000
#define NEODEVICE_VIVIDCAN 0x40000000
#define NEODEVICE_OBD2_SIM 0x80000000
#define NEODEVICE_ANY_PLASMA                                                   \
  (NEODEVICE_PLASMA_1_11 | NEODEVICE_FIRE_VNET | NEODEVICE_PLASMA_1_12 |       \
   NEODEVICE_PLASMA_1_13)
#define NEODEVICE_ANY_ION (NEODEVICE_ION_2 | NEODEVICE_ION_3)
#define NEODEVICE_ALL 0xFFFFBFFF
#define NEODEVICE_NEOECUCHIP NEODEVICE_IEVB

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
#define SPY_STATUS_FLEXRAY_PDU 0x20000000
#define SPY_STATUS_HIGH_SPEED 0x40000000
#define SPY_STATUS_EXTENDED                                                    \
  0x80000000 /* if this bit is set than decode StatusBitField3 in AckBytes */
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
#define SPY_STATUS2_MOST_STATUS                                                \
  0x400000 /* reflects changes in light/lock/MPR/SBC/etc... */
#define SPY_STATUS2_MOST_LOW_LEVEL                                             \
  0x800000 /* MOST low level message, allocs, deallocs, remote requests...*/
#define SPY_STATUS2_MOST_CONTROL_DATA 0x1000000
#define SPY_STATUS2_MOST_MHP_USER_DATA 0x2000000 /* MOST HIGH User Data Frame  \
                                                    */
#define SPY_STATUS2_MOST_MHP_CONTROL_DATA 0x4000000 /* MOST HIGH Control Data  \
                                                       */
#define SPY_STATUS2_MOST_I2S_DUMP 0x8000000
#define SPY_STATUS2_MOST_TOO_SHORT 0x10000000
#define SPY_STATUS2_MOST_MOST50                                                \
  0x20000000 /* absence of MOST50 and MOST150 implies it's MOST25 */
#define SPY_STATUS2_MOST_MOST150 0x40000000
#define SPY_STATUS2_MOST_CHANGED_PAR                                           \
  0x80000000 /* first byte in ack reflects what changed. */

/* Ethernet Specific - check protocol before handling */
#define SPY_STATUS2_ETHERNET_CRC_ERROR 0x200000
#define SPY_STATUS2_ETHERNET_FRAME_TOO_SHORT 0x400000
#define SPY_STATUS2_ETHERNET_FCS_AVAILABLE                                     \
  0x800000 /* This frame contains FCS (4 bytes) obtained from ICS Ethernet     \
              hardware (ex. RAD-STAR) */
#define SPY_STATUS2_ETHERNET_NO_PADDING 0x1000000
#define SPY_STATUS2_ETHERNET_PREEMPTION_ENABLED 0x2000000

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

typedef struct {
  uint32_t DeviceType;
  int32_t Handle;
  int32_t NumberOfClients;
  int32_t SerialNumber;
  int32_t MaxAllowedClients;

} NeoDevice;

typedef union tagOptionsOpenNeoEx {
  struct {
    int32_t iNetworkID; /* Network ID indicating which CAN network to
                           communicate over */
  } CANOptions;

  uint32_t Reserved[16]; /* may be expanded in future revisions */
} OptionsOpenNeoEx, *POptionsOpenNeoEx;

typedef union tagOptionsFindNeoEx {
  struct {
    int32_t iNetworkID; /* Network ID indicating which CAN network to
                           communicate over */
  } CANOptions;
  uint32_t Reserved[16]; /* may be expanded in future revisions */

} OptionsFindNeoEx, *POptionsFindNeoEx;

typedef struct tagicsneoVICommand {
  uint8_t CommandType;
  uint8_t CommandByteLength;
  uint8_t Data[14];
} icsneoVICommand;

#pragma pack(push, 1)

typedef struct _stAPIFirmwareInfo {
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

} stAPIFirmwareInfo;

#pragma pack(pop)

/* Settings structures come are all packed to 2 bytes */
#pragma pack(push, 2)

/* SetBaudrate in CAN_SETTINGS */
enum { AUTO, USE_TQ };

/* Baudrate in CAN_SETTINGS/CANFD_SETTINGS */
enum {
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
enum { NORMAL = 0, DISABLE = 1, LOOPBACK = 2, LISTEN_ONLY = 3, LISTEN_ALL = 7 };

typedef struct {
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
enum {
  NO_CANFD,
  CANFD_ENABLED,
  CANFD_BRS_ENABLED,
  CANFD_ENABLED_ISO,
  CANFD_BRS_ENABLED_ISO
};

typedef struct _CANFD_SETTINGS {
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
enum {
  SWCAN_AUTOSWITCH_DISABLED,
  SWCAN_AUTOSWITCH_NO_RESISTOR,
  SWCAN_AUTOSWITCH_WITH_RESISTOR,
  SWCAN_AUTOSWITCH_DISABLED_RESISTOR_ENABLED
};

typedef struct {
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
enum {
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
enum { RESISTOR_ON, RESISTOR_OFF };

/* Mode in LIN_SETTINGS */
enum { SLEEP_MODE, SLOW_MODE, NORMAL_MODE, FAST_MODE };

typedef struct _LIN_SETTINGS {
  uint32_t
      Baudrate;   /* New products since FIREVNETEP should rely on this only */
  uint16_t spbrg; /* Precompiled to be 40Mhz/Baudrate/16 - 1.  Only used in
                     neoVI FIRE/FIREVNET(4dw) */
  uint8_t brgh;   /* Must be zero */
  uint8_t numBitsDelay;
  uint8_t MasterResistor;
  uint8_t Mode;
} LIN_SETTINGS;
#define LIN_SETTINGS_SIZE 10

typedef struct {
  uint16_t time_500us;
  uint16_t k;
  uint16_t l;
} ISO9141_KEYWORD2000__INIT_STEP;
#define ISO9141_KEYWORD2000__INIT_STEP_SIZE 6

typedef struct {
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

typedef struct _UART_SETTINGS {
  uint16_t Baudrate;
  uint16_t spbrg;
  uint16_t brgh;
  uint16_t parity;
  uint16_t stop_bits;
  uint8_t flow_control; /* 0- off, 1 - Simple CTS RTS */
  uint8_t reserved_1;
  union {
    uint32_t bOptions;
    struct {
      unsigned invert_tx : 1;
      unsigned invert_rx : 1;
      unsigned half_duplex : 1;
      unsigned reserved_bits : 13;
      unsigned reserved_bits2 : 16;
    };
  };
} UART_SETTINGS;
#define UART_SETTINGS_SIZE 16

typedef struct { uint16_t enable_convert_mode; } J1708_SETTINGS;
#define J1708_SETTINGS_SIZE 2

typedef struct _SRedSettings {
  CAN_SETTINGS can1;
  CAN_SETTINGS can2;
  LIN_SETTINGS lin1;
  LIN_SETTINGS lin2;
} SRedSettings;
#define SRedSettings_SIZE 44

typedef struct _STextAPISettings {
  uint32_t can1_tx_id;
  uint32_t can1_rx_id;
  union {
    struct {
      unsigned bExtended : 1;
      unsigned : 15;
    };
    uint32_t DWord;
  } can1_options;
  uint32_t can2_tx_id;
  uint32_t can2_rx_id;
  union {
    struct {
      unsigned bExtended : 1;
      unsigned : 15;
    };
    uint32_t DWord;
  } can2_options;

  uint32_t network_enables;

  uint32_t can3_tx_id;
  uint32_t can3_rx_id;
  union {
    struct {
      unsigned bExtended : 1;
      unsigned : 15;
    };
    uint32_t DWord;
  } can3_options;

  uint32_t can4_tx_id;
  uint32_t can4_rx_id;
  union {
    struct {
      unsigned bExtended : 1;
      unsigned : 15;
    };
    uint32_t DWord;
  } can4_options;

  uint32_t reserved[5];

} STextAPISettings;
#define STextAPISettings_SIZE 72

typedef union _stChipVersions {
  struct {
    uint8_t mpic_maj;
    uint8_t mpic_min;
    uint8_t upic_maj;
    uint8_t upic_min;
    uint8_t lpic_maj;
    uint8_t lpic_min;
    uint8_t jpic_maj;
    uint8_t jpic_min;
  } fire_versions;

  struct {
    uint8_t mpic_maj;
    uint8_t mpic_min;
    uint8_t core_maj;
    uint8_t core_min;
    uint8_t lpic_maj;
    uint8_t lpic_min;
    uint8_t hid_maj;
    uint8_t hid_min;
  } plasma_fire_vnet;

  struct {
    uint8_t mpic_maj;
    uint8_t mpic_min;
  } vcan3_versions;

  struct {
    uint8_t mpic_maj;
    uint8_t mpic_min;
  } vcanrf_versions;

  struct {
    uint8_t zynq_core_major;
    uint8_t zynq_core_minor;
  } radgalaxy_versions;

  struct {
    uint8_t zynq_core_major;
    uint8_t zynq_core_minor;
  } radstar2_versions;
  struct {
    uint8_t mpic_maj;
    uint8_t mpic_min;
  } vividcan_versions;

} stChipVersions;
#define stChipVersions_SIZE 8

typedef struct _SNeoMostGatewaySettings {
  uint16_t netId;
  uint8_t zero0;
  uint8_t Config;
} SNeoMostGatewaySettings;
#define SNeoMostGatewaySettings_SIZE 4

/* ucInterfaceType in OP_ETH_GENERAL_SETTINGS */
enum {
  OPETH_FUNC_TAP = 0,
  OPETH_FUNC_MEDIACONVERTER,
  OPETH_FUNC_TAP_LOW_LATENCY
};

typedef struct OP_ETH_GENERAL_SETTINGS_t {
  uint8_t ucInterfaceType;
  uint8_t reserved0[3];
  uint16_t tapPair0;
  uint16_t tapPair1;
  uint16_t tapPair2;
  uint16_t tapPair3;
  uint16_t tapPair4;
  uint16_t tapPair5;
  union {
    struct {
      unsigned bTapEnSwitch : 1;
      unsigned bTapEnPtp : 1;
      unsigned bEnReportLinkQuality : 1;
    } flags;
    unsigned uFlags;
  };
} OP_ETH_GENERAL_SETTINGS;
#define OP_ETH_GENERAL_SETTINGS_SIZE 20

/* ucConfigMode in OP_ETH_SETTINGS */
enum { OPETH_LINK_AUTO = 0, OPETH_LINK_MASTER, OPETH_LINK_SLAVE };

typedef struct OP_ETH_SETTINGS_t {
  uint8_t ucConfigMode;
  unsigned char preemption_en;
  unsigned char reserved0[14];
} OP_ETH_SETTINGS;
#define OP_ETH_SETTINGS_SIZE 16

typedef struct ETHERNET_SETTINGS_t {
  uint8_t duplex; /* 0 = half, 1 = full */
  uint8_t link_speed;
  uint8_t auto_neg;
  uint8_t led_mode;
  uint8_t rsvd[4];
} ETHERNET_SETTINGS;
#define ETHERNET_SETTINGS_SIZE 8

typedef struct {
  uint8_t term_enabled;
  uint8_t term_network;
  uint16_t reserved[2];
} CANTERM_SETTINGS;
#define CANTERM_SETTINGS_SIZE 6

typedef struct {
  uint8_t MasterEnable;
  uint8_t SlaveEnable;
  uint8_t MasterNetwork;
  uint8_t SlaveNetwork;
} TIMESYNC_ICSHARDWARE_SETTINGS;

/* These are bit positions for misc_io_on_report_eventsin SFireSettings */
enum {
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
  REPORT_ON_GPS,     /* send GPS 0x110-0x116 on change */
};

typedef struct _SFireSettings {
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

  /* ISO9141: iso_parity 0 - no parity, 1 - event, 2 - odd; iso_msg_termination
   * 0 - use inner frame time, 1 - GME CIM-SCL */

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
*Unfortuntely I haven't gone thru the trouble
*of splitting the FIRE VNET and FIRE settings
*structures. So until I can do so and reserve
*some time to test it, add a member that only
*VNET looks at for VNET features (like
*Android CoreMiniMsg pump).
*Defaults to zero.
*@see VNETBITS_FEATURE_ANDROID_MSGS
*/
  uint16_t vnetBits;
} SFireSettings;
#define SFireSettings_SIZE 744

typedef struct _SFireVnetSettings {
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
  uint16_t
      pwr_man_enable; /* 0 - off, 1 - sleep enabled, 2- idle enabled (fast
                         wakeup) */

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

  /* ISO9141: iso_parity 0 - no parity, 1 - event, 2 - odd; iso_msg_termination
   * 0 - use inner frame time, 1 - GME CIM-SCL */

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
*VNET options bitfield.
*Defaults to zero.
*@see VNETBITS_FEATURE_ANDROID_MSGS
*/
  uint16_t vnetBits;

  CAN_SETTINGS can5;
  CAN_SETTINGS can6;
  LIN_SETTINGS lin5;
  SWCAN_SETTINGS swcan2;
} SFireVnetSettings;
#define SFireVnetSettings_SIZE 792

typedef struct _SCyanSettings {
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
  struct {
    uint32_t disableUsbCheckOnBoot : 1;
    uint32_t reserved : 31;
  } flags;
  uint16_t digitalIoThresholdTicks;
  uint16_t digitalIoThresholdEnable;
} SCyanSettings;
#define SCyanSettings_SIZE 902

typedef SCyanSettings SFire2Settings;

typedef struct _SVCAN3Settings {
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

typedef struct _SVCAN4Settings {
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

  CAN_SETTINGS can3;
  CAN_SETTINGS can4;

  /* these correlate directly to the can1,2,3,4 settings above */
  CANFD_SETTINGS canfd1;
  CANFD_SETTINGS canfd2;
  CANFD_SETTINGS canfd3;
  CANFD_SETTINGS canfd4;

  LIN_SETTINGS lin1;
  LIN_SETTINGS lin2;

  uint16_t iso9141_kwp_enable_reserved;
  ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings;

  uint16_t iso_parity;
  uint16_t iso_msg_termination;
  uint16_t iso_tester_pullup_enable;

  uint16_t network_enables_2;

  ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_2;
  uint16_t iso_parity_2;
  uint16_t iso_msg_termination_2;

  UART_SETTINGS uart;
  UART_SETTINGS uart2;

  STextAPISettings text_api;
} SVCAN4Settings;
#define SVCAN4Settings_SIZE 470

typedef struct _SVCANRFSettings {
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

typedef struct _SECUSettings {
  /* ECU ID used in CAN communications.
*TX ID = ECU ID with bit28 cleared,
*RX ID = ECUID with bit28 set,
*ECU ID = 0 implies ECU ID = serial no with bit 27 set\
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

typedef struct _SPendantSettings {
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

typedef struct _SIEVBSettings {
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

typedef struct _SEEVBSettings {
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

typedef struct _SRADGalaxySettings {
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
} SRADGalaxySettings;
#define SRADGalaxySettings_SIZE 662

typedef struct _SRADStar2Settings {
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
} SRADStar2Settings;

#define SRADStar2Settings_SIZE 344

typedef struct _SVividCANSettings {
  uint32_t ecu_id;

  CAN_SETTINGS can1;     // 12 bytes
  SWCAN_SETTINGS swcan1; // 14 bytes
  CAN_SETTINGS lsftcan1; // 12 bytes

  uint16_t network_enables;
  uint16_t network_enabled_on_boot;

  uint16_t iso15765_separation_time_offset;

  uint16_t perf_en;

  uint32_t pwr_man_timeout;
  uint16_t pwr_man_enable;

  uint16_t can_switch_mode;

  uint16_t rsvd;
} SVividCANSettings;
#define SVividCANSettings_SIZE 60

typedef struct _SOBD2SimSettings {
  CAN_SETTINGS can1;
  CAN_SETTINGS can2;

  uint16_t network_enables;
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

  CANFD_SETTINGS canfd1;
  CANFD_SETTINGS canfd2;

  uint16_t network_enables_2;

  STextAPISettings text_api;

} SOBD2SimSettings;
#define SOBD2SimSettings_SIZE 140

#define GS_VERSION 5
typedef struct _GLOBAL_SETTINGS {
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
  };
} GLOBAL_SETTINGS;
#define GLOBAL_SETTINGS_SIZE (SCyanSettings_SIZE + 6)

#define NEOVI_3G_MAX_SETTINGS_SIZE sizeof(GLOBAL_SETTINGS)

typedef struct _stCM_ISO157652_TxMessage {
  uint16_t vs_netid; /* The netid of the message (determines which network to
                        transmit on),  not supported */

  uint8_t
      padding; /* The padding byte to use to fill the unused portion of
                       * transmitted CAN frames (single frame, first frame,
                * consecutive frame) */
  uint8_t tx_index;

  uint32_t id; /* arbId of transmitted frames (CAN id to transmit to) */
  uint32_t
      fc_id; /* flow control arb id filter value (response id from receiver) */
  uint32_t fc_id_mask; /* The flow control arb filter mask (response id from
                          receiver) */

  uint8_t stMin; /* Overrides the stMin that the receiver reports, see
                    overrideSTmin. Set to J2534's STMIN_TX if <= 0xFF */
  uint8_t
      blockSize; /* Overrides the block size that the receiver reports, see
                    overrideBlockSize.   Set to J2534's BS_TX if <= 0xFF */
  uint8_t flowControlExtendedAddress; /* Expected Extended Address byte of
                                         response from receiver.  see
                                         fc_ext_address_enable, not supported */
  uint8_t extendedAddress; /* Extended Address byte of transmitter. see
                              ext_address_enable, not supported */

  uint16_t
      fs_timeout;   /* max timeout (ms) for waiting on flow control respons. Set
                       this to N_BS_MAX's value if J2534 */
  uint16_t fs_wait; /* max timeout (ms) for waiting on flow control response
                     * after receiving flow control
                               * with flow status set to WAIT.   Set this to
                     * N_BS_MAX's value if J2534. */

  uint8_t data[4 * 1024]; /* The data */

  uint32_t num_bytes; /* Number of data bytes */

  union {
    struct {
      unsigned id_29_bit_enable : 1; /* Enables 29 bit arbId for transmitted
                                        frames.  Set to 1 so transmitted frames
                                        use 29 bit ids, not supported */
      unsigned
          fc_id_29_bit_enable : 1; /* Enables 29 bit arbId for Flow Control
                                      filter.  Set to 1 if receiver response
                                      uses 29 bit ids, not supported */
      unsigned
          ext_address_enable : 1; /* Enables Extended Addressing, Set to 1 if
                                     transmitted frames should have extended
                                     addres byte, not supported */
      unsigned fc_ext_address_enable : 1; /* Enables Extended Addressing for
                                             Flow Control filter.  Set to 1 if
                                             receiver responds with extended
                                             address byte, not supported */

      unsigned overrideSTmin : 1; /* Uses member stMin and not receiver's flow
                                     control's stMin */
      unsigned overrideBlockSize : 1; /* Uses member BlockSize and not
                                         receiver's flow control's BlockSize */
      unsigned paddingEnable : 1;     /* Enables padding */
      unsigned iscanFD : 1;
      unsigned isBRSEnabled : 1;
    };
    uint32_t flags;
  };
} stCM_ISO157652_TxMessage;
#define stCM_ISO157652_TxMessage_SIZE 4128

typedef struct _stCM_ISO157652_RxMessage {
  uint16_t vs_netid; /* The netid of the message (determines which network to
                        decode receives),  not supported */

  uint8_t padding; /* The padding byte to use to fill the unused portion of
                           * transmitted CAN frames (flow control), see
                    * paddingEnable. */

  uint32_t id; /* ArbId filter value for frames from transmitter (from ECU to
                  neoVI) */
  uint32_t id_mask; /* ArbId filter mask for frames from transmitter (from ECU
                       to neoVI) */
  uint32_t
      fc_id; /* flow control arbId to transmit in flow control (from neoVI to
                ECU) */

  uint8_t flowControlExtendedAddress; /* Extended Address byte used in flow
                                         control (from neoVI to ECU). see
                                         fc_ext_address_enable */
  uint8_t extendedAddress; /* Expected Extended Address byte of frames sent by
                              transmitter (from ECU to neoVI).  see
                              ext_address_enable */

  uint8_t blockSize; /* Block Size to report in flow control response */
  uint8_t stMin;     /* Minimum seperation time (between consecutive frames) to
                        report in flow control response */

  uint16_t cf_timeout; /* max timeout (ms) for waiting on consecutive frame.
                          Set this to N_CR_MAX's value in J2534 */

  union {
    struct {
      unsigned id_29_bit_enable : 1; /* Enables 29 bit arbId filter for frames
                                        (from ECU to neoVI) */
      unsigned
          fc_id_29_bit_enable : 1; /* Enables 29 bit arbId for Flow Control
                                      (from neoVI to ECU) */
      unsigned
          ext_address_enable : 1; /* Enables Extended Addressing (from ECU to
                                     neoVI) */
      unsigned fc_ext_address_enable : 1; /* Enables Extended Addressing (from
                                             neoVI to ECU) */
      unsigned
          enableFlowControlTransmission : 1; /*< Enables Flow Control frame
                                                transmission (from neoVI to ECU)
                                                */
      unsigned paddingEnable : 1;            /* Enables padding */
      unsigned iscanFD : 1;
      unsigned isBRSEnabled : 1;
    };
    uint32_t flags;
  };
  uint8_t reserved[16];
} stCM_ISO157652_RxMessage;
#define stCM_ISO157652_RxMessage_SIZE 42

#pragma pack(pop)

typedef struct {
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

#if !defined(VSPY3_GUI) && !defined(WIVI_EXPORT) && !defined(VS4A)
typedef int16_t descIdType;
#else
typedef uint32_t descIdType;
#endif

typedef struct _icsSpyMessage {
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
    struct {
      uint32_t StatusBitField3;
      uint32_t StatusBitField4;
    };
    uint8_t AckBytes[8];
  };
  void *ExtraDataPtr;
  uint8_t MiscData;
  uint8_t Reserved[3];
} icsSpyMessage;

#if defined(_WIN64) || defined(__x86_64__)
#ifdef VSPY3_GUI
#define icsSpyMessage_SIZE 80
#else
#define icsSpyMessage_SIZE 72
#endif
#else
#ifdef VSPY3_GUI
#define icsSpyMessage_SIZE 68
#else
#define icsSpyMessage_SIZE 64
#endif
#endif

typedef struct _icsSpyMessageLong {
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
    struct {
      uint32_t StatusBitField3;
      uint32_t StatusBitField4;
    };
    uint8_t AckBytes[8];
  };
  void *ExtraDataPtr;
  uint8_t MiscData;
  uint8_t Reserved[3];
} icsSpyMessageLong;
#define icsSpyMessageLong_SIZE icsSpyMessage_SIZE

typedef struct _icsSpyMessageJ1850 {
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
    struct {
      uint32_t StatusBitField3;
      uint32_t StatusBitField4;
    };
    uint8_t AckBytes[8];
  };
  void *ExtraDataPtr;
  uint8_t MiscData;
  uint8_t Reserved[3];
} icsSpyMessageJ1850;
#define icsSpyMessageJ1850_SIZE icsSpyMessage_SIZE

typedef struct _icsSpyMessageVSB {
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
    struct {
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
  * Be sure to use ICS_GET_NETWORKID and ICS_SET_NETWORKID, especially for slave
 * VNETs.
  */

#define ICS_GET_NETWORKID(m) ((((unsigned int)m.NetworkID2) << 8) | m.NetworkID)
#define ICS_SET_NETWORKID(m, X)                                                \
  do {                                                                         \
    m.NetworkID = X;                                                           \
    m.NetworkID2 = X >> 8;                                                     \
  } while (0)

#ifndef INTREPID_NO_CHECK_STRUCT_SIZE

#if defined(__cplusplus) && (__cplusplus > 199711L)
#define ics_static_assert(e, msg) static_assert(e, msg)
#else
#define ASSERT_CONCAT_(a, b) a##b
#define ASSERT_CONCAT(a, b) ASSERT_CONCAT_(a, b)
#define ics_static_assert(e, msg)                                              \
  enum { ASSERT_CONCAT(assert_line_, __LINE__) = 1 / (int)(!!(e)) }
#endif

#define CHECK_STRUCT_SIZE(X)                                                   \
  ics_static_assert(sizeof(X) == X##_SIZE, #X " is the wrong size");

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
CHECK_STRUCT_SIZE(GLOBAL_SETTINGS);
CHECK_STRUCT_SIZE(stCM_ISO157652_TxMessage);
CHECK_STRUCT_SIZE(stCM_ISO157652_RxMessage);
CHECK_STRUCT_SIZE(spyFilterLong);
CHECK_STRUCT_SIZE(icsSpyMessage);
CHECK_STRUCT_SIZE(icsSpyMessageLong);
CHECK_STRUCT_SIZE(icsSpyMessageJ1850);
CHECK_STRUCT_SIZE(icsSpyMessageVSB);

#endif /* INTREPID_NO_CHECK_STRUCT_SIZE */

#endif /* _ICSNVC40_H */
