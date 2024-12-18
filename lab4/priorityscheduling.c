#include <stdio.h>
#define maxsize 8

int main()
{
    int size = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &size);

    int pid[maxsize];      // Process IDs
    int bt[maxsize];       // Burst times
    int priority[maxsize]; // Priorities
    int wt[maxsize];       // Waiting times
    int tat[maxsize];      // Turnaround times
    int ct[maxsize];       // Completion times

    // Input for process IDs
    printf("Enter process IDs:\n");
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &pid[i]);
    }
    // Input for burst times
    printf("Enter burst times:\n");
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &bt[i]);
    }
    // Input for priorities
    printf("Enter priorities:\n");
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &priority[i]);
    }

    // Sorting based on priority
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (priority[j] > priority[j + 1])
            {
                // Swap priorities
                int temp = priority[j];
                priority[j] = priority[j + 1];
                priority[j + 1] = temp;

                // Swap burst times
                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                // Swap process IDs
                temp = pid[j];
                pid[j] = pid[j + 1];
                pid[j + 1] = temp;
            }
        }
    }

    // Calculate waiting times and turnaround times
    wt[0] = 0; // First process has no waiting time
    for (int i = 1; i < size; i++)
    {
        wt[i] = wt[i - 1] + bt[i - 1];
    }

    for (int i = 0; i < size; i++)
    {
        tat[i] = wt[i] + bt[i];
        ct[i] = tat[i]; // Completion time is equal to turnaround time since no arrival time is considered
    }

    // Display the process information with turnaround and waiting times
    printf("\nProcess\tPriority\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < size; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], priority[i], bt[i], wt[i], tat[i]);
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
    for (int i = 0; i < size; i++)
    {
        printf("|   P%d\t", pid[i]);
    }
    printf("|\n");
    // Print the timeline under the Gantt chart
    int timeline = 0;
    printf("%d", timeline);
    for (int i = 0; i < size; i++)
    {
        timeline += bt[i];
        printf("\t%d", timeline);
    }
    printf("\n");

    return 0;
}
