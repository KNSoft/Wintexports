#include "Startup.h"

EXTERN_C INT __isa_available_init();

NTSTATUS WIE_CRT_Startup_Init()
{
    __security_init_cookie();

#ifdef _M_IX86
    _asm { fnclex }
    __isa_available_init();
#endif
    return STATUS_SUCCESS;
}
