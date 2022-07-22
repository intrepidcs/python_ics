#pragma pack(push, 8)
#pragma warning(push)
#pragma warning(disable : 4514 4820)
typedef unsigned __int64 uintptr_t;
typedef char* va_list;
void __cdecl __va_start(va_list*, ...);
#pragma warning(pop)
#pragma pack(pop)

#pragma warning(push)
#pragma warning(disable : 4514 4820)
#pragma pack(push, 8)
typedef unsigned __int64 size_t;
typedef __int64 ptrdiff_t;
typedef __int64 intptr_t;
typedef _Bool __vcrt_bool;
typedef unsigned short wchar_t;
void __cdecl __security_init_cookie(void);
void __cdecl __security_check_cookie(uintptr_t _StackCookie);
__declspec(noreturn) void __cdecl __report_gsfailure(uintptr_t _StackCookie);

extern uintptr_t __security_cookie;

#pragma pack(pop)

#pragma warning(pop)

#pragma warning(push)
#pragma warning(disable : 4514 4820)

typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef signed char int_least8_t;
typedef short int_least16_t;
typedef int int_least32_t;
typedef long long int_least64_t;
typedef unsigned char uint_least8_t;
typedef unsigned short uint_least16_t;
typedef unsigned int uint_least32_t;
typedef unsigned long long uint_least64_t;

typedef signed char int_fast8_t;
typedef int int_fast16_t;
typedef int int_fast32_t;
typedef long long int_fast64_t;
typedef unsigned char uint_fast8_t;
typedef unsigned int uint_fast16_t;
typedef unsigned int uint_fast32_t;
typedef unsigned long long uint_fast64_t;

typedef long long intmax_t;
typedef unsigned long long uintmax_t;
#pragma warning(pop)
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

  uint32_t Status;

  uint32_t Options;

  void* pAvailWIFINetwork;
  void* pWIFIInterfaceInfo;

  int isEthernetDevice;

  uint8_t MACAddress[6];
  uint16_t hardwareRev;
  uint16_t revReserved;
  uint32_t Reserved[6];

} NeoDeviceEx;

typedef union tagOptionsOpenNeoEx
{
  struct
  {
    int32_t iNetworkID;
  } CANOptions;

  uint32_t Reserved[16];
} OptionsOpenNeoEx, *POptionsOpenNeoEx;

typedef union tagOptionsFindNeoEx
{
  struct
  {
    int32_t iNetworkID;
  } CANOptions;
  uint32_t Reserved[16];

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
  int32_t iType;

  int32_t iMainFirmDateDay;
  int32_t iMainFirmDateMonth;
  int32_t iMainFirmDateYear;
  int32_t iMainFirmDateHour;
  int32_t iMainFirmDateMin;
  int32_t iMainFirmDateSecond;
  int32_t iMainFirmChkSum;

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

#pragma pack(push, 2)

enum
{
  AUTO,
  USE_TQ
};

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
  uint8_t FDMode;
  uint8_t FDBaudrate;
  uint8_t FDTqSeg1;
  uint8_t FDTqSeg2;
  uint8_t FDTqProp;
  uint8_t FDTqSync;
  uint16_t FDBRP;
  uint8_t FDTDC;
  uint8_t reserved;
} CANFD_SETTINGS;

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

enum
{
  RESISTOR_ON,
  RESISTOR_OFF
};

enum
{
  SLEEP_MODE,
  SLOW_MODE,
  NORMAL_MODE,
  FAST_MODE
};

typedef struct _LIN_SETTINGS
{
  uint32_t Baudrate;
  uint16_t spbrg;
  uint8_t brgh;
  uint8_t numBitsDelay;
  uint8_t MasterResistor;
  uint8_t Mode;
} LIN_SETTINGS;

typedef struct
{
  uint16_t time_500us;
  uint16_t k;
  uint16_t l;
} ISO9141_KEYWORD2000__INIT_STEP;

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

typedef struct _UART_SETTINGS
{
  uint16_t Baudrate;
  uint16_t spbrg;
  uint16_t brgh;
  uint16_t parity;
  uint16_t stop_bits;
  uint8_t flow_control;
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

typedef struct
{
  uint16_t enable_convert_mode;
} J1708_SETTINGS;

typedef struct _SRedSettings
{
  CAN_SETTINGS can1;
  CAN_SETTINGS can2;
  LIN_SETTINGS lin1;
  LIN_SETTINGS lin2;
} SRedSettings;

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

typedef struct _SNeoMostGatewaySettings
{
  uint16_t netId;
  uint8_t zero0;
  uint8_t Config;
} SNeoMostGatewaySettings;

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

typedef struct SRAD_GPTP_SETTINGS_s
{
  uint32_t neighborPropDelayThresh;
  uint32_t sys_phc_sync_interval;
  int8_t logPDelayReqInterval;
  int8_t logSyncInterval;
  int8_t logAnnounceInterval;
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
} RAD_GPTP_SETTINGS;

typedef struct SRAD_GPTP_AND_TAP_SETTINGS_s
{
  RAD_GPTP_SETTINGS gPTP;
  OP_ETH_GENERAL_SETTINGS tap;
} RAD_GPTP_AND_TAP_SETTINGS;

typedef struct HW_ETH_SETTINGS_t
{
  OP_ETH_GENERAL_SETTINGS General_Settings;
} HW_ETH_SETTINGS;

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
  union
  {
    struct
    {

      unsigned char mac_addr1[6];
      unsigned char mac_addr2[6];
      unsigned short mac_spoofing_en : 1;
      unsigned short mac_spoofing_isDstOrSrc : 1;
      unsigned short link_spd : 2;
      unsigned short q2112_phy_mode : 1;
      unsigned short reserved : 11;
    };
    unsigned char reserved0[14];
  };
} OP_ETH_SETTINGS;

typedef struct ETHERNET_SETTINGS_t
{
  uint8_t duplex;
  uint8_t link_speed;
  uint8_t auto_neg;
  uint8_t led_mode;
  uint8_t rsvd[4];
} ETHERNET_SETTINGS;
typedef struct ETHERNET_SETTINGS2_t
{

  uint8_t flags;
  uint8_t link_speed;
  uint32_t ip_addr;
  uint32_t netmask;
  uint32_t gateway;
  uint8_t rsvd[2];
} ETHERNET_SETTINGS2;

enum
{
  LINK_SPEED_AUTO_NEGOTIATION = 0,
  LINK_SPEED_1GBPS_FULL_DUPLEX,
  LINK_SPEED_1GBPS_HALF_DUPLEX,
  LINK_SPEED_100MBPS_FULL_DUPLEX,
  LINK_SPEED_100MBPS_HALF_DUPLEX,
  LINK_SPEED_10MBPS_FULL_DUPLEX,
  LINK_SPEED_10MBPS_HALF_DUPLEX,

