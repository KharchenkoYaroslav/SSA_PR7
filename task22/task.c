#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_PROCESSES 1024

typedef struct {
    int pid;
    char status;
    double cpu_time;
    char command[256];
} ProcessInfo;

void get_process_info(ProcessInfo *processes, int *count) {
    FILE *fp;
    char line[1024];

    fp = popen("ps -eo pid,stime,etime,%cpu,stat,comm", "r");
    if (fp == NULL) {
        perror("popen failed");
        exit(1);
    }

    fgets(line, sizeof(line), fp);

    *count = 0;
    while (fgets(line, sizeof(line), fp)) {
        int pid;
        double cpu_time;
        char stime[32], etime[32], status;
        char command[256];

        if (sscanf(line, "%d %s %s %lf %c %s", &pid, stime, etime, &cpu_time, &status, command) == 6) {
            processes[*count].pid = pid;
            processes[*count].status = status;
            processes[*count].cpu_time = cpu_time;
            strncpy(processes[*count].command, command, sizeof(processes[*count].command));
            (*count)++;
        }
    }

    fclose(fp);
}

void detect_sleeping_processes(ProcessInfo *processes, int count) {
    printf("Sleeping processes detected:\n");
    printf("%-10s %-10s %-10s %-20s\n", "PID", "Status", "CPU Time", "Command");

    for (int i = 0; i < count; i++) {
        if (processes[i].status == 'S' && processes[i].cpu_time < 1.0) {
            printf("%-10d %-10c %-10.2f %-20s\n", processes[i].pid, processes[i].status, processes[i].cpu_time, processes[i].command);
        }
    }
}

int main() {
    ProcessInfo processes[MAX_PROCESSES];
    int count = 0;

    get_process_info(processes, &count);

    detect_sleeping_processes(processes, count);

    return 0;
}
