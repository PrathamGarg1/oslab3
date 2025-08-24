#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) { perror("open"); exit(1); }

    off_t size = lseek(fd, 0, SEEK_END); // mark the file pointer to the end of file .. retunrs the file size in bytes
    if (size == -1) { perror("lseek"); exit(1); }
    close(fd);

    struct stat st;
    if (stat(argv[1], &st) < 0) { perror("stat"); exit(1); }

    long block_size = st.st_blksize;
    long num_blocks = (size + block_size - 1) / block_size;

    printf("File size (lseek) = %ld bytes\n", (long)size);
    printf("File size (stat)  = %ld bytes\n", (long)st.st_size);
    printf("Block size        = %ld bytes\n", block_size);
    printf("Blocks allocated  = %ld\n", (long)(st.st_blocks));
    printf("Blocks (calc)     = %ld\n", num_blocks);

    return 0;
}
