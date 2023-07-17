#pragma once

#ifndef _WINTEXPORTS_
#define _WINTEXPORTS_

/* Include Windows.h */

#include "WIE_Windows.h"

/* Inculde KM headers */

#include "MS_wdm.h"
#include "MS_ntddk.h"
#include "Undoc_ntddk.h"
#include "MS_ntifs.h"
#include "Undoc_ntifs.h"
#include "MS_fltKernel.h"

/* Include internals */

#include "MS_winternl.h"
#include "WIE_Internal.h"

/* Include UM dlls */

#include "Undoc_API_Ntdll.h"
#include "Undoc_API_Kernel32.h"

/* Include useful headers */

#include <intrin.h>
#include <suppress.h>

/* Include WinUser optionally */

#if defined(WIE_CONFIG_INCLUDE_WINUSER)
#include "WIE_CommCtrl.h"
#include "WIE_WinUser.h"
#include "Undoc_API_User32.h"
#endif

/* Include Ntdll hash API optionally */

#if defined(WIE_CONFIG_INCLUDE_HASH)
#include "Undoc_API_Ntdll_Hash.h"
#endif

/* Include Wintexports extended features optionally */

#if defined(WIE_CONFIG_INCLUDE_WIEEXT)
#include "WIE_Ext.h"
#include "WIE_Ext_CPU.h"
#endif

/* Link default libs optionally */

#if defined(WIE_CONFIG_LINK_DEFAULTLIB)

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

#endif /* defined(WIE_CONFIG_LINK_DEFAULTLIB) */
