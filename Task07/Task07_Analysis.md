# Task 7 – Control Type Conversion and Precision

Demonstrations in the program:
1. `10 / 3` gives 3 because both operands are integers; the fractional part is discarded.
2. `(double)10 / 3` gives approximately 3.333333 because one operand is converted to floating point.
3. `(int)3.99` gives 3 because conversion to integer truncates toward zero; it does not round.
4. `0.1 + 0.2` may print a value close to, but not exactly, 0.3 because binary floating point cannot represent both decimal fractions exactly.
5. `(5 / 2) * 2.0` gives 4.0 because integer division occurs before conversion; `5 / 2.0 * 2` gives 5.0.

Rounding to paise: if a calculated charge is in rupees with fractions, multiply by 100 and use a defined rounding rule such as round-half-up. Prefer integer paise from the beginning when tariff rates are given in paise.

Alternative all-float design: calculate each bill in `float` rupees and round once at the end. Measure the sum error for n=4,000, 60,000 and 800,000 against integer paise. Both approaches perform O(1) arithmetic per bill and use O(1) space per accumulator; `float` usually uses fewer bytes than `long long`, but has limited precision. Error depends on value magnitude, operation order and rounding policy; do not claim a measured value without running the experiment.
