#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <stdlib.h>

typedef struct {
    int n;
    int arr[100];
} pack_t;

int main() {
    key_t key = 1234;
    int shmid = shmget(key, sizeof(pack_t), 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    pack_t* shm_ptr = (pack_t*) shmat(shmid, NULL, 0);
    if (shm_ptr == (void*) -1) {
        perror("shmat");
        exit(1);
    }

    printf("[CHILD] Attached to shared memory with key = %d, id = %d\n", key, shmid);

    for (int i = 0; i < shm_ptr->n; i++)
        shm_ptr->arr[i] = 2 * i + 1;

    printf("[CHILD] Finished generating first %d odd numbers\n", shm_ptr->n);

    shmdt((void*) shm_ptr);

    return 0;
}
