#include <stdio.h>
#include <stdbool.h>

#define P 5
#define R 3

// updated and modified version

bool isSafe(int processes[], int n, int avail[], int max[][R], int allot[][R])
{
    int work[R];
    bool finish[n];
    for (int i = 0; i < R; i++)
        work[i] = avail[i];
    for (int i = 0; i < n; i++)
        finish[i] = false;
    int safeSeq[n];
    int count = 0;
    while (count < n)
    {
        bool found = false;
        for (int p = 0; p < n; p++)
        {
            if (finish[p] == false)
            {
                int j;
                for (j = 0; j < R; j++)
                    if (max[p][j] - allot[p][j] > work[j])
                        break;
                if (j == R)
                {
                    for (int k = 0; k < R; k++)
                        work[k] += allot[p][k];
                    safeSeq[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (found == false)
        {
            printf("System is not in a safe state\n");
            return false;
        }
    }
    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < n; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");
    return true;
}

bool requestResources(int processes[], int n, int avail[], int max[][R], int allot[][R], int req[])
{
    int need[n][R];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - allot[i][j];
    for (int j = 0; j < R; j++)
        if (req[j] > need[processes[0]][j])
            return false;
    for (int j = 0; j < R; j++)
        if (req[j] > avail[j])
            return false;
    int old_avail[R];
    int old_allot[n][R];
    for (int j = 0; j < R; j++)
    {
        old_avail[j] = avail[j];
        avail[j] -= req[j];
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < R; j++)
            old_allot[i][j] = allot[i][j];
    for (int j = 0; j < R; j++)
        allot[processes[0]][j] += req[j];
    if (isSafe(processes, n, avail, max, allot))
    {
        return true;
    }
    else
    {
        for (int j = 0; j < R; j++)
        {
            avail[j] = old_avail[j];
            allot[processes[0]][j] = old_allot[processes[0]][j];
        }
        return false;
    }
}

int main()
{
    int processes[] = {0, 1, 2, 3, 4};
    int n = sizeof(processes) / sizeof(processes[0]);
    int resources[] = {10, 5, 7};
    int m = sizeof(resources) / sizeof(resources[0]);
    int avail[] = {3, 3, 3};
    int max[][R] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}};
    int allot[][R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}};
    int request[] = {1, 0, 2};
    if (requestResources(processes, n, avail, max, allot, request))
    {
        printf("Request can be granted safely.\n");
    }
    else
    {
        printf("Request cannot be granted safely.\n");
    }
    return 0;
}
