#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int a, b;
    char op;
    while (1) {
        printf("Enter two integers and an operator (+ or -): ");
        scanf("%d %d %c", &a, &b, &op);

        pid_t pid = fork();
        if (pid == 0) {
            char a_str[10], b_str[10], op_str[2];
            snprintf(a_str, sizeof(a_str), "%d", a); // converts a to string 
            snprintf(b_str, sizeof(b_str), "%d", b);
            op_str[0] = op;
            op_str[1] = '\0'; 
            execl("./q7_server", "./q7_server", a_str, b_str, op_str, NULL);
            perror("execl failed"); 
            exit(1); // exit with staus 1 if execl fails 
        } else {
            int status;
            wait(&status); // parent waits until child completes
            printf("Result: %d\n", WEXITSTATUS(status));
        }
    }
    return 0;
}