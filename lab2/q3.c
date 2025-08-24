#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

void delete_dir(const char *path) {
    struct dirent *entry;
    DIR *dir = opendir(path);

    if (!dir) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
       
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)  // Skip "." and ".."
        continue;

        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        struct stat st; 
        if (stat(fullpath, &st) == 0) { // is successful .. then stat cotnains info like permission 
            if (S_ISDIR(st.st_mode)) {
                // If it's a directory, delete its contents recursively
                delete_dir(fullpath);
            } else {
                // If it's a file, delete it
                remove(fullpath);
            }
        }
    }
    closedir(dir);
    // Delete the directory itself
    rmdir(path);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <directory>\n", argv[0]);
        return 1;
    }
    delete_dir(argv[1]);
    return 0;
}