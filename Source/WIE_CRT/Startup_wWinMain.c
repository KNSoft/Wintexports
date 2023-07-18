#include "Startup.h"

VOID wWinMainCRTStartup()
{
    NTSTATUS Status;
    PRTL_USER_PROCESS_PARAMETERS ProcessParameters;

    Status = WIE_CRT_Startup_Init();
    if (!NT_SUCCESS(Status))
    {
        goto _exit;
    }

    ProcessParameters = NtCurrentPeb()->ProcessParameters;
    Status = wWinMain(CURRENT_IMAGE_BASE,
                      NULL,
                      ProcessParameters->CommandLine.Buffer,
                      ProcessParameters->ShowWindowFlags);

_exit:
    RtlExitUserProcess(Status);
    __assume(0);
    __fastfail(FAST_FAIL_FATAL_APP_EXIT);
}
