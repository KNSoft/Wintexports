#pragma once

#include <Wintexports/Wintexports.h>

EXTERN_C_START

/* Tests */
BOOL Test_new_delete();
BOOL Test_Memory_Allocate();
BOOL Test_String();

/* Demos */
BOOL Demo_FindFile();
BOOL Demo_QueryStorageProperty();
BOOL Demo_SMBIOS();

EXTERN_C_END