  LINK_SPEED_COUNT,
};
typedef struct ETHERNET10G_SETTINGS_t
{

  uint32_t flags;
  uint32_t ip_addr;
  uint32_t netmask;
  uint32_t gateway;
  uint8_t link_speed;
  uint8_t rsvd2[7];
} ETHERNET10G_SETTINGS;

typedef struct LOGGER_SETTINGS_t
{

  uint8_t extraction_timeout;
  uint8_t rsvd[3];
} LOGGER_SETTINGS;

typedef struct DISK_SETTINGS_t
{
  uint8_t disk_layout;
  uint8_t disk_format;
  uint32_t disk_enables;
  uint8_t rsvd[8];
} DISK_SETTINGS;

typedef struct
{
  uint8_t term_enabled;
  uint8_t term_network;
  uint16_t reserved[2];
} CANTERM_SETTINGS;

typedef struct
{
  uint8_t MasterEnable;
  uint8_t SlaveEnable;
  uint8_t MasterNetwork;
  uint8_t SlaveNetwork;
} TIMESYNC_ICSHARDWARE_SETTINGS;

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

typedef struct _SDiskStatus
{
  uint16_t status;
  uint8_t sectors[8];
  uint8_t bytesPerSector[4];
} SDiskStatus;

typedef struct _SDiskStructure
{
  DISK_SETTINGS settings;
  uint16_t options;
} SDiskStructure;

typedef struct _SDiskDetails
{
  SDiskStructure structure;
  SDiskStatus status[12];
} SDiskDetails;

typedef struct _SDiskFormatProgress
{
  uint16_t state;
  uint8_t sectorsRemaining[8];
} SDiskFormatProgress;

typedef struct _StartDHCPServerCommand
{
  uint16_t networkId;
  uint32_t serverIpAddress;
  uint32_t subnetMask;
  uint32_t gatewayAddress;
  uint32_t startAddress;
  uint32_t endAddress;
  uint32_t leaseTime;
  uint32_t overwrite;
} StartDHCPServerCommand;

typedef struct _StopDHCPServerCommand
{
  uint16_t networkId;
} StopDHCPServerCommand;

typedef enum _ExtendedResponseCode
{
  EXTENDED_RESPONSE_OK = 0,

  EXTENDED_RESPONSE_INVALID_COMMAND = -1,

  EXTENDED_RESPONSE_INVALID_STATE = -2,

  EXTENDED_RESPONSE_OPERATION_FAILED = -3,

  EXTENDED_RESPONSE_OPERATION_PENDING = -4,

  EXTENDED_RESPONSE_INVALID_PARAMETER = -5,
} ExtendedResponseCode;

typedef struct _ExtendedResponseGeneric
{
  uint16_t commandType;
  int32_t returnCode;
} ExtendedResponseGeneric;

typedef struct
{
  uint16_t cmdVersion;
  uint16_t numValidBits;
  uint32_t featureBitfields[0];
} GetSupportedFeaturesResponse;

typedef struct _VersionReport
{
  uint8_t valid;
  uint8_t expansionSlot;
  uint8_t componentInfo;
  uint8_t reserved;
  uint32_t identifier;
  uint32_t dotVersion;
  uint32_t commitHash;
} VersionReport;

typedef struct _GetComponentVersions
{
  uint32_t reserved[2];
} GetComponentVersions;

typedef struct _ExtendedGetVersionsResponse
{
  uint16_t numVersions;
  VersionReport versions[(16)];
} GetComponentVersionsResponse;

enum
{
  swUpdateWrite,
  swUpdateErase,
  swUpdateGetProgress,
  swUpdateValidateAll,
  swUpdateGetBufferSize,
  swUpdateCheckVersion,
};

typedef struct
{
  uint32_t componentIdentifier;
  uint8_t commandType;
  uint32_t offset;
  uint32_t commandSizeOrProgress;
  uint8_t commandData[0];
} SoftwareUpdateCommand;

typedef struct _SExtSubCmdHdr
{
  uint16_t command;
  uint16_t length;
} SExtSubCmdHdr;

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
  union
  {
    SDiskStructure structure;
    SDiskDetails details;
    SDiskFormatProgress progress;
    StartDHCPServerCommand startDHCPServer;
    StopDHCPServerCommand stopDHCPServer;
    GetSupportedFeaturesResponse getSupportedFeatures;
    ExtendedResponseGeneric genericResponse;
    GPTPStatus gptpStatus;
    GetComponentVersions getComponentVersions;
    SoftwareUpdateCommand softwareUpdate;
    GetComponentVersionsResponse getComponentVersionsResponse;

  } extension;
} SExtSubCmdComm;
enum
{
  SERDESCAM_MODE_TAP_REPEATER = 0,
  SERDESCAM_MODE_SPLITTER,
  SERDESCAM_MODE_LOG_ONLY,
  SERDESCAM_MODE_CUSTOM,

  SERDESCAM_MODE_COUNT,
};

enum
{
  SERDESCAM_PIXEL_BIT_POS_0 = 0,
  SERDESCAM_PIXEL_BIT_POS_1,
  SERDESCAM_PIXEL_BIT_POS_2,
  SERDESCAM_PIXEL_BIT_POS_3,
};

