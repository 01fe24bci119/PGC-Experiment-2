#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*
 * Experiment 2 - Part 1: POSIX Threads Basics
 * Program: thread1.c
 * Objective: Demonstrate basic thread creation and termination using pthread_create and pthread_join.
 */

void* thread_function(void* arg) {
    printf("Hello from the thread!\n");
    return NULL;
}

int main() {
    pthread_t thread_id;

    // Create a new thread executing thread_function
    if (pthread_create(&thread_id, NULL, thread_function, NULL) != 0) {
        perror("Failed to create thread");
        return 1;
    }

    // Wait for the created thread to complete execution
    if (pthread_join(thread_id, NULL) != 0) {
        perror("Failed to join thread");
        return 1;
    }

    printf("Main thread finished.\n");
    return 0;
}
