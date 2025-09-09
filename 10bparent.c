#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    const int SIZE = 4096;
    pid_t pid;
    int shm_fd;
    void *ptr;

    if (argc < 3) {
        printf("Error: Minimum of two arguments must be passed!\n");
        exit(1);
    }

    int start, end;
    sscanf(argv[1], "%d", &start);
    sscanf(argv[2], "%d", &end);

    if (start < 2) {
        printf("Error input: %d\n", start);
        return 0;
    }

    pid = fork();
    if (pid == 0) {
        // child process
        execlp("./child", "child", argv[1], argv[2], NULL);
        perror("execlp failed");
        exit(1);
    } else if (pid > 0) {
        // parent process
        wait(NULL);
        printf("\n[PARENT] Child complete!\n");

        shm_fd = shm_open("VSS", O_RDONLY, 0666);
        ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

        printf("[PARENT] Prime numbers from %d to %d:\n", start, end);
        printf("%s\n", (char *)ptr);

        shm_unlink("VSS"); // cleanup
    } else {
        perror("fork failed");
        exit(1);
    }

    return 0;
}