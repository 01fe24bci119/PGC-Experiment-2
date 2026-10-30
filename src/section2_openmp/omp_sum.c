#include <stdio.h>
#include <omp.h>

#define ARRAY_SIZE 8

/*
 * Experiment 2 - Part 2: OpenMP Parallel Work-Sharing and Reduction
 * Program: omp_sum.c
 * Objective: Demonstrate automatic loop partitioning and sum reduction with #pragma omp parallel for reduction.
 */

int main() {
    int array[ARRAY_SIZE] = {10, 20, 30, 40, 50, 60, 70, 80};
    int total_sum = 0;

    #pragma omp parallel for reduction(+:total_sum)
    for (int i = 0; i < ARRAY_SIZE; i++) {
        int tid = omp_get_thread_num();
        printf("Thread %d processed array[%d] = %d\n", tid, i, array[i]);
        total_sum += array[i];
    }

    printf("Total sum = %d\n", total_sum);
    return 0;
}
