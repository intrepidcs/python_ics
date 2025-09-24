// --------------------------------------------------------------------------
// COPYRIGHT INTREPID CONTROL SYSTEMS, INC. (c) 1994-20xx
// Confidential and proprietary. This document and its contents are the
// property of Intrepid Control Systems, Inc. It is not to be copied,
// distributed, or otherwise disclosed or used without the prior written
// consent of Intrepid Control Systems Inc.
// All rights reserved.
// --------------------------------------------------------------------------

// SPY Status Bit Definitions
// Generated automatically - DO NOT MODIFY
// Modify cicsSpyStatusBits_config.yml and run cicsSpyStatusBits_gen.py
// Generated on: 2025-07-14 14:31:40

#ifndef CICSSPYSTATUSBITS_H_
#define CICSSPYSTATUSBITS_H_ 1

// WARNING: The following bit conflicts were detected:
// spystatus value 0x10000000: // VSI value 'SPY_STATUS_VSI_IFR_CRC_BIT' conflicts with common value 'SPY_STATUS_PDU'
// spystatus value 0x10000000: // A2B value 'SPY_STATUS_A2B_CONTROL' conflicts with common value 'SPY_STATUS_PDU'
// spystatus value 0x08: // A2B value 'SPY_STATUS_A2B_SCF_VALID_WAITING' conflicts with common value 'SPY_STATUS_REMOTE_FRAME'
// spystatus value 0x40000000: // A2B value 'SPY_STATUS_A2B_UPSTREAM' conflicts with common value 'SPY_STATUS_HIGH_SPEED'
// spystatus value 0x10000000: // FLEXRAY value 'SPY_STATUS_FLEXRAY_PDU' conflicts with common value 'SPY_STATUS_PDU'
// spystatus value 0x40000000: // FLEXRAY value 'SPY_STATUS_FLEXRAY_PDU_UPDATE_BIT_SET' conflicts with common value 'SPY_STATUS_HIGH_SPEED'
// spystatus value 0x08: // FLEXRAY value 'SPY_STATUS_FLEXRAY_PDU_NO_UPDATE_BIT' conflicts with common value 'SPY_STATUS_REMOTE_FRAME'

// Glyph definitions
// '|' - byte divider
// '.' - nibble divider
// '-' - unused bit
// 'o' - common bit
// 'x' - protocol specific bit
// '!' - conflict bit

// SPYSTATUS bit definitions
// SPYSTATUS - Common bits
// |oo-o.oooo|oooo.oooo|oooo.oo-o|oo-o.oooo|
#define SPY_STATUS_GLOBAL_ERR 0x01                   // Global error flag
#define SPY_STATUS_TX_MSG 0x02                       // Transmitted message
#define SPY_STATUS_XTD_FRAME 0x04                    // Extended frame
#define SPY_STATUS_REMOTE_FRAME 0x08                 // Remote frame
#define SPY_STATUS_CRC_ERROR 0x10                    // CRC error
#define SPY_STATUS_INCOMPLETE_FRAME 0x40             // Incomplete frame
#define SPY_STATUS_LOST_ARBITRATION 0x80             // Lost arbitration
#define SPY_STATUS_UNDEFINED_ERROR 0x0100            // Undefined error
#define SPY_STATUS_BUS_RECOVERED 0x0400              // Bus recovered
#define SPY_STATUS_BUS_SHORTED_PLUS 0x0800           // Bus shorted to plus
#define SPY_STATUS_BUS_SHORTED_GND 0x1000            // Bus shorted to ground
#define SPY_STATUS_CHECKSUM_ERROR 0x2000             // Checksum error
#define SPY_STATUS_BAD_MESSAGE_BIT_TIME_ERROR 0x4000 // Bad message bit time error
#define SPY_STATUS_TX_NOMATCH 0x8000                 // TX no match
#define SPY_STATUS_COMM_IN_OVERFLOW 0x010000         // Communication input overflow
#define SPY_STATUS_EXPECTED_LEN_MISMATCH 0x020000    // Expected length mismatch
#define SPY_STATUS_MSG_NO_MATCH 0x040000             // Message no match
#define SPY_STATUS_BREAK 0x080000                    // Break detected
#define SPY_STATUS_AVSI_REC_OVERFLOW 0x100000        // AVSI record overflow
#define SPY_STATUS_TEST_TRIGGER 0x200000             // Test trigger
#define SPY_STATUS_AUDIO_COMMENT 0x400000            // Audio comment
#define SPY_STATUS_GPS_DATA 0x800000                 // GPS data
#define SPY_STATUS_ANALOG_DIGITAL_INPUT 0x01000000   // Analog digital input
#define SPY_STATUS_TEXT_COMMENT 0x02000000           // Text comment
#define SPY_STATUS_NETWORK_MESSAGE_TYPE 0x04000000   // Network message type
#define SPY_STATUS_VSI_TX_UNDERRUN 0x08000000        // VSI TX underrun
#define SPY_STATUS_PDU 0x10000000                    // PDU message
#define SPY_STATUS_HIGH_SPEED 0x40000000             // High speed
#define SPY_STATUS_EXTENDED 0x80000000               // Extended - if this bit is set than decode StatusBitField3 in AckBytes

