#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid1, pid2;

    pid1 = fork();
    if (pid1 == 0) {
        // Child process
        pid2 = fork();
        if (pid2 == 0) {
            printf("Grandchild: PID=%d, PPID=%d\n", getpid(), getppid());
        } else {
            printf("Child: PID=%d, PPID=%d\n", getpid(), getppid());
        }
    } 
    
    else {
        pid2 = fork();
        if (pid2 == 0) {
            printf("Another Child: PID=%d, PPID=%d\n", getpid(), getppid());
        } else {
            printf("Parent: PID=%d, PPID=%d\n", getpid(), getppid());
        }
    }
    return 0;
}
