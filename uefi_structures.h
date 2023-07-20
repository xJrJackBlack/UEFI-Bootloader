#pragma once

#include <stdint.h>
#include <stddef.h>

#define EFI_SIZE_TO_PAGES(Size) (((Size) >> 12) + (((Size) & 0xfff) ? 1 : 0))

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32; // Ensure 32 bit integer
typedef int64_t i64;

// unsigned types
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32; // Ensure 32 bit unsigned integer
typedef uint64_t u64;

#define IN
#define OUT
#define OPTIONAL
#define CONST const
#define EFIAPI

#define TRUE 1
#define FALSE 0

typedef u8 BOOLEAN;

typedef int64_t INTN;   // In 64 bit system
typedef uint64_t UINTN; // In 64 bit system

typedef int8_t INT8;
typedef uint8_t UINT8;
typedef int16_t INT16;
typedef uint16_t UINT16;
typedef int32_t INT32;
typedef uint32_t UINT32;
typedef int64_t INT64;
typedef uint64_t UINT64;

typedef char CHAR8;
typedef u16 CHAR16;
typedef void VOID;

typedef UINTN EFI_STATUS;
typedef VOID *EFI_HANDLE;
typedef VOID *EFI_EVENT;
typedef UINT64 EFI_LBA;
typedef UINTN EFI_TPL;

typedef struct
{
    UINT32 Data1;
    UINT16 Data2;
    UINT16 Data3;
    UINT8 Data4[8];
} EFI_GUID;

EFI_GUID EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID = {0x9042A9DE, 0x23DC, 0x4A38, {0x96, 0xFB, 0x7A, 0xDE, 0xD0, 0x80, 0x51, 0x6A}};

#define EFI_EDID_ACTIVE_PROTOCOL_GUID                                                  \
    {                                                                                  \
        0xBD8C1056, 0x9F36, 0x44EC, { 0x92, 0xA8, 0xA6, 0x33, 0x7F, 0x81, 0x79, 0x86 } \
    }

#define EFI_EDID_DISCOVERED_PROTOCOL_GUID                                              \
    {                                                                                  \
        0x1C0C34F6, 0xD380, 0x41FA, { 0xA0, 0x49, 0x8A, 0xD0, 0x6C, 0x1A, 0x66, 0xAA } \
    }

#define EFI_DEVICE_PATH_PROTOCOL_GUID                                                  \
    {                                                                                  \
        0x09576E91, 0x6D3F, 0x11D2, { 0x8E, 0x39, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3b } \
    }

#define EFI_BLOCK_IO_PROTOCOL_GUID                                                     \
    {                                                                                  \
        0x964E5B21, 0x6459, 0x11D2, { 0x8E, 0x39, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B } \
    }

#define EFI_DISK_IO_PROTOCOL_GUID                                                      \
    {                                                                                  \
        0xCE345171, 0xBA0B, 0x11D2, { 0x8E, 0x4F, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B } \
    }

#define EFI_SUCCESS 0

#define EFI_WARN_UNKNOWN_GLYPH 1
#define EFI_WARN_DELETE_FAILURE 2
#define EFI_WARN_WRITE_FAILURE 3
#define EFI_WARN_BUFFER_TOO_SMALL 4
#define EFI_WARN_STALE_DATA 5
#define EFI_WARN_FILE_SYSTEM 6
#define EFI_WARN_RESET_REQUIRED 7

#define ERROR_BIT ((UINTN)1 << ((sizeof(VOID *) * 8) - 1))
#define EFI_ENCODE_ERROR(code) (ERROR_BIT | (code))
#define EFI_ERROR(sts) ((INTN)(sts) < 0)

// highest bit set
#define EFI_LOAD_ERROR EFI_ENCODE_ERROR(1)
#define EFI_INVALID_PARAMETER EFI_ENCODE_ERROR(2)
#define EFI_UNSUPPORTED EFI_ENCODE_ERROR(3)
#define EFI_BAD_BUFFER_SIZE EFI_ENCODE_ERROR(4)
#define EFI_BUFFER_TOO_SMALL EFI_ENCODE_ERROR(5)
#define EFI_NOT_READY EFI_ENCODE_ERROR(6)
#define EFI_DEVICE_ERROR EFI_ENCODE_ERROR(7)
#define EFI_WRITE_PROTECTED EFI_ENCODE_ERROR(8)
#define EFI_OUT_OF_RESOURCES EFI_ENCODE_ERROR(9)
#define EFI_VOLUME_CORRUPTED EFI_ENCODE_ERROR(10)
#define EFI_VOLUME_FULL EFI_ENCODE_ERROR(11)
#define EFI_NO_MEDIA EFI_ENCODE_ERROR(12)
#define EFI_MEDIA_CHANGED EFI_ENCODE_ERROR(13)
#define EFI_NOT_FOUND EFI_ENCODE_ERROR(14)
#define EFI_ACCESS_DENIED EFI_ENCODE_ERROR(15)
#define EFI_NO_RESPONSE EFI_ENCODE_ERROR(16)
#define EFI_NO_MAPPING EFI_ENCODE_ERROR(17)
#define EFI_TIMEOUT EFI_ENCODE_ERROR(18)
#define EFI_NOT_STARTED EFI_ENCODE_ERROR(19)
#define EFI_ALREADY_STARTED EFI_ENCODE_ERROR(20)
#define EFI_ABORTED EFI_ENCODE_ERROR(21)
#define EFI_ICMP_ERROR EFI_ENCODE_ERROR(22)
#define EFI_TFTP_ERROR EFI_ENCODE_ERROR(23)
#define EFI_PROTOCOL_ERROR EFI_ENCODE_ERROR(24)
#define EFI_INCOMPATIBLE_VERSION EFI_ENCODE_ERROR(25)
#define EFI_SECURITY_VIOLATION EFI_ENCODE_ERROR(26)
#define EFI_CRC_ERROR EFI_ENCODE_ERROR(27)
#define EFI_END_OF_MEDIA EFI_ENCODE_ERROR(28)
#define EFI_END_OF_FILE EFI_ENCODE_ERROR(31)
#define EFI_INVALID_LANGUAGE EFI_ENCODE_ERROR(32)
#define EFI_COMPROMISED_DATA EFI_ENCODE_ERROR(33)
#define EFI_IP_ADDRESS_CONFLICT EFI_ENCODE_ERROR(34)
#define EFI_HTTP_ERROR EFI_ENCODE_ERROR(35)

