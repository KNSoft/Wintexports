# Wintexports
Wintexports (Windows INTernal EXPORTS) brings Windows NT low-level definitions (i.e. NT*/Zw*, Rtl*, PEB, TEB, ...) to user-mode, and also supplement a few CRT functions to allow user-mode program depends ntdll.dll only.

## Install and usage
Install Wintexports nuget package or add Wintexports headers (required) and libs (optional).

```C
#include <Wintexports/Wintexports.h>
```

Includes the header instead of `Windows.h`, then you can access all the low-level definitions provided by Wintexports.

Requires Visual Studio 2019 and above, with corresponding SDK

Project Wintexports in solution is a demo.

## Caution
In alpha stage, do not use on production environment.
