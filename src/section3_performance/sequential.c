#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100000000LL

/*
 * Experiment 2 - Part 3: Sequential Baseline Performance
 * Program: sequential.c
 * Objective: Measure execution time of a single-threaded baseline computation to serve as a benchmark.
 */

int main() {
    struct timespec start, end;
    double result = 0.0;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (long long i = 0; i < N; i++) {
        result += (double)i * 0.00001;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double time_taken = (end.tv_sec - start.tv_sec) + 
                        (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Result = %.2f\n", result);
    printf("Execution time = %.6f seconds\n", time_taken);

    return 0;
}
