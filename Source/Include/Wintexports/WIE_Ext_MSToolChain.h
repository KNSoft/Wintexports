﻿#pragma once

#include "NtMinDef.h"

#pragma region MSVC

EXTERN_C_START

extern IMAGE_DOS_HEADER __ImageBase;

EXTERN_C_END

#if _WIN64
#define IS_WIN64 TRUE
#else
#define IS_WIN64 FALSE
#endif

/* Patch _STATIC_ASSERT to avoid confusion amount static_assert, _Static_assert and C_ASSERT */

#undef _STATIC_ASSERT
#define _STATIC_ASSERT(expr) static_assert((expr), #expr)

#define _A2U8(quote) __A2U8(quote)
#define __A2U8(quote) u8##quote

#define _A2W(quote) __A2W(quote)
#define __A2W(quote) L##quote

#pragma endregion MSVC

#pragma region VS

#if defined(_M_IX86)
#define VS_PLATFORMTARGET "x86"
#elif defined(_M_X64)
#define VS_PLATFORMTARGET "x64"
#elif defined(_M_ARM64)
#define VS_PLATFORMTARGET "ARM64"
#endif

#if defined(_DEBUG)
#define VS_CONFIGURATION "Debug"
#define VS_IS_DEBUG TRUE
#else
#define VS_CONFIGURATION "Release"
#define VS_IS_DEBUG FALSE
#endif

#define VS_LIB_PATH(LibName) VS_PLATFORMTARGET"\\"VS_CONFIGURATION"\\"LibName

#pragma endregion VS

#pragma region WinSDK

#define DECLSPEC_EXPORT __declspec(dllexport)
typedef unsigned __int64 QWORD, near *PQWORD, far *LPQWORD;

// Makes a DWORD value by LOWORD and HIWORD
#define MAKEDWORD(l, h) ((DWORD)MAKELONG(l, h))
#define MAKEQWORD(l, h) ((QWORD)(((DWORD)(((DWORD_PTR)(l)) & 0xffffffff)) | ((QWORD)((DWORD)(((DWORD_PTR)(h)) & 0xffffffff))) << 32))

#pragma endregion WinSDK
