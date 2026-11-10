# Task 9 – Implement and Test the Billing Program

Compile: `gcc -std=c11 -Wall -Wextra -pedantic billing.c -o billing`.
Input one line: `household previous current`. Example: `101 1200 1530`.

The program uses `fgets` and token validation to reject letters, negative values, extra fields and out-of-range readings. It accepts a lower current reading as rollover only when previous ≥ 60000 and current ≤ 5535. This threshold is an explicit engineering assumption because the PDF asks for a case where a lower reading is not a rollover; the meter operator should confirm the threshold policy.

## Expected test table
| Test | Input (household previous current) | Expected result |
|---|---|---|
| Normal 150 units | `101 1000 1150` | 150 units; energy ₹112.50; total ₹162.50 |
| Exactly 100 | `102 1000 1100` | 100 units; total ₹50.00 |
| Exactly 200 | `103 1000 1200` | 200 units; total ₹275.00 |
| Zero | `104 1000 1000` | 0 units; total ₹50.00 |
| Rollover | `105 65400 120` | 256 units; energy ₹477.00; total ₹527.00 |
| Letters | `106 abc 100` | Reject invalid input |
| Negative | `107 -10 100` | Reject invalid input |
| Lower, not rollover | `108 5000 100` | Reject implausible rollover |

For 5 bills, use these readings and calculate manually:
- 101: 1000→1150 = 150 units, ₹162.50
- 102: 1000→1100 = 100 units, ₹50.00
- 103: 1000→1200 = 200 units, ₹275.00
- 104: 1000→1000 = 0 units, ₹50.00
- 105: 65400→120 = 256 units, ₹527.00
Total = ₹1,064.50. Verify by running each case and summing paise.

Alternative array-and-loop design stores slab boundaries and rates in arrays. It takes O(s) time per bill for s slabs and O(s) storage for tariff data. Fixed statements take O(1) time and O(1) space. Arrays are easier to extend when the number of slabs changes; fixed statements are simple and efficient for a small tariff with a fixed number of slabs.
