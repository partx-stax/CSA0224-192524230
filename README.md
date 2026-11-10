# CSA0224-192524230 — C Programming CO1 Assignment 1

**Student:** Parthiban M  
**Register number:** 192524230  
**Course:** C Programming (CO1)

This repository is intended for the 12-task electricity-billing assignment.

## Submission structure

Create one folder per task:

- `Task01/` — Problem analysis
- `Task02/` — Data types, ranges and meter rollover
- `Task03/` — Tariff constants and slab calculation
- `Task04/` — Safe macros and inline functions
- `Task05/` — Header files, include guards and DEBUG build
- `Task06/` — Formatted input/output and validation
- `Task07/` — Type conversions and floating-point precision
- `Task08/` — Compilation stages
- `Task09/` — Complete validated billing program
- `Task10/` — Precision and large-total experiment
- `Task11/` — Design recommendation
- `Task12/` — Smart-meter redesign challenge

Each task folder should contain its source files or analysis, plus an `Output/` folder with genuine screenshots of local execution.

## Build

For a single C source file:

```sh
gcc -std=c11 -Wall -Wextra -pedantic Task02/task02.c -o task02
./task02
```

For Windows PowerShell, run `./task02.exe` after compiling. Task05 has multiple source files; Task09 and Task12 use supporting input/configuration files. Follow the compile/run notes in each task folder.

## Evidence and academic integrity

Run and verify every program on your own computer. Add screenshots showing the actual command, input and output. Record your own compiler version using `gcc --version`; do not copy machine-specific measurements or screenshots from another environment.

## Progressive commits

Make a separate commit as each task is completed and tested. Suggested messages:

```text
Complete Task 01 problem analysis
Complete Task 02 data types and rollover
...
Complete Task 12 smart meter redesign
```

The consolidated report should include problem analysis, data types/constants, code and output, UML/flowcharts, pseudocode, test tables, complexity analysis, experiments and final design recommendations.
