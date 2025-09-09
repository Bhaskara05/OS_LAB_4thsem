// gcc producer_consumer.c -pthread -o pc
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MaxItems 3     // Maximum items a producer can produce or a consumer can consume
#define BufferSize 3   // Size of the buffer

sem_t empty;
sem_t full;
int in = 0;
int out = 0;
int buffer[BufferSize];
pthread_mutex_t mutex;

void *producer(void *pno) {   
    int item;
    for (int i = 0; i < MaxItems; i++) {
        item = rand() % 100; // Produce a random item
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("Producer %d: Insert Item %d at %d\n", *((int *)pno), buffer[in], in);
        in = (in + 1) % BufferSize;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
    return NULL;
}

void *consumer(void *cno) {   
    for (int i = 0; i < MaxItems; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        int item = buffer[out];
        printf("Consumer %d: Remove Item %d from %d\n", *((int *)cno), item, out);
        out = (out + 1) % BufferSize;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
    return NULL;
}

int main() {
    pthread_t pro[3], con[3];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BufferSize);
    sem_init(&full, 0, 0);

    srand(time(NULL));  // seed random number generator

    int a[3] = {1, 2, 3}; // Just used for numbering the producer and consumer

    // Create producer threads
    for (int i = 0; i < 3; i++) {
        pthread_create(&pro[i], NULL, producer, (void *)&a[i]);
    }

    // Create consumer threads
    for (int i = 0; i < 3; i++) {
        pthread_create(&con[i], NULL, consumer, (void *)&a[i]);
    }

    // Wait for all producers
    for (int i = 0; i < 3; i++) {
        pthread_join(pro[i], NULL);
    }

    // Wait for all consumers
    for (int i = 0; i < 3; i++) {
        pthread_join(con[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}