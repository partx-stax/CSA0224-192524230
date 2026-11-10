# Task 8 – Trace the Compilation Process

Use Task04 or Task09 as the source file:

```bash
gcc -E Task04/task04.c -o task04.i      # preprocessing

gcc -S Task04/task04.c -o task04.s      # compile to assembly

gcc -c Task04/task04.c -o task04.o     # object file

gcc Task04/task04.c -o task04          # compile + link executable

gcc -std=c11 -Wall -Wextra -pedantic Task04/task04.c -o task04
```

- Preprocessing expands macros and includes headers; conditional compilation removes inactive branches.
- Assembly (`.s`) contains target-specific assembly instructions.
- Object (`.o`) contains machine code and unresolved external references.
- Linking combines object files and libraries into an executable.

Error categories:
- Compile-time: syntax error such as a missing semicolon.
- Link-time: calling a declared function whose definition is not linked (undefined reference).
- Run-time: invalid input or a division-by-zero path during execution.

`-Wall -Wextra -pedantic` enables useful diagnostics. Record each warning you actually receive and the code change used to resolve it; do not invent warning output.

Alternative multi-file build:
```bash
gcc -std=c11 -Wall -Wextra -pedantic -c input.c tariff.c report.c
gcc input.o tariff.o report.o -o billing
```
When one source file changes, only that file needs recompilation, then the program is relinked. In a one-file program, the entire translation unit is recompiled. Multi-file projects produce separate object files, using additional disk space, but can reduce incremental compile time as projects grow. Per-file compilation cost depends on file size; linking combines the objects.