#define EFI_SYSTEM_TABLE_SIGNATURE 0x5453595320494249
#define EFI_2_90_SYSTEM_TABLE_REVISION ((2 << 16) | 90)
#define EFI_2_80_SYSTEM_TABLE_REVISION ((2 << 16) | 80)
#define EFI_2_70_SYSTEM_TABLE_REVISION ((2 << 16) | 70)
#define EFI_2_60_SYSTEM_TABLE_REVISION ((2 << 16) | 60)
#define EFI_2_50_SYSTEM_TABLE_REVISION ((2 << 16) | 50)
#define EFI_2_40_SYSTEM_TABLE_REVISION ((2 << 16) | 40)
#define EFI_2_31_SYSTEM_TABLE_REVISION ((2 << 16) | 31)
#define EFI_2_30_SYSTEM_TABLE_REVISION ((2 << 16) | 30)
#define EFI_2_20_SYSTEM_TABLE_REVISION ((2 << 16) | 20)
#define EFI_2_10_SYSTEM_TABLE_REVISION ((2 << 16) | 10)
#define EFI_2_00_SYSTEM_TABLE_REVISION ((2 << 16) | 00)
#define EFI_1_10_SYSTEM_TABLE_REVISION ((1 << 16) | 10)
#define EFI_1_02_SYSTEM_TABLE_REVISION ((1 << 16) | 02)

typedef struct
{
    UINT64 Signature;
    UINT32 Revision;
    UINT32 HeaderSize;
    UINT32 CRC32;
    UINT32 Reserved;
} EFI_TABLE_HEADER;

typedef struct
{
    UINT16 ScanCode;
    CHAR16 UnicodeChar;
} EFI_INPUT_KEY;

typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL EFI_SIMPLE_TEXT_INPUT_PROTOCOL;
typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

// TODO: implement? if this becomes useful at some point

typedef EFI_STATUS(EFIAPI *EFI_INPUT_RESET)(
    IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,
    IN BOOLEAN ExtendedVerification);

typedef EFI_STATUS(EFIAPI *EFI_INPUT_READ_KEY)(
    IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,
    OUT EFI_INPUT_KEY *Key);

typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL
{
    EFI_INPUT_RESET Reset;
    EFI_INPUT_READ_KEY ReadKeyStroke;
    EFI_EVENT WaitForKey;
} EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_TEXT_RESET)(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
    IN BOOLEAN ExtendedVerification);

typedef EFI_STATUS(EFIAPI *EFI_TEXT_STRING)(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
    IN CHAR16 *String);

typedef EFI_STATUS(EFIAPI *EFI_TEXT_TEST_STRING)(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
    IN CHAR16 *String);

typedef EFI_STATUS(EFIAPI *EFI_TEXT_QUERY_MODE)(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
    IN UINTN ModeNumber,
    OUT UINTN *Columns,
    OUT UINTN *Rows);

typedef EFI_STATUS(EFIAPI *EFI_TEXT_SET_MODE)(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
    IN UINTN ModeNumber);

#define EFI_BLACK 0x00
#define EFI_BLUE 0x01
#define EFI_GREEN 0x02
#define EFI_CYAN 0x03
#define EFI_RED 0x04
#define EFI_MAGENTA 0x05
#define EFI_BROWN 0x06
#define EFI_LIGHTGRAY 0x07
#define EFI_BRIGHT 0x08
#define EFI_DARKGRAY (EFI_BLACK | EFI_BRIGHT)
#define EFI_LIGHTBLUE 0x09
#define EFI_LIGHTGREEN 0x0A
#define EFI_LIGHTCYAN 0x0B
#define EFI_LIGHTRED 0x0C
#define EFI_LIGHTMAGENTA 0x0D
#define EFI_YELLOW 0x0E
#define EFI_WHITE 0x0F

#define EFI_BACKGROUND_BLACK 0x00
#define EFI_BACKGROUND_BLUE 0x10
#define EFI_BACKGROUND_GREEN 0x20
#define EFI_BACKGROUND_CYAN 0x30
#define EFI_BACKGROUND_RED 0x40
#define EFI_BACKGROUND_MAGENTA 0x50
#define EFI_BACKGROUND_BROWN 0x60
#define EFI_BACKGROUND_LIGHTGRAY 0x70

//
// Macro to accept color values in their raw form to create
// a value that represents both a foreground and background
// color in a single byte.
// For Foreground, and EFI_* value is valid from EFI_BLACK(0x00)
// to EFI_WHITE (0x0F).
// For Background, only EFI_BLACK, EFI_BLUE, EFI_GREEN,
// EFI_CYAN, EFI_RED, EFI_MAGENTA, EFI_BROWN, and EFI_LIGHTGRAY
// are acceptable.
//
// Do not use EFI_BACKGROUND_xxx values with this macro.
#define EFI_TEXT_ATTR(Foreground, Background) ((Foreground) | ((Background) << 4))

typedef EFI_STATUS(EFIAPI *EFI_TEXT_SET_ATTRIBUTE)(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
    IN UINTN Attribute);

typedef EFI_STATUS(EFIAPI *EFI_TEXT_CLEAR_SCREEN)(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This);

typedef EFI_STATUS(EFIAPI *EFI_TEXT_SET_CURSOR_POSITION)(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
    IN UINTN Column,
    IN UINTN Row);

typedef EFI_STATUS(EFIAPI *EFI_TEXT_ENABLE_CURSOR)(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
    IN BOOLEAN Visible);

typedef struct
{
    INT32 MaxMode;
    // current settings
    INT32 Mode;
    INT32 Attribute;
    INT32 CursorColumn;
    INT32 CursorRow;
    BOOLEAN CursorVisible;
} SIMPLE_TEXT_OUTPUT_MODE;

typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL
{
    EFI_TEXT_RESET Reset;
    EFI_TEXT_STRING OutputString;
    EFI_TEXT_TEST_STRING TestString;
    EFI_TEXT_QUERY_MODE QueryMode;
    EFI_TEXT_SET_MODE SetMode;
    EFI_TEXT_SET_ATTRIBUTE SetAttribute;
    EFI_TEXT_CLEAR_SCREEN ClearScreen;
    EFI_TEXT_SET_CURSOR_POSITION SetCursorPosition;
    EFI_TEXT_ENABLE_CURSOR EnableCursor;
    SIMPLE_TEXT_OUTPUT_MODE *Mode;
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

#define EFI_BOOT_SERVICES_SIGNATURE 0x56524553544f4f42
#define EFI_BOOT_SERVICES_REVISION EFI_SPECIFICATION_VERSION

#define TPL_APPLICATION 4
#define TPL_CALLBACK 8
#define TPL_NOTIFY 16
#define TPL_HIGH_LEVEL 31
typedef EFI_TPL(EFIAPI *EFI_RAISE_TPL)(
    IN EFI_TPL NewTpl);

typedef VOID(EFIAPI *EFI_RESTORE_TPL)(
    IN EFI_TPL OldTpl);

typedef enum
{
    AllocateAnyPages,
    AllocateMaxAddress,
    AllocateAddress,
    MaxAllocateType
} EFI_ALLOCATE_TYPE;

typedef enum
{
    EfiReservedMemoryType,
    EfiLoaderCode,
    EfiLoaderData,
    EfiBootServicesCode,
    EfiBootServicesData,
    EfiRuntimeServicesCode,
    EfiRuntimeServicesData,
    EfiConventionalMemory,
    EfiUnusableMemory,
    EfiACPIReclaimMemory,
    EfiACPIMemoryNVS,
    EfiMemoryMappedIO,
    EfiMemoryMappedIOPortSpace,
    EfiPalCode,
    EfiPersistentMemory,
    EfiUnacceptedMemoryType,
    EfiMaxMemoryType
} EFI_MEMORY_TYPE;

typedef UINT64 EFI_PHYSICAL_ADDRESS;

typedef EFI_STATUS(EFIAPI *EFI_ALLOCATE_PAGES)(
    IN EFI_ALLOCATE_TYPE Type,
    IN EFI_MEMORY_TYPE MemoryType,
    IN UINTN Pages,
    IN OUT EFI_PHYSICAL_ADDRESS *Memory);

typedef EFI_STATUS(EFIAPI *EFI_FREE_PAGES)(
    IN EFI_PHYSICAL_ADDRESS Memory,
    IN UINTN Pages);

typedef UINT64 EFI_VIRTUAL_ADDRESS;
#define EFI_MEMORY_DESCRIPTOR_VERSION 1

typedef struct
{
    UINT32 Type;
    EFI_PHYSICAL_ADDRESS PhysicalStart;
    EFI_VIRTUAL_ADDRESS VirtualStart;
    UINT64 NumberOfPages;
    UINT64 Attribute;
} EFI_MEMORY_DESCRIPTOR;

typedef EFI_STATUS(EFIAPI *EFI_GET_MEMORY_MAP)(
    IN OUT UINTN *MemoryMapSize,
    OUT EFI_MEMORY_DESCRIPTOR *MemoryMap,
    OUT UINTN *MapKey,
    OUT UINTN *DescriptorSize,
    OUT UINT32 *DescriptorVersion);

typedef EFI_STATUS(EFIAPI *EFI_ALLOCATE_POOL)(
    IN EFI_MEMORY_TYPE PoolType,
    IN UINTN Size,
    OUT VOID **Buffer);

typedef EFI_STATUS(EFIAPI *EFI_FREE_POOL)(
    IN VOID *Buffer);

#define EVT_TIMER 0x80000000
#define EVT_RUNTIME 0x40000000
#define EVT_NOTIFY_WAIT 0x00000100
#define EVT_NOTIFY_SIGNAL 0x00000200
#define EVT_SIGNAL_EXIT_BOOT_SERVICES 0x00000201
#define EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE 0x60000202

typedef VOID(EFIAPI *EFI_EVENT_NOTIFY)(
    IN EFI_EVENT Event,
    IN VOID *Context);

typedef EFI_STATUS(EFIAPI *EFI_CREATE_EVENT)(
    IN UINT32 Type,
    IN EFI_TPL NotifyTpl,
    IN OPTIONAL EFI_EVENT_NOTIFY NotifyFunction,
    IN OPTIONAL VOID *NotifyContext,
    OUT EFI_EVENT *Event);

typedef enum
{
    TimerCancel,
    TimerPeriodic,
    TimerRelative
} EFI_TIMER_DELAY;

typedef EFI_STATUS(EFIAPI *EFI_SET_TIMER)(
    IN EFI_EVENT Event,
    IN EFI_TIMER_DELAY Type,
    IN UINT64 TriggerTime);

typedef EFI_STATUS(EFIAPI *EFI_WAIT_FOR_EVENT)(
    IN UINTN NumberOfEvents,
    IN EFI_EVENT *Event,
    OUT UINTN *Index);

typedef EFI_STATUS(EFIAPI *EFI_SIGNAL_EVENT)(
    IN EFI_EVENT Event);

typedef EFI_STATUS(EFIAPI *EFI_CLOSE_EVENT)(
    IN EFI_EVENT Event);

typedef EFI_STATUS(EFIAPI *EFI_CHECK_EVENT)(
    IN EFI_EVENT Event);

typedef enum
{
    EFI_NATIVE_INTERFACE
} EFI_INTERFACE_TYPE;

typedef EFI_STATUS(EFIAPI *EFI_INSTALL_PROTOCOL_INTERFACE)(
    IN OUT EFI_HANDLE *Handle,
    IN EFI_GUID *Protocol,
    IN EFI_INTERFACE_TYPE InterfaceType,
    IN VOID *Interface);

typedef EFI_STATUS(EFIAPI *EFI_REINSTALL_PROTOCOL_INTERFACE)(
    IN EFI_HANDLE Handle,
    IN EFI_GUID *Protocol,
    IN VOID *OldInterface,
    IN VOID *NewInterface);

typedef EFI_STATUS(EFIAPI *EFI_UNINSTALL_PROTOCOL_INTERFACE)(
    IN EFI_HANDLE Handle,
    IN EFI_GUID *Protocol,
    IN VOID *Interface);

typedef EFI_STATUS(EFIAPI *EFI_HANDLE_PROTOCOL)(
    IN EFI_HANDLE Handle,
    IN EFI_GUID *Protocol,
    OUT VOID **Interface);

typedef EFI_STATUS(EFIAPI *EFI_REGISTER_PROTOCOL_NOTIFY)(
    IN EFI_GUID *Protocol,
    IN EFI_EVENT Event,
    OUT VOID **Registration);

typedef enum
{
    AllHandles,
    ByRegisterNotify,
    ByProtocol
} EFI_LOCATE_SEARCH_TYPE;

typedef EFI_STATUS(EFIAPI *EFI_LOCATE_HANDLE)(
    IN EFI_LOCATE_SEARCH_TYPE SearchType,
    IN OPTIONAL EFI_GUID *Protocol,
    IN OPTIONAL VOID *SearchKey,
    IN OUT UINTN *BufferSize,
    OUT EFI_HANDLE *Buffer);

typedef struct
{
    UINT8 Type;
    UINT8 SubType;
    UINT8 Length[2];
} EFI_DEVICE_PATH_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_LOCATE_DEVICE_PATH)(
    IN EFI_GUID *Protocol,
    IN OUT EFI_DEVICE_PATH_PROTOCOL **DevicePath,
    OUT EFI_HANDLE *Device);

