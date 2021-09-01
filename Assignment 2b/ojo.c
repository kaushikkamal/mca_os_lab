#include <stdio.h>

struct PROCESS
{
    int process_number, arrival_time, burst_time, waiting_time, turn_around_time, response_time;
};

void sort(struct PROCESS a[], int process_number)
{
    int i, j;
    struct PROCESS temp;
    for (i = 0; i < process_number; i++)
    {
        for (j = i + 1; j < process_number; j++)
        {
            if (a[j].arrival_time < a[i].arrival_time)
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}

int main()
{
    int i, j, number_process, time_quantum, time, process_left, flag = 0;
    struct PROCESS process[50];
    float average_wt = 0.0, average_tat = 0.0;
    printf("Enter Time Quantum : ");
    scanf("%d", &time_quantum);
    printf("\nEnter Number Of Processes : ");
    scanf("%d", &number_process);
    process_left = number_process;
   
    for (i = 0; i < number_process; i++)
    {
        printf("Enter Arrival time and Burst time for Process P%d : ", i + 1);
        scanf("%d %d", &process[i].arrival_time, &process[i].burst_time);
        process[i].process_number = i + 1;
        process[i].response_time = process[i].burst_time;
    }
    sort(process, number_process);
    printf("\nGantt Chart\n");
    printf("0");
    for (time = 0, i = 0; process_left != 0;)
    {
        if (process[i].response_time <= time_quantum && process[i].response_time > 0)
        {
            time = time + process[i].response_time;
            printf(" -> P%d <- %d", process[i].process_number, time);
            process[i].response_time = 0;
            flag = 1;
        }
        else if (process[i].response_time > 0)
        {
            process[i].response_time = process[i].response_time - time_quantum;
            time = time + time_quantum;
            printf(" -> P%d <- %d", process[i].process_number, time);
        }
        if (process[i].response_time == 0 && flag == 1)
        {
            process_left--;
            process[i].turn_around_time = time - process[i].arrival_time;
            process[i].waiting_time = time - process[i].arrival_time - process[i].burst_time;
            average_wt = average_wt + time - process[i].arrival_time - process[i].burst_time;
            average_tat = average_tat + time - process[i].arrival_time;
            flag = 0;
        }

        if (i == number_process - 1)
        {
            i = 0;
        }
        else if (process[i + 1].arrival_time <= time)
        {
            i++;
        }
        else
        {
            i = 0;
        }
    }

    printf("\n\n");

    printf("PNO\tAT\tBT\tTAT\tWT\n");

    for (i = 0; i < number_process; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\n", process[i].process_number, process[i].arrival_time, process[i].burst_time, process[i].turn_around_time, process[i].waiting_time);
    }

    average_wt = average_wt / number_process;
    average_tat = average_tat / number_process;

    printf("\n");
    printf("Average Waiting Time : %f\n", average_wt);
    printf("Average Turn Around Time : %f\n", average_tat);

    return 0;
}
