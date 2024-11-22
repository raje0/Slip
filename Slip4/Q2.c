// Write a C program which creates a child process and child process catches a signal SIGHUP,
// SIGINT and SIGQUIT. The Parent process send a SIGHUP or SIGINT signal after every 3
// seconds, at the end of 15 second parent send SIGQUIT signal to child and child terminates by
// displaying message "My Papa has Killed me!!!”.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

void handle_sighup(int sig) {
    printf("Child received SIGHUP signal.\n");
}

void handle_sigint(int sig) {
    printf("Child received SIGINT signal.\n");
}

void handle_sigquit(int sig) {
    printf("My Papa has Killed me!!!\n");
    exit(0);
}

int main() {
    pid_t child_pid = fork(); 

    if (child_pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (child_pid == 0) {
        
        signal(SIGHUP, handle_sighup);
        signal(SIGINT, handle_sigint);
        signal(SIGQUIT, handle_sigquit);

        while (1) {
            pause(); 
        }
    } else {
    
        for (int i = 0; i < 5; i++) {
            sleep(3);
            if (i < 4) {
            
                if (i % 2 == 0) {
                    kill(child_pid, SIGHUP); 
                } else {
                    kill(child_pid, SIGINT);
                }
            }
        }
        sleep(3);
        kill(child_pid, SIGQUIT); 
        wait(NULL);
    }

    return 0;
}


