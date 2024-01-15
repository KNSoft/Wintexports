#pragma once

#include "NtMinDef.h"

#define _NO_CRT_STDIO_INLINE

#if !defined(_VCRT_BUILD) && defined(_VC_NODEFAULTLIB)
#pragma comment(linker, "/DEFAULTLIB:WIE_CRT.lib")
#endif

#if defined(_VC_NODEFAULTLIB) && defined(__cplusplus) && defined(_MT)
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

EXTERN_C NTSTATUS NTAPI ExeMain();

EXTERN_C_START

NTSTATUS WIE_CRT_Startup_Init();

EXTERN_C_END