enum
{
  SERDESCAM_VIDEO_FORMAT_NONE = -1,
  SERDESCAM_VIDEO_FORMAT_UYVY_422_8 = 0,
  SERDESCAM_VIDEO_FORMAT_YUYV_422_8,
  SERDESCAM_VIDEO_FORMAT_YVYU_422_8,
  SERDESCAM_VIDEO_FORMAT_VYUY_422_8,
  SERDESCAM_VIDEO_FORMAT_BAYER_BGGR_8,
  SERDESCAM_VIDEO_FORMAT_RAW_8,
  SERDESCAM_VIDEO_FORMAT_RAW_10,
  SERDESCAM_VIDEO_FORMAT_RAW_12,
  SERDESCAM_VIDEO_FORMAT_RAW_16,
  SERDESCAM_VIDEO_FORMAT_RAW_20,
  SERDESCAM_VIDEO_FORMAT_RAW_24,
  SERDESCAM_VIDEO_FORMAT_RAW_30,
  SERDESCAM_VIDEO_FORMAT_RAW_32,
  SERDESCAM_VIDEO_FORMAT_RAW_36,
  SERDESCAM_VIDEO_FORMAT_RGB888,
  SERDESCAM_VIDEO_FORMAT_UYVY_422_10LE_PACKED,
  SERDESCAM_VIDEO_FORMAT_YUYV_422_10LE_PACKED,
  SERDESCAM_VIDEO_FORMAT_YVYU_422_10LE_PACKED,
  SERDESCAM_VIDEO_FORMAT_VYUY_422_10LE_PACKED,
  SERDESCAM_VIDEO_FORMAT_BAYER_BGGR_10LE_PACKED,
  SERDESCAM_VIDEO_FORMAT_BAYER_BGGR_12LE_PACKED,
  SERDESCAM_VIDEO_FORMAT_BAYER_BGGR_16LE,
  SERDESCAM_VIDEO_FORMAT_BAYER_BGGR_16BE,
  SERDESCAM_VIDEO_FORMAT_JPEG,
  SERDESCAM_VIDEO_FORMAT_UYVY_422_12LE_PACKED,
  SERDESCAM_VIDEO_FORMAT_YUYV_422_12LE_PACKED,
  SERDESCAM_VIDEO_FORMAT_YVYU_422_12LE_PACKED,
  SERDESCAM_VIDEO_FORMAT_VYUY_422_12LE_PACKED,
  SERDESCAM_VIDEO_FORMAT_YUV422_10LE_PLANAR,
  SERDESCAM_VIDEO_FORMAT_YUV422_16LE_PLANAR,
  SERDESCAM_VIDEO_FORMAT_RGB565,
  SERDESCAM_VIDEO_FORMAT_RGB666,
  SERDESCAM_VIDEO_FORMAT_RAW_11x2,
  SERDESCAM_VIDEO_FORMAT_RAW_12x2,
  SERDESCAM_VIDEO_FORMAT_RAW_14,

  SERDESCAM_VIDEO_FORMAT_CSI2_UYVY_422_8,
  SERDESCAM_VIDEO_FORMAT_CSI2_YUYV_422_8,
  SERDESCAM_VIDEO_FORMAT_CSI2_YVYU_422_8,
  SERDESCAM_VIDEO_FORMAT_CSI2_VYUY_422_8,
  SERDESCAM_VIDEO_FORMAT_CSI2_UYVY_422_10LE_PACKED,
  SERDESCAM_VIDEO_FORMAT_CSI2_YUYV_422_10LE_PACKED,
  SERDESCAM_VIDEO_FORMAT_CSI2_YVYU_422_10LE_PACKED,
  SERDESCAM_VIDEO_FORMAT_CSI2_VYUY_422_10LE_PACKED,
  SERDESCAM_VIDEO_FORMAT_CSI2_UYVY_422_12LE_PACKED,
  SERDESCAM_VIDEO_FORMAT_CSI2_YUYV_422_12LE_PACKED,
  SERDESCAM_VIDEO_FORMAT_CSI2_YVYU_422_12LE_PACKED,
  SERDESCAM_VIDEO_FORMAT_CSI2_VYUY_422_12LE_PACKED,
  SERDESCAM_VIDEO_FORMAT_CSI2_RGB565,
  SERDESCAM_VIDEO_FORMAT_CSI2_RGB666,
  SERDESCAM_VIDEO_FORMAT_CSI2_RGB888,
  SERDESCAM_VIDEO_FORMAT_CSI2_BAYER_BGGR_8,
  SERDESCAM_VIDEO_FORMAT_CSI2_BAYER_BGGR_10LE_PACKED,
  SERDESCAM_VIDEO_FORMAT_CSI2_BAYER_BGGR_12LE_PACKED,
  SERDESCAM_VIDEO_FORMAT_CSI2_RAW_8,
  SERDESCAM_VIDEO_FORMAT_CSI2_RAW_10,
  SERDESCAM_VIDEO_FORMAT_CSI2_RAW_11x2,
  SERDESCAM_VIDEO_FORMAT_CSI2_RAW_12,
  SERDESCAM_VIDEO_FORMAT_CSI2_RAW_12x2,
  SERDESCAM_VIDEO_FORMAT_CSI2_RAW_14,
  SERDESCAM_VIDEO_FORMAT_CSI2_RAW_16,
  SERDESCAM_VIDEO_FORMAT_CSI2_RAW_20,
  SERDESCAM_VIDEO_FORMAT_CSI2_RAW_24,
  SERDESCAM_VIDEO_FORMAT_CSI2_RAW_30,
  SERDESCAM_VIDEO_FORMAT_CSI2_RAW_32,
  SERDESCAM_VIDEO_FORMAT_CSI2_RAW_36,

  SERDESCAM_VIDEO_FORMAT_BAYER_RGGB_8,
  SERDESCAM_VIDEO_FORMAT_BAYER_RGGB_10LE_PACKED,
  SERDESCAM_VIDEO_FORMAT_BAYER_RGGB_12LE_PACKED,
  SERDESCAM_VIDEO_FORMAT_BAYER_RGGB_16LE,
  SERDESCAM_VIDEO_FORMAT_BAYER_RGGB_16BE,
  SERDESCAM_VIDEO_FORMAT_CSI2_BAYER_RGGB_8,
  SERDESCAM_VIDEO_FORMAT_CSI2_BAYER_RGGB_10LE_PACKED,
  SERDESCAM_VIDEO_FORMAT_CSI2_BAYER_RGGB_12LE_PACKED,

  SERDESCAM_VIDEO_FORMAT_BAYER_GBRG_8,
  SERDESCAM_VIDEO_FORMAT_BAYER_GBRG_10LE_PACKED,
  SERDESCAM_VIDEO_FORMAT_BAYER_GBRG_12LE_PACKED,
  SERDESCAM_VIDEO_FORMAT_BAYER_GBRG_16LE,
  SERDESCAM_VIDEO_FORMAT_BAYER_GBRG_16BE,
  SERDESCAM_VIDEO_FORMAT_CSI2_BAYER_GBRG_8,
  SERDESCAM_VIDEO_FORMAT_CSI2_BAYER_GBRG_10LE_PACKED,
  SERDESCAM_VIDEO_FORMAT_CSI2_BAYER_GBRG_12LE_PACKED,

  SERDESCAM_VIDEO_FORMAT_BAYER_GRBG_8,
  SERDESCAM_VIDEO_FORMAT_BAYER_GRBG_10LE_PACKED,
  SERDESCAM_VIDEO_FORMAT_BAYER_GRBG_12LE_PACKED,
  SERDESCAM_VIDEO_FORMAT_BAYER_GRBG_16LE,
  SERDESCAM_VIDEO_FORMAT_BAYER_GRBG_16BE,
  SERDESCAM_VIDEO_FORMAT_CSI2_BAYER_GRBG_8,
  SERDESCAM_VIDEO_FORMAT_CSI2_BAYER_GRBG_10LE_PACKED,
  SERDESCAM_VIDEO_FORMAT_CSI2_BAYER_GRBG_12LE_PACKED,

