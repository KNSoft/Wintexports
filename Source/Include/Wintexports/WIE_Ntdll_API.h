#pragma once

#include "WIE_Windows.h"

EXTERN_C_START

#pragma region Csr*

NTSYSAPI
HANDLE
NTAPI
CsrGetProcessId();

#pragma endregion Csr*

#pragma region Ldr*

NTSYSAPI
NTSTATUS
NTAPI
LdrLoadDll(
    IN PWSTR SearchPath OPTIONAL,
    IN PULONG DllCharacteristics OPTIONAL,
    IN PUNICODE_STRING DllName,
    OUT PVOID* BaseAddress);

NTSYSAPI
NTSTATUS
NTAPI
LdrGetProcedureAddress(
    IN PVOID BaseAddress,
    IN PANSI_STRING Name,
    IN ULONG Ordinal,
    OUT PVOID* ProcedureAddress);

#pragma endregion Ldr*

#pragma region Rtl*

#pragma region Heap

NTSYSAPI
PVOID
NTAPI
RtlCreateHeap(
    ULONG                Flags,
    PVOID                HeapBase,
    SIZE_T               ReserveSize,
    SIZE_T               CommitSize,
    PVOID                Lock,
    PRTL_HEAP_PARAMETERS Parameters);

NTSYSAPI
PVOID
NTAPI
RtlAllocateHeap(
    PVOID  HeapHandle,
    ULONG  Flags,
    SIZE_T Size);

NTSYSAPI
BOOL
NTAPI
RtlFreeHeap(
    PVOID                 HeapHandle,
    ULONG                 Flags,
    _Frees_ptr_opt_ PVOID BaseAddress);

NTSYSAPI
PVOID
NTAPI
RtlDestroyHeap(
    PVOID HeapHandle);

#pragma endregion Heap

#pragma region Process and Thread

NTSYSAPI
NTSTATUS
NTAPI
RtlCreateUserThread(
    HANDLE                  hProcess,
    PSECURITY_DESCRIPTOR    ThreadSecurityDescriptor,
    BOOLEAN                 CreateSuspended,
    ULONG                   ZeroBits,
    SIZE_T                  MaximumStackSize,
    SIZE_T                  CommittedStackSize,
    LPTHREAD_START_ROUTINE  StartAddress,
    PVOID                   Parameter,
    PHANDLE                 hThread,
    PCLIENT_ID              ClientId);

NTSYSAPI
VOID
NTAPI
RtlExitUserThread(
    _In_ NTSTATUS Status);

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
    _Inout_ PRTL_SRWLOCK SRWLock
);

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

#pragma region One-Time initialization

NTSYSAPI
VOID
NTAPI
RtlRunOnceInitialize(
  _Out_ PRTL_RUN_ONCE RunOnce);

NTSYSAPI
NTSTATUS
NTAPI
RtlRunOnceExecuteOnce(
  _Inout_ PRTL_RUN_ONCE         RunOnce,
  _In_ PRTL_RUN_ONCE_INIT_FN    InitFn,
  _Inout_opt_ PVOID             Parameter,
  _Out_opt_ PVOID*              Context);

NTSYSAPI
NTSTATUS
NTAPI
RtlRunOnceBeginInitialize(
  _Inout_ PRTL_RUN_ONCE RunOnce,
  _In_ ULONG            Flags,
  _Out_opt_ PVOID*      Context);

NTSYSAPI
NTSTATUS
NTAPI
RtlRunOnceComplete(
  _Inout_ PRTL_RUN_ONCE RunOnce,
  _In_ ULONG            Flags,
  _In_opt_ PVOID        Context);

#pragma endregion One-Time initialization

#pragma region Bitmap

NTSYSAPI
VOID
NTAPI
RtlInitializeBitMap(
    _Out_ PRTL_BITMAP BitMapHeader,
    _In_opt_ __drv_aliasesMem PULONG BitMapBuffer,
    _In_opt_ ULONG SizeOfBitMap);

#pragma endregion Bitmap

#pragma region String conversion

