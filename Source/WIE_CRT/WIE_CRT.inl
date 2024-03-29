﻿#pragma once

#define _VCRT_BUILD
#define _CORECRT_BUILD

#include <Wintexports/WIE_CRT.h>

#pragma region Entry points defined in vcstartup_internal.h

EXTERN_C BOOL WINAPI DllMain(
    _In_ HINSTANCE  hInstance,
    _In_ DWORD      fdwReason,
    _In_opt_ LPVOID lpvReserved /* Can be NULL */
);

EXTERN_C int __CRTDECL main(
    _In_                     int    argc,
    _In_reads_(argc) _Pre_z_ char** argv,
    _Reserved_               char** envp /* Caution: Not support */
);

EXTERN_C int __CRTDECL wmain(
    _In_                     int       argc,
    _In_reads_(argc) _Pre_z_ wchar_t** argv,
    _Reserved_               wchar_t** envp /* Caution: Not support */
);

#pragma endregion
