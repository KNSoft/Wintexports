#pragma once

#include "NtMinDef.h"

#define MM_SHARED_USER_DATA_VA 0x7FFE0000

typedef enum _SECTION_INHERIT
{
    ViewShare = 1,
    ViewUnmap = 2
} SECTION_INHERIT;

typedef struct _MEMORY_RANGE_ENTRY
{
    PVOID VirtualAddress;
    SIZE_T NumberOfBytes;
} MEMORY_RANGE_ENTRY, *PMEMORY_RANGE_ENTRY;

typedef enum _MEMORY_INFORMATION_CLASS
{
    MemoryBasicInformation,
    MemoryWorkingSetList,
    MemorySectionName,
    MemoryBasicVlmInformation,
    MemoryWorkingSetExList
} MEMORY_INFORMATION_CLASS, *PMEMORY_INFORMATION_CLASS;
