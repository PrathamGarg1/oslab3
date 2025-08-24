#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int x = 10; // Each process has its own copy of x
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        x = 20;
        printf("Child: PID=%d, x=%d, address=%p\n", getpid(), x, &x);
        while(1); // Keep running to show concurrency
    } else {
        // Parent process
        x = 30;
        printf("Parent: PID=%d, x=%d, address=%p\n", getpid(), x, &x);
        while(1); // Keep running to show concurrency
    }
    return 0;
}