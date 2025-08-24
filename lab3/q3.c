
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();
    int status;

    if (pid == 0) {
        printf("Child process running with PID=%d\n", getpid());
        exit(42); 
    } else {
        wait(&status);  // makes the parent wait until the child finishes
        printf("Child PID=%d terminated with status (decimal)=%d (hex)=%x\n", pid, status, status);
    }
    return 0;
}
