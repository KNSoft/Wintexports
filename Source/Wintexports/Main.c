#define WIE_CONFIG_INCLUDE_WINUSER
#define WIE_CONFIG_INCLUDE_HASH
#define WIE_CONFIG_INCLUDE_WIEEXT

#include "..\Include\Wintexports.h"

#pragma comment(lib, "ntdll.lib")

#pragma comment(lib, "WinAPI.lib")
#pragma comment(lib, "WIE_CRT.lib")

#define _NO_CRT_STDIO_INLINE
#include <stdio.h>

int wmain()
{
    char sz[100];
    _snprintf_s(sz, _countof(sz), _countof(sz) - 1, "xxx %p", &__ImageBase);
    return 0;
}
