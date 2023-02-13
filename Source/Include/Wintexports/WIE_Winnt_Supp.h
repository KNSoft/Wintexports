#pragma once

#ifdef _WINNT_

#undef PSID
typedef SID* PSID;

#else

#define PSID MS_PSID

#endif
