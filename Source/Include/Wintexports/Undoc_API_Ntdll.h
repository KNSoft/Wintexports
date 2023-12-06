#pragma once

#include "WIE_ntdef.h"
#include "MS_ntifs.h"
#include "MS_wdm.h"
#include "MS_ntddk.h"

EXTERN_C_START

#pragma region Csr*

NTSYSAPI
HANDLE
NTAPI
CsrGetProcessId();

#pragma endregion Csr*

#pragma region Ldr*

NTSTATUS
NTAPI
LdrLockLoaderLock(
    _In_ ULONG Flags,
    _Out_opt_ PULONG Disposition,
    _Out_opt_ PULONG_PTR Cookie);

NTSTATUS
NTAPI
LdrUnlockLoaderLock(
    _In_ ULONG Flags,
    _In_opt_ ULONG Cookie);

NTSTATUS
NTAPI
LdrDisableThreadCalloutsForDll(
    _In_ PVOID BaseAddress);

NTSTATUS
NTAPI
LdrFindEntryForAddress(
    _In_ PVOID Address,
    _Out_ PLDR_DATA_TABLE_ENTRY* Module);

typedef VOID(NTAPI LDR_ENUM_CALLBACK)(_In_ PLDR_DATA_TABLE_ENTRY ModuleInformation, _In_opt_ PVOID Context, _Out_ BOOLEAN* Stop);
typedef LDR_ENUM_CALLBACK *PLDR_ENUM_CALLBACK;

NTSTATUS
NTAPI
LdrEnumerateLoadedModules(
    _Reserved_ ULONG ReservedFlag,
    _In_ PLDR_ENUM_CALLBACK EnumProc,
    _In_opt_ PVOID Context);

NTSTATUS
NTAPI
LdrGetDllHandle(
    _In_opt_ PWSTR DllPath,
    _In_opt_ PULONG DllCharacteristics,
    _In_ PUNICODE_STRING DllName,
    _Out_ PVOID* DllHandle);

NTSYSAPI
NTSTATUS
NTAPI
LdrLoadDll(
    _In_opt_ PWSTR DllSearchPath,
    _In_opt_ PULONG DllCharacteristics,
    _In_ PUNICODE_STRING DllName,
    _Out_ PVOID* BaseAddress);

NTSYSAPI
NTSTATUS
NTAPI
LdrUnloadDll(
    _In_ PVOID* BaseAddress);

NTSYSAPI
NTSTATUS
NTAPI
LdrGetProcedureAddress(
    _In_ PVOID BaseAddress,
    _In_opt_ _When_(Ordinal == 0, _Notnull_) PANSI_STRING Name,
    _In_opt_ _When_(Name == NULL, _In_range_(> , 0)) ULONG Ordinal,
    _Out_ PVOID* ProcedureAddress);

#pragma endregion Ldr*

#pragma region Rtl*

#pragma region Process and Thread

NTSYSAPI
NTSTATUS
NTAPI
RtlCreateUserThread(
    _In_ HANDLE hProcess,
    _In_opt_ PSECURITY_DESCRIPTOR ThreadSecurityDescriptor,
    _In_ BOOLEAN CreateSuspended,
    _In_opt_ ULONG ZeroBits,
    _In_opt_ SIZE_T MaximumStackSize,
    _In_opt_ SIZE_T CommittedStackSize,
    _In_ LPTHREAD_START_ROUTINE StartAddress,
    _In_opt_ PVOID Parameter,
    _Out_opt_ PHANDLE hThread,
    _Out_opt_ PCLIENT_ID ClientId);

NTSYSAPI
VOID
NTAPI
RtlExitUserThread(
    _In_ NTSTATUS ExitStatus);

typedef ULONG
(NTAPI *RTLP_UNHANDLED_EXCEPTION_FILTER)(
    _In_ PEXCEPTION_POINTERS ExceptionInfo
);
typedef RTLP_UNHANDLED_EXCEPTION_FILTER *PRTLP_UNHANDLED_EXCEPTION_FILTER;

NTSYSAPI
VOID
NTAPI
RtlSetUnhandledExceptionFilter(
    _In_opt_ PRTLP_UNHANDLED_EXCEPTION_FILTER TopLevelExceptionFilter);