typedef EFI_STATUS(EFIAPI *EFI_INSTALL_CONFIGURATION_TABLE)(
    IN EFI_GUID *Guid,
    IN VOID *Table);

typedef EFI_STATUS(EFIAPI *EFI_IMAGE_LOAD)(
    IN BOOLEAN BootPolicy,
    IN EFI_HANDLE ParentImageHandle,
    IN EFI_DEVICE_PATH_PROTOCOL *DevicePath,
    IN OPTIONAL VOID *SourceBuffer,
    IN UINTN SourceSize,
    OUT EFI_HANDLE *ImageHandle);

typedef EFI_STATUS(EFIAPI *EFI_IMAGE_START)(
    IN EFI_HANDLE ImageHandle,
    OUT UINTN *ExitDataSize,
    OUT OPTIONAL CHAR16 **ExitData);

typedef EFI_STATUS(EFIAPI *EFI_EXIT)(
    IN EFI_HANDLE ImageHandle,
    IN EFI_STATUS ExitStatus,
    IN UINTN ExitDataSize,
    IN OPTIONAL CHAR16 *ExitData);

typedef EFI_STATUS(EFIAPI *EFI_IMAGE_UNLOAD)(
    IN EFI_HANDLE ImageHandle);

typedef EFI_STATUS(EFIAPI *EFI_EXIT_BOOT_SERVICES)(
    IN EFI_HANDLE ImageHandle,
    IN UINTN MapKey);

typedef EFI_STATUS(EFIAPI *EFI_GET_NEXT_MONOTONIC_COUNT)(
    OUT UINT64 *Count);

typedef EFI_STATUS(EFIAPI *EFI_STALL)(
    IN UINTN Microseconds);

typedef EFI_STATUS(EFIAPI *EFI_SET_WATCHDOG_TIMER)(
    IN UINTN Timeout,
    IN UINT64 WatchdogCode,
    IN UINTN DataSize,
    IN OPTIONAL CHAR16 *WatchdogData);

typedef EFI_STATUS(EFIAPI *EFI_CONNECT_CONTROLLER)(
    IN EFI_HANDLE ControllerHandle,
    IN OPTIONAL EFI_HANDLE *DriverImageHandle,
    IN OPTIONAL EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath,
    IN BOOLEAN Recursive);

typedef EFI_STATUS(EFIAPI *EFI_DISCONNECT_CONTROLLER)(
    IN EFI_HANDLE ControllerHandle,
    IN OPTIONAL EFI_HANDLE DriverImageHandle,
    IN OPTIONAL EFI_HANDLE ChildHandle);

#define EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL 0x00000001
#define EFI_OPEN_PROTOCOL_GET_PROTOCOL 0x00000002
#define EFI_OPEN_PROTOCOL_TEST_PROTOCOL 0x00000004
#define EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER 0x00000008
#define EFI_OPEN_PROTOCOL_BY_DRIVER 0x00000010
#define EFI_OPEN_PROTOCOL_EXCLUSIVE 0x00000020

typedef EFI_STATUS(EFIAPI *EFI_OPEN_PROTOCOL)(
    IN EFI_HANDLE Handle,
    IN EFI_GUID *Protocol,
    OUT OPTIONAL VOID **Interface,
    IN EFI_HANDLE AgentHandle,
    IN EFI_HANDLE ControllerHandle,
    IN UINT32 Attributes);

typedef EFI_STATUS(EFIAPI *EFI_CLOSE_PROTOCOL)(
    IN EFI_HANDLE Handle,
    IN EFI_GUID *Protocol,
    IN EFI_HANDLE AgentHandle,
    IN EFI_HANDLE ControllerHandle);

typedef struct
{
    EFI_HANDLE AgentHandle;
    EFI_HANDLE ControllerHandle;
    UINT32 Attributes;
    UINT32 OpenCount;
} EFI_OPEN_PROTOCOL_INFORMATION_ENTRY;

typedef EFI_STATUS(EFIAPI *EFI_OPEN_PROTOCOL_INFORMATION)(
    IN EFI_HANDLE Handle,
    IN EFI_GUID *Protocol,
    OUT EFI_OPEN_PROTOCOL_INFORMATION_ENTRY **EntryBuffer,
    OUT UINTN *EntryCount);

typedef EFI_STATUS(EFIAPI *EFI_PROTOCOLS_PER_HANDLE)(
    IN EFI_HANDLE Handle,
    OUT EFI_GUID ***ProtocolBuffer,
    OUT UINTN *ProtocolBufferCount);

typedef EFI_STATUS(EFIAPI *EFI_LOCATE_HANDLE_BUFFER)(
    IN EFI_LOCATE_SEARCH_TYPE SearchType,
    IN OPTIONAL EFI_GUID *Protocol,
    IN OPTIONAL VOID *SearchKey,
    OUT UINTN *NoHandles,
    OUT EFI_HANDLE **Buffer);

