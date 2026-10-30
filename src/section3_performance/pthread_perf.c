#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 100000000LL

/*
 * Experiment 2 - Part 3: Pthreads Multi-threaded Performance Benchmark
 * Program: pthread_perf.c
 * Objective: Benchmark execution time across varying thread counts using POSIX threads.
 */

typedef struct {
    long long start;
    long long end;
    double partial_result;
} ThreadData;

void* thread_work(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    double local_sum = 0.0;
    for (long long i = data->start; i < data->end; i++) {
        local_sum += (double)i * 0.00001;
    }
    data->partial_result = local_sum;
    pthread_exit(NULL);
}

int main() {
    int num_threads;
    printf("Enter number of threads: ");
    if (scanf("%d", &num_threads) != 1 || num_threads <= 0) {
        fprintf(stderr, "Invalid number of threads\n");
        return 1;
    }

    pthread_t* threads = (pthread_t*)malloc(num_threads * sizeof(pthread_t));
    ThreadData* tdata = (ThreadData*)malloc(num_threads * sizeof(ThreadData));

    long long chunk_size = N / num_threads;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < num_threads; i++) {
        tdata[i].start = i * chunk_size;
        tdata[i].end = (i == num_threads - 1) ? N : (i + 1) * chunk_size;
        tdata[i].partial_result = 0.0;
        pthread_create(&threads[i], NULL, thread_work, (void*)&tdata[i]);
    }

    double result = 0.0;
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
        result += tdata[i].partial_result;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double time_taken = (end.tv_sec - start.tv_sec) + 
                        (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Result = %.2f\n", result);
    printf("Execution time = %.6f seconds\n", time_taken);

    free(threads);
    free(tdata);
    return 0;
}
