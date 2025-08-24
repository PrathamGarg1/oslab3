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

    int fd = open(argv[1], O_RDWR);
    if (fd < 0) { perror("open"); exit(1); }

    struct stat st; // holds file info 

    off_t read_pos = 0, write_pos = 0;
    char c;
    int count = 0;

    while (read(fd, &c, 1) == 1) {
        count++;
        if (count % 5 != 0) {
            lseek(fd, write_pos, SEEK_SET);
            if (write(fd, &c, 1) != 1) { perror("write"); exit(1); }
            write_pos++;
            lseek(fd, read_pos + 1, SEEK_SET);
        }
        read_pos++;
    }


    close(fd);
    return 0;
}