NTSYSAPI
NTSTATUS
NTAPI
RtlMultiByteToUnicodeN(
    PWCH       UnicodeString,
    ULONG      MaxBytesInUnicodeString,
    PULONG     BytesInUnicodeString,
    const CHAR* MultiByteString,
    ULONG      BytesInMultiByteString);

NTSYSAPI
NTSTATUS
NTAPI
RtlUnicodeToMultiByteN(
    PCHAR  MultiByteString,
    ULONG  MaxBytesInMultiByteString,
    PULONG BytesInMultiByteString,
    PCWCH  UnicodeString,
    ULONG  BytesInUnicodeString);

NTSYSAPI
NTSTATUS
NTAPI
RtlUnicodeStringToInteger(
    PCUNICODE_STRING String,
    ULONG            Base,
    PULONG           Value);

NTSYSAPI
NTSTATUS
NTAPI
RtlIntegerToUnicodeString(
    ULONG           Value,
    ULONG           Base,
    PUNICODE_STRING String);

#pragma endregion String conversion

#pragma region Uncategorized

NTSYSAPI
NTSTATUS
NTAPI
RtlFindMessage(
    IN PVOID    BaseAddress,
    IN ULONG    Type,
    IN ULONG    Language,
    IN ULONG    MessageId,
    OUT PMESSAGE_RESOURCE_ENTRY* MessageResourceEntry);

NTSYSAPI
BOOL
NTAPI
RtlDosPathNameToNtPathName_U(
    IN LPCWSTR                  DosName,
    OUT PUNICODE_STRING         NtName,
    OUT LPCWSTR* PartName,
    OUT PRTL_RELATIVE_NAME_U    RelativeName);

NTSYSAPI
ULONG
NTAPI
RtlRandomEx(
    PULONG Seed);

NTSYSAPI
ULONG
NTAPI
RtlNtStatusToDosErrorNoTeb(
    IN NTSTATUS Status);

NTSYSAPI
NTSTATUS
NTAPI
RtlWow64EnableFsRedirectionEx(
    IN PVOID Wow64FsEnableRedirection,
    OUT PVOID* OldFsRedirectionLevel);

NTSYSAPI
NTSTATUS
NTAPI
RtlGetUserPreferredUILanguages(
    _In_ ULONG Flags,
    _In_opt_ PCWSTR LocaleName,
    _Out_ PULONG NumLanguages,
    _Out_writes_opt_z_(*LanguagesCchSize) PWSTR LanguagesBuffer,
    _Inout_ PULONG LanguagesCchSize);

#pragma endregion Uncategorized

#pragma endregion Rtl*

#pragma region Nt*

#pragma region Virtual Memory

NTSYSAPI
NTSTATUS
NTAPI
NtAllocateVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _Inout_ _At_(*BaseAddress, _Readable_bytes_(*RegionSize) _Writable_bytes_(*RegionSize) _Post_readable_byte_size_(*RegionSize)) PVOID* BaseAddress,
    _In_ ULONG_PTR ZeroBits,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG AllocationType,
    _In_ ULONG Protect);

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
NtFreeVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _Inout_ __drv_freesMem(Mem) PVOID* BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG FreeType);

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

NTSYSAPI
NTSTATUS
NTAPI
NtQueryVirtualMemory(
    IN HANDLE ProcessHandle,
    IN PVOID BaseAddress,
    IN MEMORY_INFORMATION_CLASS MemoryInformationClass,
    OUT PVOID MemoryInformation,
    IN SIZE_T MemoryInformationLength,
    OUT PSIZE_T ReturnLength);

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

NTSYSAPI
NTSTATUS
NTAPI
NtOpenProcess(
    PHANDLE            ProcessHandle,
    ACCESS_MASK        DesiredAccess,
    POBJECT_ATTRIBUTES ObjectAttributes,
    PCLIENT_ID         ClientId);

NTSTATUS
NTAPI
NtSuspendThread(
    _In_ HANDLE ThreadHandle,
    _Out_opt_ PULONG SuspendCount);

