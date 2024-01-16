#include <Wintexports/Wintexports.h>

#pragma comment(lib, "WIE_WinAPI.lib")

#pragma comment(lib, "ntdll.lib")

#include "Demo/Demo.h"

int wmain(int argc, wchar_t** argv)
{
    BOOL bRet = TRUE;

    /* Run tests */
    bRet &= Test_new_delete();
    bRet &= Test_Memory_Allocate();
    bRet &= Test_String();

    /* Run demos */
    bRet &= Demo_FindFile();
    bRet &= Demo_QueryStorageProperty();
    bRet &= Demo_FirmwareTable();
    
    return bRet ? 0 : 1;
}
