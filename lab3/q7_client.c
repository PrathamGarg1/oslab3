
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int a, b;
    char op;
    printf("Enter two integers and an operator (+ or -): ");
    scanf("%d %d %c", &a, &b, &op);

    pid_t pid = fork();
    if (pid == 0) {
        char a_str[10], b_str[10];
        sprintf(a_str, "%d", a);
        sprintf(b_str, "%d", b);
        execl("./q7_server", "./q7_server", a_str, b_str, &op, NULL);
    } else {
        int status;
        wait(&status);
        printf("Result: %d\n", WEXITSTATUS(status));
    }
    return 0;
}
