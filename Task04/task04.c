#include <stdio.h>
#define RUPEES_TO_PAISE(r) ((long)(r) * 100L)
#define SQUARE(x) ((x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

static inline long rupees_to_paise(long r) { return r * 100L; }
static inline int square_int(int x) { return x * x; }
static inline int max_int(int a, int b) { return a > b ? a : b; }

int main(void)
{
    int a = 4, b = 7;
    printf("Rupees to paise: %ld\n", RUPEES_TO_PAISE(50));
    printf("SQUARE(a + 1): %d\n", SQUARE(a + 1));
    printf("MAX(a, b): %d\n", MAX(a, b));
    printf("Inline square: %d, inline max: %d\n", square_int(a + 1), max_int(a, b));
    return 0;
}
