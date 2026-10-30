#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4
#define INCREMENTS_PER_THREAD 100000

/*
 * Experiment 2 - Part 1: Race Condition Demonstration
 * Program: race.c
 * Objective: Demonstrate data hazard / race condition when shared memory is updated without synchronization.
 */

long counter = 0;

void* worker(void* arg) {
    for (int i = 0; i < INCREMENTS_PER_THREAD; i++) {
        counter++; // Critical section left unprotected
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, worker, NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Final counter value = %ld\n", counter);
    return 0;
}
