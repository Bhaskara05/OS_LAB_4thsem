#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("Error: not passing N in command line\n");
        return 1;
    }

    int n = atoi(argv[1]);
    if (n < 1) {
        printf("Invalid N: %d\n", n);
        return 1;
    }

    int shmid = shmget((key_t)1122, 4096, 0666);
    if (shmid < 0) {
        perror("shmget failed");
        return 1;
    }

    char *ptr = (char *)shmat(shmid, NULL, 0);
    if (ptr == (void *)-1) {
        perror("shmat failed");
        return 1;
    }

    printf("CHILD:\n");

    int n1 = 0, n2 = 1, n3;
    int offset = 0;

    // First number
    offset += sprintf(ptr + offset, "%d ", n1);
    printf("%d ", n1);

    if (n > 1) {
        offset += sprintf(ptr + offset, "%d ", n2);
        printf("%d ", n2);
    }

    for (int k = 2; k < n; k++) {
        n3 = n1 + n2;
        offset += sprintf(ptr + offset, "%d ", n3);
        printf("%d ", n3);
        n1 = n2;
        n2 = n3;
    }

    printf("\n");

    shmdt(ptr); // detach
    return 0;
}