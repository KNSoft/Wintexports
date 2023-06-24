#pragma once

#include "MS_wdm.h"

typedef struct _THREAD_BASIC_INFORMATION {
    NTSTATUS ExitStatus;
    struct PTEB* TebBaseAddress;
    CLIENT_ID ClientId;
    KAFFINITY AffinityMask;
    KPRIORITY Priority;
    KPRIORITY BasePriority;
} THREAD_BASIC_INFORMATION, *PTHREAD_BASIC_INFORMATION;
