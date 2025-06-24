#include <stdio.h>
struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
};
int main() {
    int n, time_quantum, current_time = 0, completed = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for Process %d: ", p[i].pid);
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
        p[i].remaining_time = p[i].burst_time;
    }
    printf("Enter Time Quantum: ");
    scanf("%d", &time_quantum);
    int queue[n];
    int front = 0, rear = 0;
    int visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;
    queue[rear++] = 0;
    visited[0] = 1;
    while (completed < n) {
        int idx = queue[front++];
        struct Process *proc = &p[idx];
        if (current_time < proc->arrival_time) {
            current_time = proc->arrival_time;
        }
        if (proc->remaining_time > time_quantum) {
            current_time += time_quantum;
            proc->remaining_time -= time_quantum;
        } else {
            current_time += proc->remaining_time;
            proc->completion_time = current_time;
            proc->turnaround_time = proc->completion_time - proc->arrival_time;
            proc->waiting_time = proc->turnaround_time - proc->burst_time;
            proc->remaining_time = 0;
            completed++;
        }
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && p[i].remaining_time > 0 && visited[i] == 0) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
        if (proc->remaining_time > 0) {
            queue[rear++] = idx;
        }
        if (front == rear && completed < n) {
            for (int i = 0; i < n; i++) {
                if (p[i].remaining_time > 0) {
                    queue[rear++] = i;
                    visited[i] = 1;
                    break;
                }
            }
        }
    }
    float total_wt = 0, total_tat = 0;
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        total_wt += p[i].waiting_time;
        total_tat += p[i].turnaround_time;
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", 
               p[i].pid, p[i].arrival_time, p[i].burst_time, 
               p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
    }
    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    return 0;
}
