#include <stdio.h>

struct process
{
    int process_number, arrival_time, burst_time, turn_around_time, waiting_time, response_time;
};

int main()
{
    int i, j, N, time, p_left, flag = 0, time_quantum;
    struct process a[50];
    float avgwt = 0, avgtt = 0;
    printf("Number Of Processes : ");
    scanf("%d", &N);
    p_left = N;
    for (i = 0; i < N; i++)
    {
        printf("Enter arrival time for Process P%d : ", i + 1);
        scanf("%d", &a[i].arrival_time);
        printf("Enter burst time for Process P%d : ", i + 1);
        scanf("%d", &a[i].burst_time);
        a[i].process_number = i + 1;
        a[i].response_time = a[i].burst_time;
        printf("\n");
    }

    printf("Enter Time Quantum : ");
    scanf("%d", &time_quantum);
    printf("\n");
    printf("Gantt Chart\n");
    for (time = 0, i = 0; p_left != 0;)
    {
        if (a[i].response_time <= time_quantum && a[i].response_time > 0)
        {
            time = time + a[i].response_time;
            printf(" P%d", a[i].process_number);
            a[i].response_time = 0;
            flag = 1;
        }
        else if (a[i].response_time > 0)
        {
            a[i].response_time = a[i].response_time - time_quantum;
            time = time + time_quantum;
            printf(" P%d", a[i].process_number);
        }
        if (a[i].response_time == 0 && flag == 1)
        {
            p_left--;
            a[i].turn_around_time = time - a[i].arrival_time;
            a[i].waiting_time = time - a[i].arrival_time - a[i].burst_time;
            avgwt = avgwt + time - a[i].arrival_time - a[i].burst_time;
            avgtt = avgtt + time - a[i].arrival_time;
            flag = 0;
        }
        if (i == N - 1)
            i = 0;
        else if (a[i + 1].arrival_time <= time)
            i++;
        else
            i = 0;
    }
    printf("\n\n");

    printf("PNO\tAT\tBT\tTAT\tWT\n");
    for (i = 0; i < N; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\n", a[i].process_number, a[i].arrival_time, a[i].burst_time, a[i].turn_around_time, a[i].waiting_time);
    }
    printf("\n");
    avgwt = avgwt / N;
    avgtt = avgtt / N;
    printf("Average Waiting Time : %f\n", avgwt);
    printf("Average Turnaround Time : %f\n", avgtt);
    return 0;
}