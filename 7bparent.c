#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    const int SIZE = 4096;
    int shmid;
    void *ptr;

    if (argc <= 1) {
        printf("Error: not passing N in command line\n");
        return 1;
    }

    int n;
    sscanf(argv[1], "%d", &n);
    if (n < 1) {
        printf("Error input: %d\n", n);
        return 1;
    }

    // Create shared memory
    shmid = shmget((key_t)1122, SIZE, 0666 | IPC_CREAT);
    if (shmid < 0) {
        perror("shmget failed");
        return 1;
    }

    ptr = shmat(shmid, NULL, 0);
    if (ptr == (void *)-1) {
        perror("shmat failed");
        return 1;
    }

    pid = fork();
    if (pid == 0) {
        // CHILD: run fib program
        execlp("./child", "child", argv[1], NULL);
        perror("execlp failed");
        return 1;
    } else if (pid > 0) {
        // PARENT
        wait(NULL);
        printf("\nPARENT: child completed\n");
        printf("Parent printing:\n");
        printf("%s\n", (char *)ptr);

        shmdt(ptr);                   // detach
        shmctl(shmid, IPC_RMID, NULL); // remove shared memory
    } else {
        perror("fork failed");
        return 1;
    }

    return 0;
}