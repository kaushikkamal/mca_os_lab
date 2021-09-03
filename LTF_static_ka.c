#include <stdio.h>
#include <stdlib.h>

typedef struct process
{
    int PID, AT, BT, isCompleted, TAT, WT, CT, RT;
} PROCESS;

// typedef struct processes
// {
//     int noOfProcesses;
//     PROCESS *list;
// } PROCESSES;

// void basicSort(PROCESSES *p)
// {
//     int i, j;
//     PROCESS temp;
//     for (i = 0; i < p->noOfProcesses; i++)
//     {
//         for (j = 1; j < p->noOfProcesses - i; j++)
//         {
//             if (p->list[j - 1].AT > p->list[j].AT)
//             {
//                 temp = p->list[j - 1];
//                 p->list[j] = p->list[j - 1];
//                 p->list[j - 1] = temp;
//             }
//         }
//     }
// }

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

int displayAvg(PROCESS process[], int n)
{
    int m;
    float tat = 0, wt = 0;
    for (m = 0; m < n; m++)
    {
        wt += process[m].WT;
        tat += process[m].TAT;
    }

    printf("\n");
    printf("Average Waiting time : %.2f\n", wt / n);
    printf("Average Turn around time : %.2f\n", tat / n);

    return 0;
}

int longestJobFirst(PROCESS process[], int n)
{
    int *tempBurstTime;
    int i, target = 0, index, curLargestBt;
    int curTime = 0, prev;
    tempBurstTime = (int *)malloc(sizeof(int) * n);

    for (i = 0; i < n; i++)
    {
        tempBurstTime[i] = process[i].BT;
    }

    printf("Gantt Chart : ");
    while (target < n)
    {
        index = -1;
        curLargestBt = 0;
        for (i = 0; i < n; i++)
        {
            if (process[i].AT <= curTime && process[i].isCompleted == 0)
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
            printf("%c%d ", 'p', process[index].PID);
            // printf("%c%d ", 'p', process[index].PID + 1);
            while (tempBurstTime[index] != 0)
            {
                tempBurstTime[index]--;
                curTime++;
            }
            if (tempBurstTime[index] == 0)
            {
                process[index].CT = curTime;
                process[index].TAT = process[index].CT - process[index].AT;
                process[index].WT = process[index].TAT - process[index].BT;
                process[index].isCompleted = 1;
                target++;
            }
        }
        else
        {
            curTime++;
        }
    }

    displayAvg(process, n);
    free(tempBurstTime);

    return 0;
}

int main()
{
    // PROCESSES *p;
    int i, numProcess;
    PROCESS process[100];

    printf("Enter the no of processes: ");
    scanf("%d", &numProcess);

    for (i = 0; i < numProcess; i++)
    {
        printf("For Process P%d\n", i + 1);
        printf("Arrival Time : ");
        scanf("%d", &process[i].AT);
        printf("Burst Time : ");
        scanf("%d", &process[i].BT);
        process[i].PID = i + 1;
        process[i].isCompleted = 0;
        process[i].CT = 0;
        process[i].TAT = 0;
        process[i].WT = 0;
        process[i].RT = process[i].BT;
        // time = time + process[i].BT;
        printf("\n");

        // printf("Enter the Arrival and Burst time of p%d ", i + 1);
        // scanf("%d %d", &at, &bt);
        // p->list[i].AT = at;
        // p->list[i].BT = bt;
        // p->list[i].isCompleted = 0;
        // p->list[i].CT = 0;
        // p->list[i].TAT = 0;
        // p->list[i].WT = 0;
        // p->list[i].PID = i;
    }

    // basicSort(p);

    sortProcessByArrivalTime(process, numProcess);

    printf("\n");
    printf("Longest Job First\n");
    longestJobFirst(process, numProcess);
    printf("\n");
    return 0;
}