typedef EFI_STATUS(EFIAPI *EFI_LOCATE_PROTOCOL)(
    IN EFI_GUID *Protocol,
    IN OPTIONAL VOID *Registration,
    OUT VOID **Interface);

typedef EFI_STATUS(EFIAPI *EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES)(
    IN OUT EFI_HANDLE *Handle,
    ...);

typedef EFI_STATUS(EFIAPI *EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES)(
    IN EFI_HANDLE Handle,
    ...);

typedef EFI_STATUS(EFIAPI *EFI_CALCULATE_CRC32)(
    IN VOID *Data,
    IN UINTN DataSize,
    OUT UINT32 *Crc32);

typedef VOID(EFIAPI *EFI_COPY_MEM)(
    IN VOID *Destination,
    IN VOID *Source,
    IN UINTN Length);

typedef VOID(EFIAPI *EFI_SET_MEM)(
    IN VOID *Buffer,
    IN UINTN Size,
    IN UINT8 Value);

typedef EFI_STATUS(EFIAPI *EFI_CREATE_EVENT_EX)(
    IN UINT32 Type,
    IN EFI_TPL NotifyTpl,
    IN OPTIONAL EFI_EVENT_NOTIFY NotifyFunction,
    IN CONST OPTIONAL VOID *NotifyContext,
    IN CONST OPTIONAL EFI_GUID *EventGroup,
    OUT EFI_EVENT *Event);

typedef struct
{
    EFI_TABLE_HEADER Hdr;
    //
    // Task Priority Services
    //
    EFI_RAISE_TPL RaiseTPL;     // EFI 1.0+
    EFI_RESTORE_TPL RestoreTPL; // EFI 1.0+

    //
    // Memory Services
    //
    EFI_ALLOCATE_PAGES AllocatePages; // EFI 1.0+
    EFI_FREE_PAGES FreePages;         // EFI 1.0+
    EFI_GET_MEMORY_MAP GetMemoryMap;  // EFI 1.0+
    EFI_ALLOCATE_POOL AllocatePool;   // EFI 1.0+
    EFI_FREE_POOL FreePool;           // EFI 1.0+

    //
    // Event & Timer Services
    //
    EFI_CREATE_EVENT CreateEvent;    // EFI 1.0+
    EFI_SET_TIMER SetTimer;          // EFI 1.0+
    EFI_WAIT_FOR_EVENT WaitForEvent; // EFI 1.0+
    EFI_SIGNAL_EVENT SignalEvent;    // EFI 1.0+
    EFI_CLOSE_EVENT CloseEvent;      // EFI 1.0+
    EFI_CHECK_EVENT CheckEvent;      // EFI 1.0+

    //
    // Protocol Handler Services
    //
    EFI_INSTALL_PROTOCOL_INTERFACE InstallProtocolInterface;     // EFI 1.0+
    EFI_REINSTALL_PROTOCOL_INTERFACE ReinstallProtocolInterface; // EFI 1.0+
    EFI_UNINSTALL_PROTOCOL_INTERFACE UninstallProtocolInterface; // EFI 1.0+
    EFI_HANDLE_PROTOCOL HandleProtocol;                          // EFI 1.0+
    VOID *Reserved;                                              // EFI 1.0+
    EFI_REGISTER_PROTOCOL_NOTIFY RegisterProtocolNotify;         // EFI 1.0+
    EFI_LOCATE_HANDLE LocateHandle;                              // EFI 1.0+
    EFI_LOCATE_DEVICE_PATH LocateDevicePath;                     // EFI 1.0+
    EFI_INSTALL_CONFIGURATION_TABLE InstallConfigurationTable;   // EFI 1.0+

    //
    // Image Services
    //
    EFI_IMAGE_LOAD LoadImage;                // EFI 1.0+
    EFI_IMAGE_START StartImage;              // EFI 1.0+
    EFI_EXIT Exit;                           // EFI 1.0+
    EFI_IMAGE_UNLOAD UnloadImage;            // EFI 1.0+
    EFI_EXIT_BOOT_SERVICES ExitBootServices; // EFI 1.0+

    //
    // Miscellaneous Services
    //
    EFI_GET_NEXT_MONOTONIC_COUNT GetNextMonotonicCount; // EFI 1.0+
    EFI_STALL Stall;                                    // EFI 1.0+
    EFI_SET_WATCHDOG_TIMER SetWatchdogTimer;            // EFI 1.0+

    //
    // DriverSupport Services
    //
    EFI_CONNECT_CONTROLLER ConnectController;       // EFI 1.1
    EFI_DISCONNECT_CONTROLLER DisconnectController; // EFI 1.1+

    //
    // Open and Close Protocol Services
    //
    EFI_OPEN_PROTOCOL OpenProtocol;                        // EFI 1.1+
    EFI_CLOSE_PROTOCOL CloseProtocol;                      // EFI 1.1+
    EFI_OPEN_PROTOCOL_INFORMATION OpenProtocolInformation; // EFI 1.1+

    //
    // Library Services
    //
    EFI_PROTOCOLS_PER_HANDLE ProtocolsPerHandle;                                    // EFI 1.1+
    EFI_LOCATE_HANDLE_BUFFER LocateHandleBuffer;                                    // EFI 1.1+
    EFI_LOCATE_PROTOCOL LocateProtocol;                                             // EFI 1.1+
    EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES InstallMultipleProtocolInterfaces;     // EFI 1.1+
    EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES UninstallMultipleProtocolInterfaces; // EFI 1.1+

    //
    // 32-bit CRC Services
    //
    EFI_CALCULATE_CRC32 CalculateCrc32; // EFI 1.1+

    //
    // Miscellaneous Services
    //
    EFI_COPY_MEM CopyMem;              // EFI 1.1+
    EFI_SET_MEM SetMem;                // EFI 1.1+
    EFI_CREATE_EVENT_EX CreateEventEx; // UEFI 2.0+
} EFI_BOOT_SERVICES;

typedef struct
{
    EFI_GUID VendorGuid;
    VOID *VendorTable;
} EFI_CONFIGURATION_TABLE;

// Reboot

