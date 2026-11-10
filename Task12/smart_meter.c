#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <errno.h>

#define CONFIG_FILE "tariff.txt"
#define INPUT_FILE "sample_readings.csv"

typedef struct {
    uint64_t base_rate_paise_per_kwh;
    uint64_t fixed_charge_paise;
    unsigned int peak_start_hour;
    unsigned int peak_end_hour;
    unsigned int peak_multiplier_percent;
} Tariff;

static int load_tariff(const char *path, Tariff *t)
{
    FILE *fp = fopen(path, "r");
    char line[160];
    int seen = 0;
    if (!fp) return 0;
    /* Start with safe defaults; every key in this small file is required. */
    t->base_rate_paise_per_kwh = 0; t->fixed_charge_paise = 0;
    t->peak_start_hour = 18; t->peak_end_hour = 22; t->peak_multiplier_percent = 120;
    while (fgets(line, sizeof line, fp)) {
        unsigned long long v;
        if (line[0] == '#' || line[0] == '\n') continue;
        if (sscanf(line, "base_rate_paise_per_kwh=%llu", &v) == 1) { t->base_rate_paise_per_kwh = v; seen |= 1; }
        else if (sscanf(line, "fixed_charge_paise=%llu", &v) == 1) { t->fixed_charge_paise = v; seen |= 2; }
        else if (sscanf(line, "peak_start_hour=%llu", &v) == 1) { t->peak_start_hour = (unsigned int)v; seen |= 4; }
        else if (sscanf(line, "peak_end_hour=%llu", &v) == 1) { t->peak_end_hour = (unsigned int)v; seen |= 8; }
        else if (sscanf(line, "peak_multiplier_percent=%llu", &v) == 1) { t->peak_multiplier_percent = (unsigned int)v; seen |= 16; }
        else { fclose(fp); return 0; }
    }
    fclose(fp);
    return seen == 31 && t->base_rate_paise_per_kwh > 0 && t->peak_start_hour < 24 && t->peak_end_hour <= 24 &&
           t->peak_start_hour < t->peak_end_hour && t->peak_multiplier_percent >= 100;
}

int main(void)
{
    Tariff tariff;
    FILE *fp;
    char line[160];
    uint64_t total_wh = 0, charge_numerator = 0;
    if (!load_tariff(CONFIG_FILE, &tariff)) {
        fprintf(stderr, "Could not read valid tariff configuration: %s\n", CONFIG_FILE);
        return 1;
    }
    fp = fopen(INPUT_FILE, "r");
    if (!fp) { perror(INPUT_FILE); return 1; }
    while (fgets(line, sizeof line, fp)) {
        unsigned int hour;
        unsigned long long wh;
        uint64_t rate, multiplier;
        if (line[0] == '#' || line[0] == '\n') continue;
        if (sscanf(line, "%u,%llu", &hour, &wh) != 2 || hour >= 24) {
            fprintf(stderr, "Invalid reading row: %s", line); fclose(fp); return 1;
        }
        if (UINT64_MAX - total_wh < (uint64_t)wh) {
            fprintf(stderr, "Watt-hour total overflow\n"); fclose(fp); return 1;
        }
        total_wh += (uint64_t)wh;
        rate = tariff.base_rate_paise_per_kwh;
        multiplier = (hour >= tariff.peak_start_hour && hour < tariff.peak_end_hour)
                     ? tariff.peak_multiplier_percent : 100U;
        /* Keep fractional paise until the final total. Denominator = 1000 Wh/kWh * 100 percent. */
        if ((uint64_t)wh > (UINT64_MAX - charge_numerator) / rate / multiplier) {
            fprintf(stderr, "Charge accumulator overflow\n"); fclose(fp); return 1;
        }
        charge_numerator += (uint64_t)wh * rate * multiplier;
    }
    fclose(fp);
    {
        uint64_t energy_paise = (charge_numerator + 50000U) / 100000U; /* nearest paise */
        uint64_t total_paise = energy_paise + tariff.fixed_charge_paise;
        printf("Year/period consumption: %" PRIu64 " Wh (%.3f kWh)\n", total_wh, (double)total_wh / 1000.0);
        printf("Energy charge: Rs %" PRIu64 ".%02" PRIu64 "\n", energy_paise / 100, energy_paise % 100);
        printf("Fixed charge: Rs %" PRIu64 ".%02" PRIu64 "\n", tariff.fixed_charge_paise / 100, tariff.fixed_charge_paise % 100);
        printf("Total: Rs %" PRIu64 ".%02" PRIu64 "\n", total_paise / 100, total_paise % 100);
    }
    return 0;
}
