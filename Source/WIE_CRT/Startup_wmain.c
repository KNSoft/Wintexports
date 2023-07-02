#define WIE_CONFIG_INCLUDE_WIEEXT

#include "..\Include\Wintexports.h"

#include <shellapi.h>
#include <suppress.h>

EXTERN_C
int
__CRTDECL
wmain(
    _In_                     int       argc,
    _In_reads_(argc) _Pre_z_ wchar_t** argv,
    _Reserved_               wchar_t** envp); // CAUTION: Never use envp

VOID wmainCRTStartup()
{
    NTSTATUS Status;
    PWSTR* argv;
    INT argc;

    argv = CommandLineToArgvW(NtCurrentPeb()->ProcessParameters->CommandLine.Buffer, &argc);
    if (argv) {
        Status = wmain(argc, argv, NULL);
        LocalFree(argv);
    } else
    {
        Status = WIE_ErrorToStatus(WIE_GetLastError());
    }

    RtlExitUserProcess(Status);

    if (NtCurrentPeb()->BeingDebugged) {
        __debugbreak();
    }
    __fastfail(FAST_FAIL_FATAL_APP_EXIT);
}
