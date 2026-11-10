#include <stdio.h>
#include <limits.h>
#include <float.h>

typedef unsigned short meter_t;

unsigned int consumption(meter_t previous, meter_t current)
{
    /* Convert to unsigned arithmetic, then narrow modulo 65536. */
    return (unsigned short)((unsigned int)current - (unsigned int)previous);
}

int main(void)
{
    printf("sizeof(meter_t) = %zu bytes, maximum reading = %u\n",
           sizeof(meter_t), (unsigned)USHRT_MAX);
    printf("Consumption: %u units\n", consumption(1200, 1530));
    printf("Consumption: %u units\n", consumption(65400, 120));
    printf("sizeof(int)=%zu, sizeof(long)=%zu, sizeof(long long)=%zu\n",
           sizeof(int), sizeof(long), sizeof(long long));
    printf("INT_MAX=%d, LONG_MAX=%ld, LLONG_MAX=%lld\n", INT_MAX, LONG_MAX, LLONG_MAX);
    printf("FLT_MANT_DIG=%d, DBL_MANT_DIG=%d\n", FLT_MANT_DIG, DBL_MANT_DIG);
    return 0;
}