// SPYSTATUS - A2B protocol bits
// |o!x!.oooo|oooo.oooo|oooo.oo-o|oo-o.!ooo|
#define SPY_STATUS_A2B_SCF_VALID_WAITING 0x08 // A2B SCF valid waiting
#define SPY_STATUS_A2B_CONTROL 0x10000000     // A2B control message
#define SPY_STATUS_A2B_MONITOR 0x20000000     // A2B monitor message
#define SPY_STATUS_A2B_UPSTREAM 0x40000000    // A2B upstream message

// SPYSTATUS - CAN protocol bits
// |ooxo.oooo|oooo.oooo|oooo.ooxo|ooxo.oooo|
#define SPY_STATUS_CAN_ERROR_PASSIVE 0x20 // CAN error passive state
#define SPY_STATUS_CAN_BUS_OFF 0x0200     // CAN bus off state
#define SPY_STATUS_CANFD 0x20000000       // CAN FD frame

// SPYSTATUS - ETHERNET protocol bits
// |oo-o.oooo|oooo.oooo|oooo.oo-o|ooxo.oooo|
#define SPY_STATUS_HEADERCRC_ERROR 0x20 // Header CRC error

// SPYSTATUS - FLEXRAY protocol bits
// |o!-!.oooo|oooo.oooo|oooo.oo-o|oo-o.!ooo|
#define SPY_STATUS_FLEXRAY_PDU_NO_UPDATE_BIT 0x08        // FlexRay PDU no update bit
#define SPY_STATUS_FLEXRAY_PDU 0x10000000                // FlexRay PDU (alias for SPY_STATUS_PDU)
#define SPY_STATUS_FLEXRAY_PDU_UPDATE_BIT_SET 0x40000000 // FlexRay PDU update bit set

// SPYSTATUS - LIN protocol bits
// |ooxo.oooo|oooo.oooo|oooo.oo-o|oo-o.oooo|
#define SPY_STATUS_LIN_MASTER 0x20000000 // LIN master message

// SPYSTATUS - VSI protocol bits
// |oox!.oooo|oooo.oooo|oooo.oo-o|oo-o.oooo|
#define SPY_STATUS_VSI_IFR_CRC_BIT 0x10000000 // VSI IFR CRC bit
#define SPY_STATUS_INIT_MESSAGE 0x20000000    // Initialization message

