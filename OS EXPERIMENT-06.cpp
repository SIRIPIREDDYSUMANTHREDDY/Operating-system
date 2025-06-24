#include <stdio.h>
#define MAX 100
struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int priority;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int is_completed;
};
int main() {
    struct Process p[MAX];
    int n, current_time = 0, completed = 0;
    int min_priority_index;
    float total_waiting_time = 0, total_turnaround_time = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time, burst time and priority for process %d: ", p[i].pid);
        scanf("%d %d %d", &p[i].arrival_time, &p[i].burst_time, &p[i].priority);
        p[i].remaining_time = p[i].burst_time;
        p[i].is_completed = 0;
    }
    while (completed < n) {
        min_priority_index = -1;
        int min_priority = 9999;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && p[i].is_completed == 0 && p[i].remaining_time > 0) {
                if (p[i].priority < min_priority) {
                    min_priority = p[i].priority;
                    min_priority_index = i;
                }
            }
        }
        if (min_priority_index != -1) {
            p[min_priority_index].remaining_time--;
            current_time++;
            if (p[min_priority_index].remaining_time == 0) {
                p[min_priority_index].completion_time = current_time;
                p[min_priority_index].turnaround_time = p[min_priority_index].completion_time - p[min_priority_index].arrival_time;
                p[min_priority_index].waiting_time = p[min_priority_index].turnaround_time - p[min_priority_index].burst_time;
                total_waiting_time += p[min_priority_index].waiting_time;
                total_turnaround_time += p[min_priority_index].turnaround_time;
                p[min_priority_index].is_completed = 1;
                completed++;
            }
        } else {
            current_time++; // CPU idle
        }
    }
    printf("\nPID\tAT\tBT\tP\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].priority,
               p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
    }
    printf("\nAverage Turnaround Time: %.2f", total_turnaround_time / n);
    printf("\nAverage Waiting Time: %.2f\n", total_waiting_time / n);
    return 0;
}
