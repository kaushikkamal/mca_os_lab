#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct
{
    int PNO, AT, BT, CT, TAT, WT;
} PROCESS;

typedef struct
{
    int n;
    PROCESS *list;
} PROCESS_LIST;

int insert_data(PROCESS_LIST *process_list, int n)
{
    process_list->n = n;
    process_list->list = (PROCESS *)malloc(n * sizeof(PROCESS));

    if (process_list->list == NULL)
    {
        return 1;
    }

    PROCESS p1 = {1, 0, 53};
    PROCESS p2 = {2, 0, 17};
    PROCESS p3 = {3, 0, 68};
    PROCESS p4 = {4, 0, 24};

    int i;

    //  1
    process_list->list[0].PNO = 1;
    (process_list->list)[0].AT = 0;
    (process_list->list)[0].BT = 53;

    //  2
    process_list->list[1].PNO = 2;
    (process_list->list)[1].AT = 0;
    (process_list->list)[1].BT = 17;

    //  3
    process_list->list[2].PNO = 3;
    (process_list->list)[2].AT = 0;
    (process_list->list)[2].BT = 68;

    //  4
    process_list->list[3].PNO = 4;
    (process_list->list)[3].AT = 0;
    (process_list->list)[3].BT = 24;

    // for (i = 0; i < n; i++)
    // {
    //     process_list->list[i].PNO = i + 1;
    //     printf("\nEnter the arrival time of process %d: ", i + 1);
    //     scanf("%d", &(process_list->list)[i].AT);
    //     printf("\nEnter the burst time of process %d: ", i + 1);
    //     scanf("%d", &(process_list->list)[i].BT);
    //     printf("\n");
    // }

    return 0;
}

int display_data(PROCESS_LIST *process_list)
{
    int i;
    for (i = 0; i < process_list->n; i++)
    {
        printf("\nProcess no. : %d ", i + 1);
        printf("\nArrival Time : %d ", (process_list->list)[i].AT);
        printf("\nBurst Time : %d ", (process_list->list)[i].BT);
        printf("\n");
    }
    return 0;
}

int main()
{
    int TQ = 20;
    PROCESS_LIST process_list;

    int n, result;
    do
    {
        printf("\nEnter the number of processes: ");
        scanf("%d", &n);

        if (n > 0)
            break;

        printf("\nEntered number should be greater than 0\n");

    } while (n <= 0);

    result = insert_data(&process_list, n);
    if (result)
    {
        printf("\nInsertion cannot be done!");
        return 0;
    }
    result = display_data(&process_list);
    return 0;
}
