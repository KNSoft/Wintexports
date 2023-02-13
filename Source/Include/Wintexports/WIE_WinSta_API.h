#pragma once

#include "WIE_Windows.h"
#include "WIE_WinSta.h"

EXTERN_C_START

NTSYSAPI
BOOL
NTAPI
WinStationEnumerateW(
    HANDLE ServerHandle,
    PSESSIONID *SessionIds,
    PULONG Count);

NTSYSAPI
BOOL
NTAPI
WinStationFreeMemory(
    PVOID Buffer);

NTSYSAPI
BOOLEAN
NTAPI
WinStationQueryInformationW(
  _In_opt_  HANDLE hServer,
  _In_      ULONG LogonId,
  _In_      WINSTATIONINFOCLASS WinStationInformationClass,
  _Out_     PVOID pWinStationInformation,
  _In_      ULONG WinStationInformationLength,
  _Out_     PULONG pReturnLength);

EXTERN_C_END
