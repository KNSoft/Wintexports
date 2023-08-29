#pragma once

#include "WIE_ntdef.h"
#include "Undoc_ntifs.h"

typedef struct _MEMORY_RANGE_ENTRY
{
    PVOID VirtualAddress;
    SIZE_T NumberOfBytes;
} MEMORY_RANGE_ENTRY, *PMEMORY_RANGE_ENTRY;

typedef struct _FILE_FULL_DIR_INFORMATION
{
    ULONG NextEntryOffset;
    ULONG FileIndex;
    LARGE_INTEGER CreationTime;
    LARGE_INTEGER LastAccessTime;
    LARGE_INTEGER LastWriteTime;
    LARGE_INTEGER ChangeTime;
    LARGE_INTEGER EndOfFile;
    LARGE_INTEGER AllocationSize;
    ULONG FileAttributes;
    ULONG FileNameLength;
    ULONG EaSize;
    _Field_size_bytes_(FileNameLength) WCHAR FileName[1];
} FILE_FULL_DIR_INFORMATION, *PFILE_FULL_DIR_INFORMATION;

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

typedef struct _RTL_HEAP_PARAMETERS {
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
    SIZE_T Reserved[ 2 ];
} RTL_HEAP_PARAMETERS, *PRTL_HEAP_PARAMETERS;

#ifndef FlagOn
#define FlagOn(_F,_SF)        ((_F) & (_SF))
#endif

#ifndef BooleanFlagOn
#define BooleanFlagOn(F,SF)   ((BOOLEAN)(((F) & (SF)) != 0))
#endif

#ifndef SetFlag
#define SetFlag(_F,_SF)       ((_F) |= (_SF))
#endif

#ifndef ClearFlag
#define ClearFlag(_F,_SF)     ((_F) &= ~(_SF))
#endif

#pragma region Rtl*

#pragma region Random

#if (NTDDI_VERSION >= NTDDI_WIN2K)
_IRQL_requires_max_(APC_LEVEL)
_Ret_range_(<= , MAXLONG)
NTSYSAPI
ULONG
NTAPI
RtlRandom(
    _Inout_ PULONG Seed
);
#endif

#if (NTDDI_VERSION >= NTDDI_WINXP)
_IRQL_requires_max_(APC_LEVEL)
_Ret_range_(<= , MAXLONG)
NTSYSAPI
ULONG
NTAPI
RtlRandomEx(
    _Inout_ PULONG Seed
);
#endif // NTDDI_VERSION >= NTDDI_WINXP

#pragma endregion Random

#pragma region Error

#if (NTDDI_VERSION >= NTDDI_WIN2K)
//@[comment("MVI_tracked")]
_IRQL_requires_max_(APC_LEVEL)
_When_(Status < 0, _Out_range_(> , 0))
_When_(Status >= 0, _Out_range_(== , 0))
NTSYSAPI
ULONG
NTAPI
RtlNtStatusToDosError(
   _In_ NTSTATUS Status
);
#endif

// end_wudfpwdm

#if (NTDDI_VERSION >= NTDDI_WINXP)
//@[comment("MVI_tracked")]
_When_(Status < 0, _Out_range_(> , 0))
_When_(Status >= 0, _Out_range_(== , 0))
NTSYSAPI
ULONG
NTAPI
RtlNtStatusToDosErrorNoTeb(
   _In_ NTSTATUS Status
);
#endif

#pragma endregion Error

#pragma region Heap

#if (NTDDI_VERSION >= NTDDI_WINXP)
//@[comment("MVI_tracked")]
_Must_inspect_result_
NTSYSAPI
PVOID
NTAPI
RtlCreateHeap(
    _In_     ULONG Flags,
    _In_opt_ PVOID HeapBase,
    _In_opt_ SIZE_T ReserveSize,
    _In_opt_ SIZE_T CommitSize,
    _In_opt_ PVOID Lock,
    _When_((Flags & 0x100) != 0,
           _In_reads_bytes_opt_(sizeof(RTL_SEGMENT_HEAP_PARAMETERS)))
    _When_((Flags & 0x100) == 0,
           _In_reads_bytes_opt_(sizeof(RTL_HEAP_PARAMETERS)))
    PRTL_HEAP_PARAMETERS Parameters
);
#endif // NTDDI_VERSION >= NTDDI_WINXP

#if (NTDDI_VERSION >= NTDDI_WIN8)
//@[comment("MVI_tracked")]
_Success_(return != 0)
NTSYSAPI
LOGICAL
NTAPI
RtlFreeHeap(
    _In_ PVOID HeapHandle,
    _In_opt_ ULONG Flags,
    _Frees_ptr_opt_ PVOID BaseAddress
);
#else
#if (NTDDI_VERSION >= NTDDI_WIN2K)
//@[comment("MVI_tracked")]
_Success_(return != 0)
NTSYSAPI
BOOLEAN
NTAPI
RtlFreeHeap(
    _In_ PVOID HeapHandle,
    _In_opt_ ULONG Flags,
    _Frees_ptr_opt_ PVOID BaseAddress
);
#endif // NTDDI_VERSION >= NTDDI_WIN2K
#endif // NTDDI_VERSION >= NTDDI_WIN8

