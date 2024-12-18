#include <stdio.h>
#include <limits.h>
#define maxsize 8

int main()
{
    int size = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &size);

    int pid[maxsize]; // Process IDs
    int at[maxsize];  // Arrival times
    int bt[maxsize];  // Burst times
    int wt[maxsize];  // Waiting times
    int tat[maxsize]; // Turnaround times
    int ct[maxsize];  // Completion times
    int completed[maxsize] = {0}; // Track if a process is completed
    int order[maxsize]; // To track the order of processes for Gantt chart

    // Input for process IDs
    printf("Enter process IDs:\n");
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &pid[i]);
    }
    // Input for arrival times
    printf("Enter arrival times:\n");
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &at[i]);
    }
    // Input for burst times
    printf("Enter burst times:\n");
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &bt[i]);
    }

    int currentTime = 0, completedProcesses = 0, index = 0;

    while (completedProcesses < size)
    {
        int shortestJobIndex = -1;
        int shortestBurstTime = INT_MAX;

        // Find the process with the shortest burst time that has arrived
        for (int i = 0; i < size; i++)
        {
            if (at[i] <= currentTime && !completed[i] && bt[i] < shortestBurstTime)
            {
                shortestBurstTime = bt[i];
                shortestJobIndex = i;
            }
        }

        if (shortestJobIndex == -1)
        {
            currentTime++; // No process is ready to execute, increment time
            continue;
        }

        // Process the selected shortest job
        order[index++] = shortestJobIndex; // Store the process order for the Gantt chart
        currentTime += bt[shortestJobIndex];
        ct[shortestJobIndex] = currentTime; // Completion time of the selected process
        tat[shortestJobIndex] = ct[shortestJobIndex] - at[shortestJobIndex]; // Turnaround time
        wt[shortestJobIndex] = tat[shortestJobIndex] - bt[shortestJobIndex]; // Waiting time
        completed[shortestJobIndex] = 1; // Mark the process as completed
        completedProcesses++;
    }

    // Display the process information with turnaround and waiting times
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < size; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], at[i], bt[i], wt[i], tat[i]);
    }

    // Calculate average waiting time and average turnaround time
    float avgwt = 0, avgtat = 0;
    for (int i = 0; i < size; i++)
    {
        avgwt += wt[i];
        avgtat += tat[i];
    }
    avgwt /= size;
    avgtat /= size;

    printf("\nAverage Waiting Time: %.2f", avgwt);
    printf("\nAverage Turnaround Time: %.2f\n", avgtat);

    // Display Gantt chart
    printf("\nGantt Chart:\n");
    for (int i = 0; i < index; i++)
    {
        printf("|   P%d\t", pid[order[i]]);
    }
    printf("|\n");
    // Print the timeline under the Gantt chart
    printf("%d", at[order[0]]);
    for (int i = 0; i < index; i++)
    {
        printf("\t%d", ct[order[i]]);
    }
    printf("\n");

    return 0;
}
