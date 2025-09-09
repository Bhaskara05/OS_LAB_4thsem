#include <stdio.h>
#include <stdlib.h>

typedef struct process {
    int Id, AT, BT, CT, TAT, WT, priority;
} pro;

pro p[15];

int main() {
    int n, tempBT[15], total_WT = 0, total_TAT = 0;
    float avg_WT = 0, avg_TAT = 0;

    printf("\nEnter the number of processes:\n");
    scanf("%d", &n);

    printf("\nEnter the arrival time, burst time and priority of the process:\n");
    printf("AT BT P\n");
    for (int i = 0; i < n; i++) {
        p[i].Id = (i + 1);
        scanf("%d%d%d", &p[i].AT, &p[i].BT, &p[i].priority);
        tempBT[i] = p[i].BT;
    }

    printf("\nGantt Chart:\n");

    int minIndex, minPriority, completed = 0, curTime = 0;

    // Print initial time
    printf("%d", curTime);

    while (completed != n) {
        minIndex = -1;
        minPriority = 9999;

        for (int i = 0; i < n; i++) {
            if (p[i].AT <= curTime && p[i].BT > 0) {
                if (p[i].priority < minPriority || 
                   (p[i].priority == minPriority && (minIndex == -1 || p[i].AT < p[minIndex].AT))) {
                    minPriority = p[i].priority;
                    minIndex = i;
                }
            }
        }

        if (minIndex == -1) {
            // CPU is idle
            curTime++;
            printf(" | idle | %d", curTime);
        } else {
            // Run the selected process for 1 unit
            p[minIndex].BT--;
            curTime++;

            printf(" | P%d | %d", p[minIndex].Id, curTime);

            if (p[minIndex].BT == 0) {
                completed++;
                p[minIndex].CT = curTime;
                p[minIndex].TAT = p[minIndex].CT - p[minIndex].AT;
                p[minIndex].WT = p[minIndex].TAT - tempBT[minIndex];

                total_TAT += p[minIndex].TAT;
                total_WT += p[minIndex].WT;
            }
        }
    }

    avg_TAT = (float)total_TAT / n;
    avg_WT = (float)total_WT / n;

    printf("\n\nProcess Table:\n");
    printf("PID\tAT\tBT\tP\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", 
               p[i].Id, p[i].AT, tempBT[i], p[i].priority,
               p[i].CT, p[i].TAT, p[i].WT);
    }

    printf("\nAverage Turnaround Time = %.2f", avg_TAT);
    printf("\nAverage Waiting Time = %.2f\n", avg_WT);

    return 0;
}
