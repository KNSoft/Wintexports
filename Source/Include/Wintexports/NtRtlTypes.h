#pragma once

#include "NtMinDef.h"

#include "NtBasicTypes.h"

typedef struct _RTLP_CURDIR_REF
{
    LONG RefCount;
    HANDLE Handle;
} RTLP_CURDIR_REF, *PRTLP_CURDIR_REF;

typedef struct _RTL_RELATIVE_NAME_U
{
    UNICODE_STRING RelativeName;
    HANDLE ContainingDirectory;
    PRTLP_CURDIR_REF CurDirRef;
} RTL_RELATIVE_NAME_U, *PRTL_RELATIVE_NAME_U;

typedef
_Function_class_(RTL_RUN_ONCE_INIT_FN)
_IRQL_requires_same_
ULONG /* LOGICAL */
NTAPI
RTL_RUN_ONCE_INIT_FN(
    _Inout_ PRTL_RUN_ONCE RunOnce,
    _Inout_opt_ PVOID Parameter,
    _Inout_opt_ PVOID *Context
);
typedef RTL_RUN_ONCE_INIT_FN *PRTL_RUN_ONCE_INIT_FN;

typedef
_Function_class_(RTL_HEAP_COMMIT_ROUTINE)
_IRQL_requires_same_
NTSTATUS
NTAPI
RTL_HEAP_COMMIT_ROUTINE(
    _In_ PVOID Base,
    _Inout_ PVOID *CommitAddress,
    _Inout_ PSIZE_T CommitSize
);
typedef RTL_HEAP_COMMIT_ROUTINE *PRTL_HEAP_COMMIT_ROUTINE;

typedef struct _RTL_HEAP_PARAMETERS
{
    ULONG Length;
    SIZE_T SegmentReserve;
    SIZE_T SegmentCommit;
    SIZE_T DeCommitFreeBlockThreshold;
    SIZE_T DeCommitTotalFreeThreshold;
    SIZE_T MaximumAllocationSize;
    SIZE_T VirtualMemoryThreshold;
    SIZE_T InitialCommit;
    SIZE_T InitialReserve;
    PRTL_HEAP_COMMIT_ROUTINE CommitRoutine;
    SIZE_T Reserved[2];
} RTL_HEAP_PARAMETERS, *PRTL_HEAP_PARAMETERS;

#pragma region RTL_DRIVE_LETTER_CURDIR[64/32]

typedef struct _RTL_DRIVE_LETTER_CURDIR
{
    USHORT Flags;
    USHORT Length;
    UINT TimeStamp;
    STRING DosPath;
} RTL_DRIVE_LETTER_CURDIR, *PRTL_DRIVE_LETTER_CURDIR;

#if !defined(WIE_NO_EXT)

typedef struct _RTL_DRIVE_LETTER_CURDIR64
{
    USHORT Flags;
    USHORT Length;
    UINT TimeStamp;
    STRING64 DosPath;
} RTL_DRIVE_LETTER_CURDIR64, *PRTL_DRIVE_LETTER_CURDIR64;

typedef struct _RTL_DRIVE_LETTER_CURDIR32
{
    USHORT Flags;
    USHORT Length;
    UINT TimeStamp;
    STRING32 DosPath;
} RTL_DRIVE_LETTER_CURDIR32, *PRTL_DRIVE_LETTER_CURDIR32;

#endif /* !defined(WIE_NO_EXT) */

#pragma endregion RTL_DRIVE_LETTER_CURDIR[64/32]

#pragma region RTL_BITMAP[64/32]

typedef struct _RTL_BITMAP
{
    ULONG SizeOfBitMap;                     // Number of bits in bit map
    PULONG Buffer;                          // Pointer to the bit map itself
} RTL_BITMAP, *PRTL_BITMAP;

#if !defined(WIE_NO_EXT)

typedef struct _RTL_BITMAP64
{
    ULONG SizeOfBitMap;
    ULONG* POINTER_64 Buffer;
} RTL_BITMAP64, *PRTL_BITMAP64;

typedef struct _RTL_BITMAP32
{
    ULONG SizeOfBitMap;
    ULONG* POINTER_32 Buffer;
} RTL_BITMAP32, *PRTL_BITMAP32;

#endif /* !defined(WIE_NO_EXT) */

#pragma endregion RTL_BITMAP[64/32]

#pragma region RTL_USER_PROCESS_PARAMETERS[64/32]

