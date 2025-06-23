#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Function to be run by thread 1
void* thread_function1(void* arg) {
    for (int i = 0; i < 5; i++) {
        printf("Thread 1 is running: %d\n", i);
        sleep(1);
    }
    return NULL;
}

// Function to be run by thread 2
void* thread_function2(void* arg) {
    for (int i = 0; i < 5; i++) {
        printf("Thread 2 is running: %d\n", i);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Create two threads
    pthread_create(&thread1, NULL, thread_function1, NULL);
    pthread_create(&thread2, NULL, thread_function2, NULL);

    // Wait for both threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Both threads have finished executing.\n");

    return 0;
}
