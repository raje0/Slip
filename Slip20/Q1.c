// Write a C program that illustrates suspending and resuming processes using signals

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void handler(int signum) {
}

int main() {
    pid_t pid;
    int count = 0;

    signal(SIGUSR1, handler);


    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        while (1) {
            printf("Child counting: %d\n", count++);
            sleep(1);
        }
    } else {
        sleep(3); 

        printf("Parent: Suspending child process...\n");
        kill(pid, SIGSTOP); 
        sleep(5); 

        printf("Parent: Resuming child process...\n");
        kill(pid, SIGCONT);

    
        sleep(5);
        
 
        printf("Parent: Terminating child process...\n");
        kill(pid, SIGTERM);
        wait(NULL);
        printf("Parent: Child process terminated.\n");
    }

    return 0;
}