NTSYSAPI
VOID
DECLSPEC_NORETURN
NTAPI
RtlExitUserProcess(
    _In_ NTSTATUS ExitStatus);

#pragma endregion Process and Thread

#pragma region Critical Section

NTSYSAPI
VOID
NTAPI
RtlInitializeCriticalSection(
    _Out_ LPCRITICAL_SECTION lpCriticalSection);

NTSYSAPI
VOID
NTAPI
RtlEnterCriticalSection(
    _Inout_ LPCRITICAL_SECTION lpCriticalSection);

NTSYSAPI
VOID
NTAPI
RtlLeaveCriticalSection(
    _Inout_ LPCRITICAL_SECTION lpCriticalSection);

NTSYSAPI
VOID
NTAPI
RtlDeleteCriticalSection(
    _Inout_ LPCRITICAL_SECTION lpCriticalSection);

#pragma endregion Critical Section

#pragma region SRW Lock

NTSYSAPI
VOID
NTAPI
RtlInitializeSRWLock(
    _Out_ PRTL_SRWLOCK SRWLock);

NTSYSAPI
VOID
NTAPI
RtlAcquireSRWLockExclusive(
    _Inout_ PRTL_SRWLOCK SRWLock);

NTSYSAPI
VOID
NTAPI
RtlAcquireSRWLockShared(
    _Inout_ PRTL_SRWLOCK SRWLock);

NTSYSAPI
VOID
NTAPI
RtlReleaseSRWLockExclusive(
    _Inout_ PRTL_SRWLOCK SRWLock);

NTSYSAPI
VOID
NTAPI
RtlReleaseSRWLockShared(
    _Inout_ PRTL_SRWLOCK SRWLock);

NTSYSAPI
BOOLEAN
NTAPI
RtlTryAcquireSRWLockExclusive(
    _Inout_ PRTL_SRWLOCK SRWLock);

NTSYSAPI
BOOLEAN
NTAPI
RtlTryAcquireSRWLockShared(
    _Inout_ PRTL_SRWLOCK SRWLock);

#pragma endregion SRW Lock

#pragma region Path

NTSYSAPI
BOOLEAN
NTAPI
RtlDosPathNameToNtPathName_U(
    _In_opt_z_ LPCWSTR              DosName,
    _Out_ PUNICODE_STRING           NtName,
    _Out_opt_ LPCWSTR*              PartName,
    _Out_opt_ PRTL_RELATIVE_NAME_U  RelativeName);

NTSYSAPI
NTSTATUS
NTAPI
RtlDosPathNameToNtPathName_U_WithStatus(
    _In_opt_z_ LPCWSTR 	            DosName,
    _Out_ PUNICODE_STRING 	        NtName,
    _Out_opt_ LPCWSTR* 	            PartName,
    _Out_opt_ PRTL_RELATIVE_NAME_U  RelativeName);

NTSYSAPI
VOID
NTAPI
RtlReleaseRelativeName(
    _In_ PRTL_RELATIVE_NAME_U RelativeName);

NTSYSAPI
NTSTATUS
NTAPI
RtlSetCurrentDirectory_U(
    _In_ PUNICODE_STRING name);

NTSYSAPI
NTSTATUS
NTAPI
RtlSetEnvironmentVariable(
    _In_z_ PWSTR *Environment,
    _In_ PUNICODE_STRING Name,
    _In_ PUNICODE_STRING Value);

#pragma endregion

#pragma region Bitmap

NTSYSAPI
VOID
NTAPI
RtlInitializeBitMap(
    _Out_ PRTL_BITMAP BitMapHeader,
    _In_opt_ __drv_aliasesMem PULONG BitMapBuffer,
    _In_opt_ ULONG SizeOfBitMap);

#pragma endregion Bitmap

#pragma region Uncategorized

NTSYSAPI
NTSTATUS
NTAPI
RtlFindMessage(
    _In_ PVOID                      BaseAddress,
    _In_ ULONG                      Type,
    _In_ ULONG                      Language,
    _In_ ULONG                      MessageId,
    _Out_ PMESSAGE_RESOURCE_ENTRY*  MessageResourceEntry);

