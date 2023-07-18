#include "Startup.h"

#include <shellapi.h>
#include <suppress.h>

VOID wmainCRTStartup()
{
    NTSTATUS Status;
    PWSTR* argv;
    INT argc;

    Status = WIE_CRT_Startup_Init();
    if (!NT_SUCCESS(Status))
    {
        goto _exit;
    }

    argv = CommandLineToArgvW(NtCurrentPeb()->ProcessParameters->CommandLine.Buffer, &argc);
    if (argv)
    {
        Status = wmain(argc, argv, NULL);
        LocalFree(argv);
    } else
    {
        Status = WIE_ErrorToStatus(WIE_GetLastError());
    }

_exit:
    RtlExitUserProcess(Status);
    __assume(0);
    __fastfail(FAST_FAIL_FATAL_APP_EXIT);
}
