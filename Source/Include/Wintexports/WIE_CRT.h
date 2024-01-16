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

VOID Startup_InitCmdlineW(); // Initialize _wcmdln
VOID Startup_InitCmdlineA(); // Initialize _acmdln

VOID Startup_InitCmdlineArgW(); // Initialize __argc and __wargv
VOID Startup_InitCmdlineArgA(); // Initialize __argc and __argv

VOID Startup_FreeCmdlineA();
VOID Startup_FreeCmdlineArgW();
VOID Startup_FreeCmdlineArgA();

EXTERN_C INT __argc;
EXTERN_C CHAR** __argv;
EXTERN_C WCHAR** __wargv;
EXTERN_C CHAR* _acmdln;
EXTERN_C WCHAR* _wcmdln;

EXTERN_C_END
