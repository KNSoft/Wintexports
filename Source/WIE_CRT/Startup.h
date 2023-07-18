#pragma once

#define WIE_CONFIG_INCLUDE_WIEEXT

#include "..\Include\Wintexports.h"

#include <vcruntime.h>

EXTERN_C INT __isa_available_init();

EXTERN_C NTSTATUS NTAPI ExeMain();

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

NTSTATUS WIE_CRT_Startup_Init();
