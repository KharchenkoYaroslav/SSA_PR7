#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

void print_permissions(mode_t mode) {
    char perms[11] = "----------";

    if (S_ISDIR(mode)) perms[0] = 'd';
    else if (S_ISLNK(mode)) perms[0] = 'l';

    if (mode & S_IRUSR) perms[1] = 'r';
    if (mode & S_IWUSR) perms[2] = 'w';
    if (mode & S_IXUSR) perms[3] = 'x';

    if (mode & S_IRGRP) perms[4] = 'r';
    if (mode & S_IWGRP) perms[5] = 'w';
    if (mode & S_IXGRP) perms[6] = 'x';

    if (mode & S_IROTH) perms[7] = 'r';
    if (mode & S_IWOTH) perms[8] = 'w';
    if (mode & S_IXOTH) perms[9] = 'x';

    printf("%s ", perms);
}

int main(int argc, char *argv[]) {
    const char *path = (argc > 1) ? argv[1] : ".";

    DIR *dir = opendir(path);
    if (!dir) {
        perror("opendir failed");
        return 1;
    }

    struct dirent *entry;
    struct stat st;
    char fullpath[1024];
    blkcnt_t total_blocks = 0;

    while ((entry = readdir(dir))) {
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
        if (stat(fullpath, &st) == -1)
            continue;

        if (entry->d_name[0] != '.')  
            total_blocks += st.st_blocks;
    }

    printf("total %ld\n", total_blocks / 2); 

    rewinddir(dir);  

    while ((entry = readdir(dir))) {
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
        if (stat(fullpath, &st) == -1)
            continue;

        if (entry->d_name[0] == '.')
            continue;

        print_permissions(st.st_mode);
        printf("%2ld ", st.st_nlink);

        struct passwd *pw = getpwuid(st.st_uid);
        struct group  *gr = getgrgid(st.st_gid);
        printf("%s %s ", pw ? pw->pw_name : "unknown", gr ? gr->gr_name : "unknown");

        printf("%8ld ", st.st_size);

        char timebuf[64];
        strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", localtime(&st.st_mtime));
        printf("%s ", timebuf);

        printf("%s\n", entry->d_name);
    }

    closedir(dir);
    return 0;
}
