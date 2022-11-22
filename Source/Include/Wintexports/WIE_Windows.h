#pragma once

#include "WIE_winnt.h"

/* Exclude less common API */
#define WIN32_LEAN_AND_MEAN
#define NOSERVICE
#define NOMCX
#define NOIME

/* Use ntstatus.h instead */
#define WIN32_NO_STATUS
#include <Windows.h>
#undef WIN32_NO_STATUS
#include <ntstatus.h>

#include "WIE_winnt.h"
