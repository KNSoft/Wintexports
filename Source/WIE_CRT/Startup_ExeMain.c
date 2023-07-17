#define WIE_CONFIG_INCLUDE_WIEEXT

#include "..\Include\Wintexports.h"

EXTERN_C NTSTATUS NTAPI ExeMain();

VOID WIEExeMainCRTStartup()
{
    NTSTATUS Status;

    Status = ExeMain();

    RtlExitUserProcess(Status);
    __assume(0);
    __fastfail(FAST_FAIL_FATAL_APP_EXIT);
}
