#include <stdio.h>
#define NO_FRAMES 3
#define MAX 30

int LRU(int[], int);

int main()
{
    int numPages, frames[MAX], pages[MAX], time[MAX], flag1, flag2, i, j, pos, counter, faults;

    counter = 0;
    faults = 0;

    printf("\nEnter number of pages: ");
    scanf("%d", &numPages);

    printf("\nEnter page numbers:\n");

    for (i = 0; i < numPages; i++)
    {
        printf("%d: ", i + 1);
        scanf("%d", &pages[i]);
    }

    for (i = 0; i < NO_FRAMES; i++)
    {
        frames[i] = -1;
    }

    printf("\nLeast Recently Used (LRU) Page Replacement: \n");

    for (i = 0; i < numPages; i++)
    {
        flag1 = flag2 = 0;
        for (j = 0; j < NO_FRAMES; j++)
        {
            if (frames[j] == pages[i])
            {
                counter++;
                time[j] = counter;
                flag1 = flag2 = 1;
                break;
            }
        }

        if (flag1 == 0)
        {
            for (j = 0; j < NO_FRAMES; j++)
            {
                if (frames[j] == -1)
                {
                    counter++;
                    faults++;
                    frames[j] = pages[i];
                    time[j] = counter;
                    flag2 = 1;
                    break;
                }
            }
        }

        if (flag2 == 0)
        {
            pos = LRU(time, NO_FRAMES);
            counter++;
            faults++;
            frames[pos] = pages[i];
            time[pos] = counter;
        }

        printf("\n");

        for (j = 0; j < NO_FRAMES; j++)
        {
            if (frames[j] == -1)
            {
                printf("\t");
            }
            else
            {
                printf("%d\t", frames[j]);
            }
        }
    }

    printf("\n\nTotal Page Faults = %d\n\n", faults);
    return 0;
}

int LRU(int time[], int n)
{
    int i, pos = 0, minimum;
    minimum = time[0];

    for (i = 1; i < n; ++i)
    {
        if (time[i] < minimum)
        {
            minimum = time[i];
            pos = i;
        }
    }
    return pos;
}
