#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>

int main() {
    int i;
    int n = 3; // Number of times to fork (i from 1 to 9)
    for (i = 1; i <= n; i++) {
        fork();
        printf("The process with PID=%d\n", getpid());

    }

    // Only the original parent should write the count
    if (getppid() != 1) { // If not an orphan (init process), wait for children
        for (i = 1; i <= n; i++) {
            wait(NULL);
        }
    }

    // Parent writes the total number of processes created
    if (getppid() != 1 && getpid() == getpid()) {
        FILE *fp = fopen("process_management.txt", "w");
        if (fp) {
            int total = (int)pow(2, n); // Total processes = 2^n
            fprintf(fp, "Total number of created processes: %d\n", total);
            fclose(fp);
        }
    }
    return 0;
}