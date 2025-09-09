#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

int isPrime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    int start = atoi(argv[1]);
    int end = atoi(argv[2]);

    int shm_fd = shm_open("VSS", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, 4096);

    void *ptr = mmap(0, 4096, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    printf("[CHILD] Generating primes from %d to %d...\n", start, end);

    char buffer[4096];
    buffer[0] = '\0'; // start empty

    for (int num = start; num <= end; num++) {
        if (isPrime(num)) {
            char temp[20];
            sprintf(temp, "%d ", num);
            strcat(buffer, temp);
        }
    }

    sprintf(ptr, "%s", buffer); // write into shared memory
    printf("[CHILD] Done. Primes written to shared memory.\n");

    return 0;
}