#include <stdio.h>
#include <stdlib.h>

typedef struct Process
{
    int id, at, bt, ct, rt, tat, wt, remainingTime, flag;
} Process;

void roundRobin(Process p[], int n, int quantum)
{
    int total_tat = 0, total_wt = 0, total_rt = 0;
    int completed = 0, elapsedTime = p[0].at;

    int waitqueue[100], front = 0, rear = 0;
    waitqueue[rear++] = 0;
    p[0].flag = 1;

    printf("\nGantt Chart:\n");
    while (completed < n)
    {
        int exec = waitqueue[front++];

        if (p[exec].remainingTime == p[exec].bt)
            p[exec].rt = elapsedTime - p[exec].at;

        if (p[exec].remainingTime > quantum)
        {
            p[exec].remainingTime -= quantum;
            elapsedTime += quantum;
            printf("| (%d) P%d (%d) ", elapsedTime - quantum, p[exec].id, elapsedTime);
        }
        else
        {
            completed++;
            elapsedTime += p[exec].remainingTime;
            printf("| (%d) P%d (%d) ", elapsedTime - p[exec].remainingTime, p[exec].id, elapsedTime);
            p[exec].remainingTime = 0;
            p[exec].ct = elapsedTime;
            p[exec].tat = p[exec].ct - p[exec].at;
            p[exec].wt = p[exec].tat - p[exec].bt;

            total_rt += p[exec].rt;
            total_tat += p[exec].tat;
            total_wt += p[exec].wt;
        }

        for (int i = 0; i < n && p[i].at <= elapsedTime; i++)
        {
            if (p[i].flag == 0 && p[i].remainingTime > 0)
            {
                waitqueue[rear++] = i;
                p[i].flag = 1;
            }
        }

        if (p[exec].remainingTime > 0)
            waitqueue[rear++] = exec;
    }

    printf("\n");
    printf("Process\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].rt);

    printf("Average TAT = %.2f\nAverage WT = %.2f\nAverage RT = %.2f\n", (float)total_tat / n, (float)total_wt / n, (float)total_rt / n);
}

int main()
{
    int n, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process p[n];

    for (int i = 0; i < n; i++)
    {
        printf("Process %d\n", i + 1);
        printf("Enter at & bt: ");
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].id = i + 1;
        p[i].remainingTime = p[i].bt;
        p[i].flag = 0;
        printf("\n");
    }

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    // Sort processes based on arrival time
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j].at > p[j + 1].at)
            {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    roundRobin(p, n, quantum);
    return 0;
}
