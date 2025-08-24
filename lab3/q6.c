#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>

int main() {
    int i;
    int n = 3; // Number of times to fork
    auto parent_pid=getpid(); // original parent process should only make the file 

    for (i = 1; i <= n; i++) {
        fork();
        printf("The process with PID=%d\n", getpid());
    }

    if (getppid() != 1) { // if par is not init (not orphan)
        for (i = 1; i <= n; i++) { // then wait for all child to complete
            wait(NULL);
        }
    }

    if (getpid() == parent_pid) { // if curr process is the oirignal
        FILE *fp = fopen("process_management.txt", "w");
        if (fp) {
            int total = (int)pow(2, n); // Total processes = 2^n
            fprintf(fp, "Total number of created processes: %d\n", total);
            fclose(fp);
        }
    }
    return 0;
}