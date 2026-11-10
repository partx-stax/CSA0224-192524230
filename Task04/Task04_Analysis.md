# Task 4 – Use Macros Safely

A macro is expanded by the preprocessor before compilation. Inspect it with `gcc -E task04.c -o task04.i` and search the `.i` file for the expanded expressions.

Unsafe `#define SQUARE(x) x*x` makes `SQUARE(a+1)` expand to `a+1*a+1`, which follows operator precedence and is not `(a+1)*(a+1)`. Correct form: `#define SQUARE(x) ((x) * (x))`. Parenthesize the whole expression and every parameter.

`MAX(i++, j)` may evaluate `i++` more than once because the selected macro expression can evaluate an argument again. Avoid side effects in macro arguments. A function evaluates each argument once.

Static inline alternative:
```c
static inline int square_int(int x) { return x * x; }
static inline int max_int(int a, int b) { return a > b ? a : b; }
```

A macro has no call overhead but duplicates expanded code at each of k uses, potentially increasing code size O(k). An inline function may be expanded by the compiler or emitted as one function; it offers type checking and evaluates arguments once. A normal function call has O(1) call overhead; both calculations themselves are O(1). Space for inline code depends on compiler decisions; one out-of-line function body can avoid repeated copies.
