#define WIE_CONFIG_INCLUDE_WIEEXT

#include "..\Include\Wintexports.h"

EXTERN_C
int
WINAPI
wWinMain(
    _In_     HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_     LPWSTR    lpCmdLine,
    _In_     int       nShowCmd);

VOID wWinMainCRTStartup()
{
    NTSTATUS Status;
    PRTL_USER_PROCESS_PARAMETERS ProcessParameters;

    ProcessParameters = NtCurrentPeb()->ProcessParameters;

    Status = wWinMain(CURRENT_IMAGE_BASE,
                      NULL,
                      ProcessParameters->CommandLine.Buffer,
                      ProcessParameters->ShowWindowFlags);

    RtlExitUserProcess(Status);
    __assume(0);
    __fastfail(FAST_FAIL_FATAL_APP_EXIT);
}
