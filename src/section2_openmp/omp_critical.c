#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4
#define ITERATIONS 100000

/*
 * Experiment 2 - Part 2: OpenMP Critical Section Synchronization
 * Program: omp_critical.c
 * Objective: Resolve race conditions in OpenMP using #pragma omp critical directive.
 */

int main() {
    int counter = 0;

    #pragma omp parallel num_threads(NUM_THREADS)
    {
        for (int i = 0; i < ITERATIONS; i++) {
            #pragma omp critical
            {
                counter++; // Mutually exclusive execution
            }
        }
    }

    printf("Expected counter = %d\n", NUM_THREADS * ITERATIONS);
    printf("Actual counter = %d\n", counter);

    return 0;
}
