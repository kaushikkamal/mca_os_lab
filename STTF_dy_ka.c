#include <stdio.h>
#include <stdlib.h>

typedef struct process
{
    int PID, AT, BT, CT, TAT, WT, isCompleted;
} PROCESS;

typedef struct processes
{
    int processNumber;
    PROCESS *processList;
} PROCESSES;

void sortByAT(PROCESSES *p)
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

int shortestRemainingJobFirst(PROCESSES *p)
{
    int *tempBurstTime;
    int i, target = 0, index, curSmallestBt,curTime = 0, prev;
    float avgTAT = 0.0, avgWT = 0.0;
    
    tempBurstTime = (int *)malloc(sizeof(int) * p->processNumber);

    for (i = 0; i < p->processNumber; i++)
    {
        tempBurstTime[i] = p->processList[i].BT;
    }

    printf("Gantt Chart : ");
    while (target < p->processNumber)
    {
        index = -1;
        curSmallestBt = __INT_MAX__;
        for (i = 0; i < p->processNumber; i++)
        {
            if (p->processList[i].AT <= curTime && p->processList[i].isCompleted == 0)
            {
                if (tempBurstTime[i] < curSmallestBt)
                {
                    curSmallestBt = tempBurstTime[i];
                    index = i;
                }
            }
        }
        if (index != -1)
        {
            if (prev != index)
            {
                printf("P%d ", p->processList[index].PID);
            }
            tempBurstTime[index]--;
            curTime++;
            prev = index;
            if (tempBurstTime[index] == 0)
            {
                p->processList[index].CT = curTime;
                p->processList[index].TAT = p->processList[index].CT - p->processList[index].AT;
                p->processList[index].WT = p->processList[index].TAT - p->processList[index].BT;
                p->processList[index].isCompleted = 1;
                target++;
            }
        }
        else
        {
            curTime++;
        }
    }

    for (i = 0; i < p->processNumber; i++)
    {
        avgWT += p->processList[i].WT;
        avgTAT += p->processList[i].TAT;
    }

    printf("\n");
    printf("Average Waiting time : %.2f\n", avgWT / p->processNumber);
    printf("Average Turn around time : %.2f\n", avgTAT / p->processNumber);

    free(tempBurstTime);

    return 0;
}

int main()
{
    PROCESSES *p;
    int i, lim, at, bt;

    printf("Enter the no of processes: ");
    scanf("%d", &lim);

    p->processList = (PROCESS *)malloc(sizeof(PROCESS) * lim);
    p->processNumber = lim;

    for (i = 0; i < p->processNumber; i++)
    {
        printf("For Process P%d\n", i + 1);
        printf("Arrival Time : ");
        scanf("%d", &p->processList[i].AT);
        printf("Burst Time : ");
        scanf("%d", &p->processList[i].BT);
        p->processList[i].PID = i + 1;
        p->processList[i].isCompleted = 0;
        p->processList[i].CT = 0;
        p->processList[i].TAT = 0;
        p->processList[i].WT = 0;
        printf("\n");
    }

    sortByAT(p);
   
    printf("Shortest Remaining Job First\n");
    shortestRemainingJobFirst(p);

    return 0;
}