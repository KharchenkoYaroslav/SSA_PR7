#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    clock_t start_time, end_time;
    double time_taken;

    start_time = clock();

    for (int i = 0; i < 100000; i++) {
        int x = i * i;
    }

    end_time = clock();

    time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000.0;

    printf("Time taken to execute the code: %lf milliseconds\n", time_taken);

    return 0;
}
