#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 100000000LL

/*
 * Experiment 2 - Part 3: OpenMP Multi-threaded Performance Benchmark
 * Program: omp_perf.c
 * Objective: Benchmark execution time across varying thread counts using OpenMP directives.
 */

int main() {
    int num_threads;
    printf("Enter number of threads: ");
    if (scanf("%d", &num_threads) != 1 || num_threads <= 0) {
        fprintf(stderr, "Invalid number of threads\n");
        return 1;
    }

    omp_set_num_threads(num_threads);

    double start_time = omp_get_wtime();
    double result = 0.0;

    #pragma omp parallel for reduction(+:result) schedule(static)
    for (long long i = 0; i < N; i++) {
        result += (double)i * 0.00001;
    }

    double end_time = omp_get_wtime();
    double time_taken = end_time - start_time;

    printf("Result = %.2f\n", result);
    printf("Execution time = %.6f seconds\n", time_taken);

    return 0;
}
