#define _WIE_HASH_SUPP_
#define _WIE_NTDLL_API_
#define _WIE_EXTENDED_

#include "..\Include\Wintexports\Wintexports.h"

DECLSPEC_EXPORT
VOID
RSA32API
A_SHAInit(
  _Inout_ PA_SHA_CTX Context)
{
}

DECLSPEC_EXPORT
VOID
RSA32API
A_SHAUpdate(
  _Inout_ PA_SHA_CTX Context,
  _In_reads_(BufferSize) PUCHAR Buffer,
  ULONG BufferSize)
{
}

DECLSPEC_EXPORT
VOID
RSA32API
A_SHAFinal(
  _Inout_ PA_SHA_CTX Context,
  _Out_ PUCHAR Result
)
{
}

DECLSPEC_EXPORT
VOID
RSA32API
MD5Init(
  _Inout_ PMD5_CTX Context)
{
}

DECLSPEC_EXPORT
VOID
RSA32API
MD5Update(
  _Inout_ PMD5_CTX Context,
  _In_reads_(BufferSize) PUCHAR Buffer,
  ULONG BufferSize)
{
}

DECLSPEC_EXPORT
VOID
RSA32API
MD5Final(
  _Inout_ PMD5_CTX Context)
{
}

DECLSPEC_EXPORT
VOID
RSA32API
MD4Init(
  _Inout_ PMD4_CTX Context)
{
}

DECLSPEC_EXPORT
VOID
RSA32API
MD4Update(
  _Inout_ PMD4_CTX Context,
  _In_reads_(BufferSize) PUCHAR Buffer,
  ULONG BufferSize)
{
}

DECLSPEC_EXPORT
VOID
RSA32API
MD4Final(
  _Inout_ PMD4_CTX Context)
{
}
