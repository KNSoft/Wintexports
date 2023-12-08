#pragma once

#ifndef _WINTEXPORTS_
#define _WINTEXPORTS_

#include "NtMinDef.h"

/* Windows.h */

#define WIN32_LEAN_AND_MEAN
#define NOSERVICE
#define NOMCX
#define NOIME

#define OEMRESOURCE

#include <Windows.h>
#include "WIE_WinUser.h"
#include "winsta.h"
#include <ntstatus.h>

/* NT support */

#include "NtTypes.h"
#include "NtMacro.h"

/* APIs */

#include "API_Ntdll.h"
#include "API_Kernel32.h"
#include "API_User32.h"
#include "API_WinSta.h"

#if !defined(WIE_NO_HASH)
#include "API_Ntdll_Hash.h"
#endif

/* Additional headers */

#include <intrin.h>
#include <suppress.h>

/* Extension */

#if !defined(WIE_NO_EXT)
#include "WIE_Ext.h"
#endif

#endif /* _WINTEXPORTS_ */