  SERDESCAM_VIDEO_FORMAT_COUNT,
};

typedef struct SERDESCAM_SETTINGS_t
{
  uint32_t flags;
  uint8_t mode;
  uint8_t rsvd1;
  uint8_t bitPos;
  uint8_t videoFormat;
  uint16_t resWidth;
  uint16_t resHeight;
  uint8_t frameSkip;
  uint8_t rsvd2[19];
} SERDESCAM_SETTINGS;

typedef struct SERDESPOC_SETTINGS_t
{
  uint8_t mode;
  uint8_t rsvd[6];
  uint8_t voltage;
  uint16_t chksum;
} SERDESPOC_SETTINGS;

enum
{
  SERDESGEN_MOD_ID_NONE = 0,
  SERDESGEN_MOD_ID_FPD3_2x2 = 1,
  SERDESGEN_MOD_ID_GMSL2_2x2 = 2,
  SERDESGEN_MOD_ID_GMSL1_4x4 = 3,
  SERDESGEN_MOD_ID_FPD3_TO_GMSL2_2x2 = 4,

  SERDESGEN_MOD_ID_UNKNOWN = -1,
};

typedef struct SERDESGEN_SETTINGS_t
{

  uint16_t flags;
  uint8_t rsvd1;
  uint8_t mod_id;
  uint16_t tx_speed;
  uint16_t rx_speed;

  uint8_t rsvd2[24];
} SERDESGEN_SETTINGS;

typedef struct _RadMoonDuoConverterSettings
{

  uint8_t linkMode0;
  uint8_t linkMode1;

  uint8_t converter1Mode;

  uint32_t ipAddress;
  uint32_t ipMask;
  uint32_t ipGateway;
} RadMoonDuoConverterSettings;
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
  REPORT_ON_PWM_IN1,
  REPORT_ON_GPS,
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
  uint16_t vnetBits;
} SFireSettings;

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
  uint16_t vnetBits;

  CAN_SETTINGS can5;
  CAN_SETTINGS can6;
  LIN_SETTINGS lin5;
  SWCAN_SETTINGS swcan2;
} SFireVnetSettings;

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
  ETHERNET_SETTINGS2 ethernet2;
} SCyanSettings;

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

typedef struct _SECUSettings
{

  uint32_t ecu_id;

  uint16_t selected_network;

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

typedef struct _SPendantSettings
{

  uint32_t ecu_id;

  uint16_t selected_network;

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

typedef struct _SIEVBSettings
{

  uint32_t ecu_id;

  uint16_t selected_network;

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

  ETHERNET_SETTINGS2 ethernet1;
  ETHERNET_SETTINGS2 ethernet2;
  uint16_t network_enables_4;

  RAD_GPTP_SETTINGS gPTP;
} SRADGalaxySettings;

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

typedef struct
{
  uint8_t tdmMode;
  uint8_t upstreamChannelOffset;
  uint8_t downstreamChannelOffset;
  uint8_t nodeType;

  uint8_t flags;
  uint8_t reserved[15];
} A2BMonitorSettings;

typedef struct _SRADA2BSettings
{

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
  uint32_t pwr_man_timeout;
  uint16_t pwr_man_enable;
} SRADA2BSettings;

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
  uint8_t rsvd1[8];
  uint8_t rsvd2[8];

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

typedef struct _SVividCANSettings
{
  uint32_t ecu_id;

  CAN_SETTINGS can1;
  SWCAN_SETTINGS swcan1;
  CAN_SETTINGS lsftcan1;

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

typedef struct _CmProbeSettings
{

  uint16_t network_enables;
  uint16_t network_enabled_on_boot;

} CmProbeSettings, SCmProbeSettings;

typedef struct _OBD2ProSettings
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

  SWCAN_SETTINGS swcan1;

  LIN_SETTINGS lin1;
  LIN_SETTINGS lin2;

  ETHERNET_SETTINGS ethernet;

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

typedef struct _VCAN412Settings
{

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

  int16_t iso15765_separation_time_offset;

  STextAPISettings text_api;
  struct
  {
    uint32_t disableUsbCheckOnBoot : 1;
    uint32_t enableLatencyTest : 1;
    uint32_t reserved : 30;
  } flags;
} VCAN412Settings, SVCAN412Settings;

typedef struct _neoECU_AVBSettings
{

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

  int16_t iso15765_separation_time_offset;

  STextAPISettings text_api;
  struct
  {
    uint32_t disableUsbCheckOnBoot : 1;
    uint32_t enableLatencyTest : 1;
    uint32_t reserved : 30;
  } flags;
} ECU_AVBSettings, SECU_AVBSettings;
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
} SPluto_L2AddressLookupEntry;

typedef struct SPluto_L2AddressLookupParams_s
{
  uint16_t maxage;
  uint8_t dyn_tbsz;
  uint8_t poly;
  uint8_t shared_learn;
  uint8_t no_enf_hostprt;
  uint8_t no_mgmt_learn;
  uint8_t pad;
} SPluto_L2AddressLookupParams;

typedef struct SPluto_L2ForwardingParams_s
{
  uint16_t part_spc[8];
  uint8_t max_dynp;
  uint8_t pad;
} SPluto_L2ForwardingParams;

typedef struct SPluto_L2ForwardingEntry_s
{
  uint8_t vlan_pmap[8];
  uint8_t bc_domain;
  uint8_t reach_port;
  uint8_t fl_domain;
  uint8_t pad;
} SPluto_L2ForwardingEntry;

typedef struct SPluto_L2Policing_s
{
  uint16_t smax;
  uint16_t rate;
  uint16_t maxlen;
  uint8_t sharindx;
  uint8_t partition;
} SPluto_L2Policing;

typedef struct SPluto_VlanLookup_s
{
  uint16_t vlanid;
  uint8_t ving_mirr;
  uint8_t vegr_mirr;
  uint8_t vmemb_port;
  uint8_t vlan_bc;
  uint8_t tag_port;
  uint8_t pad;
} SPluto_VlanLookup;

typedef struct SPluto_MacConfig_s
{
  uint16_t top[8];
  uint16_t base[8];
  uint16_t tp_delin;
  uint16_t tp_delout;
  uint16_t vlanid;
  uint8_t enabled[8];
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
} SPluto_MacConfig;

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
} SPluto_RetaggingEntry;

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
} SPluto_GeneralParams;

