#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX_DIRS 1024

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    struct dirent *entry;
    DIR *dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return 1;
    }

    char *dirs[MAX_DIRS];
    int count = 0;

    while ((entry = readdir(dir)) != NULL) {
        struct stat st;
        if (stat(entry->d_name, &st) == 0 && S_ISDIR(st.st_mode)) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            dirs[count] = strdup(entry->d_name);
            if (dirs[count] == NULL) {
                perror("strdup");
                closedir(dir);
                return 1;
            }
            count++;
            if (count >= MAX_DIRS) break;
        }
    }

    closedir(dir);

    qsort(dirs, count, sizeof(char *), compare);

    for (int i = 0; i < count; i++) {
        printf("%s/\n", dirs[i]);
        free(dirs[i]);
    }

    return 0;
}
