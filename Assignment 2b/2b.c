#include <stdio.h>

typedef struct
{
    int PNO, AT, BT, WT, TAT, RT;
} PROCESS;

void sortProcessByArrivalTime(PROCESS[], int);

int main()
{
    int i, j, numProcess, time, remain, flag = 0, TQ;
    float avgWT = 0.0, avgTAT = 0.0;
    PROCESS process[100];

    printf("Enter Number Of Processes : ");
    scanf("%d", &numProcess);
    remain = numProcess;

    for (i = 0; i < numProcess; i++)
    {
        printf("For Process P%d\n", i + 1);
        printf("Arrival Time : ");
        scanf("%d", &process[i].AT);
        printf("Burst Time : ");
        scanf("%d", &process[i].BT);
        process[i].PNO = i + 1;
        process[i].RT = process[i].BT;
        printf("\n");
    }

    sortProcessByArrivalTime(process, numProcess);

    printf("Enter Time Quantum : ");
    scanf("%d", &TQ);
    printf("\n");

    time = 0;
    i = 0;

    printf("Gantt Chart\n");
    printf("0");

    while (remain)
    {
        if (process[i].RT <= TQ && process[i].RT > 0)
        {
            time = time + process[i].RT;
            printf(" - P%d - %d", process[i].PNO, time);
            process[i].RT = 0;
            flag = 1;
        }
        else if (process[i].RT > 0)
        {
            process[i].RT = process[i].RT - TQ;
            time = time + TQ;
            printf(" - P%d - %d", process[i].PNO, time);
        }
        if (process[i].RT == 0 && flag == 1)
        {
            remain--;
            process[i].TAT = time - process[i].AT;
            process[i].WT = time - process[i].AT - process[i].BT;
            avgWT = avgWT + time - process[i].AT - process[i].BT;
            avgTAT = avgTAT + time - process[i].AT;
            flag = 0;
        }

        if (i == numProcess - 1)
        {
            i = 0;
        }
        else if (process[i + 1].AT <= time)
        {
            i++;
        }
        else
        {
            i = 0;
        }
    }

    printf("\n\n");

    printf("Process\t  Arrival Time\tBurst Time\tTurn Around Time\tWaiting Time\n");

    for (i = 0; i < numProcess; i++)
    {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", process[i].PNO, process[i].AT, process[i].BT, process[i].TAT, process[i].WT);
    }

    printf("\n");
    printf("Average Waiting Time : %.2f\n", avgWT / numProcess);
    printf("Average Turn Around Time : %.2f\n", avgTAT / numProcess);

    return 0;
}

void sortProcessByArrivalTime(PROCESS process[], int n)
{
    int i, j;
    PROCESS temp;
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (process[i].AT > process[j].AT)
            {
                temp = process[i];
                process[i] = process[j];
                process[j] = temp;
            }
        }
    }
}
