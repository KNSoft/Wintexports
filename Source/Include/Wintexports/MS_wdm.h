#pragma once

#include "WIE_ntdef.h"

EXTERN_C_START

#define PROCESSOR_FEATURE_MAX 64

typedef const struct _KUSER_SHARED_DATA* PCKUSER_SHARED_DATA;
#define MM_SHARED_USER_DATA_VA 0x7FFE0000
#define SharedUserData  ((PCKUSER_SHARED_DATA)MM_SHARED_USER_DATA_VA)

typedef enum _ALTERNATIVE_ARCHITECTURE_TYPE {
    StandardDesign,                 // None == 0 == standard design
    NEC98x86,                       // NEC PC98xx series on X86
    EndAlternatives                 // past end of known alternatives
} ALTERNATIVE_ARCHITECTURE_TYPE;

typedef struct _CLIENT_ID {
    HANDLE UniqueProcess;
    HANDLE UniqueThread;
} CLIENT_ID;
typedef CLIENT_ID *PCLIENT_ID;

typedef enum _SECTION_INHERIT {
    ViewShare = 1,
    ViewUnmap = 2
} SECTION_INHERIT;

typedef struct _KSYSTEM_TIME {
    ULONG LowPart;
    LONG High1Time;
    LONG High2Time;
} KSYSTEM_TIME, *PKSYSTEM_TIME;

typedef LONG KPRIORITY;

typedef enum _KWAIT_REASON {
    Executive,
    FreePage,
    PageIn,
    PoolAllocation,
    DelayExecution,
    Suspended,
    UserRequest,
    WrExecutive,
    WrFreePage,
    WrPageIn,
    WrPoolAllocation,
    WrDelayExecution,
    WrSuspended,
    WrUserRequest,
    WrSpare0,
    WrQueue,
    WrLpcReceive,
    WrLpcReply,
    WrVirtualMemory,
    WrPageOut,
    WrRendezvous,
    WrKeyedEvent,
    WrTerminated,
    WrProcessInSwap,
    WrCpuRateControl,
    WrCalloutStack,
    WrKernel,
    WrResource,
    WrPushLock,
    WrMutex,
    WrQuantumEnd,
    WrDispatchInt,
    WrPreempted,
    WrYieldExecution,
    WrFastMutex,
    WrGuardedMutex,
    WrRundown,
    WrAlertByThreadId,
    WrDeferredPreempt,
    WrPhysicalFault,
    WrIoRing,
    MaximumWaitReason
} KWAIT_REASON;

typedef struct _RTL_BITMAP {
    ULONG SizeOfBitMap;                     // Number of bits in bit map
    PULONG Buffer;                          // Pointer to the bit map itself
} RTL_BITMAP;
typedef RTL_BITMAP *PRTL_BITMAP;

#pragma region Debug Print

ULONG
__cdecl
DbgPrint(
    _In_z_ _Printf_format_string_ PCSTR Format,
    ...
);



#if (NTDDI_VERSION >= NTDDI_WINXP)
NTSYSAPI
ULONG
__cdecl
DbgPrintEx(
    _In_ ULONG ComponentId,
    _In_ ULONG Level,
    _In_z_ _Printf_format_string_ PCSTR Format,
    ...
);
#endif



#ifdef _VA_LIST_DEFINED

#if (NTDDI_VERSION >= NTDDI_WINXP)
NTSYSAPI
ULONG
NTAPI
vDbgPrintEx(
    _In_ ULONG ComponentId,
    _In_ ULONG Level,
    _In_z_ PCCH Format,
    _In_ va_list arglist
);

NTSYSAPI
ULONG
NTAPI
vDbgPrintExWithPrefix(
    _In_z_ PCCH Prefix,
    _In_ ULONG ComponentId,
    _In_ ULONG Level,
    _In_z_ PCCH Format,
    _In_ va_list arglist
);

#endif

#endif // _VA_LIST_DEFINED



#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTSYSAPI
ULONG
__cdecl
DbgPrintReturnControlC(
    _In_z_ _Printf_format_string_ PCCH Format,
    ...
);
#endif

#if (NTDDI_VERSION >= NTDDI_WINXP)
NTSYSAPI
NTSTATUS
NTAPI
DbgQueryDebugFilterState(
    _In_ ULONG ComponentId,
    _In_ ULONG Level
);
#endif

