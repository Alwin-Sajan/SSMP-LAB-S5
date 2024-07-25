#include <stdio.h>

struct Node {
    int pid;
    int at;
    int bt;
    int rm;
    int wt;
    int tata;
};

void displayProcessTable(struct Node p[], int n) {
    printf("\nProcess ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].wt, p[i].tata);
    }
}

void main() {
    int n, i, quantum, temp, remaining;
    struct Node p[10];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time of process %d: ", i + 1);
        scanf("%d", &p[i].at);
        printf("Enter burst time of process %d: ", i + 1);
        scanf("%d", &p[i].bt);
        p[i].rm = p[i].bt;
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    remaining = n;

    temp = 0;
    while (remaining != 0) {
        for (i = 0; i < n; i++) {
            if (p[i].rm > 0) {
                if (p[i].rm <= quantum) {
                    temp += p[i].rm;
                    p[i].wt = temp - p[i].at - p[i].bt;
                    p[i].tata = temp - p[i].at;
                    p[i].rm = 0;
                    remaining--;
                } else {
                    temp += quantum;
                    p[i].rm -= quantum;
                }
            }
        }
    }

    int total_wt = 0, total_tata = 0;
    for (i = 0; i < n; i++) {
        total_wt += p[i].wt;
        total_tata += p[i].tata;
    }

    displayProcessTable(p, n);
    //displayGanttChart(p, n, quantum); // Function not provided
    printf("Average Turn Around Time: %.2f\n", (float)total_tata / n);
    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);

    // Gantt chart logic
    printf("\nGantt Chart:\n");
    printf("P%d -> ", p[0].pid);
    for (int i = 0; i < n; i++) {
        printf("-> P%d ", p[i].pid);
    }
}
