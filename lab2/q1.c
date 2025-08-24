#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUF_SIZE 1024

void cat_command(const char *filename) {
    int fd = open(filename, O_RDONLY); //file descriptor
    if (fd < 0) { perror("open"); exit(1); }

    char buf[BUF_SIZE];
    ssize_t n;
    while ((n = read(fd, buf, BUF_SIZE)) > 0) { // reading in chunks of 1024 bytes .. number of bytes read
        if (write(STDOUT_FILENO, buf, n) != n) { // STDOUT_FILENO : 1 (std output)
            perror("write");    // read bytes shiuld be same as write
            exit(1);
        }
    }
    close(fd);
}

void mv_command(const char *src, const char *dest) {
    int fd_src = open(src, O_RDONLY);
    if (fd_src < 0) { perror("open src"); exit(1); }

    int fd_dest = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);// opens or creates the destination file for writing ,, O_TRUNC ->clears
    if (fd_dest < 0) { perror("open dest"); exit(1); }

    char buf[BUF_SIZE];
    ssize_t n;
    while ((n = read(fd_src, buf, BUF_SIZE)) > 0) {
        if (write(fd_dest, buf, n) != n) {
            perror("write");
            exit(1);
        }
    }
    close(fd_src);
    close(fd_dest);

    if (unlink(src) < 0) { perror("unlink"); exit(1); } // DELETE THE SOURCE FILE 
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage:\n  %s cat <filename>\n  %s mv <src> <dest>\n", argv[0], argv[0]);
        exit(1);
    }

    if (strcmp(argv[1], "cat") == 0) {
        cat_command(argv[2]);
    } else if (strcmp(argv[1], "mv") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Usage: %s mv <src> <dest>\n", argv[0]);
            exit(1);
        }
        mv_command(argv[2], argv[3]);
    } else {
        fprintf(stderr, "Unknown command: %s\n", argv[1]);
    }

    return 0;
}
