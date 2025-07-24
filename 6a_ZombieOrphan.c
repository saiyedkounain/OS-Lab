#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t cpid = fork(); // create child

    if (cpid < 0) { perror("fork"); exit(1); }

    if (cpid == 0) { // Child process
        printf("[CHILD] PID=%d, Parent PID=%d\n", getpid(), getppid());
        printf("[CHILD] Exiting...\n");
        exit(0);
    } else {        // Parent process
        printf("[PARENT] PID=%d, Parent PID=%d\n", getpid(), getppid());
        printf("[PARENT] Sleeping 10s → child becomes zombie.\n");
        sleep(10);
        printf("[PARENT] Child PID=%d is zombie (entry in process table).\n", cpid);
    }
    return 0;
}



//orphan
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t cpid = fork(); // create child

    if (cpid < 0) { perror("fork"); exit(1); }

    if (cpid == 0) { // Child process
        printf("[CHILD] PID=%d, Parent PID=%d\n", getpid(), getppid());
        printf("[CHILD] Sleeping 10s...\n");
        sleep(10);
        printf("[CHILD] Parent ended → adopted by init (new Parent PID=%d)\n", getppid());
    } else {         // Parent process
        printf("[PARENT] PID=%d, Parent PID=%d\n", getpid(), getppid());
        printf("[PARENT] Exiting...\n");
        exit(0);
    }
    return 0;
}
