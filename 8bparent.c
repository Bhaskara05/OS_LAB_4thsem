// parent.c
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    const int SIZE = 4096;
    int shm_fd;
    void *ptr;

    if (argc <= 1) {
        printf("Error: not passing N in command line\n");
        exit(0);
    }

    int i;
    sscanf(argv[1], "%d", &i);
    if (i < 1) {
        printf("Error input: %d\n", i);
        return 0;
    }

    pid = fork();
    if (pid == 0) { 
        // CHILD
        execlp("./child", "child", argv[1], NULL);
    } else if (pid > 0) { 
        // PARENT
        wait(NULL);
        printf("\nPARENT: child completed\n");

        shm_fd = shm_open("VSS", O_RDONLY, 0666);
        ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

        printf("Parent printing:\n");
        printf("%s\n", (char *)ptr);

        shm_unlink("VSS");
    }
    return 0;
}
// child.c

