#include "../WIE_CRT.inl"

int __stdcall _DllMainCRTStartup(
    _In_     void*         DllHandle,
    _In_     unsigned long Reason,
    _In_opt_ void*         Reserved)
{
    if (Reason == DLL_PROCESS_ATTACH)
    {
        if (!NT_SUCCESS(WIE_CRT_Startup_Init()))
        {
            return FALSE;
        }
    }
    return DllMain((HMODULE)DllHandle, Reason, Reserved);
}
