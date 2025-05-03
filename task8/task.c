#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    struct dirent *entry;
    DIR *dp = opendir(".");

    if (dp == NULL) {
        perror("Unable to open directory");
        return 1;
    }

    while ((entry = readdir(dp)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        printf("Do you want to delete file: %s? (y/n): ", entry->d_name);
        char response;
        scanf(" %c", &response);

        if (response == 'y' || response == 'Y') {
            if (remove(entry->d_name) == 0) {
                printf("File %s deleted successfully.\n", entry->d_name);
            } else {
                perror("Error deleting file");
            }
        }
    }

    closedir(dp);

    return 0;
}
