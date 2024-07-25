#include <stdio.h>
#include <stdlib.h>

struct Node {
    int pid;
    int bt;
    int at;
    int wt;
    int tat;
    int pr;
};

void swap(struct Node *a, struct Node *b) {
    struct Node temp = *a;
    *a = *b;
    *b = temp;
}

void priority(struct Node p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].pr > p[j + 1].pr) {
                swap(&p[j], &p[j + 1]);
            }
        }
    }


    float awt = 0, atat = 0;
    p[0].wt = 0;
    p[0].tat = p[0].bt;
    for (int i = 1; i < n; i++) {
        p[i].wt = p[i - 1].bt + p[i - 1].wt;
        p[i].tat = p[i].bt + p[i].wt;
        awt += p[i].wt;
        atat += p[i].tat;
    }

    awt /= n;
    atat /= n;

    // Display result
    printf("\nProcess ID | Burst Time | Waiting Time | Turnaround Time | Priority\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].bt, p[i].wt, p[i].tat, p[i].pr);
    }

    printf("\nAverage Waiting Time = %.2f\n", awt);
    printf("Average Turnaround Time = %.2f\n", atat);

    // Gantt 
    printf("\nGantt Chart:\n");
    printf("P%d -> ", p[0].pid);
    for (int i = 0; i < n; i++) {
        printf("-> P%d ", p[i].pid);
    }
}

void main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Node p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter the burst time of P%d: ", i + 1);
        scanf("%d", &p[i].bt);
        printf("Enter the priority of P%d: ", i + 1);
        scanf("%d", &p[i].pr);
    }

    priority(p, n);

}
