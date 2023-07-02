#define WIE_CONFIG_INCLUDE_WIEEXT

#include "..\Include\Wintexports.h"

EXTERN_C NTSTATUS NTAPI ExeMain();

VOID WIEExeMainCRTStartup()
{
    NTSTATUS Status;

    Status = ExeMain();

    RtlExitUserProcess(Status);

    if (NtCurrentPeb()->BeingDebugged)
    {
        __debugbreak();
    }
    __fastfail(FAST_FAIL_FATAL_APP_EXIT);
}
