#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> 

int main() {
    int num_processes = 5;
    pid_t pid;

    for (int i = 0; i < num_processes; i++) {
        pid = fork();  

        if (pid == 0) {
            printf("Process %d (PID: %d) sleeps for 60 seconds...\n", i+1, getpid());
            sleep(60);  
            printf("Process %d (PID: %d) finished.\n", i+1, getpid());
            exit(0);
        } else if (pid < 0) {
            perror("Error creating process");
            exit(1);
        }
    }

    for (int i = 0; i < num_processes; i++) {
        wait(NULL);
    }

    printf("All processes have finished.\n");
    return 0;
}