typedef struct SPluto_VlLookupEntry_s
{
  union
  {

    struct
    {
      uint64_t macaddr;
      uint16_t vlanid;
      uint8_t destports;
      uint8_t iscritical;
      uint8_t port;
      uint8_t vlanprior;
    } vllupformat0;

    struct
    {
      uint16_t vlid;
      uint8_t egrmirr;
      uint8_t ingrmirr;
      uint8_t port;
    } vllupformat1;
  };
} SPluto_VlLookupEntry;

typedef struct SPluto_VlPolicingEntry_s
{
  uint64_t type;
  uint64_t maxlen;
  uint64_t sharindx;
  uint64_t bag;
  uint64_t jitter;
} SPluto_VlPolicingEntry;

typedef struct SPluto_VlForwardingParams_s
{
  uint16_t partspc[8];
  uint8_t debugen;
  uint8_t pad;
} SPluto_VlForwardingParams;

typedef struct SPluto_VlForwardingEntry_s
{
  uint8_t type;
  uint8_t priority;
  uint8_t partition;
  uint8_t destports;
} SPluto_VlForwardingEntry;

typedef struct SPluto_AVBParams_s
{
  uint64_t destmeta;
  uint64_t srcmeta;
} SPluto_AVBParams;

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
} SPluto_ClockSyncParams;
typedef struct SPlutoPtpParams_s
{
  uint32_t neighborPropDelayThresh;
  uint32_t sys_phc_sync_interval;
  int8_t logPDelayReqInterval;
  int8_t logSyncInterval;
  int8_t logAnnounceInterval;
  uint8_t profile;
  uint8_t priority1;
  uint8_t clockclass;
  uint8_t clockaccuracy;
  uint8_t priority2;
  uint16_t offset_scaled_log_variance;
  uint8_t gPTPportRole[5 - 1];
  uint8_t portEnable[5 - 1];
} PlutoPtpParams_t;

typedef struct SPluto_CustomParams_s
{
  uint8_t mode[5];
  uint8_t speed[5];
  uint8_t enablePhy[5];
  uint8_t ae1Select;
  uint8_t usbSelect;
  uint8_t pad;
  PlutoPtpParams_t ptpParams;
} SPluto_CustomParams;

typedef struct SPlutoSwitchSettings_s
{
  ExtendedDataFlashHeader_t flashHeader;
  SPluto_L2AddressLookupParams l2_addressLookupParams;
  SPluto_L2AddressLookupEntry l2_addressLookupEntries[1024];
  SPluto_L2Policing l2_policing[45];
  SPluto_L2ForwardingParams l2_forwardingParams;
  SPluto_L2ForwardingEntry l2_ForwardingEntries[13];
  SPluto_VlanLookup vlan_LookupEntries[4096];
  SPluto_MacConfig macConfig[5];
  SPluto_GeneralParams generalParams;
  SPluto_RetaggingEntry retagging[32];

} SPlutoSwitchSettings;

typedef struct _RADPlutoSettings
{

  uint16_t perf_en;

  CAN_SETTINGS can1;
  CANFD_SETTINGS canfd1;
  CAN_SETTINGS can2;
  CANFD_SETTINGS canfd2;
  LIN_SETTINGS lin1;

  uint16_t network_enables;
  uint16_t network_enables_2;
  uint16_t network_enables_3;
  uint64_t termination_enables;
  uint16_t misc_io_analog_enable;

  uint32_t pwr_man_timeout;
  uint16_t pwr_man_enable;

  uint16_t network_enabled_on_boot;

  int16_t iso15765_separation_time_offset;
  uint16_t iso9141_kwp_enable_reserved;
  uint16_t iso_tester_pullup_enable;
  uint16_t iso_parity;
  uint16_t iso_msg_termination;
  ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings;
  ETHERNET_SETTINGS ethernet;

  STextAPISettings text_api;
  struct
  {
    uint32_t disableUsbCheckOnBoot : 1;
    uint32_t enableLatencyTest : 1;
    uint32_t enablePcEthernetComm : 1;
    uint32_t reserved : 29;
  } flags;

  SPluto_CustomParams custom;
  ETHERNET_SETTINGS2 ethernet2;
} SRADPlutoSettings;

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
  uint32_t reserved_field[2];
} SNeoECU12Settings;

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

typedef struct _SOBD2LCSettings
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
  SWCAN_SETTINGS swcan1;
  LIN_SETTINGS lin1;

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
    };
  } network_enables;
  uint32_t pwr_man_timeout;
  uint16_t pwr_man_enable;
  uint16_t network_enabled_on_boot;

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
  ETHERNET_SETTINGS2 ethernet2;
} OBD2LCSettings, SOBD2LCSettings;

typedef struct SJupiterPtpParams_s
{
  uint32_t neighborPropDelay;
  int8_t initLogPDelayReqInterval;
  int8_t initLogSyncInterval;
  int8_t operationLogPDelayReqInterval;
  int8_t operationLogSyncInterval;
  uint8_t gPTPportRole[8];
} JupiterPtpParams_t;

typedef struct _SRADJupiterSwitchSettings
{
  uint8_t phyMode[8];
  uint8_t enablePhy[8];
  uint8_t port7Select;
  uint8_t port8Select;
  uint8_t port8Speed;
  uint8_t port8Legacy;
  uint8_t spoofMacFlag;
  uint8_t spoofedMac[6];
  uint8_t pad;
  JupiterPtpParams_t ptpParams;
} SRADJupiterSwitchSettings;

typedef struct _SRADJupiterSettings
{

  uint16_t perf_en;

  CAN_SETTINGS can1;
  CANFD_SETTINGS canfd1;
  CAN_SETTINGS can2;
  CANFD_SETTINGS canfd2;
  LIN_SETTINGS lin1;

  uint16_t network_enables;
  uint16_t network_enables_2;
  uint16_t network_enables_3;
  uint64_t termination_enables;
  uint16_t misc_io_analog_enable;

  uint32_t pwr_man_timeout;
  uint16_t pwr_man_enable;

  uint16_t network_enabled_on_boot;

  int16_t iso15765_separation_time_offset;
  uint16_t iso9141_kwp_enable_reserved;
  uint16_t iso_tester_pullup_enable;
  uint16_t iso_parity;
  uint16_t iso_msg_termination;
  ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings;
  ETHERNET_SETTINGS ethernet;

  STextAPISettings text_api;

  struct
  {
    uint32_t disableUsbCheckOnBoot : 1;
    uint32_t enableLatencyTest : 1;
    uint32_t enablePcEthernetComm : 1;
    uint32_t reserved : 29;
  } flags;

  SRADJupiterSwitchSettings switchSettings;
  ETHERNET_SETTINGS2 ethernet2;
} SRADJupiterSettings;