typedef struct _RTL_USER_PROCESS_PARAMETERS
{
    ULONG MaximumLength;
    ULONG Length;
    ULONG Flags;
    ULONG DebugFlags;
    HANDLE ConsoleHandle;
    ULONG ConsoleFlags;
    HANDLE StandardInput;
    HANDLE StandardOutput;
    HANDLE StandardError;
    CURDIR CurrentDirectory;
    UNICODE_STRING DllPath;
    UNICODE_STRING ImagePathName;
    UNICODE_STRING CommandLine;
    LPWSTR Environment;
    ULONG StartingX;
    ULONG StartingY;
    ULONG CountX;
    ULONG CountY;
    ULONG CountCharsX;
    ULONG CountCharsY;
    ULONG FillAttribute;
    ULONG WindowFlags;
    ULONG ShowWindowFlags;
    UNICODE_STRING WindowTitle;
    UNICODE_STRING DesktopInfo;
    UNICODE_STRING ShellInfo;
    UNICODE_STRING RuntimeData;
    RTL_DRIVE_LETTER_CURDIR CurrentDirectores[32];
    ULONG_PTR EnvironmentSize;
    ULONG_PTR EnvironmentVersion;
    PVOID PackageDependencyData;
    ULONG ProcessGroupId;
    ULONG LoaderThreads;
    UNICODE_STRING RedirectionDllName;
    UNICODE_STRING HeapPartitionName;
    PULONGLONG DefaultThreadpoolCpuSetMasks;
    ULONG DefaultThreadpoolCpuSetMaskCount;
    ULONG DefaultThreadpoolThreadMaximum;
    ULONG HeapMemoryTypeMask;
} RTL_USER_PROCESS_PARAMETERS, *PRTL_USER_PROCESS_PARAMETERS;

#if !defined(WIE_NO_EXT)

typedef struct _RTL_USER_PROCESS_PARAMETERS64
{
    ULONG MaximumLength;
    ULONG Length;
    ULONG Flags;
    ULONG DebugFlags;
    VOID* POINTER_64 ConsoleHandle;
    ULONG ConsoleFlags;
    VOID* POINTER_64 StandardInput;
    VOID* POINTER_64 StandardOutput;
    VOID* POINTER_64 StandardError;
    CURDIR64 CurrentDirectory;
    UNICODE_STRING64 DllPath;
    UNICODE_STRING64 ImagePathName;
    UNICODE_STRING64 CommandLine;
    WCHAR* POINTER_64 Environment;
    ULONG StartingX;
    ULONG StartingY;
    ULONG CountX;
    ULONG CountY;
    ULONG CountCharsX;
    ULONG CountCharsY;
    ULONG FillAttribute;
    ULONG WindowFlags;
    ULONG ShowWindowFlags;
    UNICODE_STRING64 WindowTitle;
    UNICODE_STRING64 DesktopInfo;
    UNICODE_STRING64 ShellInfo;
    UNICODE_STRING64 RuntimeData;
    RTL_DRIVE_LETTER_CURDIR64 CurrentDirectores[32];
    ULONGLONG EnvironmentSize;
    ULONGLONG EnvironmentVersion;
    VOID* POINTER_64 PackageDependencyData;
    ULONG ProcessGroupId;
    ULONG LoaderThreads;
    UNICODE_STRING64 RedirectionDllName;
    UNICODE_STRING64 HeapPartitionName;
    ULONGLONG* POINTER_64 DefaultThreadpoolCpuSetMasks;
    ULONG DefaultThreadpoolCpuSetMaskCount;
    ULONG DefaultThreadpoolThreadMaximum;
    ULONG HeapMemoryTypeMask;
} RTL_USER_PROCESS_PARAMETERS64, *PRTL_USER_PROCESS_PARAMETERS64;

typedef struct _RTL_USER_PROCESS_PARAMETERS32
{
    ULONG MaximumLength;
    ULONG Length;
    ULONG Flags;
    ULONG DebugFlags;
    VOID* POINTER_32 ConsoleHandle;
    ULONG ConsoleFlags;
    VOID* POINTER_32 StandardInput;
    VOID* POINTER_32 StandardOutput;
    VOID* POINTER_32 StandardError;
    CURDIR32 CurrentDirectory;
    UNICODE_STRING32 DllPath;
    UNICODE_STRING32 ImagePathName;
    UNICODE_STRING32 CommandLine;
    WCHAR* POINTER_32 Environment;
    ULONG StartingX;
    ULONG StartingY;
    ULONG CountX;
    ULONG CountY;
    ULONG CountCharsX;
    ULONG CountCharsY;
    ULONG FillAttribute;
    ULONG WindowFlags;
    ULONG ShowWindowFlags;
    UNICODE_STRING32 WindowTitle;
    UNICODE_STRING32 DesktopInfo;
    UNICODE_STRING32 ShellInfo;
    UNICODE_STRING32 RuntimeData;
    RTL_DRIVE_LETTER_CURDIR32 CurrentDirectores[32];
    ULONG EnvironmentSize;
    ULONG EnvironmentVersion;
    VOID* POINTER_32 PackageDependencyData;
    ULONG ProcessGroupId;
    ULONG LoaderThreads;
    UNICODE_STRING32 RedirectionDllName;
    UNICODE_STRING32 HeapPartitionName;
    ULONGLONG* POINTER_32 DefaultThreadpoolCpuSetMasks;
    ULONG DefaultThreadpoolCpuSetMaskCount;
    ULONG DefaultThreadpoolThreadMaximum;
    ULONG HeapMemoryTypeMask;
} RTL_USER_PROCESS_PARAMETERS32, *PRTL_USER_PROCESS_PARAMETERS32;

