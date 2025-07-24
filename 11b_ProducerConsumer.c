#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUF 3
#define MAX 3

int buffer[BUF], in = 0, out = 0;
sem_t empty, full;
pthread_mutex_t m;

void *producer(void *p) {
    int id = *(int*)p;
    for (int i = 0; i < MAX; i++) {
        int item = rand() % 100;

        sem_wait(&empty);
        pthread_mutex_lock(&m);

        buffer[in] = item;
        printf("Producer %d inserted %d at %d\n", id, item, in);
        in = (in + 1) % BUF;

        pthread_mutex_unlock(&m);
        sem_post(&full);
    }
    return NULL;
}

void *consumer(void *c) {
    int id = *(int*)c;
    for (int i = 0; i < MAX; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&m);

        printf("Consumer %d removed %d at %d\n", id, buffer[out], out);
        out = (out + 1) % BUF;

        pthread_mutex_unlock(&m);
        sem_post(&empty);
    }
    return NULL;
}

int main() {
    pthread_t prod[3], cons[3];
    int ids[3] = {1, 2, 3};

    pthread_mutex_init(&m, NULL);
    sem_init(&empty, 0, BUF);
    sem_init(&full, 0, 0);

    for (int i = 0; i < 3; i++) {
        pthread_create(&prod[i], NULL, producer, &ids[i]);
        pthread_create(&cons[i], NULL, consumer, &ids[i]);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(prod[i], NULL);
        pthread_join(cons[i], NULL);
    }

    pthread_mutex_destroy(&m);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
