#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LEN 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <word> <file>\n", argv[0]);
        return 1;
    }

    const char *word = argv[1];
    const char *filename = argv[2];

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("can't open file");
        return 1;
    }

    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, word)) {
            printf("%s", line);
        }
    }

    fclose(file);
    return 0;
}
