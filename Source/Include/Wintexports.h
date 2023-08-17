#pragma once

#ifndef _WINTEXPORTS_
#define _WINTEXPORTS_

/* Include Windows.h */

#include "WIE_Windows.h"
#include "WIE_WinUser.h"

/* Inculde KM headers */

#include "MS_wdm.h"
#include "MS_ntddk.h"
#include "MS_ntifs.h"
#include "MS_fltKernel.h"

/* Include internals */

#include "MS_winternl.h"
#include "WIE_Internal.h"

/* Include UM dlls */

#include "Undoc_API_Ntdll.h"
#include "Undoc_API_Kernel32.h"
#include "Undoc_API_User32.h"

/* Include useful headers */

#include <intrin.h>
#include <suppress.h>

/* Include Ntdll hash API optionally */

#if !defined(WIE_NO_HASH)
#include "Undoc_API_Ntdll_Hash.h"
#endif

/* Include Wintexports extended features optionally */

#if !defined(WIE_NO_WIEEXT)
#include "WIE_Ext.h"
#include "WIE_Ext_CPU.h"
#endif

#endif /* _WINTEXPORTS_ */
