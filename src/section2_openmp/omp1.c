#include <stdio.h>
#include <omp.h>

/*
 * Experiment 2 - Part 2: OpenMP Basic Parallel Region
 * Program: omp1.c
 * Objective: Demonstrate parallel thread spawning using #pragma omp parallel and query thread IDs.
 */

int main() {
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int total_threads = omp_get_num_threads();
        printf("Hello from thread %d of %d\n", tid, total_threads);
    }

    return 0;
}