#if (NTDDI_VERSION >= NTDDI_WINXP)
//@[comment("MVI_tracked")]
NTSYSAPI
PVOID
NTAPI
RtlDestroyHeap(
    _In_ _Post_invalid_ PVOID HeapHandle
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
//@[comment("MVI_tracked")]
NTSYSAPI
_Must_inspect_result_
_Ret_maybenull_
_Post_writable_byte_size_(Size)
PVOID
NTAPI
RtlAllocateHeap(
    _In_ PVOID HeapHandle,
    _In_opt_ ULONG Flags,
    _In_ SIZE_T Size
);
#endif

#pragma endregion Heap

#pragma region String

#if (NTDDI_VERSION >= NTDDI_WIN2K)
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlMultiByteToUnicodeN(
    _Out_writes_bytes_to_(MaxBytesInUnicodeString, *BytesInUnicodeString) PWCH UnicodeString,
    _In_ ULONG MaxBytesInUnicodeString,
    _Out_opt_ PULONG BytesInUnicodeString,
    _In_reads_bytes_(BytesInMultiByteString) const CHAR *MultiByteString,
    _In_ ULONG BytesInMultiByteString
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlUnicodeToMultiByteN(
    _Out_writes_bytes_to_(MaxBytesInMultiByteString, *BytesInMultiByteString) PCHAR MultiByteString,
    _In_ ULONG MaxBytesInMultiByteString,
    _Out_opt_ PULONG BytesInMultiByteString,
    _In_reads_bytes_(BytesInUnicodeString) PCWCH UnicodeString,
    _In_ ULONG BytesInUnicodeString
);
#endif

#pragma endregion String

#pragma endregion Rtl*

#pragma region Nt*

#pragma region Virtual Memory

#if (NTDDI_VERSION >= NTDDI_WIN2K)
//@[comment("MVI_tracked")]
_Must_inspect_result_
__drv_allocatesMem(Mem)
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtAllocateVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _Inout_ _At_(*BaseAddress, _Readable_bytes_(*RegionSize) _Writable_bytes_(*RegionSize) _Post_readable_byte_size_(*RegionSize)) PVOID *BaseAddress,
    _In_ ULONG_PTR ZeroBits,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG AllocationType,
    _In_ ULONG Protect
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
//@[comment("MVI_tracked")]
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtFreeVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _Inout_ __drv_freesMem(Mem) PVOID *BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG FreeType
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
//@[comment("MVI_tracked")]
_Must_inspect_result_
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress,
    _In_ MEMORY_INFORMATION_CLASS MemoryInformationClass,
    _Out_writes_bytes_(MemoryInformationLength) PVOID MemoryInformation,
    _In_ SIZE_T MemoryInformationLength,
    _Out_opt_ PSIZE_T ReturnLength
);
#endif

#pragma endregion Virtual Memory

#pragma region Process and Thread

//@[comment("MVI_tracked")]
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetInformationThread(
    _In_ HANDLE ThreadHandle,
    _In_ THREADINFOCLASS ThreadInformationClass,
    _When_((ThreadInformationClass != ThreadManageWritesToExecutableMemory),
           _In_reads_bytes_(ThreadInformationLength))
    _When_((ThreadInformationClass == ThreadManageWritesToExecutableMemory),
           _Inout_updates_(ThreadInformationLength))
    PVOID ThreadInformation,
    _In_ ULONG ThreadInformationLength
);

#pragma endregion Process and Thread

#pragma region File

#if (NTDDI_VERSION >= NTDDI_WIN2K)
//@[comment("MVI_tracked")]
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateFile(
    _Out_ PHANDLE FileHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_opt_ PLARGE_INTEGER AllocationSize,
    _In_ ULONG FileAttributes,
    _In_ ULONG ShareAccess,
    _In_ ULONG CreateDisposition,
    _In_ ULONG CreateOptions,
    _In_reads_bytes_opt_(EaLength) PVOID EaBuffer,
    _In_ ULONG EaLength
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
//@[comment("MVI_tracked")]
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtReadFile(
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _Out_writes_bytes_(Length) PVOID Buffer,
    _In_ ULONG Length,
    _In_opt_ PLARGE_INTEGER ByteOffset,
    _In_opt_ PULONG Key
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
//@[comment("MVI_tracked")]
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtWriteFile(
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_reads_bytes_(Length) PVOID Buffer,
    _In_ ULONG Length,
    _In_opt_ PLARGE_INTEGER ByteOffset,
    _In_opt_ PULONG Key
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
//@[comment("MVI_tracked")]
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryInformationFile(
    _In_ HANDLE FileHandle,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _Out_writes_bytes_(Length) PVOID FileInformation,
    _In_ ULONG Length,
    _In_ FILE_INFORMATION_CLASS FileInformationClass
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
//@[comment("MVI_tracked")]
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetInformationFile(
    _In_ HANDLE FileHandle,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_reads_bytes_(Length) PVOID FileInformation,
    _In_ ULONG Length,
    _In_ FILE_INFORMATION_CLASS FileInformationClass
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
//@[comment("MVI_tracked")]
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtDeviceIoControlFile(
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG IoControlCode,
    _In_reads_bytes_opt_(InputBufferLength) PVOID InputBuffer,
    _In_ ULONG InputBufferLength,
    _Out_writes_bytes_opt_(OutputBufferLength) PVOID OutputBuffer,
    _In_ ULONG OutputBufferLength
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
//@[comment("MVI_tracked")]
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtFsControlFile(
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG FsControlCode,
    _In_reads_bytes_opt_(InputBufferLength) PVOID InputBuffer,
    _In_ ULONG InputBufferLength,
    _Out_writes_bytes_opt_(OutputBufferLength) PVOID OutputBuffer,
    _In_ ULONG OutputBufferLength
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
//@[comment("MVI_tracked")]
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenFile(
    _Out_ PHANDLE FileHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG ShareAccess,
    _In_ ULONG OpenOptions
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryDirectoryFile(
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _Out_writes_bytes_(Length) PVOID FileInformation,
    _In_ ULONG Length,
    _In_ FILE_INFORMATION_CLASS FileInformationClass,
    _In_ BOOLEAN ReturnSingleEntry,
    _In_opt_ PUNICODE_STRING FileName,
    _In_ BOOLEAN RestartScan
);
#endif

#pragma endregion File

#pragma region Section

#if (NTDDI_VERSION >= NTDDI_WINXP)
//@[comment("MVI_tracked")]
_Must_inspect_result_
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateSection(
    _Out_ PHANDLE SectionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ PLARGE_INTEGER MaximumSize,
    _In_ ULONG SectionPageProtection,
    _In_ ULONG AllocationAttributes,
    _In_opt_ HANDLE FileHandle
);
#endif // NTDDI_VERSION >= NTDDI_WINXP

#pragma endregion Section

#pragma region Token

#if (NTDDI_VERSION >= NTDDI_WIN2K)
//@[comment("MVI_tracked")]
_Must_inspect_result_
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenProcessToken(
    _In_ HANDLE ProcessHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _Out_ PHANDLE TokenHandle
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
_When_(TokenInformationClass == TokenAccessInformation,
       _At_(TokenInformationLength,
            _In_range_(>= , sizeof(TOKEN_ACCESS_INFORMATION))))
    _Must_inspect_result_
    __kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryInformationToken(
    _In_ HANDLE TokenHandle,
    _In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
    _Out_writes_bytes_to_opt_(TokenInformationLength, *ReturnLength) PVOID TokenInformation,
    _In_ ULONG TokenInformationLength,
    _Out_ PULONG ReturnLength
);
#endif

#if (NTDDI_VERSION >= NTDDI_WINXP)
//@[comment("MVI_tracked")]
_Must_inspect_result_
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetInformationToken(
    _In_ HANDLE TokenHandle,
    _In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
    _In_reads_bytes_(TokenInformationLength) PVOID TokenInformation,
    _In_ ULONG TokenInformationLength
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
//@[comment("MVI_tracked")]
_Must_inspect_result_
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtAdjustPrivilegesToken(
    _In_ HANDLE TokenHandle,
    _In_ BOOLEAN DisableAllPrivileges,
    _In_opt_ PTOKEN_PRIVILEGES NewState,
    _In_ ULONG BufferLength,
    _Out_writes_bytes_to_opt_(BufferLength, *ReturnLength) PTOKEN_PRIVILEGES PreviousState,
    _Out_ _When_(PreviousState == NULL, _Out_opt_) PULONG ReturnLength
);
#endif

#if (NTDDI_VERSION >= NTDDI_WINXP)
_Must_inspect_result_
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtDuplicateToken(
    _In_ HANDLE ExistingTokenHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ BOOLEAN EffectiveOnly,
    _In_ TOKEN_TYPE TokenType,
    _Out_ PHANDLE NewTokenHandle
);
#endif

#pragma endregion Token

#pragma region Uncategorized

#if (NTDDI_VERSION >= NTDDI_WIN2K)
//@[comment("MVI_tracked")]
_IRQL_requires_max_(PASSIVE_LEVEL)
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtClose(
    _In_ _Post_ptr_invalid_ HANDLE Handle
);
#endif // NTDDI_VERSION >= NTDDI_WIN2K

#pragma endregion Uncategorized

#pragma endregion Nt*
