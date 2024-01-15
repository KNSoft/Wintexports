#pragma once

#include "NtMinDef.h"

#include "NtTypes.h"

#pragma region TEB/PEB

#if defined(_M_X64)

#define WIE_ReadTEB(m) (\
    RTL_FIELD_SIZE(TEB, m) == sizeof(ULONGLONG) ? __readgsqword(UFIELD_OFFSET(TEB, m)) : (\
        RTL_FIELD_SIZE(TEB, m) == sizeof(ULONG) ? __readgsdword(UFIELD_OFFSET(TEB, m)) : (\
            RTL_FIELD_SIZE(TEB, m) == sizeof(USHORT) ? __readgsword(UFIELD_OFFSET(TEB, m)) :\
                __readgsbyte(UFIELD_OFFSET(TEB, m))\
        )\
    )\
)

#define WIE_WriteTEB(m, val) (\
    RTL_FIELD_SIZE(TEB, m) == sizeof(ULONGLONG) ? __writegsqword(UFIELD_OFFSET(TEB, m), (ULONGLONG)(val)) : (\
        RTL_FIELD_SIZE(TEB, m) == sizeof(ULONG) ? __writegsdword(UFIELD_OFFSET(TEB, m), (ULONG)(val)) : (\
            RTL_FIELD_SIZE(TEB, m) == sizeof(USHORT) ? __writegsword(UFIELD_OFFSET(TEB, m), (USHORT)(val)) :\
                __writegsbyte(UFIELD_OFFSET(TEB, m), (UCHAR)(val))\
        )\
    )\
)

#elif defined(_M_IX86)

#define WIE_ReadTEB(m) (\
    RTL_FIELD_SIZE(TEB, m) == sizeof(ULONG) ? __readfsdword(UFIELD_OFFSET(TEB, m)) : (\
        RTL_FIELD_SIZE(TEB, m) == sizeof(USHORT) ? __readfsword(UFIELD_OFFSET(TEB, m)) :\
            __readfsbyte(UFIELD_OFFSET(TEB, m))\
    )\
)

#define WIE_WriteTEB(m, val) (\
    RTL_FIELD_SIZE(TEB, m) == sizeof(ULONG) ? __writefsdword(UFIELD_OFFSET(TEB, m), (ULONG)(val)) : (\
        RTL_FIELD_SIZE(TEB, m) == sizeof(USHORT) ? __writefsword(UFIELD_OFFSET(TEB, m), (USHORT)(val)) :\
            __writefsbyte(UFIELD_OFFSET(TEB, m), (UCHAR)(val))\
    )\
)

#else

#define WIE_ReadTEB(m) (NtCurrentTeb()->m)
#define WIE_WriteTEB(m, val) (NtCurrentTeb()->m = (val))

#endif

#define NtCurrentPeb() ((PPEB)WIE_ReadTEB(ProcessEnvironmentBlock))

#pragma endregion TEB/PEB

#pragma region Error codes

/* Gets or sets the last error */

#define WIE_GetLastError() ((ULONG)WIE_ReadTEB(LastErrorValue))
#define WIE_SetLastError(Error) WIE_WriteTEB(LastErrorValue, Error)

/* Gets or sets the last status */

#define WIE_GetLastStatus() ((NTSTATUS)(WIE_ReadTEB(LastStatusValue)))
#define WIE_SetLastStatus(Status) WIE_WriteTEB(LastStatusValue, Status)

/* Error code conversion (NOT translation) Win32 Error/NtStatus/HResult */

#define WIE_ErrorToResult HRESULT_FROM_WIN32
#define WIE_ErrorToStatus NTSTATUS_FROM_WIN32
#define WIE_StatusToResult HRESULT_FROM_NT

#pragma endregion Error codes

#pragma region Current runtime information

#define CURRENT_PROCESS_ID ((HANDLE)WIE_ReadTEB(ClientId.UniqueProcess))
#define CURRENT_THREAD_ID ((HANDLE)WIE_ReadTEB(ClientId.UniqueThread))
#define CURRENT_DIRECTORY_HANDLE (NtCurrentPeb()->ProcessParameters->CurrentDirectory.Handle)
#define CURRENT_IMAGE_BASE (NtCurrentPeb()->ImageBaseAddress)
#define CURRENT_NTDLL_BASE (CONTAINING_RECORD(NtCurrentPeb()->Ldr->InInitializationOrderModuleList.Flink, LDR_DATA_TABLE_ENTRY, InInitializationOrderModuleList)->DllBase)
#define CURRENT_PROCESS_HEAP (NtCurrentPeb()->ProcessHeap)

#pragma endregion Current runtime information

#pragma region Context

#if defined(_M_IX86)
#define CONTEXT_PC Eip
#elif defined(_M_X64)
#define CONTEXT_PC Rip
#elif defined(_M_ARM64)
#define CONTEXT_PC Pc
#endif

#pragma endregion Context