NTSYSAPI
NTSTATUS
NTAPI
RtlWow64EnableFsRedirectionEx(
    _In_ PVOID Wow64FsEnableRedirection,
    _Out_ PVOID* OldFsRedirectionLevel);

NTSYSAPI
NTSTATUS
NTAPI
RtlGetUserPreferredUILanguages(
    _In_ ULONG Flags,
    _In_opt_ PCWSTR LocaleName,
    _Out_ PULONG NumLanguages,
    _Out_writes_opt_z_(*LanguagesCchSize) PWSTR LanguagesBuffer,
    _Inout_ PULONG LanguagesCchSize);

NTSYSAPI
VOID
NTAPI
RtlRaiseStatus(
    _In_ NTSTATUS Status);

NTSYSAPI
_Must_inspect_result_
_Ret_maybenull_
_Post_writable_byte_size_(Size)
PVOID
NTAPI
RtlReAllocateHeap(
    _In_ PVOID HeapHandle,
    _In_opt_ ULONG Flags,
    _Frees_ptr_opt_ PVOID BaseAddress,
    _In_ SIZE_T Size);

NTSYSAPI
SIZE_T
NTAPI
RtlSizeHeap(
    _In_ PVOID HeapHandle,
    _In_opt_ ULONG Flags,
    _In_ PVOID BaseAddress);

#pragma endregion Uncategorized

#pragma endregion Rtl*

#pragma region Nt*

#pragma region Virtual Memory

NTSYSAPI
NTSTATUS
NTAPI
NtProtectVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _Inout_ _At_(*BaseAddress, _Readable_bytes_(*RegionSize) _Writable_bytes_(*RegionSize) _Post_readable_byte_size_(*RegionSize)) PVOID* BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG Protect,
    _Out_ PULONG OldProtect);

NTSYSAPI
NTSTATUS
NTAPI
NtReadVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _In_ PVOID BaseAddress,
    _Out_ PVOID Buffer,
    _In_ SIZE_T NumberOfBytesToRead,
    _Out_opt_ PSIZE_T NumberOfBytesRead);

NTSYSAPI
NTSTATUS
NTAPI
NtWriteVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _In_ PVOID BaseAddress,
    _In_ PVOID Buffer,
    _In_ SIZE_T NumberOfBytesToWrite,
    _Out_opt_ PSIZE_T NumberOfBytesWritten);

#pragma endregion Virtual Memory

#pragma region Process and Thread

NTSYSAPI
NTSTATUS
NTAPI
NtOpenThread(
    _Out_ PHANDLE            ThreadHandle,
    _In_  ACCESS_MASK        DesiredAccess,
    _In_  POBJECT_ATTRIBUTES ObjectAttributes,
    _In_  PCLIENT_ID         ClientId);

NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenProcess(
    _Out_ PHANDLE ProcessHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ PCLIENT_ID ClientId);

NTSYSAPI
NTSTATUS
NTAPI
NtSuspendThread(
    _In_ HANDLE ThreadHandle,
    _Out_opt_ PULONG SuspendCount);

NTSYSAPI
NTSTATUS
NTAPI
NtResumeThread(
    _In_ HANDLE ThreadHandle,
    _Out_opt_ PULONG SuspendCount);

NTSYSAPI
NTSTATUS
NTAPI
NtQueryInformationThread(
    _In_ HANDLE ThreadHandle,
    _In_ THREADINFOCLASS ThreadInformationClass,
    _Out_writes_bytes_to_(ThreadInformationLength, *ReturnLength) PVOID ThreadInformation,
    _In_ ULONG ThreadInformationLength,
    _Out_opt_ PULONG ReturnLength);

NTSYSAPI
NTSTATUS
NTAPI
NtQueryInformationProcess(
    _In_ HANDLE ProcessHandle,
    _In_ PROCESSINFOCLASS ProcessInformationClass,
    _Out_writes_bytes_to_(ProcessInformationLength, *ReturnLength) PVOID ProcessInformation,
    _In_ ULONG ProcessInformationLength,
    _Out_opt_ PULONG ReturnLength);

NTSYSAPI
NTSTATUS
NTAPI
NtFlushInstructionCache(
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress,
    _In_ SIZE_T FlushSize);

NTSYSAPI
NTSTATUS
NTAPI
NtGetContextThread(
    _In_ HANDLE ThreadHandle,
    _Inout_ PCONTEXT ThreadContext);

