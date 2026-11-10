# Task 11 – Recommend and Defend the Final Design

## Recommendation
- Store 16-bit meter readings in an unsigned type whose range is checked (`unsigned short` only after verifying `USHRT_MAX >= 65535`).
- Store units as `unsigned int`.
- Store all monetary values as integer paise; use `long long` for district-wide totals.
- Keep original fixed tariff constants in one header or configuration module.
- Use functions for slab calculations and validation; use fully parenthesised macros only for simple compile-time substitutions.
- Use `fgets` plus checked conversion (`strtol`/`strtoul`) for robust input validation.
- Compile with `-std=c11 -Wall -Wextra -pedantic`.

The original design scales linearly with household count: O(N) total time and O(1) working memory per household if bills are processed one at a time. District totals must be proven to fit the accumulator. A 32-bit `long` is insufficient for the sample ₹688,000,000 district total in Task 10; 64-bit `long long` is suitable for this measured scenario.

## Limitations
The original design assumes one meter rollover between readings, one tariff schedule, fixed monthly billing and a known threshold for distinguishing rollover from data-entry error. It does not model time-of-day usage, meter telemetry gaps, customer-specific tariffs or runtime tariff updates.

## Alternative: tariff configuration file
At program startup, read t tariff values from a validated configuration file. Startup parsing takes O(t) time and O(t) storage. This avoids recompiling and redistributing the program for every tariff revision, but introduces file-format validation, missing-file handling, permissions and versioning concerns. For a cooperative that revises tariffs, a validated runtime configuration is more maintainable than hard-coded macros. Keep safe defaults or fail closed if the file is invalid.
