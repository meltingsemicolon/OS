#include <stdio.h>
#define maxsize 8
int main() 
{
    int size = 0, quantum = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &size);

    int pid[maxsize];               // Process IDs
    int at[maxsize];                // Arrival times
    int bt[maxsize];                // Burst times
    int bt_remaining[maxsize];      // Remaining burst times
    int wt[maxsize] = {0};          // Waiting times
    int tat[maxsize];               // Turnaround times
    int ct[maxsize];                // Completion times
    int order[maxsize * maxsize];   // To store the execution order for Gantt chart
    int time_slice[maxsize * maxsize]; // To store the time slices for Gantt chart

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
        bt_remaining[i] = bt[i]; // Initialize remaining burst times
    }
    // Input for time quantum
    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    int currentTime = 0, completedProcesses = 0, index = 0;

    while (completedProcesses < size)
    {
        int process_executed = 0;

        for (int i = 0; i < size; i++)
        {
            if (bt_remaining[i] > 0 && at[i] <= currentTime)
            {
                process_executed = 1;
                order[index] = pid[i]; // Store the process ID in order for Gantt chart

                if (bt_remaining[i] > quantum)
                {
                    currentTime += quantum;
                    bt_remaining[i] -= quantum;
                    time_slice[index] = quantum; // Store the time slice used
                }
                else
                {
                    currentTime += bt_remaining[i];
                    time_slice[index] = bt_remaining[i]; // Store the time slice used
                    bt_remaining[i] = 0;
                    ct[i] = currentTime; // Completion time of the process

                    // Calculate turnaround time and waiting time correctly
                    tat[i] = ct[i] - at[i]; // Turnaround time
                    wt[i] = tat[i] - bt[i]; // Waiting time

                    completedProcesses++;
                }

                index++;
            }
        }

        if (!process_executed) {
            currentTime++; // Increment time if no process is executed
        }
    }

    // Display the process information with turnaround and waiting times
    printf("\nProcess\tArrival Time\tBurst Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < size; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], at[i], bt[i], tat[i], wt[i]);
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
        printf("|   P%d\t", order[i]);
    }
    printf("|\n");
    // Print the timeline under the Gantt chart
    int timeline = 0;
    printf("%d", timeline);
    for (int i = 0; i < index; i++)
    {
        timeline += time_slice[i];
        printf("\t%d", timeline);
    }
    printf("\n");

    return 0;
}
