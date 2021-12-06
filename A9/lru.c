#include <stdio.h>
#include <stdlib.h>

int main()
{
    int pageNum[] = {4, 7, 6, 1, 7, 6, 1, 2, 7, 2};
    int frames[3];
    int i, j, hit = 0, fault = 0, notMatch = 1, leastIndexVal = 0;
    int noOfpages = 10;
    int noOfFrames = 3;

    for (j = 0; j < noOfFrames; j++)
    {
        frames[j] = -1;
    }

    j = 0;

    for (i = 0; i < noOfpages; i++)
    {
        if (frames[j] == -1 && j < noOfFrames)
        {
            frames[j] = pageNum[i];
            fault++;
            j++;
        }
        else
        {
            for (j = 0; j < noOfFrames; j++)
            {
                if (pageNum[i] == frames[j])
                {
                    hit++;
                    notMatch = 0;
                    break;
                }
                notMatch = 1;
            }
            if (notMatch == 1)
            {
                leastIndexVal = pageNum[i - noOfFrames];
                for (j = 0; j < noOfFrames; j++)
                {
                    if (leastIndexVal == frames[j])
                    {
                        frames[j] = pageNum[i];
                        fault++;
                        break;
                    }
                }
            }
        }
    }

    printf("Page fault: %d\n", fault);
    printf("Page hit: %d\n", hit);

    return 0;
}