NTSTATUS
NTAPI
NtResumeThread(
    _In_ HANDLE ThreadHandle,
    _Out_opt_ PULONG SuspendCount);

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
    IN HANDLE ThreadHandle,
    IN OUT PCONTEXT ThreadContext);

NTSTATUS
NTAPI
NtSetContextThread(
    IN HANDLE ThreadHandle,
    IN PCONTEXT ThreadContext);

NTSYSAPI
NTSTATUS
NTAPI
NtTerminateProcess(
    HANDLE   ProcessHandle,
    NTSTATUS ExitStatus);

#pragma endregion Process and Thread

#pragma region File

NTSYSAPI
NTSTATUS
NTAPI
NtReadFile(
    HANDLE              FileHandle,
    HANDLE              Event,
    PIO_APC_ROUTINE     ApcRoutine,
    PVOID               ApcContext,
    PIO_STATUS_BLOCK    IoStatusBlock,
    PVOID               Buffer,
    ULONG               Length,
    PLARGE_INTEGER      ByteOffset,
    PULONG              Key);

NTSYSAPI
NTSTATUS
NTAPI
NtWriteFile(
    HANDLE           FileHandle,
    HANDLE           Event,
    PIO_APC_ROUTINE  ApcRoutine,
    PVOID            ApcContext,
    PIO_STATUS_BLOCK IoStatusBlock,
    PVOID            Buffer,
    ULONG            Length,
    PLARGE_INTEGER   ByteOffset,
    PULONG           Key);

NTSYSAPI
NTSTATUS
NTAPI
NtQueryInformationFile(
    IN HANDLE hFile,
    OUT PIO_STATUS_BLOCK pIoStatusBlock,
    OUT PVOID FileInformationBuffer,
    IN ULONG FileInformationBufferLength,
    IN FILE_INFORMATION_CLASS FileInfoClass);

NTSYSAPI
NTSTATUS
NTAPI
NtQueryAttributesFile(
    _In_  POBJECT_ATTRIBUTES      ObjectAttributes,
    _Out_ PFILE_BASIC_INFORMATION FileInformation);

NTSYSAPI
NTSTATUS
NTAPI
NtQueryFullAttributesFile(
    POBJECT_ATTRIBUTES             ObjectAttributes,
    PFILE_NETWORK_OPEN_INFORMATION FileInformation);

NTSYSAPI
NTSTATUS
NTAPI
NtSetInformationFile(
    HANDLE                 FileHandle,
    PIO_STATUS_BLOCK       IoStatusBlock,
    PVOID                  FileInformation,
    ULONG                  Length,
    FILE_INFORMATION_CLASS FileInformationClass);

#pragma endregion File

#pragma region Section

NTSYSAPI
NTSTATUS
NTAPI
NtCreateSection(
    PHANDLE            SectionHandle,
    ACCESS_MASK        DesiredAccess,
    POBJECT_ATTRIBUTES ObjectAttributes,
    PLARGE_INTEGER     MaximumSize,
    ULONG              SectionPageProtection,
    ULONG              AllocationAttributes,
    HANDLE             FileHandle);

NTSYSAPI
NTSTATUS
NTAPI
NtMapViewOfSection(
    HANDLE          SectionHandle,
    HANDLE          ProcessHandle,
    PVOID* BaseAddress,
    ULONG_PTR       ZeroBits,
    SIZE_T          CommitSize,
    PLARGE_INTEGER  SectionOffset,
    PSIZE_T         ViewSize,
    SECTION_INHERIT InheritDisposition,
    ULONG           AllocationType,
    ULONG           Win32Protect);

NTSYSAPI
NTSTATUS
NTAPI
NtUnmapViewOfSection(
    HANDLE ProcessHandle,
    PVOID  BaseAddress);

#pragma endregion Section

#pragma region Token

NTSYSAPI
NTSTATUS
NTAPI
NtOpenProcessToken(
    _In_ HANDLE         ProcessHandle,
    _In_ ACCESS_MASK    DesiredAccess,
    _Out_ PHANDLE       TokenHandle);

