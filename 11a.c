// gcc thread.c -pthread -o thread
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int sm = 0, prod = 1;

void *sum(void *parm) {
    int i, n;
    n = atoi((char *)parm);
    printf("Inside sum thread\n");
    for (i = 1; i <= n; i++) {
        sm += i;
    }
    printf("Sum thread completed\n");
    pthread_exit(0);
}

void *mul(void *parm) {
    int i, n;
    n = atoi((char *)parm);
    printf("Inside mul thread\n");
    for (i = 2; i <= n; i++) {
        prod *= i;
    }
    printf("Mul thread completed\n");
    pthread_exit(0);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <number>\n", argv[0]);
        return 1;
    }

    pthread_t T1, T2;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_create(&T1, &attr, sum, argv[1]);
    pthread_create(&T2, &attr, mul, argv[1]);

    pthread_join(T1, NULL);
    pthread_join(T2, NULL);

    printf("Inside main thread\n");
    printf("Sum = %d\n", sm);
    printf("Factorial = %d\n", prod);

    return 0;
}
