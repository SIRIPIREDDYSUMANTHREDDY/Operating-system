#include <stdio.h>
struct Process {
    int pid;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};
int main() {
    int n, i;
    struct Process p[100];
    int total_waiting_time = 0, total_turnaround_time = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter burst time for Process %d: ", p[i].pid);
        scanf("%d", &p[i].burst_time);
    }
    p[0].waiting_time = 0;
    p[0].turnaround_time = p[0].burst_time;
    for (i = 1; i < n; i++) {
        p[i].waiting_time = p[i - 1].waiting_time + p[i - 1].burst_time;
        p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
    }
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time);
        total_waiting_time += p[i].waiting_time;
        total_turnaround_time += p[i].turnaround_time;
    }
    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
    return 0;
}
