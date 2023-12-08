/* Include this file before and after winnt.h */

#ifdef _WINNT_

#undef WIN32_NO_STATUS

#undef PSID
typedef SID* PSID;

#else

#define WIN32_NO_STATUS

#define PSID MS_PSID

#endif
