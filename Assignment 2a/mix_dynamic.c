#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct process
{
    int arrivalTime;
    int burstTime;
    int isCompleted;
    int turnAroundTime;
    int waitingTime;
    int completionTime;
    int processId;
} PROCESS;

typedef struct processes
{
    int noOfProcesses;
    PROCESS *list;
} PROCESSES;

void swap(PROCESS *a, PROCESS *b)
{
    PROCESS temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void basicSort(PROCESSES *p)
{
    int i, j;
    for (i = 0; i < p->noOfProcesses; i++)
    {
        for (j = 1; j < p->noOfProcesses - i; j++)
        {
            if (p->list[j - 1].arrivalTime > p->list[j].arrivalTime)
            {
                swap(&p->list[j - 1], &p->list[j]);
            }
        }
    }
}

int reset(PROCESSES *p)
{
    int i;
    for (i = 0; i < p->noOfProcesses; i++)
    {
        p->list[i].completionTime = 0;
        p->list[i].isCompleted = FALSE;
        p->list[i].turnAroundTime = 0;
        p->list[i].waitingTime = 0;
    }
    return 0;
}

int displayAvg(PROCESSES *p)
{
    int m;
    float tat = 0, wt = 0;
    for (m = 0; m < p->noOfProcesses; m++)
    {
        wt += p->list[m].waitingTime;
        tat += p->list[m].turnAroundTime;
    }

    printf("\n");
    printf("Average Waiting time : %.2f\n", wt / p->noOfProcesses);
    printf("Average Turn around time : %.2f\n", tat / p->noOfProcesses);

    return 0;
}

int longestJobFirst(PROCESSES *p)
{
    reset(p);
    int *tempBurstTime;
    int i, target = 0, index, curLargestBt;
    int curTime = 0, prev;
    tempBurstTime = (int *)malloc(sizeof(int) * p->noOfProcesses);

    for (i = 0; i < p->noOfProcesses; i++)
    {
        tempBurstTime[i] = p->list[i].burstTime;
    }

    printf("Gantt Chart : ");
    while (target < p->noOfProcesses)
    {
        index = -1;
        curLargestBt = 0;
        for (i = 0; i < p->noOfProcesses; i++)
        {
            if (p->list[i].arrivalTime <= curTime && p->list[i].isCompleted == FALSE)
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
            printf("%c%d ", 'p', p->list[index].processId + 1);
            while (tempBurstTime[index] != 0)
            {
                tempBurstTime[index]--;
                curTime++;
            }
            if (tempBurstTime[index] == 0)
            {
                p->list[index].completionTime = curTime;
                p->list[index].turnAroundTime = p->list[index].completionTime - p->list[index].arrivalTime;
                p->list[index].waitingTime = p->list[index].turnAroundTime - p->list[index].burstTime;
                p->list[index].isCompleted = TRUE;
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

int shortestRemainingJobFirst(PROCESSES *p)
{
    reset(p);
    int *tempBurstTime;
    int i, target = 0, index, curSmallestBt;
    int curTime = 0, prev;
    tempBurstTime = (int *)malloc(sizeof(int) * p->noOfProcesses);

    for (i = 0; i < p->noOfProcesses; i++)
    {
        tempBurstTime[i] = p->list[i].burstTime;
    }

    printf("Gantt Chart : ");
    while (target < p->noOfProcesses)
    {
        index = -1;
        curSmallestBt = __INT_MAX__;
        for (i = 0; i < p->noOfProcesses; i++)
        {
            if (p->list[i].arrivalTime <= curTime && p->list[i].isCompleted == FALSE)
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
                printf("%c%d ", 'p', p->list[index].processId + 1);
            }
            tempBurstTime[index]--;
            curTime++;
            prev = index;
            if (tempBurstTime[index] == 0)
            {
                p->list[index].completionTime = curTime;
                p->list[index].turnAroundTime = p->list[index].completionTime - p->list[index].arrivalTime;
                p->list[index].waitingTime = p->list[index].turnAroundTime - p->list[index].burstTime;
                p->list[index].isCompleted = TRUE;
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
    int i,lim, at, bt;

    printf("Enter the no of processes: ");
    scanf("%d", &lim);

    p->list = (PROCESS *)malloc(sizeof(PROCESS) * lim);
    p->noOfProcesses = lim;

    for (i = 0; i < p->noOfProcesses; i++)
    {
        printf("Enter the Arrival and Burst time of p%d ", i + 1);
        scanf("%d %d", &at, &bt);
        p->list[i].arrivalTime = at;
        p->list[i].burstTime = bt;
        p->list[i].isCompleted = FALSE;
        p->list[i].completionTime = 0;
        p->list[i].turnAroundTime = 0;
        p->list[i].waitingTime = 0;
        p->list[i].processId = i;
    }

    basicSort(p);

    printf("\n");
    printf("Longest Job First\n");
    longestJobFirst(p);
    printf("\n");
    printf("Shortest Remaining Job First\n");
    shortestRemainingJobFirst(p);
    printf("\n");

    return 0;
}