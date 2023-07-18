#include "Startup.h"

VOID WIEExeMainCRTStartup()
{
    NTSTATUS Status;

    Status = WIE_CRT_Startup_Init();
    if (!NT_SUCCESS(Status))
    {
        goto _exit;
    }

    Status = ExeMain();

_exit:
    RtlExitUserProcess(Status);
    __assume(0);
    __fastfail(FAST_FAIL_FATAL_APP_EXIT);
}
