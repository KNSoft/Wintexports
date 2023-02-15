﻿#pragma once

#ifdef _WINDOWS_

/* Conflicts in Windows.h */

#undef LANGIDFROMLCID
#undef MAKELANGID
#undef MAKELCID
#undef MAKESORTLCID
#undef MAX_NATURAL_ALIGNMENT
#undef PRIMARYLANGID
#undef SUBLANGID
#undef PROBE_ALIGNMENT
#undef PROBE_ALIGNMENT32
#undef SORTIDFROMLCID
#undef SORTVERSIONFROMLCID
#undef UNICODE_STRING_MAX_BYTES

#define _LIST_ENTRY _MS_LIST_ENTRY
#define LIST_ENTRY MS_LIST_ENTRY
#define PLIST_ENTRY PMS_LIST_ENTRY
#define PRLIST_ENTRY PRMS_LIST_ENTRY
#define LIST_ENTRY32 MS_LIST_ENTRY32
#define PLIST_ENTRY32 PMS_LIST_ENTRY32
#define LIST_ENTRY64 MS_LIST_ENTRY64
#define PLIST_ENTRY64 PMS_LIST_ENTRY64
#define _SINGLE_LIST_ENTRY _MS_SINGLE_LIST_ENTRY
#define SINGLE_LIST_ENTRY MS_SINGLE_LIST_ENTRY
#define PSINGLE_LIST_ENTRY PMS_SINGLE_LIST_ENTRY
#define _LARGE_INTEGER _MS_LARGE_INTEGER
#define LARGE_INTEGER MS_LARGE_INTEGER
#define PLARGE_INTEGER PMS_LARGE_INTEGER
#define _ULARGE_INTEGER _MS_ULARGE_INTEGER
#define ULARGE_INTEGER MS_ULARGE_INTEGER
#define PULARGE_INTEGER PMS_ULARGE_INTEGER
#define _LUID _MS_LUID
#define LUID MS_LUID
#define PLUID PMS_LUID
#define _FLOAT128 _MS_FLOAT128
#define FLOAT128 MS_FLOAT128
#define PFLOAT128 PMS_FLOAT128
#define _PROCESSOR_NUMBER _MS_PROCESSOR_NUMBER
#define PROCESSOR_NUMBER MS_PROCESSOR_NUMBER
#define PPROCESSOR_NUMBER PMS_PROCESSOR_NUMBER
#define _GROUP_AFFINITY _MS_GROUP_AFFINITY
#define GROUP_AFFINITY MS_GROUP_AFFINITY
#define PGROUP_AFFINITY PMS_GROUP_AFFINITY

#if defined(_M_IX86)
#define Int64ShllMod32 MS_Int64ShllMod32
#define Int64ShraMod32 MS_Int64ShraMod32
#define Int64ShrlMod32 MS_Int64ShrlMod32
#endif

#define _ENUM_FLAG_SIZED_INTEGER _MS_ENUM_FLAG_SIZED_INTEGER
#define _ENUM_FLAG_INTEGER_FOR_SIZE _MS_ENUM_FLAG_INTEGER_FOR_SIZE

#endif /* _WINDOWS_ */

#include <ntdef.h>

#ifdef _WINDOWS_

#undef _ENUM_FLAG_SIZED_INTEGER
#undef _ENUM_FLAG_INTEGER_FOR_SIZE

#undef Int64ShllMod32
#undef Int64ShraMod32
#undef Int64ShrlMod32

#undef _LIST_ENTRY
#undef LIST_ENTRY
#undef PLIST_ENTRY
#undef PRLIST_ENTRY
#undef LIST_ENTRY32
#undef PLIST_ENTRY32
#undef LIST_ENTRY64
#undef PLIST_ENTRY64
#undef _SINGLE_LIST_ENTRY
#undef SINGLE_LIST_ENTRY
#undef PSINGLE_LIST_ENTRY

#undef _LARGE_INTEGER
#undef LARGE_INTEGER
#undef PLARGE_INTEGER
#undef _ULARGE_INTEGER
#undef ULARGE_INTEGER
#undef PULARGE_INTEGER
#undef _LUID
#undef LUID
#undef PLUID
#undef _FLOAT128
#undef FLOAT128
#undef PFLOAT128
#undef _PROCESSOR_NUMBER
#undef PROCESSOR_NUMBER
#undef PPROCESSOR_NUMBER
#undef _GROUP_AFFINITY
#undef GROUP_AFFINITY
#undef PGROUP_AFFINITY

#endif /* _WINDOWS_ */
