#include <stdio.h>
#include <conio.h>
int initialize();
int p[10], a[10], b[10], w[10], ta[10], t1, gantt[20][2];
int main()
{
    int i, j, n, k, t, e = 0, m = 0;
    float aw, at, sum1;
    
    printf("\n\nP  A  B  W  TAT\n\n");
    n = initialize();
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if ((a[i] > a[j]) || ((a[i] == a[j]) && (b[i] > b[j])))
            {
                t = a[i];
                a[i] = a[j];
                a[j] = t;

                t = b[i];
                b[i] = b[j];
                b[j] = t;

                t = p[i];
                p[i] = p[j];
                p[j] = t;
            }
        }
    }
    k = a[0] + b[0];
    for (i = 1; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (b[i] > b[j] && k >= a[j])
            {
                m = 1;

                t = b[i];
                b[i] = b[j];
                b[j] = t;

                t = a[i];
                a[i] = a[j];
                a[j] = t;

                t = p[i];
                p[i] = p[j];
                p[j] = t;
            }
        }
        if (m == 0)
            k = k + b[i];
        else
            k++;
        m = 0;
    }

    t1 = 0;
    for (i = 0; i < n; i++)
    {
        if (t1 - a[i] < 0)
        {
            gantt[e][0] = -1;
            gantt[e++][1] = t1;
            t1 += a[i] - t1;
        }
        if (i == 0)
            w[i] = 0;
        else
            w[i] = t1 - a[i];
        gantt[e][0] = a[i];
        gantt[e++][1] = t1;
        t1 += b[i];
    }
    gantt[e][1] = t1;
    for (i = 0; i < n; i++)
    {
        ta[i] = b[i] + w[i];
    }
    for (i = 0; i < n; i++)
    {
        printf("%d  %d  %d  %d  %d\n", p[i], a[i], b[i], w[i], ta[i]);
    }
    printf("\nAverage waiting time is:");
    sum1 = 0.0;
    for (i = 0; i < n; i++)
    {
        sum1 += w[i];
    }
    aw = sum1 / n;
    printf("%.2f", aw);

    printf("\nAverage turn around time is:");
    sum1 = 0.0;
    for (i = 0; i < n; i++)
    {
        sum1 += ta[i];
    }
    at = sum1 / n;
    printf("%.2f", at);
    printf("\n\nThe Gantt chart is:\n\n");
    /*for(i=0;i<n;i++)
  {
   printf("|%d",p[i]);
    if(i==n-1)
     printf("|");
  } */
    printf(" ");
    for (i = 0; i < e; i++)
    {

        printf("--- ");
    }
    printf("\n");
    for (i = 0; i < e; i++)
    {
        printf(gantt[i][0] == -1 ? "|   " : "| %d ", gantt[i][0]);
    }

    printf("|\n ");
    for (i = 0; i < e; i++)
    {
        printf("--- ");
    }

    printf("\n");
    for (i = 0; i <= e; i++)
    {
        printf("%d   ", gantt[i][1]);
    }

    getch();
}

int initialize()
{
    int n, n1, n2, n3, i = 0;
    FILE *fp;
    fp = fopen("sjf.txt", "r");
    while (fscanf(fp, "%d%d%d", &n1, &n2, &n3) != EOF)
    {
        p[i] = n1;
        a[i] = n2;
        b[i] = n3;
        i++;
    }
    return i;
}