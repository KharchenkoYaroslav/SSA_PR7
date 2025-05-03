#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

void list_files(const char *path) {
    struct dirent *entry;
    DIR *dir = opendir(path);

    if (!dir) {
        perror(path);
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char full_path[4096];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        struct stat st;
        if (stat(full_path, &st) == -1) {
            perror(full_path);
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            list_files(full_path);
        } else {
            printf("%s\n", full_path);
        }
    }

    closedir(dir);
}

int main() {
    list_files(".");
    return 0;
}
