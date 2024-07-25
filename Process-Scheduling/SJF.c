#include <stdio.h>

struct Process {
    int pid;
    int burst_time;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
};

void SJF(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burst_time > processes[j + 1].burst_time) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    // Calculate 
    processes[0].waiting_time = 0;
    processes[0].turnaround_time = processes[0].burst_time;
    for (int i = 1; i < n; i++) {
        processes[i].waiting_time = processes[i - 1].burst_time + processes[i - 1].waiting_time;
        processes[i].turnaround_time = processes[i].burst_time + processes[i].waiting_time;
    }

    // Calculate average waiting time and average turnaround time
    float avg_wait_time = 0, avg_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        avg_wait_time += processes[i].waiting_time;
        avg_turnaround_time += processes[i].turnaround_time;
    }
    avg_wait_time /= n;
    avg_turnaround_time /= n;

    // Display result
    printf("\nProcess ID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t\t%d\t\t\t%d\t\t\t\t%d\n", processes[i].pid, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }

    printf("\nAverage Waiting Time = %.2f\n", avg_wait_time);
    printf("Average Turnaround Time = %.2f\n", avg_turnaround_time);
}

void main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1; // Assign process ID
        printf("Enter the burst time of P%d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
    }

    SJF(processes, n);

    
}
