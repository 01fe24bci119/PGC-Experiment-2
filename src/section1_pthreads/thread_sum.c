#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4
#define ARRAY_SIZE 8

/*
 * Experiment 2 - Part 1: Parallel Array Summation
 * Program: thread_sum.c
 * Objective: Partition workload across multiple POSIX threads to compute partial sums and total sum.
 */

int array[ARRAY_SIZE] = {10, 20, 30, 40, 50, 60, 70, 80};
int partial_sums[NUM_THREADS] = {0};

typedef struct {
    int thread_id;
    int start_index;
    int end_index;
} ThreadData;

void* compute_sum(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int sum = 0;
    for (int i = data->start_index; i <= data->end_index; i++) {
        sum += array[i];
    }
    partial_sums[data->thread_id - 1] = sum;
    printf("Thread %d calculated sum = %d\n", data->thread_id, sum);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    int elements_per_thread = ARRAY_SIZE / NUM_THREADS;
    int total_sum = 0;

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].thread_id = i + 1;
        thread_data[i].start_index = i * elements_per_thread;
        thread_data[i].end_index = thread_data[i].start_index + elements_per_thread - 1;

        if (pthread_create(&threads[i], NULL, compute_sum, (void*)&thread_data[i]) != 0) {
            perror("Failed to create thread");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
        total_sum += partial_sums[i];
    }

    printf("Total sum = %d\n", total_sum);
    return 0;
}
