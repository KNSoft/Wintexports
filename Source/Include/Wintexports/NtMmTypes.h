#pragma once

#include "NtMinDef.h"

#define PAGE_SIZE 0x1000
#define MM_ALLOCATION_GRANULARITY 0x10000
#define MM_SHARED_USER_DATA_VA 0x7FFE0000

#if defined(_WIN64)
#define MI_HIGHEST_USER_ADDRESS (PVOID)0x000007FFFFFEFFFFULL
#else
#define MI_HIGHEST_USER_ADDRESS (PVOID)0x7FFEFFFFUL
#endif
#define MM_LOWEST_USER_ADDRESS (PVOID)0x10000

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
