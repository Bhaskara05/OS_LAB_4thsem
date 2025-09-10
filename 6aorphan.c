//---- orphan.c ---- //
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    pid_t child_pid, my_pid, parent_pid;

    child_pid = fork();
    if (child_pid < 0) {
        printf("Fork failed. Exiting!\n");
        exit(1);
    }

    if (child_pid == 0) {
        // Child process
        printf("[CHILD] This is the child process.\n");
        my_pid = getpid();
        parent_pid = getppid();
        printf("[CHILD] My pid is %d\n", my_pid);
        printf("[CHILD] My parent's pid is %d\n", parent_pid);
        printf("[CHILD] Sleeping for 10 seconds.\n");
        sleep(10);
        parent_pid = getppid(); // After parent exits, update
        printf("[CHILD] My parent ended. Now my parent pid is %d (adopted by init).\n", parent_pid);
        printf("[CHILD] I am an orphan process.\n");
    } else {
        // Parent process
        printf("[PARENT] This is the parent process.\n");
        my_pid = getpid();
        parent_pid = getppid();
        printf("[PARENT] My pid is %d\n", my_pid);
        printf("[PARENT] My parent's pid is %d\n", parent_pid);
        printf("[PARENT] Exiting immediately.\n");
        exit(0);   // Parent exits before child → child becomes orphan
    }

    return 0;
}