#endif /* !defined(WIE_NO_EXT) */

#pragma endregion RTL_USER_PROCESS_PARAMETERS[64/32]

#if !defined(WIE_NO_EXT)

#pragma region RTL_BALANCED_NODE(64/32)

typedef struct _RTL_BALANCED_NODE64
{
    union
    {
        struct _RTL_BALANCED_NODE64* POINTER_64 Children[2];
        struct
        {
            struct _RTL_BALANCED_NODE64* POINTER_64 Left;
            struct _RTL_BALANCED_NODE64* POINTER_64 Right;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;

#define RTL_BALANCED_NODE_RESERVED_PARENT_MASK 3

    union
    {
        UCHAR Red : 1;
        UCHAR Balance : 2;
        ULONGLONG ParentValue;
    } DUMMYUNIONNAME2;
} RTL_BALANCED_NODE64, *PRTL_BALANCED_NODE64;

typedef struct _RTL_BALANCED_NODE32
{
    union
    {
        struct _RTL_BALANCED_NODE32* POINTER_32 Children[2];
        struct
        {
            struct _RTL_BALANCED_NODE32* POINTER_32 Left;
            struct _RTL_BALANCED_NODE32* POINTER_32 Right;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;

#define RTL_BALANCED_NODE_RESERVED_PARENT_MASK 3

    union
    {
        UCHAR Red : 1;
        UCHAR Balance : 2;
        ULONG ParentValue;
    } DUMMYUNIONNAME2;
} RTL_BALANCED_NODE32, *PRTL_BALANCED_NODE32;

#pragma endregion RTL_BALANCED_NODE(64/32)

#pragma region RTL_CRITICAL_SECTION[_DEBUG](64/32)

typedef struct _RTL_CRITICAL_SECTION64 RTL_CRITICAL_SECTION64, *PRTL_CRITICAL_SECTION64;
typedef struct _RTL_CRITICAL_SECTION32 RTL_CRITICAL_SECTION32, *PRTL_CRITICAL_SECTION32;

typedef struct _RTL_CRITICAL_SECTION_DEBUG64
{
    WORD Type;
    WORD CreatorBackTraceIndex;
    RTL_CRITICAL_SECTION64* POINTER_64 CriticalSection;
    LIST_ENTRY64 ProcessLocksList;
    DWORD EntryCount;
    DWORD ContentionCount;
    DWORD Flags;
    WORD CreatorBackTraceIndexHigh;
    WORD Identifier;
} RTL_CRITICAL_SECTION_DEBUG64, *PRTL_CRITICAL_SECTION_DEBUG64, RTL_RESOURCE_DEBUG64, *PRTL_RESOURCE_DEBUG64;

typedef struct _RTL_CRITICAL_SECTION_DEBUG32
{
    WORD Type;
    WORD CreatorBackTraceIndex;
    RTL_CRITICAL_SECTION32* POINTER_32 CriticalSection;
    LIST_ENTRY32 ProcessLocksList;
    DWORD EntryCount;
    DWORD ContentionCount;
    DWORD Flags;
    WORD CreatorBackTraceIndexHigh;
    WORD Identifier;
} RTL_CRITICAL_SECTION_DEBUG32, *PRTL_CRITICAL_SECTION_DEBUG32, RTL_RESOURCE_DEBUG32, *PRTL_RESOURCE_DEBUG32;

struct _RTL_CRITICAL_SECTION64
{
    RTL_CRITICAL_SECTION_DEBUG64* POINTER_64 DebugInfo;
    LONG LockCount;
    LONG RecursionCount;
    VOID* POINTER_64 OwningThread;
    VOID* POINTER_64 LockSemaphore;
    ULONGLONG SpinCount;
};

struct _RTL_CRITICAL_SECTION32
{
    RTL_CRITICAL_SECTION_DEBUG32* POINTER_32 DebugInfo;
    LONG LockCount;
    LONG RecursionCount;
    VOID* POINTER_32 OwningThread;
    VOID* POINTER_32 LockSemaphore;
    ULONG SpinCount;
};

#pragma endregion RTL_CRITICAL_SECTION[_DEBUG](64/32)

#endif /* !defined(WIE_NO_EXT) */