// SPYSTATUS2 bit definitions
// SPYSTATUS2 - Common bits
// |----.----|---o.--oo|----.----|----.oooo|
#define SPY_STATUS2_HAS_VALUE 0x01
#define SPY_STATUS2_VALUE_IS_BOOLEAN 0x02
#define SPY_STATUS2_HIGH_VOLTAGE 0x04
#define SPY_STATUS2_LONG_MESSAGE 0x08
#define SPY_STATUS2_GLOBAL_CHANGE 0x010000
#define SPY_STATUS2_ERROR_FRAME 0x020000
#define SPY_STATUS2_END_OF_LONG_MESSAGE 0x100000

// SPYSTATUS2 - CAN protocol bits
// |----.----|-xxo.--oo|----.----|----.oooo|
#define SPY_STATUS2_CAN_ISO15765_LOGICAL_FRAME 0x200000
#define SPY_STATUS2_CAN_HAVE_LINK_DATA 0x400000

// SPYSTATUS2 - ETHERNET protocol bits
// |xxxx.xxxx|xxxo.--oo|----.----|----.oooo|
#define SPY_STATUS2_ETHERNET_CRC_ERROR 0x200000
#define SPY_STATUS2_ETHERNET_FRAME_TOO_SHORT 0x400000
#define SPY_STATUS2_ETHERNET_FCS_AVAILABLE 0x800000 // This frame contains FCS (4 bytes) obtained from ICS Ethernet hardware (ex. RAD-STAR)
#define SPY_STATUS2_ETHERNET_NO_PADDING 0x01000000
#define SPY_STATUS2_ETHERNET_PREEMPTION_ENABLED 0x02000000
#define SPY_STATUS2_ETHERNET_UPDATE_CHECKSUMS 0x04000000
#define SPY_STATUS2_ETHERNET_MANUALFCS_ENABLED 0x08000000
#define SPY_STATUS2_ETHERNET_FCS_VERIFIED 0x10000000
#define SPY_STATUS2_ETHERNET_T1S_SYMBOL 0x20000000
#define SPY_STATUS2_ETHERNET_T1S_BURST 0x40000000
#define SPY_STATUS2_ETHERNET_T1S_ETHERNET 0x80000000

// SPYSTATUS2 - FLEXRAY protocol bits
// |----.-xxx|xxxo.--oo|----.----|----.oooo|
#define SPY_STATUS2_FLEXRAY_TX_AB 0x200000
#define SPY_STATUS2_FLEXRAY_TX_AB_NO_A 0x400000
#define SPY_STATUS2_FLEXRAY_TX_AB_NO_B 0x800000
#define SPY_STATUS2_FLEXRAY_TX_AB_NO_MATCH 0x01000000
#define SPY_STATUS2_FLEXRAY_NO_CRC 0x02000000
#define SPY_STATUS2_FLEXRAY_NO_HEADERCRC 0x04000000 //

// SPYSTATUS2 - I2C protocol bits
// |----.----|xxxo.--oo|----.----|----.oooo|
#define SPY_STATUS2_I2C_ERR_TIMEOUT 0x200000
#define SPY_STATUS2_I2C_ERR_NACK 0x400000
#define SPY_STATUS2_I2C_DIR_READ 0x800000

// SPYSTATUS2 - ISO protocol bits
// |-xxx.x---|---o.--oo|----.----|----.oooo|
#define SPY_STATUS2_ISO_FRAME_ERROR 0x08000000      // ISO frame error
#define SPY_STATUS2_ISO_OVERFLOW_ERROR 0x10000000   // ISO overflow error
#define SPY_STATUS2_ISO_PARITY_ERROR 0x20000000     // ISO parity error
#define SPY_STATUS2_ISO_RX_TIMEOUT_ERROR 0x40000000 // ISO specific timeout error

