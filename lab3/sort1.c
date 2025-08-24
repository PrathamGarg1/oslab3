#include <stdio.h>
#include <stdlib.h>

#define MAX_INTS 1000

static int cmp_int(const void *a, const void *b) {
    int ia = *(const int *)a; // tyoecast then derefernce
    int ib = *(const int *)b;
    if (ia < ib) return -1;
    if (ia > ib) return 1;
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    int arr[MAX_INTS];
    int n = 0;
    while (n < MAX_INTS && fscanf(fp, "%d", &arr[n]) == 1) {
        n++;
    }
    fclose(fp);

    qsort(arr, n, sizeof(int), cmp_int);

    for (int i = 0; i < n; i++) {
        if (i) putchar(' ');
        printf("%d", arr[i]);
    }
    putchar('\n');

    return 0;
}
