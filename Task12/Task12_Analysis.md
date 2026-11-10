# Task 12 – Day-4 Smart-Meter Design Challenge (8 Marks)

## A. Impact analysis
The original system receives one cumulative 16-bit register reading per month. The new system receives 15-minute interval energy in watt-hours, 35,040 records per house per year, and applies a time-of-day price premium from 18:00 through 21:59 (the stated interval is 6 PM up to 10 PM). Tariff values must be changed without recompilation. Therefore the original `unsigned short` monthly register and compile-time tariff macros are not sufficient as the complete data model. Use `uint64_t` for yearly watt-hour totals and integer paise/rational arithmetic for charges. Store tariff settings in a validated runtime file.

## B. Magnitude analysis
Records per house per year = 365 × 24 × 4 = 35,040. For H households, yearly records = 35,040H. At 800,000 households: 28,032,000,000 records/year. A 32-bit unsigned counter cannot represent that many records in one aggregate counter; a 64-bit counter can. The PDF does not specify maximum meter power or maximum Wh per interval, so an absolute maximum yearly Wh total cannot be derived from the brief alone. State the assumed physical meter limit if one is provided by the utility. `uint64_t` is the practical selected type, with overflow checks.

## C. Revised design
The sample implementation reads tariff values from `tariff.txt` at runtime and interval readings from `sample_readings.csv`. Each record contains hour and watt-hours. Hours 18, 19, 20 and 21 receive a 20% premium; hour 22 is outside the peak interval. The base rate is stored in paise/kWh. It accumulates the exact numerator `Wh × rate_paise_per_kWh × multiplier_percent` and divides by 100,000 once at the end (1,000 Wh/kWh × 100 percent), rounding to the nearest paisa. This avoids rounding each 15-minute record separately.

Compile and run from the Task12 directory:
```bash
gcc -std=c11 -Wall -Wextra -pedantic smart_meter.c -o smart_meter
./smart_meter
```

With sample readings (total 5,000 Wh; 3,000 Wh peak and 2,000 Wh off-peak), base rate 450 paise/kWh, fixed charge 5,000 paise:
- Off-peak energy = 2 kWh × ₹4.50 = ₹9.00
- Peak energy = 3 kWh × ₹4.50 × 1.20 = ₹16.20
- Energy charge = ₹25.20
- Fixed charge = ₹50.00
- Total = ₹75.20

## D. Evidence-based defence
RETAIN the original integer-money principle, MODIFY the widths and data flow, and REDESIGN tariff loading and time classification. The new implementation uses 64-bit counters and runtime tariff configuration. It retains exact integer-based money arithmetic and performs one final rounding. Trade-offs include larger storage, file validation, clock/time-zone correctness, missing interval handling and overflow checks. The example assumes the supplied hour is already local utility time; a production system should store timestamps with timezone/offset and validate duplicate or missing intervals.

## Complexity
For R interval records, processing is O(R) time and O(1) working memory (streaming one record at a time). Tariff configuration has O(t) startup parsing time and O(t) space for t settings. Storing every annual interval instead would require O(R) storage, so streaming is preferable for billing aggregation.
