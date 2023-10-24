#include "Demo.h"

#include <vcruntime_new.h>

BOOL Test_new_delete()
{
    void* pv;
    char* pc;

    /* Test new(std::nothrow)[] and delete[] */
    pv = new(std::nothrow) char[100];
    if (pv)
    {
        delete[] pv;
    } else
    {
        DbgPrint("new(std::nothrow) char[] failed with 0x%08lX\n", WIE_GetLastStatus());
        return FALSE;
    }

    /* Test new()[] and delete[] */
    pv = new char[100];
    if (pv)
    {
        delete[] pv;
    } else
    {
        DbgPrint("new char[] failed with 0x%08lX\n", WIE_GetLastStatus());
        return FALSE;
    }

    /* Test new() and delete */
    pc = new char;
    if (pc)
    {
        delete pc;
    } else
    {
        DbgPrint("new char failed with 0x%08lX\n", WIE_GetLastStatus());
        return FALSE;
    }

    return TRUE;
}
