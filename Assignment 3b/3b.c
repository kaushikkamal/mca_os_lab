#include <stdio.h>
#include <stdlib.h>

typedef struct process
{
    int PID, priority, AT, BT, CT, TAT, WT, isDone;
} PROCESS;

typedef struct
{
    int processNumber;
    PROCESS *processList;
} PROCESSES;

typedef struct node
{
    int priority;
    PROCESS *data;
    struct node *next;
} NODE;

typedef struct
{
    NODE *FRONT, *REAR;
} PRIORITYQUEUE;

int isEmpty(PRIORITYQUEUE *);
int sortByAT(PROCESSES *);
int arrangeByPriority(PRIORITYQUEUE *);
int enqueue(PRIORITYQUEUE *, PROCESS *, int);
PROCESS *dequeue(PRIORITYQUEUE *);
int reset(PROCESSES *);
int displayAvg(PROCESSES *);
int prioritySchedulingNonPreemtive(PROCESSES *, PRIORITYQUEUE *);
int prioritySchedulingPreemptive(PROCESSES *, PRIORITYQUEUE *);

int main()
{
    PROCESSES *p;
    PRIORITYQUEUE pq;
    pq.FRONT = NULL;
    pq.REAR = NULL;

    int i, processNumber;

    printf("Enter the number of processes: ");
    scanf("%d", &processNumber);

    p = (PROCESSES *)malloc(sizeof(PROCESSES));
    p->processList = (PROCESS *)malloc(sizeof(PROCESS) * processNumber);

    if (p == NULL || p->processList == NULL)
    {
        return -1;
    }

    p->processNumber = processNumber;

    for (i = 0; i < p->processNumber; i++)
    {
        printf("For Process P%d\n", i + 1);
        printf("Priority : ");
        scanf("%d", &p->processList[i].priority);
        printf("Arrival Time : ");
        scanf("%d", &p->processList[i].AT);
        printf("Burst Time : ");
        scanf("%d", &p->processList[i].BT);
        p->processList[i].PID = i;
        p->processList[i].isDone = 0;
        p->processList[i].CT = 0;
        p->processList[i].TAT = 0;
        p->processList[i].WT = 0;

        printf("\n");
    }

    sortByAT(p);

    printf("\nPriority Scheduling (Non Preemptive)\n\n");
    prioritySchedulingNonPreemtive(p, &pq);

    printf("\nPriority Scheduling (Preemptive)\n\n");
    prioritySchedulingPreemptive(p, &pq);

    return 0;
}

int isEmpty(PRIORITYQUEUE *pq)
{
    return (pq->FRONT == NULL || pq->REAR == NULL);
}

int sortByAT(PROCESSES *p)
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
    return 0;
}

int arrangeByPriority(PRIORITYQUEUE *pq)
{
    NODE *temp, *highestPriority, *previousNode;

    temp = (NODE *)malloc(sizeof(NODE));
    highestPriority = (NODE *)malloc(sizeof(NODE));

    if (temp == NULL || highestPriority == NULL)
    {
        return -1;
    }

    temp = pq->FRONT;
    highestPriority = pq->FRONT;
    previousNode = NULL;

    while (temp != NULL)
    {
        if (temp->next != NULL && temp->next->priority > highestPriority->priority)
        {
            previousNode = temp;
            highestPriority = temp->next;
        }
        temp = temp->next;
    }

    if (previousNode != NULL)
    {
        if (highestPriority->next == NULL)
        {
            pq->REAR = previousNode;
        }
        previousNode->next = highestPriority->next;
        highestPriority->next = pq->FRONT;
        pq->FRONT = highestPriority;
    }

    return 0;
}

int enqueue(PRIORITYQUEUE *pq, PROCESS *data, int priority)
{
    NODE *temp;
    temp = (NODE *)malloc(sizeof(NODE));
    if (temp == NULL)
    {
        return -1;
    }

    temp->data = data;
    temp->priority = priority;
    temp->next = NULL;

    if (isEmpty(pq))
    {
        pq->FRONT = temp;
        pq->REAR = temp;
    }
    else
    {
        pq->REAR->next = temp;
        pq->REAR = temp;
        arrangeByPriority(pq);
    }

    return 0;
}

PROCESS *dequeue(PRIORITYQUEUE *pq)
{
    PROCESS *deletedProcess;
    deletedProcess = (PROCESS *)malloc(sizeof(PROCESS));
    NODE *temp;
    temp = (NODE *)malloc(sizeof(NODE));

    temp = pq->FRONT;
    pq->FRONT = pq->FRONT->next;
    deletedProcess = temp->data;
    free(temp);
    arrangeByPriority(pq);

    return deletedProcess;
}

