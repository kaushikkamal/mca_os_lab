#include <stdio.h>

typedef struct
{
    int PID, AT, BT, WT, TAT, RT;
} PROCESS;

int main()
{
    int i, j, numProcess, min, time = 0, remain;
    PROCESS process[100];

    printf("Enter Number Of Processes : ");
    scanf("%d", &numProcess);
    remain = numProcess - 1;

    for (i = 0; i < numProcess; i++)
    {
        printf("For Process P%d\n", i + 1);
        printf("Arrival Time : ");
        scanf("%d", &process[i].AT);
        printf("Burst Time : ");
        scanf("%d", &process[i].BT);
        process[i].PID = i + 1;
        process[i].RT = process[i].BT;
        time = time + process[i].BT;
        printf("\n");
    }

    printf("Gantt Chart\n");

    // for (i = 0; i <= time; i++)
    // {
    //     min = 0;
    //     for (j = 0; j < numProcess; j++)
    //     {
    //         if (process[j].AT <= i && process[j].RT < process[min].RT && process[j].RT != 0)
    //         {
    //             min = j;
    //         }
    //     }
    //     if (remain != min || i == 0)
    //     {
    //         printf("%d - P%d - ", i, process[min].PID);
    //     }
    //     process[min].RT -= 1;
    //     if (process[min].RT == 0)
    //     {
    //         process[min].TAT = i - process[min].AT + 1;
    //     }
    //     remain = min;
    // }
    // printf("%d\n\n", time);

    printf("Process\t  Arrival Time\tBurst Time\tTurn Around Time\tWaiting Time\n");

    for (i = 0; i < numProcess; i++)
    {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", process[i].PID, process[i].AT, process[i].BT, process[i].TAT, process[i].TAT - process[i].BT);
    }

    return 0;
}