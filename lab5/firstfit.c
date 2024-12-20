#include <stdio.h>
#define maxsize 10
int main()
{
    int partitions[maxsize], partitionSize[maxsize], allocation[maxsize], wastage[maxsize];
    int numPartitions, numProcesses;

    printf("Enter the number of partitions: ");
    scanf("%d", &numPartitions);

    printf("Enter the sizes of the partitions:\n");
    for (int i = 0; i < numPartitions; i++)
    {
        printf("Partition %d: ", i + 1);
        scanf("%d", &partitions[i]);
        partitionSize[i] = partitions[i]; // Store the original sizes for display later
        allocation[i] = -1;               // Initialize all allocations to -1, meaning no process is allocated
    }

    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    int processes[maxsize];
    printf("Enter the sizes of the processes:\n");
    for (int i = 0; i < numProcesses; i++)
    {
        printf("Process %d: ", i + 1);
        scanf("%d", &processes[i]);
    }

    // First Fit Allocation
    for (int i = 0; i < numProcesses; i++)
    {
        for (int j = 0; j < numPartitions; j++)
        {
            if (partitions[j] >= processes[i])
            {
                allocation[j] = i;             // Allocate process to this partition
                partitions[j] -= processes[i]; // Reduce available partition size
                wastage[j] = partitions[j];    // Calculate wastage
                break;                         // Move to the next process once allocated
            }
        }
    }

    // display results
    for (int i = 0; i < numPartitions; i++)
    {
        printf("  %d\t", partitionSize[i]);
    }
    printf("\n");

    for (int i = 0; i < numPartitions; i++)
    {
        if (allocation[i] != -1)
        {
            printf("| %d\t", allocation[i] + 1);
        }
        else
        {
            printf("| -\t");
        }
    }
    int i = 0;
    int sum = 0;
    while (i < numPartitions)
    {
        if (allocation[i] != -1)
        {
            sum += wastage[i];
        }
        i++;
    }
    printf("|\nTotal wastage =%dKB", sum);
    return 0;
}
