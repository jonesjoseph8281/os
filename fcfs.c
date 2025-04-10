#include<stdio.h>


struct process
{
    int pid,at,bt,wt,tat,ct;    
};
void main()
{
    int pno,i,j;
    printf("Enter no of process: ");
    scanf("%d",&pno);
    struct process p[pno];
    int time = 0;  
    
    for(i = 0; i < pno; i++) {
        printf("Enter arrival time and burst time for Process %d: ", i+1);
        p[i].pid = i + 1;
        scanf("%d%d", &p[i].at, &p[i].bt);
    }
    
    for(i = 0;i<pno-1;i++)
    {
        for(j=0;j<pno-1-i;j++)
        {
            if(p[j].at>p[j+1].at)
            {
                struct process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
            
        }
    }
    
    for(i = 0; i < pno; i++) {
        if(p[i].at>time)
        {
            time = p[i].at;
        }
        p[i].ct = time + p[i].bt;
        p[i].tat = p[i].ct  - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        time = p[i].ct;
    }
    
    printf("\nProcess\tAT\tBT\tWT\tTAT\tCT\n");
    float avg_wt = 0, avg_tat = 0;
    for(i = 0; i < pno; i++) {
        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].wt, p[i].tat, p[i].ct);
    }

    printf("\nAverage Waiting Time: %.2f", avg_wt/pno);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat/pno);

        // Gantt Chart Header
    printf("\n\nGANTT CHART\n");
    printf(" ");

    time = 0;

    for(i = 0; i < pno; i++) {
        if(p[i].at > time) {
            printf(" IDLE |");
            time = p[i].at;
        }
        printf(" P%d |", p[i].pid);
        time = p[i].ct;
    }

    // Timeline numbers below the chart
    printf("\n");
    time = 0;
    printf("%d", time);

    for(i = 0; i < pno; i++) {
        if(p[i].at > time) {
            printf("    %d", p[i].at);  // after IDLE
            time = p[i].at;
        }
        printf("    %d", p[i].ct);
        time = p[i].ct;
    }

    
    
    
}