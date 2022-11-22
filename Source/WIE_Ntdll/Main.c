typedef unsigned short wchar_t;
typedef int errno_t;
#ifdef _WIN64
typedef unsigned __int64 size_t;
#else
typedef unsigned int     size_t;
#endif
typedef char* va_list;
#define NULL ((void *)0);
typedef size_t rsize_t;
#define EINVAL 22

/* String */

__declspec(dllexport) size_t __cdecl wcslen(wchar_t const* _String)
{
    return 0;
}

__declspec(dllexport) size_t __cdecl strlen(char const* _Str)
{
    return 0;
}

__declspec(dllexport) int __cdecl wcscmp(wchar_t const* _String1, wchar_t const* _String2)
{
    return 0;
}

__declspec(dllexport) int __cdecl strcmp(char const* _Str1, char const* _Str2)
{
    return 0;
}

__declspec(dllexport) wchar_t* __cdecl wcsstr(wchar_t* _String, wchar_t const*_SubStr)
{
    return NULL;
}

__declspec(dllexport) char* __cdecl strstr(char* const _String, char const* const _SubString)
{
    return NULL;
}

__declspec(dllexport) int __cdecl vswprintf_s(wchar_t* const _Buffer, const _BufferCount, wchar_t const* const _Format, va_list _ArgList)
{
    return -1;
}

__declspec(dllexport) int __cdecl vsprintf_s(char *const _Buffer, const size_t _BufferCount, const char *const _Format, va_list _ArgList)
{
    return -1;
}

/* Memory */

__declspec(dllexport) void* __cdecl memset(void* _Dst, int _Val, size_t _Size)
{
    return NULL;
}

__declspec(dllexport) void* __cdecl memcpy(void* _Dst, void const* _Src, size_t _Size)
{
    return NULL;
}

__declspec(dllexport) errno_t __cdecl memcpy_s(void* const _Destination, rsize_t const _DestinationSize, void const* const _Source, rsize_t const _SourceSize)
{
    return EINVAL;
}

__declspec(dllexport) void* __cdecl memmove(void* _Dst, void const* _Src, size_t _Size)
{
    return NULL;
}

__declspec(dllexport) errno_t __cdecl memmove_s(void* const _Destination, rsize_t const _DestinationSize, void const* const _Source, rsize_t const _SourceSize)
{
    return EINVAL;
}

__declspec(dllexport) void __cdecl memchr(void const* _Buf, int _Val, size_t _MaxCount)
{}

__declspec(dllexport) int __cdecl memcmp(void const* _Buf1, void const* _Buf2, size_t _Size)
{
    return 0;
}

/* Arithmetic */

#if defined(_M_IX86)

#pragma comment(linker, "/export:__alldiv=__alldiv@16")
__int64 __stdcall _alldiv(__int64 a1, __int64 a2)
{
    return 0;
}

#pragma comment(linker, "/export:__alldvrm=__alldvrm@16")
__int64 __stdcall _alldvrm(__int64 a1, __int64 a2)
{
    return 0;
}

#pragma comment(linker, "/export:__allrem=__allrem@16")
__int64 __stdcall _allrem(__int64 a1, __int64 a2)
{
    return 0;
}

#pragma comment(linker, "/export:__aulldiv=__aulldiv@16")
unsigned __int64 __stdcall _aulldiv(unsigned __int64 a1, unsigned __int64 a2)
{
    return 0;
}

#pragma comment(linker, "/export:__aulldvrm=__aulldvrm@16")
unsigned __int64 __stdcall _aulldvrm(unsigned __int64 a1, unsigned __int64 a2)
{
    return 0;
}

#pragma comment(linker, "/export:__aullrem=__aullrem@16")
unsigned __int64 __stdcall _aullrem(unsigned __int64 a1, unsigned __int64 a2)
{
    return 0;
}

#endif /* defined(_M_IX86) */
