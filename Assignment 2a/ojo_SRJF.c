#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int process_id, arrival_time, burst_time, completion_time, turn_around_time, waiting_time, is_complete;
} PROCESS;

typedef struct
{
    int process_number;
    PROCESS *process_list;
} PROCESSES;

void sort(PROCESSES *p)
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
}

int shortestRemainingJobFirst(PROCESSES *p)
{
    int *temp_BT;
    int i, target = 0, index, smallest_BT, current_time = 0, prev;
    float avg_TAT = 0.0, avg_WT = 0.0;

    temp_BT = (int *)malloc(sizeof(int) * p->process_number);
    for (i = 0; i < p->process_number; i++)
    {
        temp_BT[i] = p->process_list[i].burst_time;
    }
    printf("Gantt Chart : ");
    while (target < p->process_number)
    {
        index = -1;
        smallest_BT = __INT_MAX__;
        for (i = 0; i < p->process_number; i++)
        {
            if (p->process_list[i].arrival_time <= current_time && p->process_list[i].is_complete == 0)
            {
                if (temp_BT[i] < smallest_BT)
                {
                    smallest_BT = temp_BT[i];
                    index = i;
                }
            }
        }
        if (index != -1)
        {
            if (prev != index)
            {
                printf("P%d ", p->process_list[index].process_id);
            }
            temp_BT[index]--;
            current_time++;
            prev = index;
            if (temp_BT[index] == 0)
            {
                p->process_list[index].completion_time = current_time;
                p->process_list[index].turn_around_time = p->process_list[index].completion_time - p->process_list[index].arrival_time;
                p->process_list[index].waiting_time = p->process_list[index].turn_around_time - p->process_list[index].burst_time;
                p->process_list[index].is_complete = 1;
                target++;
            }
        }
        else
        {
            current_time++;
        }
    }

    printf("\n\n");
    printf("Process\tAT\tBT\tTAT\tWT\n");

    for (i = 0; i < p->process_number; i++)
    {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p->process_list[i].process_id, p->process_list[i].arrival_time, p->process_list[i].burst_time, p->process_list[i].turn_around_time, p->process_list[i].waiting_time);
    }

    for (i = 0; i < p->process_number; i++)
    {
        avg_WT += p->process_list[i].waiting_time;
        avg_TAT += p->process_list[i].turn_around_time;
    }

    avg_WT /= p->process_number;
    avg_TAT /= p->process_number;
    printf("\n");

    printf("Average Waiting time : %.2f\n", avg_WT);
    printf("Average Turn around time : %.2f\n", avg_TAT);

    free(temp_BT);

    return 0;
}

int main()
{
    int i, process_number;
    PROCESSES *p;

    printf("Enter the no of processes: ");
    scanf("%d", &process_number);

    p->process_list = (PROCESS *)malloc(sizeof(PROCESS) * process_number);
    p->process_number = process_number;

    for (i = 0; i < p->process_number; i++)
    {
        printf("Arrival Time and Burst Time for Process P%d\n", i + 1);
        scanf("%d %d", &p->process_list[i].arrival_time, &p->process_list[i].burst_time);
        p->process_list[i].process_id = i + 1;
        p->process_list[i].is_complete = 0;
        p->process_list[i].completion_time = 0;
        p->process_list[i].turn_around_time = 0;
        p->process_list[i].waiting_time = 0;
    }
    sort(p);
    shortestRemainingJobFirst(p);
    return 0;
}