_Must_inspect_result_
__kernel_entry
NTSYSAPI
NTSTATUS
NTAPI
NtQueryInformationToken(
    _In_ HANDLE TokenHandle,
    _In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
    _Out_writes_bytes_to_opt_(TokenInformationLength, *ReturnLength) PVOID TokenInformation,
    _In_ ULONG TokenInformationLength,
    _Out_ PULONG ReturnLength);

NTSYSAPI
NTSTATUS
NTAPI
NtAdjustPrivilegesToken(
    _In_ HANDLE TokenHandle,
    _In_ BOOLEAN DisableAllPrivileges,
    _In_opt_ PTOKEN_PRIVILEGES NewState,
    _In_ ULONG BufferLength,
    _Out_writes_bytes_to_opt_(BufferLength, *ReturnLength) PTOKEN_PRIVILEGES PreviousState,
    _When_(PreviousState != NULL, _Out_) PULONG ReturnLength);

NTSYSAPI
NTSTATUS
NTAPI
NtDuplicateToken(
  _In_ HANDLE ExistingTokenHandle,
  _In_ ACCESS_MASK DesiredAccess,
  _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
  _In_ BOOLEAN EffectiveOnly,
  _In_ TOKEN_TYPE TokenType,
  _Out_ PHANDLE NewTokenHandle);

__kernel_entry
NTSYSAPI
NTSTATUS
NTAPI
NtSetInformationToken(
  _In_ HANDLE TokenHandle,
  _In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
  _In_ PVOID TokenInformation,
  _In_ ULONG TokenInformationLength);

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
    OUT PHANDLE KeyHandle,
    IN ACCESS_MASK DesiredAccess,
    IN POBJECT_ATTRIBUTES ObjectAttributes);

NTSYSAPI
NTSTATUS
NTAPI
NtCreateKey(
    OUT PHANDLE KeyHandle,
    IN ACCESS_MASK DesiredAccess,
    IN POBJECT_ATTRIBUTES ObjectAttributes,
    IN ULONG TitleIndex,
    IN PUNICODE_STRING Class OPTIONAL,
    IN ULONG CreateOptions,
    OUT PULONG Disposition OPTIONAL);

NTSYSAPI
NTSTATUS
NTAPI
NtQueryValueKey(
  _In_ HANDLE KeyHandle,
  _In_ PUNICODE_STRING ValueName,
  _In_ KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
  _Out_opt_ PVOID KeyValueInformation,
  _In_ ULONG Length,
  _Out_ PULONG ResultLength);

NTSYSAPI
NTSTATUS
NTAPI
NtSetValueKey(
    IN HANDLE KeyHandle,
    IN PUNICODE_STRING ValueName,
    IN ULONG TitleIndex,
    IN ULONG Type,
    IN PVOID Data,
    IN ULONG DataSize);

NTSYSAPI
NTSTATUS
NTAPI
NtDeleteKey(
    IN HANDLE KeyHandle);

#pragma endregion Registry

#pragma region Driver

NTSYSAPI
NTSTATUS
NTAPI
NtLoadDriver(
    IN PUNICODE_STRING DriverServiceName);

NTSYSAPI
NTSTATUS
NTAPI
NtUnloadDriver(
    IN PUNICODE_STRING DriverServiceName);

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

NTSYSAPI
NTSTATUS
NTAPI
NtQueryPerformanceCounter(
  _Out_     PLARGE_INTEGER PerformanceCounter,
  _Out_opt_ PLARGE_INTEGER PerformanceFrequency
);

NTSYSAPI
NTSTATUS
NTAPI
NtQueryInformationAtom(
    RTL_ATOM Atom,
    ATOM_INFORMATION_CLASS AtomInformationClass,
    PVOID AtomInformation,
    ULONG AtomInformationLength,
    PULONG ReturnLength
);

NTSYSAPI
NTSTATUS
NTAPI
NtDelayExecution(
    IN BOOLEAN Alertable,
    IN PLARGE_INTEGER DelayInterval
);

#pragma endregion Nt*

EXTERN_C_END
