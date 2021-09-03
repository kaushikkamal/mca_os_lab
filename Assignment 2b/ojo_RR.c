#include <stdio.h>
#include <stdlib.h>

typedef struct process
{
    int process_id, arrival_time, burst_time, waiting_time, turn_around_time, response_time;
} PROCESS;

typedef struct processes
{
    int process_number;
    PROCESS *process_list;
} PROCESSES;

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

int RR(PROCESSES *p, int TQ)
{
    int i, j, time, remain, flag = 0;
    float avgWT = 0.0, avgTAT = 0.0;

    time = 0;
    i = 0;
    remain = p->process_number;

    printf("Gantt Chart\n");

    while (remain)
    {
        if (p->process_list[i].response_time <= TQ && p->process_list[i].response_time > 0)
        {
            time = time + p->process_list[i].response_time;
            printf(" P%d ", p->process_list[i].process_id);
            p->process_list[i].response_time = 0;
            flag = 1;
        }
        else if (p->process_list[i].response_time > 0)
        {
            p->process_list[i].response_time = p->process_list[i].response_time - TQ;
            time = time + TQ;
            printf(" P%d ", p->process_list[i].process_id);
        }
        if (p->process_list[i].response_time == 0 && flag == 1)
        {
            remain--;
            p->process_list[i].turn_around_time = time - p->process_list[i].arrival_time;
            p->process_list[i].waiting_time = time - p->process_list[i].arrival_time - p->process_list[i].burst_time;
            avgWT = avgWT + time - p->process_list[i].arrival_time - p->process_list[i].burst_time;
            avgTAT = avgTAT + time - p->process_list[i].arrival_time;
            flag = 0;
        }

        if (i == p->process_number - 1)
        {
            i = 0;
        }
        else if (p->process_list[i + 1].arrival_time <= time)
        {
            i++;
        }
        else
        {
            i = 0;
        }
    }

    printf("\n\n");
    printf("Process\tAT\tBT\tTAT\tWT\n");

    for (i = 0; i < p->process_number; i++)
    {
        avgWT += p->process_list[i].waiting_time;
        avgTAT += p->process_list[i].turn_around_time;
        printf("P%d\t%d\t%d\t%d\t%d\n", p->process_list[i].process_id, p->process_list[i].arrival_time, p->process_list[i].burst_time, p->process_list[i].turn_around_time, p->process_list[i].waiting_time);
    }

    printf("\n");
    printf("Average Waiting Time : %.2f\n", avgWT / p->process_number);
    printf("Average Turn Around Time : %.2f\n", avgTAT / p->process_number);

    return 0;
}

int main()
{
    int i, process_number, TQ;
    PROCESSES *p;

    printf("Enter the number of processes: ");
    scanf("%d", &process_number);

    p->process_list = (PROCESS *)malloc(process_number * sizeof(PROCESS));

    p->process_number = process_number;

    for (i = 0; i < p->process_number; i++)
    {
        printf("Arrival Time and Burst Time for Procees %d: ", i + 1);
        scanf("%d %d", &p->process_list[i].arrival_time, &p->process_list[i].burst_time);
        p->process_list[i].process_id = i + 1;
        p->process_list[i].response_time = p->process_list[i].burst_time;
    }

    sortByAT(p);

    printf("Enter Time Quantum : ");
    scanf("%d", &TQ);
    printf("\n");

    printf("Round Robin\n");

    RR(p, TQ);

    return 0;
}
