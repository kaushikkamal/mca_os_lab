#include <stdio.h>
#include <stdlib.h>

typedef struct process
{
    int PID, AT, BT, isCompleted, TAT, WT, CT;
} PROCESS;

typedef struct processes
{
    int noOfProcesses;
    PROCESS *list;
} PROCESSES;

void basicSort(PROCESSES *p)
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

int displayAvg(PROCESSES *p)
{
    int m;
    float tat = 0, wt = 0;
    for (m = 0; m < p->noOfProcesses; m++)
    {
        wt += p->list[m].WT;
        tat += p->list[m].TAT;
    }

    printf("\n");
    printf("Average Waiting time : %.2f\n", wt / p->noOfProcesses);
    printf("Average Turn around time : %.2f\n", tat / p->noOfProcesses);

    return 0;
}

int longestJobFirst(PROCESSES *p)
{
    int *tempBurstTime;
    int i, target = 0, index, curLargestBt;
    int curTime = 0, prev;
    tempBurstTime = (int *)malloc(sizeof(int) * p->noOfProcesses);

    for (i = 0; i < p->noOfProcesses; i++)
    {
        tempBurstTime[i] = p->list[i].BT;
    }

    printf("Gantt Chart : ");
    while (target < p->noOfProcesses)
    {
        index = -1;
        curLargestBt = 0;
        for (i = 0; i < p->noOfProcesses; i++)
        {
            if (p->list[i].AT <= curTime && p->list[i].isCompleted == 0)
            {
                if (tempBurstTime[i] > curLargestBt)
                {
                    curLargestBt = tempBurstTime[i];
                    index = i;
                }
            }
        }
        if (index != -1)
        {
            printf("%c%d ", 'p', p->list[index].PID + 1);
            while (tempBurstTime[index] != 0)
            {
                tempBurstTime[index]--;
                curTime++;
            }
            if (tempBurstTime[index] == 0)
            {
                p->list[index].CT = curTime;
                p->list[index].TAT = p->list[index].CT - p->list[index].AT;
                p->list[index].WT = p->list[index].TAT - p->list[index].BT;
                p->list[index].isCompleted = 1;
                target++;
            }
        }
        else
        {
            curTime++;
        }
    }

    displayAvg(p);
    free(tempBurstTime);

    return 0;
}

int main()
{
    PROCESSES *p;
    int i, lim, at, bt;

    printf("Enter the no of processes: ");
    scanf("%d", &lim);

    p->list = (PROCESS *)malloc(sizeof(PROCESS) * lim);
    p->noOfProcesses = lim;

    for (i = 0; i < p->noOfProcesses; i++)
    {
        printf("Enter the Arrival and Burst time of p%d ", i + 1);
        scanf("%d %d", &at, &bt);
        p->list[i].AT = at;
        p->list[i].BT = bt;
        p->list[i].isCompleted = 0;
        p->list[i].CT = 0;
        p->list[i].TAT = 0;
        p->list[i].WT = 0;
        p->list[i].PID = i;
    }

    basicSort(p);

    printf("\n");
    printf("Longest Job First\n");
    longestJobFirst(p);
    printf("\n");
    return 0;
}