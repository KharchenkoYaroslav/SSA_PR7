#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 20
#define MAX_LINE_LEN 1024

void wait_for_keypress() {
    printf("Press Enter to continue...");
    while (getchar() != '\n');
}

void display_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror(filename);
        return;
    }

    char line[MAX_LINE_LEN];
    int line_count = 0;

    while (fgets(line, sizeof(line), file)) {
        fputs(line, stdout);
        line_count++;
        if (line_count >= PAGE_SIZE) {
            wait_for_keypress();
            line_count = 0;
        }
    }
    printf("\nEnd of file\n");

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> <file2> ...\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        printf("==== %s ====\n", argv[i]);
        display_file(argv[i]);
    }

    return 0;
}
