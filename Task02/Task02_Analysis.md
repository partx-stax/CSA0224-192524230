# Task 2 – Choose the Data Types

## Data-type decisions
| Data | Type | Reason |
|---|---|---|
| Meter register | `unsigned short` typedef `meter_t` | Assignment's 16-bit register; verify `USHRT_MAX` and `sizeof` on the target system. C guarantees at least 16 bits for `unsigned short`, not exactly 16 on every platform. |
| Household count / units | `unsigned int` | Non-negative values; units fit easily. |
| Single bill in paise | `long` | Exact integer arithmetic; check `LONG_MAX` on the actual system. |
| District aggregate | `long long` | Larger guaranteed minimum range than `long`; still verify the maximum possible total. |
| Rates/config decimals | integer paise or `double` for non-money measurements | Avoid `float` for money. |
| Category code | `enum` | Named finite choices. |

Run the program to obtain the actual `sizeof` and limits. Include `<limits.h>` and `<float.h>`; never assume a particular size from another computer. C standard minimum ranges include `INT_MAX >= 32767`, `LONG_MAX >= 2147483647`, and `LLONG_MAX >= 9223372036854775807`.

## Money representation
₹2.25 is stored as 225 paise. ₹50 is stored as 5000 paise. Addition and multiplication of integer paise are exact as long as the integer type does not overflow. `float` and `double` use binary floating-point and cannot represent every decimal fraction exactly.

## Rollover TODO explanation
The expression is converted to unsigned arithmetic and narrowed to `unsigned short`. For 65400 → 120, the mathematical difference is -65280; modulo 65536 it is 256. It is therefore 256, not a negative number. This code assumes one 16-bit rollover between readings.

## Float experiment
Use Task10's program to sum the same set of bills in `float` rupees and integer paise for 4,000, 60,000 and 800,000 households. Record actual output on your compiler. The exact integer-pa​​ise total is the reference; floating-point output may differ due to representation and accumulation order. Do not invent an observed discrepancy: include your measured result.

## Alternative: `double` rupees
Store each bill as a `double`, add in `double`, and round to paise only at the required billing boundary using `llround(rupees * 100.0)`. Addition remains O(1) time in either representation. Integer paise typically occupies `sizeof(long)` or `sizeof(long long)` bytes; `double` typically occupies `sizeof(double)` bytes. Floating-point accumulated error can grow with the number and order of additions; integer paise avoids representation error but can overflow if the range is insufficient.
