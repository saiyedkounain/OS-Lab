#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

sem_t wrt;
pthread_mutex_t mutex;
int cnt = 1, numreader = 0;

void *writer(void *wno) {
    sem_wait(&wrt);
    cnt *= 2;
    printf("Writer %d modified cnt to %d\n", *(int*)wno, cnt);
    sem_post(&wrt);
    return NULL;
}

void *reader(void *rno) {
    pthread_mutex_lock(&mutex);
    if (++numreader == 1) sem_wait(&wrt);
    pthread_mutex_unlock(&mutex);

    printf("Reader %d: read cnt as %d\n", *(int*)rno, cnt);

    pthread_mutex_lock(&mutex);
    if (--numreader == 0) sem_post(&wrt);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t r[3], w[3];
    int a[3] = {1, 2, 3};

    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt, 0, 1);

    for (int i = 0; i < 3; i++) {
        pthread_create(&r[i], NULL, reader, &a[i]);
        pthread_create(&w[i], NULL, writer, &a[i]);
    }
    for (int i = 0; i < 3; i++) {
        pthread_join(r[i], NULL);
        pthread_join(w[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);
    return 0;
}
