#include <stdio.h>

typedef struct process {
    int processId;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;
    int responseTime;
} Process;

void sjfPreemptive(Process processes[], int n);

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    // Accept process details from the user
    for (int i = 0; i < n; i++) {
        printf("Process %d\n", i + 1);
        printf("Enter Arrival Time: ");
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter Burst Time: ");
        scanf("%d", &processes[i].burstTime);

        processes[i].processId = i + 1;
        processes[i].remainingTime = processes[i].burstTime; // copy burst time
        printf("\n");
    }

    sjfPreemptive(processes, n);
    return 0;
}

void sjfPreemptive(Process processes[], int n) {
    int timeProgress[200], processTrack[200], j = -1, k = -1;
    float avgWaitingTime = 0, avgTurnAroundTime = 0, avgResponseTime = 0;
    int totalWaitingTime = 0, totalTurnAroundTime = 0, totalResponseTime = 0;
    int elapsedTime = 0, remainingProcesses = n;

    timeProgress[++j] = 0;

    while (remainingProcesses) {
        int exec = -1; // index of process to execute
        int shortestBurstTime = 9999;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= elapsedTime && processes[i].remainingTime > 0) {
                if (processes[i].remainingTime < shortestBurstTime) {
                    shortestBurstTime = processes[i].remainingTime;
                    exec = i;
                }
            }
        }

        if (exec == -1) { // No process available → idle time
            processTrack[++k] = 0;
            elapsedTime++;
            timeProgress[++j] = elapsedTime;
            continue;
        }

        if (processes[exec].remainingTime == processes[exec].burstTime) {
            // First CPU allocation → Response Time
            processes[exec].responseTime = elapsedTime - processes[exec].arrivalTime;
        }

        // Execute process for 1 unit
        processes[exec].remainingTime--;
        elapsedTime++;
        processTrack[++k] = processes[exec].processId;
        timeProgress[++j] = elapsedTime;

        if (processes[exec].remainingTime == 0) {
            // Process completed
            processes[exec].completionTime = elapsedTime;
            processes[exec].turnAroundTime = processes[exec].completionTime - processes[exec].arrivalTime;
            processes[exec].waitingTime = processes[exec].turnAroundTime - processes[exec].burstTime;

            totalTurnAroundTime += processes[exec].turnAroundTime;
            totalWaitingTime += processes[exec].waitingTime;
            totalResponseTime += processes[exec].responseTime;

            remainingProcesses--;
        }
    }

    avgTurnAroundTime = (float)totalTurnAroundTime / n;
    avgWaitingTime = (float)totalWaitingTime / n;
    avgResponseTime = (float)totalResponseTime / n;

    printf("\nObservation Table\n");
    printf("PID\tAT\tBT\tCT\tTT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               processes[i].processId,
               processes[i].arrivalTime,
               processes[i].burstTime,
               processes[i].completionTime,
               processes[i].turnAroundTime,
               processes[i].waitingTime,
               processes[i].responseTime);
    }

    printf("\nGantt Chart\n(P0 --> idle)\n");
    for (int i = 0; i <= k; i++) {
        if (processTrack[i] == 0)
            printf("| P0\t");
        else
            printf("| P%d\t", processTrack[i]);
    }
    printf("|\n");

    for (int i = 0; i <= j; i++) {
        printf("%d\t", timeProgress[i]);
    }
    printf("\n");

    printf("\nAverage Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnAroundTime);
    printf("Average Response Time: %.2f\n", avgResponseTime);
}
