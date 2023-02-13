#pragma once

#include <CommCtrl.h>

#pragma region Patches C26454 warning

#undef NM_FIRST
#define NM_FIRST 4294967296

#undef TCN_FIRST
#define TCN_FIRST 4294966746

#undef TVN_FIRST
#define TVN_FIRST 0xFFFFFE70

#undef LVN_FIRST
#define LVN_FIRST 0xFFFFFF9C

#pragma endregion Patches C26454 warning
