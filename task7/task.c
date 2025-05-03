#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#define BUFFER_SIZE 10

int has_c_extension(const char *filename) {
    const char *ext = strrchr(filename, '.');
    return ext && strcmp(ext, ".c") == 0;
}

int is_owned_by_user(const char *filename, uid_t uid) {
    struct stat st;
    if (stat(filename, &st) != 0) return 0;
    return st.st_uid == uid;
}

void prompt_and_set_permission(const char *filename) {
    char answer[BUFFER_SIZE];
    printf("Give permission to '%s'? (y/n): ", filename);
    if (fgets(answer, sizeof(answer), stdin) && (answer[0] == 'y' || answer[0] == 'Y')) {
        struct stat st;
        if (stat(filename, &st) == 0) {
            mode_t new_mode = st.st_mode | S_IROTH;
            if (chmod(filename, new_mode) == 0) {
                printf("Permission granted.\n");
            } else {
                perror("chmod");
            }
        }
    }
}

int main() {
    DIR *dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return 1;
    }

    uid_t uid = getuid();
    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type != DT_REG) continue;

        if (has_c_extension(entry->d_name) && is_owned_by_user(entry->d_name, uid)) {
            printf("File: %s\n", entry->d_name);
            prompt_and_set_permission(entry->d_name);
        }
    }

    closedir(dir);
    return 0;
}