typedef struct
{
  uint8_t allowBoot;
  uint8_t useExternalWifiAntenna;
  uint8_t reserved[6];
} Fire3LinuxSettings;

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
} SFire3Settings;

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

typedef struct _SEtherBadgeSettings
{

  uint16_t perf_en;

  CAN_SETTINGS can1;
  CANFD_SETTINGS canfd1;
  CAN_SETTINGS can2;
  CANFD_SETTINGS canfd2;
  LIN_SETTINGS lin1;

  uint16_t network_enables;
  uint16_t network_enables_2;
  uint16_t network_enables_3;
  uint64_t termination_enables;

  uint32_t pwr_man_timeout;
  uint16_t pwr_man_enable;

  uint16_t network_enabled_on_boot;

  int16_t iso15765_separation_time_offset;
  uint16_t iso9141_kwp_enable_reserved;
  uint16_t iso_tester_pullup_enable;
  uint16_t iso_parity;
  uint16_t iso_msg_termination;
  ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings;
  ETHERNET_SETTINGS ethernet;

  uint16_t misc_io_initial_ddr;
  uint16_t misc_io_initial_latch;
  uint16_t misc_io_report_period;
  uint16_t misc_io_on_report_events;
  uint16_t misc_io_analog_enable;
  uint16_t ain_sample_period;
  uint16_t ain_threshold;

  STextAPISettings text_api;

  struct
  {
    uint32_t disableUsbCheckOnBoot : 1;
    uint32_t enableLatencyTest : 1;
    uint32_t enablePcEthernetComm : 1;
    uint32_t reserved : 29;
  } flags;

  ETHERNET_SETTINGS2 ethernet2;
} SEtherBadgeSettings;

typedef struct _SRADEpsilonSwitchSettings
{
  uint8_t phyMode[18];
  uint8_t enablePhy[18];
  uint8_t speed[18];
  uint8_t legacy[18];
  uint8_t spoofedMac[6];
  uint8_t spoofMacFlag;
  uint8_t pad;
} SRADEpsilonSwitchSettings;

typedef struct _SRADEpsilonSettings
{

  uint16_t perf_en;

  CAN_SETTINGS can1;
  CANFD_SETTINGS canfd1;
  CAN_SETTINGS can2;
  CANFD_SETTINGS canfd2;
  LIN_SETTINGS lin1;

  uint16_t network_enables;
  uint16_t network_enables_2;
  uint16_t network_enables_3;
  uint64_t termination_enables;
  uint16_t misc_io_analog_enable;

  uint32_t pwr_man_timeout;
  uint16_t pwr_man_enable;

  uint16_t network_enabled_on_boot;

  int16_t iso15765_separation_time_offset;
  uint16_t iso9141_kwp_enable_reserved;
  uint16_t iso_tester_pullup_enable;
  uint16_t iso_parity;
  uint16_t iso_msg_termination;
  ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings;
  ETHERNET_SETTINGS ethernet;

  STextAPISettings text_api;

  struct
  {
    uint32_t disableUsbCheckOnBoot : 1;
    uint32_t enableLatencyTest : 1;
    uint32_t enablePcEthernetComm : 1;
    uint32_t reserved : 29;
  } flags;

  SRADEpsilonSwitchSettings switchSettings;
  ETHERNET_SETTINGS2 ethernet2;
} SRADEpsilonSettings;

typedef union
{
  uint64_t dword;
  struct
  {
    unsigned can_id : 29;
    unsigned can_id_isExtended : 1;
    uint16_t tcp_port;
    unsigned reserved : 18;
  } config;
} SWILBridgeConfig;

typedef struct _SRADBMSSettings
{

  uint16_t perf_en;

  uint64_t termination_enables;

  CAN_SETTINGS can1;
  CANFD_SETTINGS canfd1;

  CAN_SETTINGS can2;
  CANFD_SETTINGS canfd2;

  uint16_t network_enables;
  uint16_t network_enables_2;
  uint16_t network_enables_3;

  int16_t iso15765_separation_time_offset;

  struct
  {
    uint32_t disableUsbCheckOnBoot : 1;
    uint32_t enableLatencyTest : 1;
    uint32_t enablePcEthernetComm : 1;
    uint32_t reserved : 29;
  } flags;

  ETHERNET_SETTINGS ethernet;
  ETHERNET_SETTINGS2 ethernet2;

  uint32_t pwr_man_timeout;
  uint16_t pwr_man_enable;
  uint16_t network_enabled_on_boot;

  SWILBridgeConfig wil_config;
} SRADBMSSettings;

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
    SIEVBSettings ievb;
    SPendantSettings pendant;
    SRADGalaxySettings radgalaxy;
    SRADStar2Settings radstar2;
    SOBD2SimSettings neoobd2_sim;
    SCmProbeSettings cmprobe;
    SOBD2ProSettings obd2pro;
    SVCAN412Settings vcan412;
    SVCAN412Settings vcan4_12;
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
  };
} GLOBAL_SETTINGS;

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

  DeviceSettingsTypeMax,
  DeviceSettingsNone = 0xFFFFFFFF
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
    SIEVBSettings ievb;
    SPendantSettings pendant;
    SRADGalaxySettings radgalaxy;
    SRADStar2Settings radstar2;
    SOBD2SimSettings neoobd2_sim;
    SCmProbeSettings cmprobe;
    SOBD2ProSettings obd2pro;
    SVCAN412Settings vcan412;
    SVCAN412Settings vcan4_12;
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

  } Settings;
} SDeviceSettings;

typedef enum _EPlasmaIonVnetChannel_t
{
  PlasmaIonVnetChannelMain,
  PlasmaIonVnetChannelA,
  PlasmaIonVnetChannelB,
  eSoftCore,
  eFpgaStatusResp,
} EPlasmaIonVnetChannel_t;

typedef struct _stCM_ISO157652_TxMessage
{
  uint16_t vs_netid;

  uint8_t padding;

  uint8_t tx_index;

  uint32_t id;
  uint32_t fc_id;
  uint32_t fc_id_mask;

  uint8_t stMin;
  uint8_t blockSize;
  uint8_t flowControlExtendedAddress;
  uint8_t extendedAddress;

  uint16_t fs_timeout;
  uint16_t fs_wait;

  uint8_t data[4 * 1024];

  uint32_t num_bytes;

  union
  {
    struct
    {
      unsigned id_29_bit_enable : 1;
      unsigned fc_id_29_bit_enable : 1;
      unsigned ext_address_enable : 1;
      unsigned fc_ext_address_enable : 1;

      unsigned overrideSTmin : 1;
      unsigned overrideBlockSize : 1;
      unsigned paddingEnable : 1;
      unsigned iscanFD : 1;
      unsigned isBRSEnabled : 1;
      unsigned : 15;
      unsigned tx_dl : 8;
    };
    uint32_t flags;
  };
} stCM_ISO157652_TxMessage;

