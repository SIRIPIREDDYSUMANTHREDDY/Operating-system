#include <stdio.h>
#include <unistd.h>     
#include <sys/types.h>  
int main() {
    pid_t pid;
    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return 1;
    }
    else if (pid == 0) {
        printf("Child Process:\n");
        printf("PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());
    }
    else {
        printf("Parent Process:\n");
        printf("PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);
    }
    return 0;
}
