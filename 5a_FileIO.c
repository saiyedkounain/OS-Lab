#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF 30

int main() {
    int fd = open("myfile.txt", O_RDWR);
    char buf[BUF];
    int n;

    if (fd == -1) { printf("File open failed\n"); exit(1); }
    printf("FD = %d\n", fd);

    // 1. Read first 10 chars
    printf("\nFirst 10 chars:\n");
    n = read(fd, buf, 10); write(1, buf, n);

    // 2. Skip 5 chars ahead
    printf("\n\nSkip 5 ahead:\n");
    lseek(fd, 5, SEEK_CUR);
    n = read(fd, buf, 10); write(1, buf, n);

    // 3. Go 10 chars back
    printf("\n\nGo 10 back:\n");
    lseek(fd, -10, SEEK_CUR);
    n = read(fd, buf, 10); write(1, buf, n);

    // 4. Go to 5th last char
    printf("\n\n5th last char:\n");
    lseek(fd, -5, SEEK_END);
    n = read(fd, buf, 5); write(1, buf, n);

    // 5. Go to 3rd char
    printf("\n\n3rd char:\n");
    lseek(fd, 3, SEEK_SET);
    n = read(fd, buf, 5); write(1, buf, n);

    close(fd);
    return 0;
}
