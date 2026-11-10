#include <stdio.h>
#include "billing.h"

long compute_bill(int units)
{
    long energy = 0;
    if (units > SLAB2_UNITS)
        energy += (long)(units - SLAB2_UNITS) * RATE3_PAISE;
    if (units > SLAB1_UNITS) {
        int count = units < SLAB2_UNITS ? units - SLAB1_UNITS : SLAB2_UNITS - SLAB1_UNITS;
        energy += (long)count * RATE2_PAISE;
    }
    if (units > 0 && units <= SLAB1_UNITS)
        energy += (long)units * RATE1_PAISE;
#ifdef DEBUG
    fprintf(stderr, "DEBUG units=%d energy_paise=%ld\n", units, energy);
#endif
    return energy + FIXED_CHARGE_PAISE;
}
