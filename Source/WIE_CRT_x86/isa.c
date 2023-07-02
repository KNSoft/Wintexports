/*
 * ISA_AVAILABLE
 * 
 * FIXME:
 *   Regression, we cannot initialize __isa_available
 *   at startup, add a TLS callback procedure?
 * 
 */

#include <isa_availability.h>
int __isa_available = __ISA_AVAILABLE_SSE2;
