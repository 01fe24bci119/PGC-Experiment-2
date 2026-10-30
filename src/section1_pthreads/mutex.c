#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4
#define INCREMENTS_PER_THREAD 100000

/*
 * Experiment 2 - Part 1: Mutex Synchronization
 * Program: mutex.c
 * Objective: Eliminate race condition by enforcing mutual exclusion using pthread_mutex_t.
 */

long counter = 0;
pthread_mutex_t lock;

void* worker(void* arg) {
    for (int i = 0; i < INCREMENTS_PER_THREAD; i++) {
        pthread_mutex_lock(&lock);
        counter++; // Protected critical section
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Initialize mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        perror("Mutex init failed");
        return 1;
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, worker, NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy mutex after completion
    pthread_mutex_destroy(&lock);

    printf("Final counter value = %ld\n", counter);
    return 0;
}
