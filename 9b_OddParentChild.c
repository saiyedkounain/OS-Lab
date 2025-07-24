#include <stdio.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct { int n, arr[100]; } pack_t;

int main() {
    int shmid = shmget(1234, sizeof(pack_t), 0666 | IPC_CREAT);
    pack_t *shm = shmat(shmid, NULL, 0);

    printf("[PARENT] Enter n: ");
    scanf("%d", &shm->n);

    if (fork() == 0) execlp("./child", "./child", NULL);  // run child
    else {
        wait(NULL);
        printf("[PARENT] The first %d odd numbers are:\n", shm->n);
        for (int i = 0; i < shm->n; i++) printf("%d ", shm->arr[i]);
        printf("\n");
        shmdt(shm);
        shmctl(shmid, IPC_RMID, NULL);
    }
    return 0;
}


//child
#include <stdio.h>
#include <sys/shm.h>

typedef struct { int n, arr[100]; } pack_t;

int main() {
    int shmid = shmget(1234, sizeof(pack_t), 0666);
    pack_t *shm = shmat(shmid, NULL, 0);

    for (int i = 0; i < shm->n; i++) shm->arr[i] = 2 * i + 1;

    shmdt(shm);
    return 0;
}
