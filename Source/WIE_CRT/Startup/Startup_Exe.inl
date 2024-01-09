#include "../CRTBuild.inl"

static void WIE_Common_Main()
{
    NTSTATUS Status;

    Status = WIE_CRT_Startup_Init();
    if (!NT_SUCCESS(Status))
    {
        goto _exit;
    }

#if defined(_WIE_CRT_STARTUP_EXEMAIN)

    Status = ExeMain();
#elif defined(_WIE_CRT_STARTUP_WMAIN)

#include <shellapi.h>

    PWSTR* argv;
    INT argc;

    argv = CommandLineToArgvW(NtCurrentPeb()->ProcessParameters->CommandLine.Buffer, &argc);
    if (argv)
    {
        Status = wmain(argc, argv, NULL);
        LocalFree(argv);
    } else
    {
        Status = WIE_ErrorToStatus(WIE_GetLastError());
    }
#elif defined(_WIE_CRT_STARTUP_WWINMAIN)

    PRTL_USER_PROCESS_PARAMETERS ProcessParameters;

    ProcessParameters = NtCurrentPeb()->ProcessParameters;
    Status = wWinMain((HINSTANCE)(&__ImageBase),
                      NULL,
                      ProcessParameters->CommandLine.Buffer,
                      ProcessParameters->ShowWindowFlags);
#endif

_exit:
    RtlExitUserProcess(Status);
    __assume(0);
    __fastfail(FAST_FAIL_FATAL_APP_EXIT);
}
