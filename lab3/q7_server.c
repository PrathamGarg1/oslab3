
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 4) return 1;
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    char op = argv[3][0];
    int result = (op == '+') ? a + b : a - b;
    exit(result);
}
