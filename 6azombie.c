//---- zombie.c ---- //
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
        printf("[CHILD] Exiting.\n");
        exit(0);   // Child exits immediately → becomes zombie until parent calls wait()
    } else {
        // Parent process
        printf("[PARENT] This is the parent process.\n");
        my_pid = getpid();
        parent_pid = getppid();
        printf("[PARENT] My pid is %d\n", my_pid);
        printf("[PARENT] My parent's pid is %d\n", parent_pid);
        printf("[PARENT] Sleeping for 10 seconds.\n");
        sleep(10); // Parent sleeps → child is already dead → child becomes zombie
        printf("[PARENT] Child pid = %d has ended, but it still has an entry in process table.\n", child_pid);
        printf("[PARENT] It is a zombie process.\n");
    }

    return 0;
}
