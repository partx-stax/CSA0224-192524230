#include <stdio.h>
#include <limits.h>

int main(void)
{
    printf("10 / 3 = %d (integer division discards fraction)\n", 10 / 3);
    printf("(double)10 / 3 = %.6f\n", (double)10 / 3);
    printf("(int)3.99 = %d (fraction is truncated)\n", (int)3.99);
    printf("0.1 + 0.2 = %.17f (binary floating approximation)\n", 0.1 + 0.2);
    printf("(5 / 2) * 2.0 = %.1f, but 5 / 2.0 * 2 = %.1f\n", (5 / 2) * 2.0, 5 / 2.0 * 2);
    if (LONG_MAX > INT_MAX)
        printf("LONG_MAX is larger than INT_MAX on this system.\n");
    return 0;
}