typedef enum
{
    EfiResetCold,
    EfiResetWarm,
    EfiResetShutdown,
    EfiResetPlatformSpecific
} EFI_RESET_TYPE;

typedef void(EFIAPI *EFI_RESET_SYSTEM)(
    EFI_RESET_TYPE ResetType,
    EFI_STATUS ResetStatus,
    UINTN DataSize,
    VOID *ResetData);

// EFI_SET_VIRTUAL_ADDRESS_MAP
typedef EFI_STATUS(EFIAPI *EFI_SET_VIRTUAL_ADDRESS_MAP)(
    UINTN MemoryMapSize,
    UINTN DescriptorSize,
    UINT32 DescriptorVersion,
    EFI_MEMORY_DESCRIPTOR *VirtualMap);

// EFI_CONVERT_POINTER
typedef EFI_STATUS(EFIAPI *EFI_CONVERT_POINTER)(
    UINTN DebugDisposition,
    VOID **Address);

typedef EFI_STATUS(EFIAPI *EFI_GET_VARIABLE)(
    CHAR16 *VariableName,
    EFI_GUID *VendorGuid,
    UINT32 *Attributes OPTIONAL,
    UINTN *DataSize,
    VOID *Data);

typedef EFI_STATUS(EFIAPI *EFI_GET_NEXT_VARIABLE_NAME)(
    UINTN *VariableNameSize,
    CHAR16 *VariableName,
    EFI_GUID *VendorGuid);

typedef EFI_STATUS(EFIAPI *EFI_SET_VARIABLE)(
    CHAR16 *VariableName,
    EFI_GUID *VendorGuid,
    UINT32 Attributes,
    UINTN DataSize,
    VOID *Data);

typedef struct
{
    EFI_GUID CapsuleGuid;
    UINT32 HeaderSize;
    UINT32 Flags;
    UINT32 CapsuleImageSize;
} EFI_CAPSULE_HEADER;

typedef EFI_STATUS(EFIAPI *EFI_GET_NEXT_HIGH_MONO_COUNT)(
    UINT32 *HighCount);

typedef void(EFIAPI *EFI_RESET_SYSTEM)(
    EFI_RESET_TYPE ResetType,
    EFI_STATUS ResetStatus,
    UINTN DataSize,
    VOID *ResetData OPTIONAL);

typedef EFI_STATUS(EFIAPI *EFI_UPDATE_CAPSULE)(
    EFI_CAPSULE_HEADER **CapsuleHeaderArray,
    UINTN CapsuleCount,
    EFI_PHYSICAL_ADDRESS ScatterGatherList OPTIONAL);

typedef EFI_STATUS(EFIAPI *EFI_QUERY_CAPSULE_CAPABILITIES)(
    EFI_CAPSULE_HEADER **CapsuleHeaderArray,
    UINTN CapsuleCount,
    UINT64 *MaximumCapsuleSize,
    EFI_RESET_TYPE *ResetType);

typedef EFI_STATUS(EFIAPI *EFI_QUERY_VARIABLE_INFO)(
    UINT32 Attributes,
    UINT64 *MaximumVariableStorageSize,
    UINT64 *RemainingVariableStorageSize,
    UINT64 *MaximumVariableSize);

typedef struct
{
    UINT16 Year;  // Year - 1900
    UINT8 Month;  // Month (1-12)
    UINT8 Day;    // Day of the month (1-31)
    UINT8 Hour;   // Hour (0-23)
    UINT8 Minute; // Minute (0-59)
    UINT8 Second; // Second (0-59)
    UINT8 Pad1;
    UINT32 Nanosecond; // Nanosecond (0-999,999,999)
    INT16 TimeZone;    // Timezone (-1440 to 1440 or 2047)
    UINT8 Daylight;
    UINT8 Pad2;
} EFI_TIME;

typedef struct
{
    UINT32 Resolution;  // 1 to 1,000,000 (1 ns to 1 s)
    UINT32 Accuracy;    // In PPM (parts per million)
    BOOLEAN SetsToZero; // Set clears sub-second time
} EFI_TIME_CAPABILITIES;

typedef EFI_STATUS(EFIAPI *EFI_GET_TIME)(
    EFI_TIME *Time,
    EFI_TIME_CAPABILITIES *Capabilities OPTIONAL);

typedef EFI_STATUS(EFIAPI *EFI_SET_TIME)(
    EFI_TIME *Time);

typedef EFI_STATUS(EFIAPI *EFI_GET_WAKEUP_TIME)(
    BOOLEAN *Enabled,
    BOOLEAN *Pending,
    EFI_TIME *Time);

typedef EFI_STATUS(EFIAPI *EFI_SET_WAKEUP_TIME)(
    BOOLEAN Enable,
    EFI_TIME *Time OPTIONAL);

typedef struct
{
    EFI_TABLE_HEADER Hdr;

    //
    // Time services
    //
    EFI_GET_TIME GetTime;
    EFI_SET_TIME SetTime;
    EFI_GET_WAKEUP_TIME GetWakeupTime;
    EFI_SET_WAKEUP_TIME SetWakeupTime;

    //
    // Virtual memory services
    //
    EFI_SET_VIRTUAL_ADDRESS_MAP SetVirtualAddressMap;
    EFI_CONVERT_POINTER ConvertPointer;

    //
    // Variable services
    //
    EFI_GET_VARIABLE GetVariable;
    EFI_GET_NEXT_VARIABLE_NAME GetNextVariableName;
    EFI_SET_VARIABLE SetVariable;

    //
    // Miscellaneous services
    //
    EFI_GET_NEXT_HIGH_MONO_COUNT GetNextHighMonotonicCount;
    EFI_RESET_SYSTEM ResetSystem;

    //
    // UEFI 2.0 Capsule Services
    //
    EFI_UPDATE_CAPSULE UpdateCapsule;
    EFI_QUERY_CAPSULE_CAPABILITIES QueryCapsuleCapabilities;

    //
    // Miscellaneous UEFI 2.0 service
    //
    EFI_QUERY_VARIABLE_INFO QueryVariableInfo;

} EFI_RUNTIME_SERVICES;

