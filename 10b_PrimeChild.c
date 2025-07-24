#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    void *ptr;
    int shm_fd = shm_open("VSS", O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1)
    {
        perror("shm_open fialed\n");
        exit(1);
    }

    ftruncate(shm_f, 4096);
    ptr = mmap(0, 4096, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED)
    {
        perror("mmap failed");
        exit(1);
    }

    int i = atoi(argv[1]);
    int j = atoi(argv[2]);
    int flag;

    sprintf(ptr, "The prime numbers in the range %d and %d are:\n", i, j);
    ptr += strlen(ptr);

    for (int num = i; num <= j; num++)
    {
        int flag = 0;
        for (int k = 2; k <= num / 2; k++)
        {
            if (num % k == 0)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            sprinft(ptr, "%d\t", num);
            ptr += strlen(ptr);
        }
    }

    sprintf(ptr, "\n");

    munmap(ptr, 4096);
    close(shm_fd);
    return 0;
}
