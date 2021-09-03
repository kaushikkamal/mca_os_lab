#include <stdio.h>
#include <stdlib.h>

typedef struct process
{
    int process_id, priority, arrival_time, burst_time, completion_time, turn_around_time, waiting_time, is_complete;
} PROCESS;

typedef struct
{
    int process_number;
    PROCESS *process_list;
} PROCESSES;

typedef struct node
{
    int priority;
    PROCESS *data;
    struct node *next;
} NODE;

typedef struct
{
    NODE *front, *rear;
} PRIORITYQUEUE;

int isEmpty(PRIORITYQUEUE *pq)
{
    return (pq->front == NULL || pq->rear == NULL);
}

int sortByAT(PROCESSES *p)
{
    int i, j;
    PROCESS temp;
    for (i = 0; i < p->process_number; i++)
    {
        for (j = 1; j < p->process_number - i; j++)
        {
            if (p->process_list[j - 1].arrival_time > p->process_list[j].arrival_time)
            {
                temp = p->process_list[j - 1];
                p->process_list[j] = p->process_list[j - 1];
                p->process_list[j - 1] = temp;
            }
        }
    }
    return 0;
}

int arrangeByPriority(PRIORITYQUEUE *pq)
{
    NODE *temp, *high_priority, *previous_node;

    temp = (NODE *)malloc(sizeof(NODE));
    high_priority = (NODE *)malloc(sizeof(NODE));

    if (temp == NULL || high_priority == NULL)
    {
        return -1;
    }

    temp = pq->front;
    high_priority = pq->front;
    previous_node = NULL;

    while (temp != NULL)
    {
        if (temp->next != NULL && temp->next->priority > high_priority->priority)
        {
            previous_node = temp;
            high_priority = temp->next;
        }
        temp = temp->next;
    }

    if (previous_node != NULL)
    {
        if (high_priority->next == NULL)
        {
            pq->rear = previous_node;
        }
        previous_node->next = high_priority->next;
        high_priority->next = pq->front;
        pq->front = high_priority;
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
        pq->front = temp;
        pq->rear = temp;
    }
    else
    {
        pq->rear->next = temp;
        pq->rear = temp;
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

    temp = pq->front;
    pq->front = pq->front->next;
    deletedProcess = temp->data;
    free(temp);
    arrangeByPriority(pq);

    return deletedProcess;
}

int reset(PROCESSES *p)
{
    int i;
    for (i = 0; i < p->process_number; i++)
    {
        p->process_list[i].completion_time = 0;
        p->process_list[i].is_complete = 0;
        p->process_list[i].turn_around_time = 0;
        p->process_list[i].waiting_time = 0;
    }
    return 0;
}

int displayAvg(PROCESSES *p)
{
    int i;
    float avgTAT = 0.0, avgWT = 0.0;

    printf("\n\n");
    printf("Process\tAT\tBT\tTAT\tWT\n");

    for (i = 0; i < p->process_number; i++)
    {
        avgWT += p->process_list[i].waiting_time;
        avgTAT += p->process_list[i].turn_around_time;
        printf("P%d\t%d\t%d\t%d\t%d\n", p->process_list[i].process_id, p->process_list[i].arrival_time, p->process_list[i].burst_time, p->process_list[i].turn_around_time, p->process_list[i].waiting_time);
    }

    printf("\n\n");
    printf("Average Waiting time : %.2f\n", avgWT / p->process_number);
    printf("Average Turn around time : %.2f\n", avgTAT / p->process_number);

    return 0;
}

int prioritySchedulingNonPreemtive(PROCESSES *p, PRIORITYQUEUE *pq)
{
    reset(p);
    int *tempBT;
    int i, time = 0, check, target = 0;
    PROCESS *currentProcess;

    currentProcess = (PROCESS *)malloc(sizeof(PROCESS));
    tempBT = (int *)malloc(sizeof(int) * p->process_number);

    for (i = 0; i < p->process_number; i++)
    {
        tempBT[i] = p->process_list[i].burst_time;
    }

    printf("Gantt Chart : ");
    while (target < p->process_number)
    {
        for (i = 0; i < p->process_number; i++)
        {
            if (p->process_list[i].arrival_time <= time && p->process_list[i].is_complete == 0)
            {
                enqueue(pq, &p->process_list[i], p->process_list[i].priority);
            }
        }

        if (!isEmpty(pq))
        {
            currentProcess = dequeue(pq);
            printf("P%d ", currentProcess->process_id + 1);
            while (tempBT[currentProcess->process_id] != 0)
            {
                tempBT[currentProcess->process_id]--;
                time++;
            }

            if (tempBT[currentProcess->process_id] == 0)
            {
                target++;
                currentProcess->is_complete = 1;
                currentProcess->completion_time = time;
                currentProcess->turn_around_time = currentProcess->completion_time - currentProcess->arrival_time;
                currentProcess->waiting_time = currentProcess->turn_around_time - currentProcess->burst_time;
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
    tempBT = (int *)malloc(sizeof(int) * p->process_number);

    for (i = 0; i < p->process_number; i++)
    {
        tempBT[i] = p->process_list[i].burst_time;
    }

    time = 0;
    target = 0;
    previous = -1;

    printf("Gantt Chart : ");
    while (target < p->process_number)
    {
        for (i = 0; i < p->process_number; i++)
        {
            if (p->process_list[i].arrival_time <= time && p->process_list[i].is_complete == 0)
            {
                enqueue(pq, &p->process_list[i], p->process_list[i].priority);
            }
        }

        if (!isEmpty(pq))
        {
            currentProcess = dequeue(pq);
            if (previous != currentProcess->process_id)
            {
                printf("P%d ", currentProcess->process_id + 1);
            }
            tempBT[currentProcess->process_id]--;
            time++;
            previous = currentProcess->process_id;
            if (tempBT[currentProcess->process_id] == 0)
            {
                p->process_list[currentProcess->process_id].completion_time = time;
                p->process_list[currentProcess->process_id].turn_around_time = p->process_list[currentProcess->process_id].completion_time - p->process_list[currentProcess->process_id].arrival_time;
                p->process_list[currentProcess->process_id].waiting_time = p->process_list[currentProcess->process_id].turn_around_time - p->process_list[currentProcess->process_id].burst_time;
                p->process_list[currentProcess->process_id].is_complete = 1;
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

int main()
{
    PROCESSES *p;
    PRIORITYQUEUE pq;
    pq.front = NULL;
    pq.rear = NULL;

    int i, process_number;

    printf("Enter the number of processes: ");
    scanf("%d", &process_number);

    p = (PROCESSES *)malloc(sizeof(PROCESSES));
    p->process_list = (PROCESS *)malloc(sizeof(PROCESS) * process_number);

    if (p == NULL || p->process_list == NULL)
    {
        return -1;
    }

    p->process_number = process_number;

    for (i = 0; i < p->process_number; i++)
    {
        printf("For Process P%d\n", i + 1);
        printf("Priority : ");
        scanf("%d", &p->process_list[i].priority);
        printf("Arrival Time : ");
        scanf("%d", &p->process_list[i].arrival_time);
        printf("Burst Time : ");
        scanf("%d", &p->process_list[i].burst_time);
        p->process_list[i].process_id = i;
        p->process_list[i].is_complete = 0;
        p->process_list[i].completion_time = 0;
        p->process_list[i].turn_around_time = 0;
        p->process_list[i].waiting_time = 0;

        printf("\n");
    }

    sortByAT(p);

    printf("\nPriority Scheduling (Non Preemtive)\n\n");
    prioritySchedulingNonPreemtive(p, &pq);

    printf("\nPriority Scheduling (Preemtive)\n\n");
    prioritySchedulingPreemptive(p, &pq);

    return 0;
}