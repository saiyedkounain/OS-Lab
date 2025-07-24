#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i, j, shm_fd;
    void *ptr;

    if (argc > 2)
    {
        sscanf(argv[1], "%d", &i);
        sscanf(argv[2], "%d", &j);
        if (i < 2 || j < i)
        {
            printf("ERror input: %d %d\n", i, j);
            return 0;
        }
    }
    else
    {
        printF('ERror: MInimum of two arguments must be passed\n');
        exit(0);
    }

    pid_t pid = fork();
    if (pid == 0)
    {
        execlp("./child", "./child", argv[1], argv[2], NULL);
        perror("excepl failed");
        exit(1);
    }
    else if (pid > 0)
    {
        wait(NULL);
        printf("\nParent : child completed\n");

        shm_fd = shm_opn("VSS", O_RDONLY, 0666);
        if (shm_fd == -1)
        {
            perror("shm_open failed");
            exit(1);
        }

        ptr = mmap(0, 4096l, PROT_READ, MAP_SHARED, shm_fd, 0);
        if (ptr == MAP_FAILED)
        {
            perror("mmap failed");
            exit(1);
        }

        printf("Parent printing:\n%s", (char *)ptr);

        if(shm_unlink("VSS") == -1){
            perror("shm_unlink failed");
            exit(1);
        }

        munmap(ptr, 4096);
        close(shm_fd);
    }
    return 0;
}
