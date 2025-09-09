#include <stdio.h>
#include <stdlib.h>

typedef struct process {
    int Id, AT, BT, CT, TAT, WT, flag;
} pro;

pro p[15];

void swap(pro *a, pro *b) {
    pro temp = *a;
    *a = *b;
    *b = temp;
}

void sort(int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].AT > p[j + 1].AT) {
                swap(&p[j], &p[j + 1]);
            }
        }
    }
}

int main() {
    int n, tempBT[15], total_WT = 0, total_TAT = 0, quantum;
    float avg_WT = 0, avg_TAT = 0;

    printf("\nEnter the number of processes:\n");
    scanf("%d", &n);

    printf("\nEnter the arrival time and burst time of the process:\n");
    printf("AT BT\n");
    for (int i = 0; i < n; i++) {
        p[i].Id = (i + 1);
        scanf("%d%d", &p[i].AT, &p[i].BT);
        tempBT[i] = p[i].BT;
        p[i].flag = 0;
    }

    printf("\nEnter the time quantum:\n");
    scanf("%d", &quantum);

    sort(n);

    int completed = 0, curIndex, curTime = 0;
    int *waitQueue = (int *)malloc(1000 * sizeof(int)); // large enough
    int front = 0, rear = -1;

    // start with first process if arrival time is 0, else wait for it
    curTime = p[0].AT;
    rear++;
    waitQueue[rear] = 0;
    p[0].flag = 1;

    printf("\nGantt Chart:\n");

    while (completed != n) {
        if (front > rear) {  // queue empty, CPU idle
            curTime++;
            for (int i = 0; i < n; i++) {
                if (p[i].flag == 0 && p[i].AT <= curTime) {
                    rear++;
                    waitQueue[rear] = i;
                    p[i].flag = 1;
                }
            }
            continue;
        }

        curIndex = waitQueue[front];
        front++;

        if (p[curIndex].BT > quantum) {
            p[curIndex].BT -= quantum;
            curTime += quantum;
            printf("| P%d(%d) %d ", p[curIndex].Id, quantum, curTime);
        } else {
            curTime += p[curIndex].BT;
            printf("| P%d(%d) %d ", p[curIndex].Id, p[curIndex].BT, curTime);
            p[curIndex].BT = 0;
            p[curIndex].CT = curTime;
            p[curIndex].TAT = p[curIndex].CT - p[curIndex].AT;
            total_TAT += p[curIndex].TAT;
            p[curIndex].WT = p[curIndex].TAT - tempBT[p[curIndex].Id - 1];
            total_WT += p[curIndex].WT;
            completed++;
        }

        // enqueue new arrivals up to curTime
        for (int i = 0; i < n; i++) {
            if (p[i].flag == 0 && p[i].AT <= curTime && p[i].BT > 0) {
                rear++;
                waitQueue[rear] = i;
                p[i].flag = 1;
            }
        }

        // if still remaining, requeue current
        if (p[curIndex].BT > 0) {
            rear++;
            waitQueue[rear] = curIndex;
        }
    }

    avg_TAT = (float)total_TAT / n;
    avg_WT = (float)total_WT / n;

    // Printing the table of processes with details
    printf("\n\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].Id, p[i].AT, tempBT[i], p[i].CT, p[i].TAT, p[i].WT);
    }

    printf("\nAverage TAT = %.2f\nAverage WT = %.2f\n", avg_TAT, avg_WT);

    free(waitQueue);
    return 0;
}
