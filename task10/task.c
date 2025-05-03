#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double generate_random_0_to_1() {
    return (double) rand() / RAND_MAX;
}

double generate_random_0_to_n(double n) {
    return (double) rand() / RAND_MAX * n;
}

int main() {
    srand(time(NULL));

    printf("Random numbers in the range [0.0, 1.0]:\n");
    for (int i = 0; i < 5; i++) {
        printf("%lf\n", generate_random_0_to_1());
    }

    double n;
    printf("\nEnter a value for n: ");
    if (scanf("%lf", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    printf("\nRandom numbers in the range [0.0, %.2f]:\n", n);
    for (int i = 0; i < 5; i++) {
        printf("%lf\n", generate_random_0_to_n(n));
    }

    return 0;
}
