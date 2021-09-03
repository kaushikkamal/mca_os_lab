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
    int priority;
    int processId;
} PROCESS;

typedef struct processes
{
    int noOfProcesses;
    PROCESS *list;
} PROCESSES;

typedef struct node
{
    PROCESS *data;
    int priority;
    struct node *next;
} NODE;

typedef struct priorityQueue
{
    NODE *front, *rear;
} PRIORITYQUEUE;

int isEmpty(PRIORITYQUEUE *pq)
{
    return (pq->front == NULL || pq->rear == NULL);
}

int rearrange(PRIORITYQUEUE *pq)
{
    NODE *temp, *highestPriority, *prevNode;

    temp = (NODE *)malloc(sizeof(NODE));
    highestPriority = (NODE *)malloc(sizeof(NODE));
    prevNode = (NODE *)malloc(sizeof(NODE));

    temp = pq->front;
    highestPriority = pq->front;
    prevNode = NULL;

    while (temp != NULL)
    {
        if (temp->next != NULL && temp->next->priority > highestPriority->priority)
        {
            prevNode = temp;
            highestPriority = temp->next;
        }
        temp = temp->next;
    }

    if (prevNode != NULL)
    {
        if (highestPriority->next == NULL)
        {
            pq->rear = prevNode;
        }
        prevNode->next = highestPriority->next;
        highestPriority->next = pq->front;
        pq->front = highestPriority;
    }

    return 0;
}

int enqueue(PRIORITYQUEUE *pq, PROCESS *data, int priority)
{
    NODE *temp;
    temp = (NODE *)malloc(sizeof(NODE));

    temp->data = data;
    temp->priority = priority;
    temp->next = NULL;

    if (isEmpty(pq))
    {
        pq->front = temp;
        pq->rear = temp;
    }
    else
    {
        pq->rear->next = temp;
        pq->rear = temp;
        rearrange(pq);
    }

    return 0;
}

PROCESS *dequeue(PRIORITYQUEUE *pq)
{
    PROCESS *delRes;
    delRes = (PROCESS *)malloc(sizeof(PROCESS));
    NODE *temp;
    temp = (NODE *)malloc(sizeof(NODE));

    temp = pq->front;
    pq->front = pq->front->next;
    delRes = temp->data;
    free(temp);
    rearrange(pq);

    return delRes;
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

int prioritySchedulingNonPreemtive(PROCESSES *p, PRIORITYQUEUE *pq)
{
    reset(p);
    int *tempBurstTime;
    int i, curTime, check, target;
    PROCESS *curProcess;
    curProcess = (PROCESS *)malloc(sizeof(PROCESS));
    tempBurstTime = (int *)malloc(sizeof(int) * p->noOfProcesses);

    for (i = 0; i < p->noOfProcesses; i++)
    {
        tempBurstTime[i] = p->list[i].burstTime;
    }

    curTime = 0;
    target = 0;

    printf("Gantt Chart : ");
    while (target < p->noOfProcesses)
    {
        for (i = 0; i < p->noOfProcesses; i++)
        {
            if (p->list[i].arrivalTime <= curTime && p->list[i].isCompleted == FALSE)
            {
                enqueue(pq, &p->list[i], p->list[i].priority);
            }
        }

        if (!isEmpty(pq))
        {
            curProcess = dequeue(pq);
            printf("%c%d ", 'p', curProcess->processId + 1);
            while (tempBurstTime[curProcess->processId] != 0)
            {
                tempBurstTime[curProcess->processId]--;
                curTime++;
            }

            if (tempBurstTime[curProcess->processId] == 0)
            {
                target++;
                curProcess->isCompleted = TRUE;
                curProcess->completionTime = curTime;
                curProcess->turnAroundTime = curProcess->completionTime - curProcess->arrivalTime;
                curProcess->waitingTime = curProcess->turnAroundTime - curProcess->burstTime;
            }
        }
        else
        {
            curTime++;
        }

        while (!isEmpty(pq))
        {
            dequeue(pq);
        }
    }

    displayAvg(p);
    free(tempBurstTime);

    return 0;
}

int prioritySchedulingPreemptive(PROCESSES *p, PRIORITYQUEUE *pq)
{
    reset(p);
    int *tempBurstTime;
    int i, curTime, target, prev;
    PROCESS *curProcess;
    curProcess = (PROCESS *)malloc(sizeof(PROCESS));
    tempBurstTime = (int *)malloc(sizeof(int) * p->noOfProcesses);

    for (i = 0; i < p->noOfProcesses; i++)
    {
        tempBurstTime[i] = p->list[i].burstTime;
    }

    curTime = 0;
    target = 0;
    prev = -1;

    printf("Gantt Chart : ");
    while (target < p->noOfProcesses)
    {
        for (i = 0; i < p->noOfProcesses; i++)
        {
            if (p->list[i].arrivalTime <= curTime && p->list[i].isCompleted == FALSE)
            {
                enqueue(pq, &p->list[i], p->list[i].priority);
            }
        }

        if (!isEmpty(pq))
        {
            curProcess = dequeue(pq);
            if (prev != curProcess->processId)
            {
                printf("%c%d ", 'p', curProcess->processId + 1);
            }
            tempBurstTime[curProcess->processId]--;
            curTime++;
            prev = curProcess->processId;
            if (tempBurstTime[curProcess->processId] == 0)
            {
                p->list[curProcess->processId].completionTime = curTime;
                p->list[curProcess->processId].turnAroundTime = p->list[curProcess->processId].completionTime - p->list[curProcess->processId].arrivalTime;
                p->list[curProcess->processId].waitingTime = p->list[curProcess->processId].turnAroundTime - p->list[curProcess->processId].burstTime;
                p->list[curProcess->processId].isCompleted = TRUE;
                target++;
            }
        }
        else
        {
            curTime++;
        }

        while (!isEmpty(pq))
        {
            dequeue(pq);
        }
    }

    displayAvg(p);
    free(tempBurstTime);

    return 0;
}

int main()
{
    PROCESSES *p;
    PRIORITYQUEUE pq;
    pq.front = NULL;
    pq.rear = NULL;

    int i, lim, at, bt, pr;

    printf("Enter the no of processes: ");
    scanf("%d", &lim);

    p->list = (PROCESS *)malloc(sizeof(PROCESS) * lim);
    p->noOfProcesses = lim;

    for (i = 0; i < p->noOfProcesses; i++)
    {
        printf("Enter the Arrival and Burst time of p%d ", i + 1);
        scanf("%d %d", &at, &bt);
        printf("Enter the Priority of p%d ", i + 1);
        scanf("%d", &pr);
        p->list[i].arrivalTime = at;
        p->list[i].burstTime = bt;
        p->list[i].isCompleted = FALSE;
        p->list[i].completionTime = 0;
        p->list[i].turnAroundTime = 0;
        p->list[i].waitingTime = 0;
        p->list[i].processId = i;
        p->list[i].priority = pr;
    }

    basicSort(p);

    printf("\n");
    printf("Priority Scheduling Non Preemtive\n");
    prioritySchedulingNonPreemtive(p, &pq);
    printf("\n");
    printf("Priority Scheduling Preemtive\n");
    prioritySchedulingPreemptive(p, &pq);
    printf("\n");

    return 0;
}