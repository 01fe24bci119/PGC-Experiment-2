#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4

/*
 * Experiment 2 - Part 2: OpenMP Barrier Synchronization
 * Program: omp_barrier.c
 * Objective: Ensure all threads synchronize at a designated checkpoint using #pragma omp barrier.
 */

int main() {
    #pragma omp parallel num_threads(NUM_THREADS)
    {
        int tid = omp_get_thread_num();

        // Stage 1
        printf("Thread %d completed Stage 1\n", tid);

        // Barrier: Wait until all threads reach here before proceeding
        #pragma omp barrier

        // Stage 2
        printf("Thread %d started Stage 2\n", tid);
    }

    return 0;
}
