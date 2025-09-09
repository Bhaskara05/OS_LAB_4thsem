//parent.c
#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct {
    int n;
    int arr[100];
} pack_t;

int main() {
    key_t key = 1234;
    int shmid = shmget(key, sizeof(pack_t), 0666 | IPC_CREAT);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    pack_t* shm_ptr = (pack_t*) shmat(shmid, NULL, 0);
    if (shm_ptr == (void*) -1) {
        perror("shmat");
        exit(1);
    }

    printf("[PARENT] Created shared memory with key = %d, id = %d\n", key, shmid);

    printf("[PARENT] Enter n: ");
    scanf("%d", &shm_ptr->n);

    pid_t child_pid = fork();
    if (child_pid == 0) {
        // Child process will run child.c
        execlp("./child", "./child", NULL);
        perror("execlp"); // If execlp fails
        exit(1);
    } else if (child_pid > 0) {
        wait(NULL); // Wait for child to complete
        printf("[PARENT] Child finished executing.\n");
        printf("[PARENT] The first %d odd numbers are:\n", shm_ptr->n);
        for (int i = 0; i < shm_ptr->n; i++)
            printf("%d ", shm_ptr->arr[i]);
        printf("\n");
    } else {
        perror("fork");
        exit(1);
    }

    shmdt((void*) shm_ptr);
    shmctl(shmid, IPC_RMID, NULL); // Delete shared memory
    printf("[PARENT] Shared Memory Deleted\n");

    return 0;
}