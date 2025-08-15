#include <stdio.h>
#include <limits.h>

void findWaitingTime(int processes[], int n, int bt[], int wt[])
{
    int rt[n];
    for (int i = 0; i < n; i++)
        rt[i] = bt[i];

    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    int check = 0;

    while (complete != n)
    {
        for (int j = 0; j < n; j++)
        {
            if ((rt[j] < minm) && (rt[j] > 0))
            {
                minm = rt[j];
                shortest = j;
                check = 1;
            }
        }

        if (check == 0)
        {
            t++;
            continue;
        }

        rt[shortest]--;
        minm = rt[shortest];
        if (minm == 0)
            minm = INT_MAX;

        if (rt[shortest] == 0)
        {
            complete++;
            check = 0;
            finish_time = t + 1;
            wt[shortest] = finish_time - bt[shortest];
            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }
        t++;
    }
}

void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[])
{
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}

void findAverageTime(int processes[], int n, int bt[])
{
    int wt[n], tat[n];
    findWaitingTime(processes, n, bt, wt);
    findTurnAroundTime(processes, n, bt, wt, tat);

    printf("Processes   Burst Time   Waiting Time   Turnaround Time\n");
    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++)
    {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("   %d ", (i + 1));
        printf("          %d ", bt[i]);
        printf("           %d ", wt[i]);
        printf("                %d\n", tat[i]);
    }

    printf("Average waiting time = %.2f\n", (float)total_wt / (float)n);
    printf("Average turnaround time = %.2f\n", (float)total_tat / (float)n);
}

int main()
{
    int processes[] = {1, 2, 3};
    int n = sizeof processes / sizeof processes[0];
    int burst_time[] = {6, 8, 7};

    findAverageTime(processes, n, burst_time);
    return 0;
}
