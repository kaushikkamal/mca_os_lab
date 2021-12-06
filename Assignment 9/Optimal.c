#include <stdio.h>
#define NO_FRAMES 3
#define MAX 30

int main()
{
    int numPages, frames[MAX], pages[MAX], temp[MAX], flag1, flag2, flag3, i, j, k, pos, max, faults;

    faults = 0;

    printf("\nEnter number of pages: ");
    scanf("%d", &numPages);

    printf("\nEnter page numbers:\n");

    for (i = 0; i < numPages; ++i)
    {
        printf("%d: ", i + 1);
        scanf("%d", &pages[i]);
    }

    for (i = 0; i < NO_FRAMES; ++i)
    {
        frames[i] = -1;
    }

    printf("\nOptimal Page Replacement: \n");

    for (i = 0; i < numPages; ++i)
    {
        flag1 = flag2 = 0;
        for (j = 0; j < NO_FRAMES; ++j)
        {
            if (frames[j] == pages[i])
            {
                flag1 = flag2 = 1;
                break;
            }
        }

        if (flag1 == 0)
        {
            for (j = 0; j < NO_FRAMES; ++j)
            {
                if (frames[j] == -1)
                {
                    faults++;
                    frames[j] = pages[i];
                    flag2 = 1;
                    break;
                }
            }
        }

        if (flag2 == 0)
        {
            flag3 = 0;
            for (j = 0; j < NO_FRAMES; ++j)
            {
                temp[j] = -1;
                for (k = i + 1; k < numPages; ++k)
                {
                    if (frames[j] == pages[k])
                    {
                        temp[j] = k;
                        break;
                    }
                }
            }

            for (j = 0; j < NO_FRAMES; ++j)
            {
                if (temp[j] == -1)
                {
                    pos = j;
                    flag3 = 1;
                    break;
                }
            }

            if (flag3 == 0)
            {
                max = temp[0];
                pos = 0;
                for (j = 1; j < NO_FRAMES; ++j)
                {
                    if (temp[j] > max)
                    {
                        max = temp[j];
                        pos = j;
                    }
                }
            }
            frames[pos] = pages[i];
            faults++;
        }

        printf("\n");

        for (j = 0; j < NO_FRAMES; ++j)
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