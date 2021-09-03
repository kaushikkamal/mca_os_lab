#include <stdio.h>
#include <stdlib.h>

typedef struct process
{
    int PID, AT, BT, WT, TAT, RT;
} PROCESS;

typedef struct processes
{
    int noOfProcesses;
    PROCESS *list;
} PROCESSES;

void sortProcessByArrivalTime(PROCESSES *p)
{
    int i, j;
    PROCESS temp;
    for (i = 0; i < p->noOfProcesses; i++)
    {
        for (j = 1; j < p->noOfProcesses - i; j++)
        {
            if (p->list[j - 1].AT > p->list[j].AT)
            {
                temp = p->list[j - 1];
                p->list[j] = p->list[j - 1];
                p->list[j - 1] = temp;
            }
        }
    }
}

int main()
{
    int i, j, numProcess, time, remain, flag = 0, TQ;
    float avgWT = 0.0, avgTAT = 0.0;
    PROCESSES *p;

    // PROCESS process[100];

    // printf("Enter Number Of Processes : ");
    // scanf("%d", &numProcess);
    // remain = numProcess;

    printf("Enter the no of processes: ");
    scanf("%d", &numProcess);
   
    p->list = (PROCESS *)malloc(numProcess * sizeof(PROCESS));
   
    if (p->list == NULL)
    {
        printf("Error");
        return -1;
    }
 
    p->noOfProcesses = numProcess;
 
    for (i = 0; i < p->noOfProcesses; i++)
    {
        printf("For Process P%d\n", i + 1);
        printf("Arrival Time : ");
        scanf("%d", &p->list[i].AT);
        printf("Burst Time : ");
        scanf("%d", &p->list[i].BT);
        p->list[i].PID = i + 1;
        p->list[i].RT = p->list[i].BT;
        printf("\n");
    }

    sortProcessByArrivalTime(p);

    printf("Enter Time Quantum : ");
    scanf("%d", &TQ);
    printf("\n");

    time = 0;
    i = 0;

    printf("Gantt Chart\n");
    printf("0");

    while (remain)
    {
        if (p->list[i].RT <= TQ && p->list[i].RT > 0)
        {
            time = time + p->list[i].RT;
            printf(" - P%d - %d", p->list[i].PID, time);
            p->list[i].RT = 0;
            flag = 1;
        }
        else if (p->list[i].RT > 0)
        {
            p->list[i].RT = p->list[i].RT - TQ;
            time = time + TQ;
            printf(" - P%d - %d", p->list[i].PID, time);
        }
        if (p->list[i].RT == 0 && flag == 1)
        {
            remain--;
            p->list[i].TAT = time - p->list[i].AT;
            p->list[i].WT = time - p->list[i].AT - p->list[i].BT;
            avgWT = avgWT + time - p->list[i].AT - p->list[i].BT;
            avgTAT = avgTAT + time - p->list[i].AT;
            flag = 0;
        }

        if (i == numProcess - 1)
        {
            i = 0;
        }
        else if (p->list[i + 1].AT <= time)
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
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p->list[i].PID, p->list[i].AT, p->list[i].BT, p->list[i].TAT, p->list[i].WT);
    }

    printf("\n");
    printf("Average Waiting Time : %.2f\n", avgWT / numProcess);
    printf("Average Turn Around Time : %.2f\n", avgTAT / numProcess);

    return 0;
}
