#pragma once

#include "WIE_winnt.h"

/* Exclude less common API */
#define WIN32_LEAN_AND_MEAN
#define NOSERVICE
#define NOMCX
#define NOIME

/* Default configurations */
#define WIN32_NO_STATUS
#define OEMRESOURCE

#include <Windows.h>

/* Use ntstatus.h instead */
#undef WIN32_NO_STATUS
#include <ntstatus.h>

#include "WIE_winnt.h"
