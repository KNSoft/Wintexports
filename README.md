# Wintexports
Wintexports (Windows INTernal EXPORTS) exposes Windows NT low-level definitions and symbols for user-mode programming, and also supplement a few CRT functions to allow program depends ntdll.dll only.

- Low-level definitions (i.e. NT*/Zw*, Rtl*, Ldr*, `PEB`, `TEB`, `KUSER_SHARED_DATA`, ...)
- Missing symbols in Lib (i.e. ntdll.dll!MD5Init, KERNEL32.dll!CreateProcessInternalW, SECHOST.dll!LsaLookupTranslateSids, ...)
- CRT functions or symbols (i.e. GS, RTC, `malloc`, `free`, ...)

## Install and usage

### General usage

1. Install [Wintexports nuget package](https://www.nuget.org/packages/KNSoft.Wintexports/) or add Wintexports headers (required) and libs (optional) to your project.

2. Include Wintexports header (`Wintexports/Wintexports.h`) instead of `Windows.h` in the source which you want to access low-level features.
    ```C
    #include <Wintexports/Wintexports.h>
    ```
3. Then you can access all the low-level features supplemented by Wintexports.
    ```C
    HANDLE CsrPid = CsrGetProcessId();
    ```

### Advanced usage: Strip Microsoft C Runtime to make program depends Ntdll only

1. Set ["Omit Default Library Name" (/Zl)](https://learn.microsoft.com/en-us/cpp/build/reference/zl-omit-default-library-name) in compiler setting, then MSVCRT will not be linked by default.

2. Link Wintexports CRT instead if [/Zl](https://learn.microsoft.com/en-us/cpp/build/reference/zl-omit-default-library-name) switch is on.
    ```C
    #if defined(_VC_NODEFAULTLIB)
    #pragma comment(lib, "WIE_CRT.lib")
    #endif
    ```

3. If Wintexports CRT (depends on Ntdll only) supplemented all missing symbols after stripping MSVCRT, the build will success and program will works well.

### Advanced usage: Get more system Dll exports

Link following libs Wintexports supplemented:
- Ntdll_Hash.lib: Hash functions in ntdll, i.e. `(A_SHA/MD5/MD4)(Init/Update/Final)`.
- WIE_WinAPI.lib: Windows SDK missing API, i.e. `KERNEL32.dll!CreateProcessInternalW`, `SECHOST.dll!LsaLookupTranslateSids`, ...

Requires Visual Studio 2019 and above with corresponding SDK, support x64/x86/ARM64 platform targets.

Project Wintexports in solution is a demo, accesses low-level system calls and functions, depends Ntdll only.

## Caution
**In alpha stage, do not use on production environment.**
