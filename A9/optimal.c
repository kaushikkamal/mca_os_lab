#include <stdio.h>
#include <stdlib.h>

int main()
{
    int pageNum[] = {4, 7, 6, 1, 7, 6, 1, 2, 7, 2};
    int frames[3];
    int temp[3];
    int i, j, k, hit = 0, fault = 0, notMatch = 1, leastIndexVal = 0, notfound = 0, s = 1;
    int noOfpages = 10;
    int noOfFrames = 3;

    for (j = 0; j < noOfFrames; j++)
    {
        frames[j] = -1;
        temp[j] = -1;
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
                k = 1;
                for (j = 0; j < noOfFrames; j++)
                {
                    if (i + k < noOfpages)
                    {
                        temp[j] = pageNum[i + k];
                        k++;
                    }
                }
                if (s == 1)
                {
                    for (j = 0; j < noOfFrames; j++)
                    {
                        for (k = 0; k < noOfFrames; k++)
                        {
                            if (frames[j] == temp[k])
                            {
                                notfound = 0;
                            }
                            notfound = 1;
                        }
                        if (notfound == 1)
                        {
                            frames[j] = pageNum[i];
                            fault++;
                            s = 0;
                            break;
                        }
                    }
                }
                else
                {
                    if (i + noOfFrames < noOfpages)
                    {
                        leastIndexVal = pageNum[i + noOfFrames];
                        for (j = 0; j < noOfFrames; j++)
                        {
                            if (leastIndexVal == frames[j])
                            {
                                frames[j] = pageNum[i];
                                fault++;
                                s = 1;
                                break;
                            }
                        }
                    }
                    else
                    {
                        frames[0] = pageNum[i];
                        fault++;
                    }
                }
            }
        }
    }

    printf("Page fault: %d\n", fault);
    printf("Page hit: %d\n", hit);

    return 0;
}