NTSYSAPI
NTSTATUS
NTAPI
NtSetContextThread(
    _In_ HANDLE ThreadHandle,
    _In_ PCONTEXT ThreadContext);

NTSYSAPI
NTSTATUS
NTAPI
NtTerminateProcess(
    _In_opt_ HANDLE ProcessHandle,
    _In_ NTSTATUS ExitStatus);

#pragma endregion Process and Thread

#pragma region File

NTSYSAPI
NTSTATUS
NTAPI
NtQueryAttributesFile(
    _In_ POBJECT_ATTRIBUTES      ObjectAttributes,
    _Out_ PFILE_BASIC_INFORMATION FileInformation);

NTSYSAPI
NTSTATUS
NTAPI
NtQueryFullAttributesFile(
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Out_ PFILE_NETWORK_OPEN_INFORMATION FileInformation);

#pragma endregion File

#pragma region Section

_Must_inspect_result_
_Post_satisfies_(*ViewSize >= _Old_(*ViewSize))
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
NtMapViewOfSection(
    _In_ HANDLE SectionHandle,
    _In_ HANDLE ProcessHandle,
    _Outptr_result_bytebuffer_(*ViewSize) PVOID *BaseAddress,
    _In_ ULONG_PTR ZeroBits,
    _In_ SIZE_T CommitSize,
    _Inout_opt_ PLARGE_INTEGER SectionOffset,
    _Inout_ PSIZE_T ViewSize,
    _In_ SECTION_INHERIT InheritDisposition,
    _In_ ULONG AllocationType,
    _In_ ULONG Win32Protect);

NTSYSAPI
NTSTATUS
NTAPI
NtUnmapViewOfSection(
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress);

#pragma endregion Section

#pragma region Token

NTSYSAPI
NTSTATUS
NTAPI
NtCreateToken(
    _Out_ PHANDLE TokenHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ TOKEN_TYPE TokenType,
    _In_ PLUID AuthenticationId,
    _In_ PLARGE_INTEGER ExpirationTime,
    _In_ PTOKEN_USER TokenUser,
    _In_ PTOKEN_GROUPS TokenGroups,
    _In_ PTOKEN_PRIVILEGES TokenPrivileges,
    _In_opt_ PTOKEN_OWNER TokenOwner,
    _In_ PTOKEN_PRIMARY_GROUP TokenPrimaryGroup,
    _In_opt_ PTOKEN_DEFAULT_DACL TokenDefaultDacl,
    _In_ PTOKEN_SOURCE TokenSource);

#pragma endregion Token

#pragma region Registry

NTSYSAPI
NTSTATUS
NTAPI
NtOpenKey(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes);

NTSYSAPI
NTSTATUS
NTAPI
NtCreateKey(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Reserved_ ULONG TitleIndex,
    _In_opt_ PUNICODE_STRING Class,
    _In_ ULONG CreateOptions,
    _Out_opt_ PULONG Disposition);

_When_(Length == 0, _Post_satisfies_(return < 0))
_When_(Length > 0, _Post_satisfies_(return <= 0))
_Success_(return == STATUS_SUCCESS)
_On_failure_(_When_(return == STATUS_BUFFER_OVERFLOW || return == STATUS_BUFFER_TOO_SMALL, _Post_satisfies_(*ResultLength > Length)))
NTSYSAPI
NTSTATUS
NTAPI
NtQueryValueKey(
    _In_ HANDLE KeyHandle,
    _In_ PUNICODE_STRING ValueName,
    _In_ KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
    _Out_writes_bytes_to_(Length, *ResultLength) PVOID KeyValueInformation,
    _In_ ULONG Length,
    _Out_ PULONG ResultLength);

NTSYSAPI
NTSTATUS
NTAPI
NtSetValueKey(
    _In_ HANDLE KeyHandle,
    _In_ PUNICODE_STRING ValueName,
    _In_opt_ ULONG TitleIndex,
    _In_ ULONG Type,
    _In_reads_bytes_(DataSize) PVOID Data,
    _In_ ULONG DataSize);

NTSYSAPI
NTSTATUS
NTAPI
NtDeleteKey(
    _In_ HANDLE KeyHandle);

