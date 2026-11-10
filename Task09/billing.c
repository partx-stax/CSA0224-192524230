#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>

#define METER_MODULUS 65536U
#define ROLLOVER_PREVIOUS_MIN 60000U
#define ROLLOVER_CURRENT_MAX 5535U
#define SLAB1_UNITS 100U
#define SLAB2_UNITS 200U
#define RATE2_PAISE 225LL
#define RATE3_PAISE 450LL
#define FIXED_PAISE 5000LL

typedef struct {
    unsigned int household;
    unsigned int previous;
    unsigned int current;
    unsigned int units;
    long long energy_paise;
    long long total_paise;
} Bill;

static int parse_uint(const char *s, unsigned int *out)
{
    char *end;
    unsigned long value;
    while (isspace((unsigned char)*s)) ++s;
    if (*s == '-' || *s == '\0') return 0;
    errno = 0;
    value = strtoul(s, &end, 10);
    if (errno || end == s || value > UINT_MAX) return 0;
    while (isspace((unsigned char)*end)) ++end;
    if (*end != '\0') return 0;
    *out = (unsigned int)value;
    return 1;
}

static int calculate_units(unsigned int previous, unsigned int current, unsigned int *units)
{
    if (previous > 65535U || current > 65535U) return 0;
    if (current >= previous) {
        *units = current - previous;
        return 1;
    }
    if (previous >= ROLLOVER_PREVIOUS_MIN && current <= ROLLOVER_CURRENT_MAX) {
        *units = (METER_MODULUS - previous) + current;
        return 1;
    }
    return 0;
}

static long long energy_charge(unsigned int units)
{
    unsigned int second = 0U, third = 0U;
    if (units > SLAB1_UNITS)
        second = units < SLAB2_UNITS ? units - SLAB1_UNITS : SLAB2_UNITS - SLAB1_UNITS;
    if (units > SLAB2_UNITS) third = units - SLAB2_UNITS;
    return (long long)second * RATE2_PAISE + (long long)third * RATE3_PAISE;
}

static int make_bill(unsigned int household, unsigned int previous, unsigned int current, Bill *b)
{
    unsigned int units;
    if (!calculate_units(previous, current, &units)) return 0;
    b->household = household;
    b->previous = previous;
    b->current = current;
    b->units = units;
    b->energy_paise = energy_charge(units);
    b->total_paise = b->energy_paise + FIXED_PAISE;
    return 1;
}

static void print_bill(const Bill *b)
{
    printf("Household %u: %u units, energy Rs %lld.%02lld, fixed Rs 50.00, total Rs %lld.%02lld\n",
           b->household, b->units, b->energy_paise / 100, b->energy_paise % 100,
           b->total_paise / 100, b->total_paise % 100);
}

int main(void)
{
    char line[256];
    unsigned int h, p, c;
    Bill bill;
    printf("Enter household previous_reading current_reading: ");
    if (!fgets(line, sizeof line, stdin)) return 1;
    char *a = strtok(line, " ,\t\r\n");
    char *b = strtok(NULL, " ,\t\r\n");
    char *d = strtok(NULL, " ,\t\r\n");
    char *extra = strtok(NULL, " ,\t\r\n");
    if (!a || !b || !d || extra || !parse_uint(a, &h) || !parse_uint(b, &p) || !parse_uint(d, &c)) {
        fprintf(stderr, "Invalid input. Enter exactly three non-negative integers.\n");
        return 1;
    }
    if (!make_bill(h, p, c, &bill)) {
        fprintf(stderr, "Invalid readings or implausible rollover. Check the meter data.\n");
        return 1;
    }
    print_bill(&bill);
    return 0;
}
