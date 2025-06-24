#include <stdio.h>
struct Process {
    int pid;
    int burst_time;
    int priority; 
    int waiting_time;
    int turnaround_time;
};
void calculateWaitingTime(struct Process p[], int n) {
    p[0].waiting_time = 0;
    for (int i = 1; i < n; i++) {
        p[i].waiting_time = p[i-1].waiting_time + p[i-1].burst_time;
    }
}
void calculateTurnaroundTime(struct Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
    }
}
void sortByPriority(struct Process p[], int n) {
    struct Process temp;
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (p[j].priority < p[i].priority) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}
void printProcesses(struct Process p[], int n) {
    printf("\nPID\tPriority\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", 
               p[i].pid, p[i].priority, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time);
    }
}
int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter burst time and priority for process %d: ", p[i].pid);
        scanf("%d %d", &p[i].burst_time, &p[i].priority);
    }
    sortByPriority(p, n);
    calculateWaitingTime(p, n);
    calculateTurnaroundTime(p, n);
    printProcesses(p, n);
    return 0;
}
