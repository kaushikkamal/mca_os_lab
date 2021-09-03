#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int PID, AT, BT, CT, TAT, WT, isCompleted;
} PROCESS;

typedef struct
{
    int processNumber;
    PROCESS *processList;
} PROCESSES;

void sortByAT(PROCESSES *);

int SRJF(PROCESSES *);

int main()
{
    int i, processNumber, res;
    PROCESSES *p;

    printf("Enter the no of processes: ");
    scanf("%d", &processNumber);

    p->processList = (PROCESS *)malloc(sizeof(PROCESS) * processNumber);
    if (p->processList == NULL)
    {
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
        p->processList[i].isCompleted = 0;
        p->processList[i].CT = 0;
        p->processList[i].TAT = 0;
        p->processList[i].WT = 0;
        printf("\n");
    }

    sortByAT(p);

    printf("Shortest Remaining Job First\n");

    res = SRJF(p);

    if (res != 0)
    {
        printf("Unsucessful!\n");
    }

    return 0;
}

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
    int *tempBT;
    int i, target = 0, index, currentSmallestBT, curTime = 0, prev;
    float avgTAT = 0.0, avgWT = 0.0;

    tempBT = (int *)malloc(sizeof(int) * p->processNumber);
    if (tempBT == NULL)
    {
        return -1;
    }

    for (i = 0; i < p->processNumber; i++)
    {
        tempBT[i] = p->processList[i].BT;
    }

    printf("Gantt Chart : ");
    while (target < p->processNumber)
    {
        index = -1;
        currentSmallestBT = __INT_MAX__;
        for (i = 0; i < p->processNumber; i++)
        {
            if (p->processList[i].AT <= curTime && p->processList[i].isCompleted == 0)
            {
                if (tempBT[i] < currentSmallestBT)
                {
                    currentSmallestBT = tempBT[i];
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
            tempBT[index]--;
            curTime++;
            prev = index;
            if (tempBT[index] == 0)
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

    free(tempBT);

    return 0;
}