typedef struct
{
    EFI_TABLE_HEADER Hdr;
    CHAR16 *FirmwareVendor;
    UINT32 FirmwareRevision;
    EFI_HANDLE ConsoleInHandle;
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL *ConIn;
    EFI_HANDLE ConsoleOutHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
    EFI_HANDLE StandardErrorHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *StdErr;
    EFI_RUNTIME_SERVICES *RuntimeServices;
    EFI_BOOT_SERVICES *BootServices;
    UINTN NumberOfTableEntries;
    EFI_CONFIGURATION_TABLE *ConfigurationTable;
} EFI_SYSTEM_TABLE;

typedef struct _EFI_GRAPHICS_OUTPUT_PROTOCOL EFI_GRAPHICS_OUTPUT_PROTOCOL;

typedef struct
{
    UINT8 Blue;
    UINT8 Green;
    UINT8 Red;
    UINT8 Reserved;
} EFI_GRAPHICS_OUTPUT_BLT_PIXEL;

typedef struct
{
    UINT32 RedMask;
    UINT32 GreenMask;
    UINT32 BlueMask;
    UINT32 ReservedMask;
} EFI_PIXEL_BITMASK;

typedef enum
{
    PixelRedGreenBlueReserved8BitPerColor,
    PixelBlueGreenRedReserved8BitPerColor,
    PixelBitMask,
    PixelBltOnly,
    PixelFormatMax
} EFI_GRAPHICS_PIXEL_FORMAT;

typedef struct
{
    UINT32 Version;
    UINT32 HorizontalResolution;
    UINT32 VerticalResolution;
    EFI_GRAPHICS_PIXEL_FORMAT PixelFormat;
    EFI_PIXEL_BITMASK PixelInformation;
    UINT32 PixelsPerScanLine;
} EFI_GRAPHICS_OUTPUT_MODE_INFORMATION;

typedef struct
{
    UINT32 MaxMode;
    UINT32 Mode;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *Info;
    UINTN SizeOfInfo;
    EFI_PHYSICAL_ADDRESS FrameBufferBase;
    UINTN FrameBufferSize;
} EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE;

typedef EFI_STATUS(EFIAPI *EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE)(
    IN EFI_GRAPHICS_OUTPUT_PROTOCOL *This,
    IN UINT32 ModeNumber,
    OUT UINTN *SizeOfInfo,
    OUT EFI_GRAPHICS_OUTPUT_MODE_INFORMATION **Info);

typedef EFI_STATUS(EFIAPI *EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE)(
    IN EFI_GRAPHICS_OUTPUT_PROTOCOL *This,
    IN UINT32 ModeNumber);

typedef enum
{
    EfiBltVideoFill,
    EfiBltVideoToBltBuffer,
    EfiBltBufferToVideo,
    EfiBltVideoToVideo,
    EfiGraphicsOutputBltOperationMax
} EFI_GRAPHICS_OUTPUT_BLT_OPERATION;

typedef EFI_STATUS(EFIAPI *EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT)(
    IN EFI_GRAPHICS_OUTPUT_PROTOCOL *This,
    IN OUT OPTIONAL EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltBuffer,
    IN EFI_GRAPHICS_OUTPUT_BLT_OPERATION BltOperation,
    IN UINTN SourceX,
    IN UINTN SourceY,
    IN UINTN DestinationX,
    IN UINTN DestinationY,
    IN UINTN Width,
    IN UINTN Height,
    IN OPTIONAL UINTN Delta);

typedef struct _EFI_GRAPHICS_OUTPUT_PROTOCOL
{
    EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE QueryMode;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE SetMode;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT Blt;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE *Mode;
} EFI_GRAPHICS_OUTPUT_PROTOCOL;

typedef struct
{
    UINT32 SizeOfEdid;
    UINT8 *Edid;
} EFI_EDID_ACTIVE_PROTOCOL;

typedef struct
{
    UINT32 MediaId;
    BOOLEAN RemovableMedia;
    BOOLEAN MediaPresent;
    BOOLEAN LogicalPartition;
    BOOLEAN ReadOnly;
    BOOLEAN WriteCaching;
    UINT32 BlockSize;
    UINT32 IoAlign;
    EFI_LBA LastBlock;
    EFI_LBA LowestAlignedLba;
    UINT32 LogicalBlocksPerPhysicalBlock;
    UINT32 OptimalTransferLengthGranularity;
} EFI_BLOCK_IO_MEDIA;

typedef struct _EFI_BLOCK_IO_PROTOCOL EFI_BLOCK_IO_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_BLOCK_RESET)(
    IN EFI_BLOCK_IO_PROTOCOL *This,
    IN BOOLEAN ExtendedVerification);

typedef EFI_STATUS(EFIAPI *EFI_BLOCK_READ)(
    IN EFI_BLOCK_IO_PROTOCOL *This,
    IN UINT32 MediaId,
    IN EFI_LBA LBA,
    IN UINTN BufferSize,
    OUT VOID *Buffer);

typedef EFI_STATUS(EFIAPI *EFI_BLOCK_WRITE)(
    IN EFI_BLOCK_IO_PROTOCOL *This,
    IN UINT32 MediaId,
    IN EFI_LBA LBA,
    IN UINTN BufferSize,
    IN VOID *Buffer);

typedef EFI_STATUS(EFIAPI *EFI_BLOCK_FLUSH)(
    IN EFI_BLOCK_IO_PROTOCOL *This);

typedef struct _EFI_BLOCK_IO_PROTOCOL
{
    UINT64 Revision;
    EFI_BLOCK_IO_MEDIA *Media;
    EFI_BLOCK_RESET Reset;
    EFI_BLOCK_READ ReadBlocks;
    EFI_BLOCK_WRITE WriteBlocks;
    EFI_BLOCK_FLUSH FlushBlocks;
} EFI_BLOCK_IO_PROTOCOL;

typedef struct _EFI_DISK_IO_PROTOCOL EFI_DISK_IO_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_DISK_READ)(
    IN EFI_DISK_IO_PROTOCOL *This,
    IN UINT32 MediaId,
    IN UINT64 Offset,
    IN UINTN BufferSize,
    OUT VOID *Buffer);

typedef EFI_STATUS(EFIAPI *EFI_DISK_WRITE)(
    IN EFI_DISK_IO_PROTOCOL *This,
    IN UINT32 MediaId,
    IN UINT64 Offset,
    IN UINTN BufferSize,
    IN VOID *Buffer);