// SPYSTATUS2 - LIN protocol bits
// |xxxx.xxxx|xxxo.--oo|----.----|----.oooo|
#define SPY_STATUS2_LIN_ERR_RX_BREAK_NOT_0 0x200000      // LIN RX break not 0 error
#define SPY_STATUS2_LIN_ERR_RX_BREAK_TOO_SHORT 0x400000  // LIN RX break too short error
#define SPY_STATUS2_LIN_ERR_RX_SYNC_NOT_55 0x800000      // LIN RX sync not 0x55 error
#define SPY_STATUS2_LIN_ERR_RX_DATA_GREATER_8 0x01000000 // LIN RX data greater than 8 bytes error
#define SPY_STATUS2_LIN_ERR_TX_RX_MISMATCH 0x02000000    // LIN TX/RX mismatch error
#define SPY_STATUS2_LIN_ERR_MSG_ID_PARITY 0x04000000     // LIN message ID parity error
#define SPY_STATUS2_LIN_SYNC_FRAME_ERROR 0x08000000      // LIN sync frame error
#define SPY_STATUS2_LIN_ID_FRAME_ERROR 0x10000000        // LIN ID frame error
#define SPY_STATUS2_LIN_SLAVE_BYTE_ERROR 0x20000000      // LIN slave byte error
#define SPY_STATUS2_LIN_RX_TIMEOUT_ERROR 0x40000000      // RX timeout error
#define SPY_STATUS2_LIN_NO_SLAVE_DATA 0x80000000         // LIN no slave data

// SPYSTATUS2 - MDIO protocol bits
// |-xxx.xxxx|xxxo.--oo|----.----|----.oooo|
#define SPY_STATUS2_MDIO_ERR_TIMEOUT 0x200000
#define SPY_STATUS2_MDIO_JOB_CANCELLED 0x400000
#define SPY_STATUS2_MDIO_INVALID_BUS 0x800000
#define SPY_STATUS2_MDIO_INVALID_PHYADDR 0x01000000
#define SPY_STATUS2_MDIO_INVALID_REGADDR 0x02000000
#define SPY_STATUS2_MDIO_UNSUPPORTED_CLAUSE 0x04000000
#define SPY_STATUS2_MDIO_UNSUPPORTED_OPCODE 0x08000000
#define SPY_STATUS2_MDIO_OVERFLOW 0x10000000
#define SPY_STATUS2_MDIO_CLAUSE45 0x20000000
#define SPY_STATUS2_MDIO_READ 0x40000000

// SPYSTATUS2 - MOST protocol bits
// |xxxx.xxxx|xxxo.--oo|----.----|----.oooo|
#define SPY_STATUS2_MOST_PACKET_DATA 0x200000
#define SPY_STATUS2_MOST_STATUS 0x400000    // reflects changes in light/lock/MPR/SBC/etc...
#define SPY_STATUS2_MOST_LOW_LEVEL 0x800000 // MOST low level message, allocs, deallocs, remote requests...*/
#define SPY_STATUS2_MOST_CONTROL_DATA 0x01000000
#define SPY_STATUS2_MOST_MHP_USER_DATA 0x02000000    // MOST HIGH User Data Frame
#define SPY_STATUS2_MOST_MHP_CONTROL_DATA 0x04000000 // MOST HIGH Control Data
#define SPY_STATUS2_MOST_I2S_DUMP 0x08000000
#define SPY_STATUS2_MOST_TOO_SHORT 0x10000000
#define SPY_STATUS2_MOST_MOST50 0x20000000 // absence of MOST50 and MOST150 implies it's MOST25
#define SPY_STATUS2_MOST_MOST150 0x40000000
#define SPY_STATUS2_MOST_CHANGED_PAR 0x80000000 // first byte in ack reflects what changed.

// SPYSTATUS2 - WBMS protocol bits
// |----.----|--xo.--oo|----.----|----.oooo|
#define SPY_STATUS2_WBMS_API_IS_CALLBACK 0x200000