#if (NTDDI_VERSION >= NTDDI_WINXP)
NTSYSAPI
NTSTATUS
NTAPI
DbgSetDebugFilterState(
    _In_ ULONG ComponentId,
    _In_ ULONG Level,
    _In_ BOOLEAN State
);
#endif

#pragma region Functions

#pragma region String

#if (NTDDI_VERSION >= NTDDI_WIN2K)
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlUnicodeStringToInteger(
    _In_ PCUNICODE_STRING String,
    _In_opt_ ULONG Base,
    _Out_ PULONG Value
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
_IRQL_requires_max_(PASSIVE_LEVEL)
_At_(String->MaximumLength, _Const_)
NTSYSAPI
NTSTATUS
NTAPI
RtlIntegerToUnicodeString(
    _In_ ULONG Value,
    _In_opt_ ULONG Base,
    _Inout_ PUNICODE_STRING String
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSYSAPI
VOID
NTAPI
RtlInitAnsiString(
    _Out_ PANSI_STRING DestinationString,
    _In_opt_z_ __drv_aliasesMem PCSZ SourceString
);
#endif

//@[comment("MVI_tracked")]
_IRQL_requires_max_(DISPATCH_LEVEL)
_At_(DestinationString->Buffer, _Post_equal_to_(SourceString))
_At_(DestinationString->Length, _Post_equal_to_(_String_length_(SourceString) * sizeof(WCHAR)))
_At_(DestinationString->MaximumLength, _Post_equal_to_((_String_length_(SourceString) + 1) * sizeof(WCHAR)))
NTSYSAPI
VOID
NTAPI
RtlInitUnicodeString(
    _Out_ PUNICODE_STRING DestinationString,
    _In_opt_z_ __drv_aliasesMem PCWSTR SourceString
);

#if (NTDDI_VERSION >= NTDDI_WIN2K)
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSYSAPI
NTSTATUS
NTAPI
RtlAnsiStringToUnicodeString(
    _When_(AllocateDestinationString, _Out_ _At_(DestinationString->Buffer, __drv_allocatesMem(Mem)))
    _When_(!AllocateDestinationString, _Inout_)
        PUNICODE_STRING DestinationString,
    _In_ PCANSI_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)

_When_(AllocateDestinationString,
       _At_(DestinationString->MaximumLength,
            _Out_range_(<= , (SourceString->MaximumLength / sizeof(WCHAR)))))
_When_(!AllocateDestinationString,
       _At_(DestinationString->Buffer, _Const_)
       _At_(DestinationString->MaximumLength, _Const_))
_IRQL_requires_max_(PASSIVE_LEVEL)
_When_(AllocateDestinationString, _Must_inspect_result_)
NTSYSAPI
NTSTATUS
NTAPI
RtlUnicodeStringToAnsiString(
    _When_(AllocateDestinationString, _Out_ _At_(DestinationString->Buffer, __drv_allocatesMem(Mem)))
    _When_(!AllocateDestinationString, _Inout_)
        PANSI_STRING DestinationString,
    _In_ PCUNICODE_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSYSAPI
LONG
NTAPI
RtlCompareUnicodeStrings(
    _In_reads_(String1Length) PCWCH String1,
    _In_ SIZE_T String1Length,
    _In_reads_(String2Length) PCWCH String2,
    _In_ SIZE_T String2Length,
    _In_ BOOLEAN CaseInSensitive
);

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSYSAPI
LONG
NTAPI
RtlCompareUnicodeString(
    _In_ PCUNICODE_STRING String1,
    _In_ PCUNICODE_STRING String2,
    _In_ BOOLEAN CaseInSensitive
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
//@[comment("MVI_tracked")]
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSYSAPI
BOOLEAN
NTAPI
RtlEqualUnicodeString(
    _In_ PCUNICODE_STRING String1,
    _In_ PCUNICODE_STRING String2,
    _In_ BOOLEAN CaseInSensitive
);
#endif

#pragma endregion String

#pragma endregion Functions

#pragma endregion Debug Print

#pragma region Pseudo Handles

#define NtCurrentProcess() ( (HANDLE)(LONG_PTR) -1 )  
#define ZwCurrentProcess() NtCurrentProcess()         
#define NtCurrentThread() ( (HANDLE)(LONG_PTR) -2 )   
#define ZwCurrentThread() NtCurrentThread()           
#define NtCurrentSession() ( (HANDLE)(LONG_PTR) -3 )  
#define ZwCurrentSession() NtCurrentSession()    

#pragma endregion Pseudo Handles

#pragma region IO

typedef struct _IO_STATUS_BLOCK {
    union {
        NTSTATUS Status;
        PVOID Pointer;
    };

    ULONG_PTR Information;
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;

typedef
VOID
(NTAPI *PIO_APC_ROUTINE) (
    _In_ PVOID ApcContext,
    _In_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG Reserved
    );

#pragma endregion IO

#pragma region File Flags

//
// Define the create disposition values
//

#define FILE_SUPERSEDE                  0x00000000
#define FILE_OPEN                       0x00000001
#define FILE_CREATE                     0x00000002
#define FILE_OPEN_IF                    0x00000003
#define FILE_OVERWRITE                  0x00000004
#define FILE_OVERWRITE_IF               0x00000005
#define FILE_MAXIMUM_DISPOSITION        0x00000005

//
// Define the create/open option flags
//

#define FILE_DIRECTORY_FILE                     0x00000001
#define FILE_WRITE_THROUGH                      0x00000002
#define FILE_SEQUENTIAL_ONLY                    0x00000004
#define FILE_NO_INTERMEDIATE_BUFFERING          0x00000008

#define FILE_SYNCHRONOUS_IO_ALERT               0x00000010
#define FILE_SYNCHRONOUS_IO_NONALERT            0x00000020
#define FILE_NON_DIRECTORY_FILE                 0x00000040
#define FILE_CREATE_TREE_CONNECTION             0x00000080

#define FILE_COMPLETE_IF_OPLOCKED               0x00000100
#define FILE_NO_EA_KNOWLEDGE                    0x00000200
#define FILE_OPEN_REMOTE_INSTANCE               0x00000400
#define FILE_RANDOM_ACCESS                      0x00000800

#define FILE_DELETE_ON_CLOSE                    0x00001000
#define FILE_OPEN_BY_FILE_ID                    0x00002000
#define FILE_OPEN_FOR_BACKUP_INTENT             0x00004000
#define FILE_NO_COMPRESSION                     0x00008000

#if (NTDDI_VERSION >= NTDDI_WIN7)
#define FILE_OPEN_REQUIRING_OPLOCK              0x00010000
#define FILE_DISALLOW_EXCLUSIVE                 0x00020000
#endif /* NTDDI_VERSION >= NTDDI_WIN7 */
#if (NTDDI_VERSION >= NTDDI_WIN8)
#define FILE_SESSION_AWARE                      0x00040000
#endif /* NTDDI_VERSION >= NTDDI_WIN8 */

//
//  CreateOptions flag to pass in call to CreateFile to allow the write through xro.sys
//

#define FILE_RESERVE_OPFILTER                   0x00100000
#define FILE_OPEN_REPARSE_POINT                 0x00200000
#define FILE_OPEN_NO_RECALL                     0x00400000
#define FILE_OPEN_FOR_FREE_SPACE_QUERY          0x00800000

#pragma endregion File Flags

#pragma region File Information

typedef enum _FILE_INFORMATION_CLASS {
    FileDirectoryInformation                         = 1,
    FileFullDirectoryInformation,                   // 2
    FileBothDirectoryInformation,                   // 3
    FileBasicInformation,                           // 4
    FileStandardInformation,                        // 5
    FileInternalInformation,                        // 6
    FileEaInformation,                              // 7
    FileAccessInformation,                          // 8
    FileNameInformation,                            // 9
    FileRenameInformation,                          // 10
    FileLinkInformation,                            // 11
    FileNamesInformation,                           // 12
    FileDispositionInformation,                     // 13
    FilePositionInformation,                        // 14
    FileFullEaInformation,                          // 15
    FileModeInformation,                            // 16
    FileAlignmentInformation,                       // 17
    FileAllInformation,                             // 18
    FileAllocationInformation,                      // 19
    FileEndOfFileInformation,                       // 20
    FileAlternateNameInformation,                   // 21
    FileStreamInformation,                          // 22
    FilePipeInformation,                            // 23
    FilePipeLocalInformation,                       // 24
    FilePipeRemoteInformation,                      // 25
    FileMailslotQueryInformation,                   // 26
    FileMailslotSetInformation,                     // 27
    FileCompressionInformation,                     // 28
    FileObjectIdInformation,                        // 29
    FileCompletionInformation,                      // 30
    FileMoveClusterInformation,                     // 31
    FileQuotaInformation,                           // 32
    FileReparsePointInformation,                    // 33
    FileNetworkOpenInformation,                     // 34
    FileAttributeTagInformation,                    // 35
    FileTrackingInformation,                        // 36
    FileIdBothDirectoryInformation,                 // 37
    FileIdFullDirectoryInformation,                 // 38
    FileValidDataLengthInformation,                 // 39
    FileShortNameInformation,                       // 40
    FileIoCompletionNotificationInformation,        // 41
    FileIoStatusBlockRangeInformation,              // 42
    FileIoPriorityHintInformation,                  // 43
    FileSfioReserveInformation,                     // 44
    FileSfioVolumeInformation,                      // 45
    FileHardLinkInformation,                        // 46
    FileProcessIdsUsingFileInformation,             // 47
    FileNormalizedNameInformation,                  // 48
    FileNetworkPhysicalNameInformation,             // 49
    FileIdGlobalTxDirectoryInformation,             // 50
    FileIsRemoteDeviceInformation,                  // 51
    FileUnusedInformation,                          // 52
    FileNumaNodeInformation,                        // 53
    FileStandardLinkInformation,                    // 54
    FileRemoteProtocolInformation,                  // 55

        //
        //  These are special versions of these operations (defined earlier)
        //  which can be used by kernel mode drivers only to bypass security
        //  access checks for Rename and HardLink operations.  These operations
        //  are only recognized by the IOManager, a file system should never
        //  receive these.
        //

    FileRenameInformationBypassAccessCheck,         // 56
    FileLinkInformationBypassAccessCheck,           // 57

        //
        // End of special information classes reserved for IOManager.
        //

    FileVolumeNameInformation,                      // 58
    FileIdInformation,                              // 59
    FileIdExtdDirectoryInformation,                 // 60
    FileReplaceCompletionInformation,               // 61
    FileHardLinkFullIdInformation,                  // 62
    FileIdExtdBothDirectoryInformation,             // 63
    FileDispositionInformationEx,                   // 64
    FileRenameInformationEx,                        // 65
    FileRenameInformationExBypassAccessCheck,       // 66
    FileDesiredStorageClassInformation,             // 67
    FileStatInformation,                            // 68
    FileMemoryPartitionInformation,                 // 69
    FileStatLxInformation,                          // 70
    FileCaseSensitiveInformation,                   // 71
    FileLinkInformationEx,                          // 72
    FileLinkInformationExBypassAccessCheck,         // 73
    FileStorageReserveIdInformation,                // 74
    FileCaseSensitiveInformationForceAccessCheck,   // 75
    FileKnownFolderInformation,                     // 76

    FileMaximumInformation
} FILE_INFORMATION_CLASS, *PFILE_INFORMATION_CLASS;

typedef struct _FILE_BASIC_INFORMATION {
    LARGE_INTEGER CreationTime;
    LARGE_INTEGER LastAccessTime;
    LARGE_INTEGER LastWriteTime;
    LARGE_INTEGER ChangeTime;
    ULONG FileAttributes;
} FILE_BASIC_INFORMATION, *PFILE_BASIC_INFORMATION;

typedef struct _FILE_STANDARD_INFORMATION {
    LARGE_INTEGER AllocationSize;
    LARGE_INTEGER EndOfFile;
    ULONG NumberOfLinks;
    BOOLEAN DeletePending;
    BOOLEAN Directory;
} FILE_STANDARD_INFORMATION, *PFILE_STANDARD_INFORMATION;

typedef struct _FILE_NETWORK_OPEN_INFORMATION {
    LARGE_INTEGER CreationTime;
    LARGE_INTEGER LastAccessTime;
    LARGE_INTEGER LastWriteTime;
    LARGE_INTEGER ChangeTime;
    LARGE_INTEGER AllocationSize;
    LARGE_INTEGER EndOfFile;
    ULONG FileAttributes;
} FILE_NETWORK_OPEN_INFORMATION, *PFILE_NETWORK_OPEN_INFORMATION;

#pragma region File Information

#pragma region Registry

typedef enum _KEY_VALUE_INFORMATION_CLASS {
    KeyValueBasicInformation,
    KeyValueFullInformation,
    KeyValuePartialInformation,
    KeyValueFullInformationAlign64,
    KeyValuePartialInformationAlign64,
    KeyValueLayerInformation,
    MaxKeyValueInfoClass  // MaxKeyValueInfoClass should always be the last enum
} KEY_VALUE_INFORMATION_CLASS;

typedef struct _KEY_VALUE_PARTIAL_INFORMATION {
    ULONG   TitleIndex;
    ULONG   Type;
    ULONG   DataLength;
    _Field_size_bytes_(DataLength) UCHAR Data[1]; // Variable size
} KEY_VALUE_PARTIAL_INFORMATION, *PKEY_VALUE_PARTIAL_INFORMATION;

#pragma endregion Registry

#pragma region SE_XXX_PRIVILEGE

//
// These must be converted to LUIDs before use.
//

#define SE_MIN_WELL_KNOWN_PRIVILEGE         (2L)
#define SE_CREATE_TOKEN_PRIVILEGE           (2L)
#define SE_ASSIGNPRIMARYTOKEN_PRIVILEGE     (3L)
#define SE_LOCK_MEMORY_PRIVILEGE            (4L)
#define SE_INCREASE_QUOTA_PRIVILEGE         (5L)


#define SE_MACHINE_ACCOUNT_PRIVILEGE        (6L)
#define SE_TCB_PRIVILEGE                    (7L)
#define SE_SECURITY_PRIVILEGE               (8L)
#define SE_TAKE_OWNERSHIP_PRIVILEGE         (9L)
#define SE_LOAD_DRIVER_PRIVILEGE            (10L)
#define SE_SYSTEM_PROFILE_PRIVILEGE         (11L)
#define SE_SYSTEMTIME_PRIVILEGE             (12L)
#define SE_PROF_SINGLE_PROCESS_PRIVILEGE    (13L)
#define SE_INC_BASE_PRIORITY_PRIVILEGE      (14L)
#define SE_CREATE_PAGEFILE_PRIVILEGE        (15L)
#define SE_CREATE_PERMANENT_PRIVILEGE       (16L)
#define SE_BACKUP_PRIVILEGE                 (17L)
#define SE_RESTORE_PRIVILEGE                (18L)
#define SE_SHUTDOWN_PRIVILEGE               (19L)
#define SE_DEBUG_PRIVILEGE                  (20L)
#define SE_AUDIT_PRIVILEGE                  (21L)
#define SE_SYSTEM_ENVIRONMENT_PRIVILEGE     (22L)
#define SE_CHANGE_NOTIFY_PRIVILEGE          (23L)
#define SE_REMOTE_SHUTDOWN_PRIVILEGE        (24L)
#define SE_UNDOCK_PRIVILEGE                 (25L)
#define SE_SYNC_AGENT_PRIVILEGE             (26L)
#define SE_ENABLE_DELEGATION_PRIVILEGE      (27L)
#define SE_MANAGE_VOLUME_PRIVILEGE          (28L)
#define SE_IMPERSONATE_PRIVILEGE            (29L)
#define SE_CREATE_GLOBAL_PRIVILEGE          (30L)
#define SE_TRUSTED_CREDMAN_ACCESS_PRIVILEGE (31L)
#define SE_RELABEL_PRIVILEGE                (32L)
#define SE_INC_WORKING_SET_PRIVILEGE        (33L)
#define SE_TIME_ZONE_PRIVILEGE              (34L)
#define SE_CREATE_SYMBOLIC_LINK_PRIVILEGE   (35L)
#define SE_DELEGATE_SESSION_USER_IMPERSONATE_PRIVILEGE   (36L)
#define SE_MAX_WELL_KNOWN_PRIVILEGE         (SE_DELEGATE_SESSION_USER_IMPERSONATE_PRIVILEGE)

#pragma endregion SE_XXX_PRIVILEGE

#include "Undoc_Types_Ke.h"
#include "Undoc_Types_Ex.h"
#include "Undoc_Types_Rtl.h"

EXTERN_C_END
