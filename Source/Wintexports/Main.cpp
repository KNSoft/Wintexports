#include <Wintexports/Wintexports.h>

#pragma comment(lib, "WIE_WinAPI.lib")

#pragma comment(lib, "ntdll.lib")

#include "Demo/Demo.h"

int WINAPI wWinMain(
    _In_     HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_     LPWSTR    lpCmdLine,
    _In_     int       nShowCmd)
{
    BOOL bRet = TRUE;

    /* Run tests */
    bRet &= Test_new_delete();
    bRet &= Test_Memory_Allocate();
    bRet &= Test_String();

    /* Run demos */
    bRet &= Demo_FindFile();
    bRet &= Demo_QueryStorageProperty();

    return bRet ? 0 : 1;
}
