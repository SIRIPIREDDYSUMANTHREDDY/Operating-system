#include <stdio.h>
struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int is_completed;
};
int main() {
    int n, current_time = 0, completed = 0;
    float total_tat = 0, total_wt = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for Process %d: ", p[i].pid);
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
        p[i].is_completed = 0;
    }
    while (completed < n) {
        int idx = -1;
        int min_bt = 1e9;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && p[i].is_completed == 0) {
                if (p[i].burst_time < min_bt) {
                    min_bt = p[i].burst_time;
                    idx = i;
                } else if (p[i].burst_time == min_bt) {
                    // Tie-breaking: choose earlier arrival time
                    if (p[i].arrival_time < p[idx].arrival_time) {
                        idx = i;
                    }
                }
            }
        }
        if (idx != -1) {
            current_time += p[idx].burst_time;
            p[idx].completion_time = current_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            p[idx].is_completed = 1;
            completed++;
            total_tat += p[idx].turnaround_time;
            total_wt += p[idx].waiting_time;
        } else {
            current_time++; // CPU idle
        }
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", 
            p[i].pid, p[i].arrival_time, p[i].burst_time,
            p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
    }
    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    return 0;
}
