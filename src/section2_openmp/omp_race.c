#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4
#define ITERATIONS 100000

/*
 * Experiment 2 - Part 2: OpenMP Race Condition Demonstration
 * Program: omp_race.c
 * Objective: Demonstrate race condition when multiple OpenMP threads modify a shared variable concurrently without synchronization.
 */

int main() {
    int counter = 0;

    #pragma omp parallel num_threads(NUM_THREADS)
    {
        for (int i = 0; i < ITERATIONS; i++) {
            counter++; // Unprotected shared write
        }
    }

    printf("Expected counter = %d\n", NUM_THREADS * ITERATIONS);
    printf("Actual counter = %d\n", counter);

    return 0;
}
