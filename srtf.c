#include <stdio.h>

#define MAX 15
int main()
{
    int number[MAX], burst[MAX], arrival[MAX], n, i, j, rem[MAX], ttime = 0, min, premin = n - 1, turnaround[MAX];
    printf("Enter Number Of Processes : ");
    scanf("%d", &n);
    printf("\nEnter arrival time , burst time for each process : ");
    for (i = 0; i < n; i++)
    {
        number[i] = i + 1;
        printf("P%d : ", i + 1);
        scanf("%d %d", &arrival[i], &burst[i]);
        rem[i] = burst[i];
        ttime = ttime + burst[i];
    }

    printf("Gantt Chart\n");

    for (i = 0; i <= ttime; i++)
    {
        min = 0;
        for (j = 0; j < n; j++)
        {
            if (arrival[j] <= i && rem[j] < rem[min] && rem[j] != 0)
            {
                min = j;
            }
        }
        if (premin != min || i == 0)
        {
            printf("%d P%d ", i, number[min]);  
        }
        rem[min] -= 1;
        if (rem[min] == 0)
        {
            turnaround[min] = i - arrival[min] + 1;
        }
        premin = min;
    }
    printf("%d\n", ttime);
    printf("Turnaround time: \n");
    for (i = 0; i < n; i++)
    {
        printf("P%d : %d\n", i + 1, turnaround[i]);
    }
    printf("Waiting time: \n");
    for (i = 0; i < n; i++)
    {
        printf("P%d : %d\n", i + 1, turnaround[i] - burst[i]);
    }
    return 0;
}