typedef struct _EFI_DISK_IO_PROTOCOL
{
    UINT64 Revision;
    EFI_DISK_READ ReadDisk;
    EFI_DISK_WRITE WriteDisk;
} EFI_DISK_IO_PROTOCOL;

// SIMPLE FS PROTOCOL and EFI_FILE protocl

#define EFI_FILE_PROTOCOL_REVISION 0x00010000
#define EFI_FILE_PROTOCOL_REVISION2 0x00020000
#define EFI_FILE_PROTOCOL_LATEST_REVISION EFI_FILE_PROTOCOL_REVISION2

#define EFI_FILE_MODE_READ 0x0000000000000001
#define EFI_FILE_MODE_WRITE 0x0000000000000002
#define EFI_FILE_MODE_CREATE 0x8000000000000000

#define EFI_FILE_READ_ONLY 0x0000000000000001
#define EFI_FILE_HIDDEN 0x0000000000000002
#define EFI_FILE_SYSTEM 0x0000000000000004
#define EFI_FILE_RESERVED 0x0000000000000008
#define EFI_FILE_DIRECTORY 0x0000000000000010
#define EFI_FILE_ARCHIVE 0x0000000000000020
#define EFI_FILE_VALID_ATTR 0x0000000000000037

typedef struct _EFI_FILE_PROTOCOL EFI_FILE_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_FILE_OPEN)(
    IN EFI_FILE_PROTOCOL *This,
    OUT EFI_FILE_PROTOCOL **NewHandle,
    IN CHAR16 *FileName,
    IN UINT64 OpenMode,
    IN UINT64 Attributes);

typedef EFI_STATUS(EFIAPI *EFI_FILE_CLOSE)(
    IN EFI_FILE_PROTOCOL *This);

typedef EFI_STATUS(EFIAPI *EFI_FILE_DELETE)(
    IN EFI_FILE_PROTOCOL *This);

typedef EFI_STATUS(EFIAPI *EFI_FILE_READ)(
    IN EFI_FILE_PROTOCOL *This,
    IN OUT UINTN *BufferSize,
    OUT VOID *Buffer);

typedef EFI_STATUS(EFIAPI *EFI_FILE_WRITE)(
    IN EFI_FILE_PROTOCOL *This,
    IN OUT UINTN *BufferSize,
    IN VOID *Buffer);

typedef EFI_STATUS(EFIAPI *EFI_FILE_GET_POSITION)(
    IN EFI_FILE_PROTOCOL *This,
    OUT UINT64 *Position);

typedef EFI_STATUS(EFIAPI *EFI_FILE_SET_POSITION)(
    IN EFI_FILE_PROTOCOL *This,
    IN UINT64 Position);

typedef EFI_STATUS(EFIAPI *EFI_FILE_GET_INFO)(
    IN EFI_FILE_PROTOCOL *This,
    IN EFI_GUID *InformationType,
    IN OUT UINTN *BufferSize,
    OUT VOID *Buffer);

typedef EFI_STATUS(EFIAPI *EFI_FILE_SET_INFO)(
    IN EFI_FILE_PROTOCOL *This,
    IN EFI_GUID *InformationType,
    IN UINTN BufferSize,
    IN VOID *Buffer);

typedef EFI_STATUS(EFIAPI *EFI_FILE_FLUSH)(
    IN EFI_FILE_PROTOCOL *This);

struct _EFI_FILE_PROTOCOL
{
    UINT64 Revision;
    EFI_FILE_OPEN Open;
    EFI_FILE_CLOSE Close;
    EFI_FILE_DELETE Delete;
    EFI_FILE_READ Read;
    EFI_FILE_WRITE Write;
    EFI_FILE_GET_POSITION GetPosition;
    EFI_FILE_SET_POSITION SetPosition;
    EFI_FILE_GET_INFO GetInfo;
    EFI_FILE_SET_INFO SetInfo;
    EFI_FILE_FLUSH Flush;
};

#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID                                           \
    {                                                                                  \
        0x964e5b22, 0x6459, 0x11d2, { 0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b } \
    }

typedef struct _EFI_SIMPLE_FILE_SYSTEM_PROTOCOL EFI_SIMPLE_FILE_SYSTEM_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_OPEN_VOLUME)(
    IN EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *This,
    OUT EFI_FILE_PROTOCOL **Root);

struct _EFI_SIMPLE_FILE_SYSTEM_PROTOCOL
{
    UINT64 Revision;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_OPEN_VOLUME OpenVolume;
};

// EFI_LOADED_IMAGE protocl

#define EFI_LOADED_IMAGE_PROTOCOL_GUID \
  { \
    0x5B1B31A1, 0x9562, 0x11d2, {0x8E, 0x3F, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B } \
  }

typedef struct
{
    UINT32 Revision;
    EFI_HANDLE ParentHandle;
    EFI_SYSTEM_TABLE *SystemTable;
    EFI_HANDLE DeviceHandle;
    EFI_DEVICE_PATH_PROTOCOL *FilePath;
    VOID *Reserved;
    UINT32 LoadOptionsSize;
    VOID *LoadOptions;
    VOID *ImageBase;
    UINT64 ImageSize;
    EFI_MEMORY_TYPE ImageCodeType;
    EFI_MEMORY_TYPE ImageDataType;
    EFI_IMAGE_UNLOAD Unload;

} EFI_LOADED_IMAGE_PROTOCOL;


// EFI_FILE_INFO

#define EFI_FILE_INFO_ID {0x09576e92, 0xa22f, 0x4840, {0xa8, 0x06, 0xeb, 0x6b, 0xad, 0x6e, 0x55, 0x65} }

typedef struct {
  UINT64                  Size;
  UINT64                  FileSize;
  UINT64                  PhysicalSize;
  EFI_TIME                CreateTime;
  EFI_TIME                LastAccessTime;
  EFI_TIME                ModificationTime;
  UINT64                  Attribute;
  CHAR16                  FileName[1];
} EFI_FILE_INFO;

typedef
VOID
(EFIAPI *EFI_COPY_MEM) (
    IN VOID     *Destination,
    IN VOID     *Source,
    IN UINTN    Length
);
