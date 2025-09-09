#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("Error: not passing N in command line\n");
        exit(0);
    }

    int n = atoi(argv[1]);
    if (n < 1) {
        printf("Invalid N: %d\n", n);
        exit(0);
    }

    int shm_fd = shm_open("VSS", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, 4096);
    void *ptr = mmap(0, 4096, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    printf("CHILD:\n");

    int n1 = 0, n2 = 1, n3;
    int offset = 0;

    // First number
    offset += sprintf((char *)ptr + offset, "%d ", n1);
    printf("%d ", n1);

    if (n > 1) {
        offset += sprintf((char *)ptr + offset, "%d ", n2);
        printf("%d ", n2);
    }

    for (int k = 2; k < n; k++) {
        n3 = n1 + n2;
        offset += sprintf((char *)ptr + offset, "%d ", n3);
        printf("%d ", n3);
        n1 = n2;
        n2 = n3;
    }
    printf("\n");

    return 0;
}