#include <stdio.h>

int main(void)
{
    unsigned int household;
    int previous, current;
    printf("Enter household number, previous reading and current reading: ");
    if (scanf("%u %d %d", &household, &previous, &current) != 3) {
        fprintf(stderr, "Invalid input. Enter three numeric values.\n");
        return 1;
    }
    if (previous < 0 || previous > 65535 || current < 0 || current > 65535) {
        fprintf(stderr, "Readings must be between 0 and 65535.\n");
        return 1;
    }
    if (current < previous) {
        fprintf(stderr, "Current reading is lower; check whether rollover occurred.\n");
        return 1;
    }
    printf("Household: %u\nUnits: %d\n", household, current - previous);
    printf("Example formatted bill: Rs %d.%02d\n", 162, 50);
    return 0;
}
