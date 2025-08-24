
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    pid_t pid = fork();
    if (pid == 0) {
        execlp("xterm", "xterm", "-e", "./sort1", argv[1], NULL);
        perror("execlp failed");
        exit(1);
    }
    return 0;
}
