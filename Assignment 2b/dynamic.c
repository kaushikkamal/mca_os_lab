#include <stdio.h>
#include <stdlib.h>

typedef struct process
{
    int PID, AT, BT, WT, TAT, RT;
} PROCESS;

typedef struct processes
{
    int processNumber;
    PROCESS *processList;
} PROCESSES;

void sortProcessByAT(PROCESSES *p)
{
    int i, j;
    PROCESS temp;

    for (i = 0; i < p->processNumber; i++)
    {
        for (j = 1; j < p->processNumber - i; j++)
        {
            if (p->processList[j - 1].AT > p->processList[j].AT)
            {
                temp = p->processList[j - 1];
                p->processList[j] = p->processList[j - 1];
                p->processList[j - 1] = temp;
            }
        }
    }
}

int RR(PROCESSES *p, int TQ)
{
    int i, j, time, remain, flag = 0;
    float avgWT = 0.0, avgTAT = 0.0;

    time = 0;
    i = 0;
    remain = p->processNumber;

    printf("Gantt Chart\n");
    printf("0");

    while (remain)
    {
        if (p->processList[i].RT <= TQ && p->processList[i].RT > 0)
        {
            time = time + p->processList[i].RT;
            printf(" - P%d - %d", p->processList[i].PID, time);
            p->processList[i].RT = 0;
            flag = 1;
        }
        else if (p->processList[i].RT > 0)
        {
            p->processList[i].RT = p->processList[i].RT - TQ;
            time = time + TQ;
            printf(" - P%d - %d", p->processList[i].PID, time);
        }
        if (p->processList[i].RT == 0 && flag == 1)
        {
            remain--;
            p->processList[i].TAT = time - p->processList[i].AT;
            p->processList[i].WT = time - p->processList[i].AT - p->processList[i].BT;
            avgWT = avgWT + time - p->processList[i].AT - p->processList[i].BT;
            avgTAT = avgTAT + time - p->processList[i].AT;
            flag = 0;
        }

        if (i == p->processNumber - 1)
        {
            i = 0;
        }
        else if (p->processList[i + 1].AT <= time)
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

    for (i = 0; i < p->processNumber; i++)
    {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p->processList[i].PID, p->processList[i].AT, p->processList[i].BT, p->processList[i].TAT, p->processList[i].WT);
    }

    printf("\n");
    printf("Average Waiting Time : %.2f\n", avgWT / p->processNumber);
    printf("Average Turn Around Time : %.2f\n", avgTAT / p->processNumber);
}

int main()
{
    int i, processNumber, res, TQ;
    PROCESSES *p;

    printf("Enter the no of processes: ");
    scanf("%d", &processNumber);

    p->processList = (PROCESS *)malloc(processNumber * sizeof(PROCESS));

    if (p->processList == NULL)
    {
        printf("Error");
        return -1;
    }

    p->processNumber = processNumber;

    for (i = 0; i < p->processNumber; i++)
    {
        printf("For Process P%d\n", i + 1);
        printf("Arrival Time : ");
        scanf("%d", &p->processList[i].AT);
        printf("Burst Time : ");
        scanf("%d", &p->processList[i].BT);
        p->processList[i].PID = i + 1;
        p->processList[i].RT = p->processList[i].BT;
        printf("\n");
    }

    sortProcessByAT(p);

    printf("Enter Time Quantum : ");
    scanf("%d", &TQ);
    printf("\n");

    printf("Round Robin\n");

    res = RR(p, TQ);
    if (res != 0)
    {
        printf("Unsucessful!\n");
    }

    return 0;
}
