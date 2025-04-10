#include <stdio.h>

struct process {
    int pid, at, bt, rt, ct, tat, wt, done;
};

int main() {
    int n, tq, time = 0, completed = 0, i;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process p[n];

    for(i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for P%d: ", p[i].pid);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt; // Remaining Time
        p[i].done = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int queue[100], front = 0, rear = 0;
    int visited[n];
    for(i = 0; i < n; i++) visited[i] = 0;

    int gantt[200]; // process sequence for Gantt Chart
    int ganttTime[200]; // time values under Gantt Chart
    int gt = 0;

    ganttTime[gt++] = 0;

    while(completed < n) {
        // Enqueue newly arrived processes
        for(i = 0; i < n; i++) {
            if(p[i].at <= time && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if(front == rear) {
            // No process ready
            gantt[gt] = -1; // IDLE
            time++;
            ganttTime[gt++] = time;
            continue;
        }

        int index = queue[front++];
        int execTime = (p[index].rt >= tq) ? tq : p[index].rt;

        for(i = 0; i < n; i++) {
            if(p[i].at > ganttTime[gt] && p[i].at <= time && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
        
        gantt[gt] = index;
        time += execTime;
        ganttTime[gt++] = time;
        p[index].rt -= execTime;

        // Enqueue newly arrived processes while running
        for(i = 0; i < n; i++) {
            if(p[i].at > ganttTime[gt-2] && p[i].at <= time && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if(p[index].rt > 0) {
            queue[rear++] = index; // Re-queue
        } else {
            p[index].ct = time;
            p[index].tat = p[index].ct - p[index].at;
            p[index].wt = p[index].tat - p[index].bt;
            p[index].done = 1;
            completed++;
        }
    }

    // Gantt Chart
    printf("\nGANTT CHART\n");
    for(i = 1; i < gt; i++) {
        if(gantt[i] == -1)
            printf("| IDLE ");
        else
            printf("| P%d   ", p[gantt[i]].pid);
    }
    printf("|\n");

    for(i = 0; i < gt; i++) {
        printf("%d     ", ganttTime[i]);
    }

    // Process Table
    float avg_wt = 0, avg_tat = 0;
    printf("\n\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
    }

    printf("\nAverage Waiting Time: %.2f", avg_wt/n);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat/n);

    return 0;
}
