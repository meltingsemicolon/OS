#include <stdio.h>
#define maxsize 100

int main()
{
    int size = 0;
    printf("Enter the number of processes (max %d): ", maxsize);
    scanf("%d", &size);

    if (size > maxsize) {
        printf("Error: Maximum process limit exceeded.\n");
        return 1;
    }

    int pid[maxsize];   // Process IDs
    int at[maxsize];    // Arrival times
    int bt[maxsize];    // Burst times
    int wt[maxsize];    // Waiting times
    int tat[maxsize];   // Turnaround times
    int ct[maxsize];    // Completion times

    // Input for process IDs
    printf("Enter process IDs:\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &pid[i]);
    }

    // Input for arrival times
    printf("Enter arrival times:\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &at[i]);
    }

    // Input for burst times
    printf("Enter burst times:\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &bt[i]);
    }

    // Calculate completion time, turnaround time, and waiting time
    ct[0] = at[0] + bt[0];  
    // Completion time for first process
    tat[0] = ct[0] - at[0]; 
    // Turnaround time for first process
    wt[0] = tat[0] - bt[0]; 
    // Waiting time for first process

    for (int i = 1; i < size; i++) {
        // Ensure the current process starts either when it arrives or when the previous process finishes
        ct[i] = (ct[i - 1] > at[i]) ? (ct[i - 1] + bt[i]) : (at[i] + bt[i]);
        
        tat[i] = ct[i] - at[i];  // Turnaround time
        wt[i] = tat[i] - bt[i];  // Waiting time
    }

    // Display the process information with turnaround and waiting times
    printf("\nProcess\tArrival Time\tBurst Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < size; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], at[i], bt[i], tat[i], wt[i]);
    }

    // Calculate average waiting time and average turnaround time
    float avgwt = 0, avgtat = 0;
    for (int i = 0; i < size; i++) {
        avgwt += wt[i];
        avgtat += tat[i];
    }
    avgwt /= size;
    avgtat /= size;

    printf("\nAverage Waiting Time: %.2f", avgwt);
    printf("\nAverage Turnaround Time: %.2f\n", avgtat);

    // Display Gantt chart
    printf("\nGantt Chart:\n");
    for (int i = 0; i < size; i++) {
        printf("| P%d\t", pid[i]);
    }
    printf("|\n");
    printf("%d", at[0]);
    for (int i = 0; i < size; i++) {
        printf("\t%d", ct[i]);
    }
    printf("\n");

    return 0;
}
