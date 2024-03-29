﻿#include <Wintexports/NtMinDef.h>

extern "C" void __cdecl _RTC_InitBase()
{
}

extern "C" void __cdecl _RTC_Shutdown()
{
}

void _RTC_StackFailure(void* p, const char* psz)
{
    __fastfail(FAST_FAIL_FATAL_APP_EXIT);
}

void _RTC_AllocaFailure(void* p, struct _RTC_ALLOCA_NODE* pst, int i)
{
    __fastfail(FAST_FAIL_FATAL_APP_EXIT);
}

void _RTC_Failure(void* p, int i)
{
    __fastfail(FAST_FAIL_FATAL_APP_EXIT);
}
