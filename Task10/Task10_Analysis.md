# Task 10 – Compare Expectations with Execution

Run `task10.c` to compare integer paise, float rupees and double rupees for 4,000, 60,000 and 800,000 identical bills of ₹860.00. The program prints the measured deltas. Record your exact terminal output and compiler version in the report.

Integer paise is exact until overflow. For the experiment, the district total is 800,000 × 86,000 = 68,800,000,000 paise = ₹688,000,000, which exceeds a typical 32-bit `int` and 32-bit `long`, but fits a 64-bit `long long`. C guarantees `long long` at least 64 bits; still inspect `LLONG_MAX`. `long` size is platform-dependent (often 64-bit on Linux and 32-bit on Windows LLP64).

A `double` accumulator avoids integer overflow for this magnitude and typically has enough precision to represent the total closely, but it is not exact decimal arithmetic. `long long` addition and `double` addition are both O(1) time and use O(1) space per accumulator. Integer overflow is catastrophic and wraps/causes undefined behaviour depending on signedness; floating-point loses low-order precision gradually.

Do not generalise one experiment's float error to every tariff amount. Record the fixed per-house amount, order of addition and measured output.


## Preparation-environment measurement (not the student's laptop)
The package was compiled with GCC 14.2.0 on a 64-bit Linux environment. With a fixed bill of ₹860.00, the observed output was:

| Bills | Exact total | float total | float difference | double total | double difference |
|---:|---:|---:|---:|---:|---:|
| 4,000 | ₹3,440,000.00 | ₹3,440,000.00 | ₹0.00 | ₹3,440,000.00 | ₹0.00 |
| 60,000 | ₹51,600,000.00 | ₹51,600,000.00 | ₹0.00 | ₹51,600,000.00 | ₹0.00 |
| 800,000 | ₹688,000,000.00 | ₹685,183,488.00 | -₹2,816,512.00 | ₹688,000,000.00 | ₹0.00 |

These are measurements from the preparation environment only. Re-run on the student's own GCC installation and include that output separately. This experiment demonstrates that repeated `float` addition can lose significant low-order value at district scale even when each individual bill is exactly representable.
