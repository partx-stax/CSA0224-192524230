# Task 1 – Understand the Problem and Identify the Data

## Problem statement
Grama Jyothi calculates monthly household electricity bills from a previous and current meter reading. The program must calculate consumption, apply the three-part slab tariff and add a fixed charge. It must handle a 16-bit meter register rollover and produce money accurate to the paisa.

## Inputs and outputs
| Item | Meaning | Suggested representation | Reason |
|---|---|---|---|
| Household number | Unique customer identifier | `unsigned int` or validated string | Non-negative identifier; string is preferable if leading zeroes are meaningful. |
| Previous reading | Previous register value | `meter_t` (`unsigned short`) | PDF specifies a 16-bit unsigned register. |
| Current reading | Current register value | `meter_t` | Same register representation. |
| Category | Household tariff category | `enum` or bounded string | Makes the category explicit; PDF does not provide different category rates. |
| Units consumed | Difference including rollover | `unsigned int` | Maximum modular difference is 65535. |
| Energy charge | Slab charge | `long` paise | Exact integer money arithmetic. |
| Fixed charge | Monthly fixed amount | `long` paise | Fixed tariff component. |
| Total bill | Energy plus fixed charge | `long` paise per household; `long long` for aggregate | Avoids floating-point money errors and supports large totals. |

## Constants
Slab 1 limit = 100 units; slab 2 cumulative limit = 200 units; rates = 0, 225 and 450 paise/unit; fixed charge = 5000 paise; meter maximum = 65535. These tariff values are fixed during a run in the original design and should be defined once, not repeated throughout the program.

## Values that may be negative, fractional or large
- Valid readings and consumption are non-negative. A negative bill is never valid.
- Tariff rates and bills can include fractional rupees (paise), so store money as integer paise.
- A district may contain 800,000 bills. Aggregate totals need a wider type than a single bill.
- Input text can contain invalid characters and must be validated before conversion.

## Correctness rules
1. Both readings must be in the meter's valid range.
2. Consumption must account for a legitimate register rollover.
3. Energy charge must follow the marginal slab rules: first 100 free; next 100 at 225 paise/unit; units above 200 at 450 paise/unit.
4. Total paise = energy-charge paise + fixed-charge paise.
5. Bill must be non-negative and all arithmetic must stay within the chosen type's range.
6. Reject invalid input rather than silently producing a bill.

## Assumptions
The register is 16-bit unsigned, range 0–65535. A simple modular difference handles one rollover between readings. For the full application, the program uses a configurable rollover plausibility threshold so an ordinary data-entry mistake is not automatically treated as a rollover. The PDF provides one tariff schedule only; category is stored for identification but does not change the rate. Fixed charge is ₹50 per billing period.

## Alternative: readings stored as strings
Example strings: `"01530"` and `"01860"`. The program must validate that each character is a digit, convert the string to an integer, then compare/subtract. For `d` digits, validation/conversion/comparison take O(d) time; integer subtraction takes O(1). A fixed-width integer uses O(1) space per reading, while a string uses O(d) characters plus a terminating null character. Integer storage is the better computational representation; strings are useful when preserving formatting or reading raw text input.

## Pseudocode
```text
READ household number, category, previous reading, current reading
VALIDATE all input fields
IF current >= previous:
    units = current - previous
ELSE IF rollover is plausible:
    units = (65536 - previous) + current
ELSE:
    REPORT invalid reading sequence
energy = slab_charge_in_paise(units)
total = energy + fixed_charge
PRINT household, units, energy, fixed charge, total
```

## Complexity
For a fixed number of slabs, per-house calculation is O(1) time and O(1) auxiliary space. For N households, total processing is O(N) time. The string alternative adds O(d) conversion/validation per reading and O(d) storage per reading.
