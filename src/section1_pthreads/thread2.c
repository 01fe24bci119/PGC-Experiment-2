#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4

/*
 * Experiment 2 - Part 1: Multiple Threads Creation
 * Program: thread2.c
 * Objective: Demonstrate creating and synchronizing multiple threads concurrently.
 */

void* print_message(void* thread_id) {
    long tid = (long)thread_id;
    printf("Hello from Thread %ld\n", tid);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    long t;

    // Create 4 concurrent threads
    for (t = 1; t <= NUM_THREADS; t++) {
        if (pthread_create(&threads[t - 1], NULL, print_message, (void*)t) != 0) {
            perror("Error creating thread");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all threads to finish
    for (t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    printf("All threads have finished.\n");
    return 0;
}