// SPYSTATUS3 bit definitions
// SPYSTATUS3 - CAN protocol bits
// |----.----|-xxx.xxxx|-xxx.xxxx|----.-xxx|
#define SPY_STATUS3_CAN_ERR_PASSIVE 0x01            // CAN error passive state: typically when error counter is > 127
#define SPY_STATUS3_CAN_BUS_OFF 0x02                // CAN bus off state
#define SPY_STATUS3_CAN_ERR_WARNING 0x04            // CAN error warning: typically when error counter is > 96
#define SPY_STATUS3_CAN_DATAERR_STUFF_ERROR 0x0100  // CAN stuff error during the data payload phase
#define SPY_STATUS3_CAN_DATAERR_FORM_ERROR 0x0200   // CAN form error during the data payload phase
#define SPY_STATUS3_CAN_DATAERR_ACK_ERROR 0x0400    // CAN ack error during the data payload phase
#define SPY_STATUS3_CAN_DATAERR_BIT1_ERROR 0x0800   // CAN bit1 error during the data payload phase
#define SPY_STATUS3_CAN_DATAERR_BIT0_ERROR 0x1000   // CAN bit0 error during the data payload phase
#define SPY_STATUS3_CAN_DATAERR_CRC_ERROR 0x2000    // CAN CRC error during the data payload phase
#define SPY_STATUS3_CAN_DATAERR_NOCHANGE 0x4000     // CAN data error occurred before and no change yet
#define SPY_STATUS3_CAN_GENERR_STUFF_ERROR 0x010000 // CAN stuff error at the general frame level
#define SPY_STATUS3_CAN_GENERR_FORM_ERROR 0x020000  // CAN form error at the general frame level
#define SPY_STATUS3_CAN_GENERR_ACK_ERROR 0x040000   // CAN ack error at the general frame level
#define SPY_STATUS3_CAN_GENERR_BIT1_ERROR 0x080000  // CAN bit1 error at the general frame level
#define SPY_STATUS3_CAN_GENERR_BIT0_ERROR 0x100000  // CAN bit0 error at the general frame level
#define SPY_STATUS3_CAN_GENERR_CRC_ERROR 0x200000   // CAN CRC error at the general frame level
#define SPY_STATUS3_CAN_GENERR_NOCHANGE 0x400000    // CAN frame Error occurred before and no change yet

// SPYSTATUS3 - CANFD protocol bits
// |----.----|----.----|----.----|---x.xxxx|
#define SPY_STATUS3_CANFD_ESI 0x01 // CAN FD Error State Indicator (ESI) reflects the error state of the transmitting node
#define SPY_STATUS3_CANFD_IDE 0x02 // CAN FD Identifier Extension (IDE) indicates if standard or extended IDs are in use
#define SPY_STATUS3_CANFD_RTR 0x04
#define SPY_STATUS3_CANFD_FDF 0x08 // CAN FD Format (FDF) flag -- distinguishes classic CAN from CANFD
#define SPY_STATUS3_CANFD_BRS 0x10 // CANFD Baud Rate Select (BRS) flag, indicates if the data portion transmits at a higher bitrate

// SPYSTATUS3 - ETHERNET protocol bits
// |----.----|----.----|----.----|----.--xx|
#define SPY_STATUS3_ETHERNET_TX_COLLISION 0x01
#define SPY_STATUS3_ETHERNET_T1S_WAKE 0x02

// SPYSTATUS3 - LIN protocol bits
// |----.----|----.----|----.----|----.-xxx|
#define SPY_STATUS3_LIN_JUST_BREAK_SYNC 0x01
#define SPY_STATUS3_LIN_SLAVE_DATA_TOO_SHORT 0x02
#define SPY_STATUS3_LIN_ONLY_UPDATE_SLAVE_TABLE_ONCE 0x04

// SPYSTATUS4 bit definitions
// SPYSTATUS4 - ETHERNET protocol bits
// |----.----|----.----|----.----|----.--xx|
#define SPY_STATUS4_ETH_CRC_ERROR 0x01      // Ethernet CRC error
#define SPY_STATUS4_ETH_FRAME_TOO_LONG 0x02 // Ethernet frame too long

#endif // CICSSPYSTATUSBITS_H_
