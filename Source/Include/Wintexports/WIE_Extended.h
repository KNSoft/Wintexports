#pragma once

#ifndef _WIE_WINDOWS_
#include "WIE_Windows.h"
#endif

#pragma region WinSDK

#define DECLSPEC_EXPORT __declspec(dllexport)
#define EXPORT_STD_FUNC #pragma comment(linker, "/EXPORT:"__FUNCTION__"="__FUNCDNAME__)

#if _WIN64
#define IS_WIN64 TRUE
#else
#define IS_WIN64 FALSE
#endif

#pragma endregion WinSDK

#pragma region VS Macros

#if defined(_M_IX86)
#define VS_PLATFORMTARGET "x86"
#elif defined(_M_X64)
#define VS_PLATFORMTARGET "x64"
#endif

#if defined(_DEBUG)
#define VS_CONFIGURATION "Debug"
#else
#define VS_CONFIGURATION "Release"
#endif

#define LIB_PATH_WITH_CONFIG(LibName) VS_PLATFORMTARGET"\\"VS_CONFIGURATION"\\"LibName

#pragma endregion VS Macros

#pragma region Pseudo Handles

#define CURRENT_PROCESS_HANDLE                  NtCurrentProcess()
#define CURRENT_THREAD_HANDLE                   NtCurrentThread()
#define CURRENT_SESSION_HANDLE                  NtCurrentSession()
#define CURRENT_PROCESS_TOKEN_HANDLE            GetCurrentProcessToken()
#define CURRENT_THREAD_TOKEN_HANDLE             GetCurrentThreadToken()
#define CURRENT_THREAD_EFFECTIVETOKEN_HANDLE    GetCurrentThreadEffectiveToken()

#pragma endregion Pseudo Handles

#pragma region TEB/PEB

#if defined(_M_X64)
#define WIE_ReadTEB(m) (\
    RTL_FIELD_SIZE(TEB, m) == sizeof(DWORD64) ? __readgsqword(FIELD_OFFSET(TEB, m) : (\
        RTL_FIELD_SIZE(TEB, m) == sizeof(DWORD) ? __readgsdword(FIELD_OFFSET(TEB, m)) : (\
            RTL_FIELD_SIZE(TEB, m) == sizeof(WORD) ? __readgsword(FIELD_OFFSET(TEB, m)) : \
                __readgsbyte(FIELD_OFFSET(TEB, m))\
        )\
    )\
)
#define WIE_WriteTEB(m, val) (\
    RTL_FIELD_SIZE(TEB, m) == sizeof(DWORD64) ? __writegsqword(FIELD_OFFSET(TEB, m), (DWORD64)(val)) : (\
        RTL_FIELD_SIZE(TEB, m) == sizeof(DWORD) ? __writegsdword(FIELD_OFFSET(TEB, m), (DWORD)(val)) : (\
            RTL_FIELD_SIZE(TEB, m) == sizeof(WORD) ? __writegsword(FIELD_OFFSET(TEB, m), (WORD)(val)) : \
                __writegsbyte(FIELD_OFFSET(TEB, m), (BYTE)(val))\
        )\
    )\
)
#elif defined(_M_IX86)
#define WIE_ReadTEB(m) (\
    RTL_FIELD_SIZE(TEB, m) == sizeof(DWORD) ? __readfsdword(FIELD_OFFSET(TEB, m)) : (\
        RTL_FIELD_SIZE(TEB, m) == sizeof(WORD) ? __readfsword(FIELD_OFFSET(TEB, m)) : \
            __readfsbyte(FIELD_OFFSET(TEB, m))\
    )\
)
#define WIE_WriteTEB(m, val) (\
    RTL_FIELD_SIZE(TEB, m) == sizeof(DWORD) ? __writefsdword(FIELD_OFFSET(TEB, m), (DWORD)(val)) : (\
        RTL_FIELD_SIZE(TEB, m) == sizeof(WORD) ? __writefsword(FIELD_OFFSET(TEB, m), (WORD)(val)) : \
            __writefsbyte(FIELD_OFFSET(TEB, m), (BYTE)(val))\
    )\
)
#endif

#define NtCurrentPeb() ((PPEB)WIE_ReadTEB(ProcessEnvironmentBlock))

#pragma endregion TEB/PEB

#pragma region Current runtime information

#define CURRENT_PROCESS_ID (WIE_ReadTEB(ClientId.UniqueProcess))
#define CURRENT_THREAD_ID (WIE_ReadTEB(ClientId.UniqueThread))
#define CURRENT_DIRECTORY_HANDLE (NtCurrentPeb()->ProcessParameters->CurrentDirectory.Handle)
#define CURRENT_IMAGE_BASE (NtCurrentPeb()->ImageBaseAddress)
#define CURRENT_NTDLL_BASE (CONTAINING_RECORD(NtCurrentPeb()->Ldr->InInitializationOrderModuleList.Flink, LDR_DATA_TABLE_ENTRY, InInitializationOrderModuleList)->DllBase)

#pragma endregion Current runtime information

#pragma region String

#define ASCII_CASE_MASK 0b100000

#pragma endregion String

#pragma region Funtion

// WIE_LINKDEFAULTLIB: link default libs
#if defined(WIE_LINKDEFAULTLIB)
#if _DEBUG
#if _DLL
#pragma comment(lib, "msvcrtd.lib")
#pragma comment(lib, "vcruntimed.lib")
#pragma comment(lib, "ucrtd.lib")
#ifdef __cplusplus
#pragma comment(lib, "msvcprtd.lib")
#endif
#else
#pragma comment(lib, "libcmtd.lib")
#pragma comment(lib, "libvcruntimed.lib")
#pragma comment(lib, "libucrtd.lib")
#ifdef __cplusplus
#pragma comment(lib, "libcpmtd.lib")
#endif
#endif
#else
#if _DLL
#pragma comment(lib, "msvcrt.lib")
#pragma comment(lib, "vcruntime.lib")
#pragma comment(lib, "ucrt.lib")
#ifdef __cplusplus
#pragma comment(lib, "msvcprt.lib")
#endif
#else
#pragma comment(lib, "libcmt.lib")
#pragma comment(lib, "libvcruntime.lib")
#pragma comment(lib, "libucrt.lib")
#ifdef __cplusplus
#pragma comment(lib, "libcpmt.lib")
#endif
#endif
#endif
#endif

#pragma endregion Funtion
