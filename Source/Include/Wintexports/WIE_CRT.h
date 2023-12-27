#pragma once

#include "NtMinDef.h"

#define _NO_CRT_STDIO_INLINE

#if !defined(_VCRT_BUILD)
#pragma comment(linker, "/DEFAULTLIB:WIE_CRT.lib")
#endif

#if defined(_MT) && defined(__cplusplus)
#if !defined(_DEBUG) && !defined(_DLL)
#pragma comment(linker, "/NODEFAULTLIB:libcpmt.lib")
#elif !defined(_DEBUG) && defined(_DLL)
#pragma comment(linker, "/NODEFAULTLIB:msvcprt.lib")
#elif defined(_DEBUG) && !defined(_DLL)
#pragma comment(linker, "/NODEFAULTLIB:libcpmtd.lib")
#elif defined(_DEBUG) && defined(_DLL)
#pragma comment(linker, "/NODEFAULTLIB:msvcprtd.lib")
#endif
#endif

EXTERN_C
BOOL
WINAPI
DllMain(
    _In_ HANDLE _HDllHandle,
    _In_ DWORD _Reason,
    _In_opt_ LPVOID _Reserved);

EXTERN_C
int
__CRTDECL
wmain(
    _In_                     int       argc,
    _In_reads_(argc) _Pre_z_ wchar_t** argv,
    _Reserved_               wchar_t** envp); // CAUTION: Never use envp

EXTERN_C
int
WINAPI
wWinMain(
    _In_     HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_     LPWSTR    lpCmdLine,
    _In_     int       nShowCmd);

EXTERN_C NTSTATUS NTAPI ExeMain();

NTSTATUS WIE_CRT_Startup_Init();
