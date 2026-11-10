# Task 5 – Header Files and Conditional Compilation

`billing.h` contains tariff macros and the function prototype. `billing.c` contains the implementation. `main.c` contains `main()` and calls the billing function. Include guards prevent a header from being processed more than once in a translation unit. `#include <...>` searches system include paths; `#include "..."` searches the local/project path first.

Compile normally:
```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c billing.c -o billing
```
Compile with debug messages:
```bash
gcc -std=c11 -Wall -Wextra -pedantic -DDEBUG main.c billing.c -o billing_debug
```

Alternative: `if (debug) printf(...)` keeps the debug code in the executable and checks a runtime flag when reached. `#ifdef DEBUG` removes debug statements at preprocessing time when DEBUG is absent. Runtime variable approach incurs a branch/test; preprocessor approach has no runtime test in non-debug builds. Debug code compiled out takes no executable code space; runtime-controlled code remains in the executable.
