#include "..\Include\Wintexports.h"

BOOL
WINAPI
DllMain(
    _In_ HANDLE _HDllHandle,
    _In_ DWORD _Reason,
    _In_opt_ LPVOID _Reserved);

int __stdcall _DllMainCRTStartup(
    _In_     void*         DllHandle,
    _In_     unsigned long Reason,
    _In_opt_ void*         Reserved)
{
    return DllMain((HMODULE)DllHandle, Reason, Reserved);
}
