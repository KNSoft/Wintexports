#pragma once

#include "WIE_Windows.h"

typedef struct _A_SHA_CTX {
    UCHAR Buffer[64];
    ULONG State[5];
    ULONG Count[2];
} A_SHA_CTX, *PA_SHA_CTX;

#define A_SHA_DIGEST_LEN 20

typedef struct _MD5_CTX {
    ULONG Count[2];
    ULONG State[4];
    UCHAR Buffer[64];
    UCHAR Hash[16];
} MD5_CTX, *PMD5_CTX;

#define MD5_DIGEST_LEN 16

typedef struct _MD4_CTX {
    ULONG State[4];
    ULONG Count[2];
    UCHAR Buffer[64];
    UCHAR Hash[16];
} MD4_CTX, *PMD4_CTX;

#define MD4_DIGEST_LEN 16