typedef struct
{
  uint16_t vs_netid;
  uint8_t padding;

  uint8_t tx_index;

  uint32_t id;
  uint32_t fc_id;
  uint32_t fc_id_mask;

  uint8_t stMin;
  uint8_t blockSize;

  uint8_t flowControlExtendedAddress;
  uint8_t extendedAddress;

  uint16_t fs_timeout;
  uint16_t fs_wait;

  uint8_t* data;
  uint32_t num_bytes;

  uint8_t tx_dl;

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

typedef struct _stCM_ISO157652_RxMessage
{
  uint16_t vs_netid;

  uint8_t padding;

  uint32_t id;
  uint32_t id_mask;
  uint32_t fc_id;

  uint8_t flowControlExtendedAddress;
  uint8_t extendedAddress;

  uint8_t blockSize;
  uint8_t stMin;

  uint16_t cf_timeout;

  union
  {
    struct
    {
      unsigned id_29_bit_enable : 1;
      unsigned fc_id_29_bit_enable : 1;
      unsigned ext_address_enable : 1;
      unsigned fc_ext_address_enable : 1;
      unsigned enableFlowControlTransmission : 1;
      unsigned paddingEnable : 1;
      unsigned iscanFD : 1;
      unsigned isBRSEnabled : 1;
    };
    uint32_t flags;
  };
  uint8_t reserved[16];
} stCM_ISO157652_RxMessage;

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

typedef int16_t descIdType;

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
  uint32_t ExtraDataPtr;
  uint8_t MiscData;
  uint8_t Reserved[3];
} icsSpyMessageVSB;
#pragma pack(push)
#pragma pack(1)
typedef struct _ethernetNetworkStatus_t
{
  uint16_t networkId;
  uint8_t linkStatus;
  uint8_t linkFullDuplex;
  uint8_t linkSpeed;
  uint8_t linkMode;
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
  ethernetNetworkStatus_t ethernetStatus;
  uint8_t unused;
} icsFire3DeviceStatus;

typedef struct
{
  ethernetNetworkStatus_t ethernetStatus[4];
} icsRadMoonDuoDeviceStatus;

