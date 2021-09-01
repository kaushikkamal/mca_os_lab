#include <stdio.h>

typedef struct
{
    int PNO, AT, BT, WT, TAT, rnt;
} PROCESS;

void sortProcessByArrivalTime(PROCESS a[], int pro)
{
    int i, j;
    PROCESS temp;
    for (i = 0; i < pro; i++)
    {
        for (j = i + 1; j < pro; j++)
        {
            if (a[i].AT > a[j].AT)
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}

int main()
{
    int i, j, numProcess, time, remain, flag = 0, TQ;
    PROCESS process[100];
    float avgWT = 0.0, avgTAT = 0.0;

    printf("Enter Number Of Processes : ");
    scanf("%d", &numProcess);
    remain = numProcess;

    for (i = 0; i < numProcess; i++)
    {
        printf("Enter Arrival time and Burst time for Process P%d : ", i + 1);
        scanf("%d%d", &process[i].AT, &process[i].BT);
        process[i].PNO = i + 1;
        process[i].rnt = process[i].BT;
    }

    sortProcessByArrivalTime(process, numProcess);

    printf("\n");
    printf("Enter Time Quantum : ");
    scanf("%d", &TQ);
    printf("\n");

    printf("Gantt Chart\n");
    printf("0");
    for (time = 0, i = 0; remain != 0;)
    {
        if (process[i].rnt <= TQ && process[i].rnt > 0)
        {
            time = time + process[i].rnt;
            printf(" -> P%d <- %d", process[i].PNO, time);
            process[i].rnt = 0;
            flag = 1;
        }
        else if (process[i].rnt > 0)
        {
            process[i].rnt = process[i].rnt - TQ;
            time = time + TQ;
            printf(" -> P%d <- %d", process[i].PNO, time);
        }
        if (process[i].rnt == 0 && flag == 1)
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

    avgWT = avgWT / numProcess;
    avgTAT = avgTAT / numProcess;

    printf("\n\n");
    printf("Average Waiting Time : %.2f\n", avgWT);
    printf("Average Turn Around Time : %.2f\n", avgTAT);

    return 0;
}
