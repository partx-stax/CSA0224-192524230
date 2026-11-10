# Task 3 – Define the Constants

The tariff macros are defined once at the top of the file. `#define` performs preprocessor text substitution and normally allocates no variable storage. A `const` object has a C type and scope and is visible to a debugger; it may occupy storage. An `enum` is suitable for named integral choices, not fractional monetary rates unless rates are stored as integer paise. Macro names use uppercase words separated by underscores.

Changing `RATE2_PAISE` from 225 to 230 changes the rate for every unit in slab 2 consistently. For 150 units the energy charge becomes 50 × ₹2.30 = ₹115, plus ₹50 fixed = ₹165.00. For 200 units: ₹230 + ₹50 = ₹280.00. For 350 units: ₹230 + ₹675 + ₹50 = ₹955.00.

Alternative: replacing tariff macros with `const long` objects provides type checking, scope and debugger visibility. `enum` constants are compile-time integer constants and have no object storage. Runtime is generally unaffected after optimization; the key differences are type/scope/debugging and whether the value is usable in preprocessor conditions.

Complexity: fixed slab arithmetic is O(1) time and O(1) space per bill.
