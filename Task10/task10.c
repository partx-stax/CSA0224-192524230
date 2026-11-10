#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* Reproducible comparison using a fixed bill amount; change amount if desired. */
int main(void)
{
    const long long bill_paise = 86000LL; /* ₹860.00 */
    const int counts[] = {4000, 60000, 800000};
    for (size_t k = 0; k < sizeof counts / sizeof counts[0]; ++k) {
        long long exact_paise = 0;
        float float_rupees = 0.0f;
        double double_rupees = 0.0;
        for (int i = 0; i < counts[k]; ++i) {
            exact_paise += bill_paise;
            float_rupees += (float)bill_paise / 100.0f;
            double_rupees += (double)bill_paise / 100.0;
        }
        printf("n=%d exact=%.2f float=%.2f float_delta=%.2f double=%.2f double_delta=%.2f\n",
               counts[k], (double)exact_paise / 100.0, (double)float_rupees,
               (double)float_rupees - (double)exact_paise / 100.0,
               double_rupees, double_rupees - (double)exact_paise / 100.0);
    }
    printf("sizeof(int)=%zu sizeof(long)=%zu sizeof(long long)=%zu sizeof(float)=%zu sizeof(double)=%zu\n",
           sizeof(int), sizeof(long), sizeof(long long), sizeof(float), sizeof(double));
    return 0;
}
