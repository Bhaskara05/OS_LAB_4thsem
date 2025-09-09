#include <stdio.h>

typedef struct process {
    int processId;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;
    int finished;
    int responseTime;
} Process;

void sjfNP(Process[], int);

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    // Accept process details from the user
    for (int i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);
        printf("Enter Arrival Time: ");
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter Burst Time: ");
        scanf("%d", &processes[i].burstTime);
        processes[i].processId = i + 1;
        processes[i].finished = 0;
    }

    sjfNP(processes, n);
    return 0;
}

void sjfNP(Process processes[], int n) {
    float avgWaitingTime = 0, avgTurnAroundTime = 0, avgResponseTime = 0;
    int totalWaitingTime = 0, totalTurnAroundTime = 0, totalResponseTime = 0;
    int elapsedTime = 0;
    int remainingProcesses = n;

    printf("\nGantt Chart:\n");
    while (remainingProcesses) {
        int exec = -1;
        int shortestBurstTime = 9999;

        // Find the process with shortest burst time among those that have arrived
        for (int i = 0; i < n; i++) {
            if (!processes[i].finished && processes[i].arrivalTime <= elapsedTime) {
                if (processes[i].burstTime < shortestBurstTime) {
                    shortestBurstTime = processes[i].burstTime;
                    exec = i;
                }
            }
        }

        if (exec == -1) {
            // No process available to execute, CPU idle
            printf("(%d) | idle | (%d)\n", elapsedTime, elapsedTime + 1);
            elapsedTime++;
        } else {
            // Execute the selected process
            int startTime = elapsedTime;

            processes[exec].responseTime = elapsedTime - processes[exec].arrivalTime;
            elapsedTime += processes[exec].burstTime;
            processes[exec].completionTime = elapsedTime;
            processes[exec].turnAroundTime = processes[exec].completionTime - processes[exec].arrivalTime;
            processes[exec].waitingTime = processes[exec].turnAroundTime - processes[exec].burstTime;
            processes[exec].finished = 1;

            remainingProcesses--;

            printf("(%d) | P%d | (%d)\n", startTime, processes[exec].processId, elapsedTime);

            totalTurnAroundTime += processes[exec].turnAroundTime;
            totalWaitingTime += processes[exec].waitingTime;
            totalResponseTime += processes[exec].responseTime;
        }
    }

    avgTurnAroundTime = (float)totalTurnAroundTime / n;
    avgWaitingTime = (float)totalWaitingTime / n;
    avgResponseTime = (float)totalResponseTime / n;

    // Print process table
    printf("\nProcess Table:\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
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

    // Print averages
    printf("\nAverage Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnAroundTime);
    printf("Average Response Time: %.2f\n", avgResponseTime);
}
