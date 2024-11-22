// Write a C program that print the exit status of a terminated child process

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { 
        printf("Child process is running...\n");
        sleep(2); 
        exit(42); 
    } else { 
        
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            printf("Child process terminated with exit status: %d\n", exit_status);
        } else {
            printf("Child process did not terminate normally.\n");
        }
    }

    return 0;
}