int reset(PROCESSES *p)
{
    int i;
    for (i = 0; i < p->processNumber; i++)
    {
        p->processList[i].CT = 0;
        p->processList[i].isDone = 0;
        p->processList[i].TAT = 0;
        p->processList[i].WT = 0;
    }
    return 0;
}

int displayAvg(PROCESSES *p)
{
    int i;
    float avgTAT = 0.0, avgWT = 0.0;

    printf("\n\n");
    printf("Process\t  Arrival Time\tBurst Time\tTurn Around Time\tWaiting Time\n");

    for (i = 0; i < p->processNumber; i++)
    {
        avgWT += p->processList[i].WT;
        avgTAT += p->processList[i].TAT;
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p->processList[i].PID, p->processList[i].AT, p->processList[i].BT, p->processList[i].TAT, p->processList[i].WT);
    }

    printf("\n\n");
    printf("Average Waiting time : %.2f\n", avgWT / p->processNumber);
    printf("Average Turn around time : %.2f\n", avgTAT / p->processNumber);

    return 0;
}

int prioritySchedulingNonPreemtive(PROCESSES *p, PRIORITYQUEUE *pq)
{
    reset(p);
    int *tempBT;
    int i, time = 0, check, target = 0;
    PROCESS *currentProcess;

    currentProcess = (PROCESS *)malloc(sizeof(PROCESS));
    tempBT = (int *)malloc(sizeof(int) * p->processNumber);

    for (i = 0; i < p->processNumber; i++)
    {
        tempBT[i] = p->processList[i].BT;
    }

    printf("Gantt Chart : ");
    while (target < p->processNumber)
    {
        for (i = 0; i < p->processNumber; i++)
        {
            if (p->processList[i].AT <= time && p->processList[i].isDone == 0)
            {
                enqueue(pq, &p->processList[i], p->processList[i].priority);
            }
        }

        if (!isEmpty(pq))
        {
            currentProcess = dequeue(pq);
            printf("P%d ", currentProcess->PID + 1);
            while (tempBT[currentProcess->PID] != 0)
            {
                tempBT[currentProcess->PID]--;
                time++;
            }

            if (tempBT[currentProcess->PID] == 0)
            {
                target++;
                currentProcess->isDone = 1;
                currentProcess->CT = time;
                currentProcess->TAT = currentProcess->CT - currentProcess->AT;
                currentProcess->WT = currentProcess->TAT - currentProcess->BT;
            }
        }
        else
        {
            time++;
        }

        while (!isEmpty(pq))
        {
            dequeue(pq);
        }
    }

    displayAvg(p);
    free(tempBT);

    return 0;
}

int prioritySchedulingPreemptive(PROCESSES *p, PRIORITYQUEUE *pq)
{
    reset(p);
    int *tempBT;
    int i, time, target, previous;
    PROCESS *currentProcess;
    currentProcess = (PROCESS *)malloc(sizeof(PROCESS));
    tempBT = (int *)malloc(sizeof(int) * p->processNumber);

    for (i = 0; i < p->processNumber; i++)
    {
        tempBT[i] = p->processList[i].BT;
    }

    time = 0;
    target = 0;
    previous = -1;

    printf("Gantt Chart : ");
    while (target < p->processNumber)
    {
        for (i = 0; i < p->processNumber; i++)
        {
            if (p->processList[i].AT <= time && p->processList[i].isDone == 0)
            {
                enqueue(pq, &p->processList[i], p->processList[i].priority);
            }
        }

        if (!isEmpty(pq))
        {
            currentProcess = dequeue(pq);
            if (previous != currentProcess->PID)
            {
                printf("P%d ", currentProcess->PID + 1);
            }
            tempBT[currentProcess->PID]--;
            time++;
            previous = currentProcess->PID;
            if (tempBT[currentProcess->PID] == 0)
            {
                p->processList[currentProcess->PID].CT = time;
                p->processList[currentProcess->PID].TAT = p->processList[currentProcess->PID].CT - p->processList[currentProcess->PID].AT;
                p->processList[currentProcess->PID].WT = p->processList[currentProcess->PID].TAT - p->processList[currentProcess->PID].BT;
                p->processList[currentProcess->PID].isDone = 1;
                target++;
            }
        }
        else
        {
            time++;
        }

        while (!isEmpty(pq))
        {
            dequeue(pq);
        }
    }

    displayAvg(p);
    free(tempBT);

    return 0;
}