typedef struct
{
  ethernetNetworkStatus_t ethernetStatus[8 - 1];
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

typedef union
{
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

typedef struct
{
  char szName[128];
  char szDeviceName[64];
  unsigned long Status;
  unsigned char bMAC_Address[6];
  unsigned char bIPV6_Address[16];
  unsigned char bIPV4_Address[4];
  unsigned long EthernetPinConfig;
} NDIS_ADAPTER_INFORMATION;

typedef struct SPhyRegPktHdr
{
  uint16_t numEntries;
  uint8_t version;
  uint8_t entryBytes;
} PhyRegPktHdr_t;

typedef struct SPhyRegPktClause22Mess
{
  uint8_t phyAddr;
  uint8_t page;
  uint16_t regAddr;
  uint16_t regVal;
} PhyRegPktClause22Mess_t;

typedef struct SPhyRegPktClause45Mess
{
  uint8_t port;
  uint8_t device;
  uint16_t regAddr;
  uint16_t regVal;
} PhyRegPktClause45Mess_t;

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
    struct
    {
      uint16_t Enabled : 1;
      uint16_t WriteEnable : 1;
      uint16_t Clause45Enable : 1;
      uint16_t status : 2;
      uint16_t reserved : 3;
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
enum
{
  assert_line_4600 = 1 / (int)(!!(sizeof(CAN_SETTINGS) == 12))
};
;
enum
{
  assert_line_4601 = 1 / (int)(!!(sizeof(CANFD_SETTINGS) == 10))
};
;
enum
{
  assert_line_4602 = 1 / (int)(!!(sizeof(SWCAN_SETTINGS) == 14))
};
;
enum
{
  assert_line_4603 = 1 / (int)(!!(sizeof(LIN_SETTINGS) == 10))
};
;
enum
{
  assert_line_4604 = 1 / (int)(!!(sizeof(ISO9141_KEYWORD2000__INIT_STEP) == 6))
};
;
enum
{
  assert_line_4605 = 1 / (int)(!!(sizeof(ISO9141_KEYWORD2000_SETTINGS) == 114))
};
;
enum
{
  assert_line_4606 = 1 / (int)(!!(sizeof(UART_SETTINGS) == 16))
};
;
enum
{
  assert_line_4607 = 1 / (int)(!!(sizeof(J1708_SETTINGS) == 2))
};
;
enum
{
  assert_line_4608 = 1 / (int)(!!(sizeof(SRedSettings) == 44))
};
;
enum
{
  assert_line_4609 = 1 / (int)(!!(sizeof(STextAPISettings) == 72))
};
;
enum
{
  assert_line_4610 = 1 / (int)(!!(sizeof(stChipVersions) == 8))
};
;
enum
{
  assert_line_4611 = 1 / (int)(!!(sizeof(SNeoMostGatewaySettings) == 4))
};
;
enum
{
  assert_line_4612 = 1 / (int)(!!(sizeof(OP_ETH_GENERAL_SETTINGS) == 20))
};
;
enum
{
  assert_line_4613 = 1 / (int)(!!(sizeof(OP_ETH_SETTINGS) == 16))
};
;
enum
{
  assert_line_4614 = 1 / (int)(!!(sizeof(ETHERNET_SETTINGS) == 8))
};
;
enum
{
  assert_line_4615 = 1 / (int)(!!(sizeof(ETHERNET_SETTINGS2) == 16))
};
;
enum
{
  assert_line_4616 = 1 / (int)(!!(sizeof(ETHERNET10G_SETTINGS) == 24))
};
;
enum
{
  assert_line_4617 = 1 / (int)(!!(sizeof(LOGGER_SETTINGS) == 4))
};
;
enum
{
  assert_line_4618 = 1 / (int)(!!(sizeof(DISK_SETTINGS) == 14))
};
;
enum
{
  assert_line_4619 = 1 / (int)(!!(sizeof(SERDESCAM_SETTINGS) == 32))
};
;
enum
{
  assert_line_4620 = 1 / (int)(!!(sizeof(SERDESPOC_SETTINGS) == 10))
};
;
enum
{
  assert_line_4621 = 1 / (int)(!!(sizeof(SERDESGEN_SETTINGS) == 32))
};
;
enum
{
  assert_line_4622 = 1 / (int)(!!(sizeof(RAD_REPORTING_SETTINGS) == 16))
};
;
enum
{
  assert_line_4623 = 1 / (int)(!!(sizeof(CANTERM_SETTINGS) == 6))
};
;
enum
{
  assert_line_4624 = 1 / (int)(!!(sizeof(SFireSettings) == 744))
};
;
enum
{
  assert_line_4625 = 1 / (int)(!!(sizeof(SFireVnetSettings) == 792))
};
;
enum
{
  assert_line_4626 = 1 / (int)(!!(sizeof(SCyanSettings) == 936))
};
;
enum
{
  assert_line_4627 = 1 / (int)(!!(sizeof(SVCAN3Settings) == 40))
};
;
enum
{
  assert_line_4628 = 1 / (int)(!!(sizeof(SVCAN4Settings) == 342))
};
;
enum
{
  assert_line_4629 = 1 / (int)(!!(sizeof(SVCANRFSettings) == 340))
};
;
enum
{
  assert_line_4630 = 1 / (int)(!!(sizeof(SECUSettings) == 470))
};
;
enum
{
  assert_line_4631 = 1 / (int)(!!(sizeof(SPendantSettings) == 470))
};
;
enum
{
  assert_line_4632 = 1 / (int)(!!(sizeof(SIEVBSettings) == 434))
};
;
enum
{
  assert_line_4633 = 1 / (int)(!!(sizeof(SEEVBSettings) == 32))
};
;
enum
{
  assert_line_4634 = 1 / (int)(!!(sizeof(SRADGalaxySettings) == 768))
};
;
enum
{
  assert_line_4635 = 1 / (int)(!!(sizeof(SRADStar2Settings) == 414))
};
;
enum
{
  assert_line_4636 = 1 / (int)(!!(sizeof(SOBD2SimSettings) == 148))
};
enum
{
  assert_line_4637 = 1 / (int)(!!(sizeof(CmProbeSettings) == 4))
};
;
enum
{
  assert_line_4638 = 1 / (int)(!!(sizeof(GLOBAL_SETTINGS) == (936 + 6)))
};
;
enum
{
  assert_line_4639 = 1 / (int)(!!(sizeof(stCM_ISO157652_TxMessage) == 4128))
};
;
enum
{
  assert_line_4640 = 1 / (int)(!!(sizeof(stCM_ISO157652_RxMessage) == 42))
};
;
enum
{
  assert_line_4641 = 1 / (int)(!!(sizeof(spyFilterLong) == 72))
};
;
enum
{
  assert_line_4642 = 1 / (int)(!!(sizeof(icsSpyMessage) == 72))
};
;
enum
{
  assert_line_4643 = 1 / (int)(!!(sizeof(icsSpyMessageLong) == 72))
};
;
enum
{
  assert_line_4644 = 1 / (int)(!!(sizeof(icsSpyMessageJ1850) == 72))
};
;
enum
{
  assert_line_4645 = 1 / (int)(!!(sizeof(icsSpyMessageVSB) == 64))
};
;
enum
{
  assert_line_4646 = 1 / (int)(!!(sizeof(OBD2ProSettings) == 482))
};
;
enum
{
  assert_line_4647 = 1 / (int)(!!(sizeof(ISO15765_2015_TxMessage) == (32 + sizeof(uint8_t*))))
};
;
enum
{
  assert_line_4648 = 1 / (int)(!!(sizeof(TIMESYNC_ICSHARDWARE_SETTINGS) == 4))
};
;
enum
{
  assert_line_4649 = 1 / (int)(!!(sizeof(SRADSuperMoonSettings) == 178))
};
;
enum
{
  assert_line_4650 = 1 / (int)(!!(sizeof(SRADMoon2Settings) == 162))
};
;
enum
{
  assert_line_4651 = 1 / (int)(!!(sizeof(SRADGigalogSettings) == 698))
};
;
enum
{
  assert_line_4652 = 1 / (int)(!!(sizeof(SRADGigastarSettings) == 702))
};
;
enum
{
  assert_line_4653 = 1 / (int)(!!(sizeof(SExtSubCmdHdr) == 4))
};
;
enum
{
  assert_line_4654 = 1 / (int)(!!(sizeof(SDiskStructure) == 16))
};
;
enum
{
  assert_line_4655 = 1 / (int)(!!(sizeof(SDiskFormatProgress) == 10))
};
;
enum
{
  assert_line_4656 = 1 / (int)(!!(sizeof(SDiskStatus) == 14))
};
;
enum
{
  assert_line_4657 = 1 / (int)(!!(sizeof(SExtSubCmdComm) == 262))
};
;
enum
{
  assert_line_4658 = 1 / (int)(!!(sizeof(SRADPlutoSettings) == 348))
};
;
enum
{
  assert_line_4659 = 1 / (int)(!!(sizeof(CANHubSettings) == 56))
};
;
enum
{
  assert_line_4660 = 1 / (int)(!!(sizeof(SNeoECU12Settings) == 358))
};
;
enum
{
  assert_line_4661 = 1 / (int)(!!(sizeof(SPlutoSwitchSettings) == 50378))
};
;
enum
{
  assert_line_4662 = 1 / (int)(!!(sizeof(VCAN4IndSettings) == (228)))
};
;
enum
{
  assert_line_4663 = 1 / (int)(!!(sizeof(SRADJupiterSettings) == 348))
};
;
enum
{
  assert_line_4664 = 1 / (int)(!!(sizeof(RadMoonDuoSettings) == 38))
};
;
enum
{
  assert_line_4665 = 1 / (int)(!!(sizeof(SFire3Settings) == (632)))
};
;
enum
{
  assert_line_4666 = 1 / (int)(!!(sizeof(SEtherBadgeSettings) == 316))
};
;
enum
{
  assert_line_4667 = 1 / (int)(!!(sizeof(SRADA2BSettings) == 280))
};
;
enum
{
  assert_line_4668 = 1 / (int)(!!(sizeof(A2BMonitorSettings) == 20))
};
;
enum
{
  assert_line_4669 = 1 / (int)(!!(sizeof(SRADEpsilonSettings) == 384))
};
;
enum
{
  assert_line_4670 = 1 / (int)(!!(sizeof(RAD_GPTP_SETTINGS) == 36))
};
;
enum
{
  assert_line_4671 = 1 / (int)(!!(sizeof(SRADBMSSettings) == 108))
};
;