#pragma endregion Registry

#pragma region Driver

NTSYSAPI
NTSTATUS
NTAPI
NtLoadDriver(
    _In_ PUNICODE_STRING DriverServiceName);

NTSYSAPI
NTSTATUS
NTAPI
NtUnloadDriver(
    _In_ PUNICODE_STRING DriverServiceName);

#pragma endregion Driver

#pragma region Event

NTSYSAPI
NTSTATUS
NTAPI
NtCreateEvent(
   _Out_ PHANDLE EventHandle,
   _In_ ACCESS_MASK DesiredAccess,
   _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
   _In_ EVENT_TYPE EventType,
   _In_ BOOLEAN InitialState);

NTSYSAPI
NTSTATUS
NTAPI
NtSetEvent(
    _In_ HANDLE EventHandle,
    _Out_opt_ PLONG PreviousState);

#pragma endregion Event

#pragma region Wow64

/* Caution: Exported from Wow Ntdll.dll only!!! */

_Must_inspect_result_
__drv_allocatesMem(Mem)
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtWow64AllocateVirtualMemory64(
    _In_ HANDLE ProcessHandle,
    _Inout_ _At_(*BaseAddress, _Readable_bytes_(*RegionSize) _Writable_bytes_(*RegionSize) _Post_readable_byte_size_(*RegionSize)) PULONGLONG BaseAddress,
    _In_ ULONGLONG ZeroBits,
    _Inout_ PULONGLONG RegionSize,
    _In_ ULONG AllocationType,
    _In_ ULONG Protect);

NTSYSAPI
NTSTATUS
NTAPI
NtWow64QueryInformationProcess64(
    _In_ HANDLE ProcessHandle,
    _In_ PROCESSINFOCLASS ProcessInformationClass,
    _Out_writes_bytes_to_(ProcessInformationLength, *ReturnLength) PVOID ProcessInformation,
    _In_ ULONG ProcessInformationLength,
    _Out_opt_ PULONG ReturnLength);

NTSYSAPI
NTSTATUS
NTAPI
NtWow64ReadVirtualMemory64(
    _In_ HANDLE ProcessHandle,
    _In_ ULONGLONG BaseAddress,
    _Out_ PVOID Buffer,
    _In_ ULONGLONG NumberOfBytesToRead,
    _Out_opt_ PULONGLONG NumberOfBytesRead);

NTSYSAPI
NTSTATUS
NTAPI
NtWow64WriteVirtualMemory64(
    _In_ HANDLE ProcessHandle,
    _In_ ULONGLONG BaseAddress,
    _In_ PVOID Buffer,
    _In_ ULONGLONG NumberOfBytesToWrite,
    _Out_opt_ ULONGLONG NumberOfBytesWritten);

#pragma endregion Wow64

NTSYSAPI
NTSTATUS
NTAPI
NtQuerySystemInformation(
    _In_ SYSTEM_INFORMATION_CLASS SystemInformationClass,
    _Out_writes_bytes_to_(SystemInformationLength, *ReturnLength) PVOID SystemInformation,
    _In_ ULONG SystemInformationLength,
    _Out_opt_ PULONG ReturnLength);

NTSYSAPI
NTSTATUS
NTAPI
NtQueryPerformanceCounter(
    _Out_ PLARGE_INTEGER PerformanceCounter,
    _Out_opt_ PLARGE_INTEGER PerformanceFrequency);

NTSYSAPI
NTSTATUS
NTAPI
NtQueryInformationAtom(
    _In_ RTL_ATOM Atom,
    _In_ ATOM_INFORMATION_CLASS AtomInformationClass,
    _Out_writes_bytes_to_(AtomInformationLength, *ReturnLength) PVOID AtomInformation,
    _In_ ULONG AtomInformationLength,
    _Out_opt_ PULONG ReturnLength);

NTSYSAPI
NTSTATUS
NTAPI
NtDelayExecution(
    _In_ BOOLEAN Alertable,
    _In_ PLARGE_INTEGER DelayInterval);

NTSYSAPI
NTSTATUS
NTAPI
NtWaitForSingleObject(
    _In_ HANDLE Handle,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout);

#pragma endregion Nt*

EXTERN_C_END
