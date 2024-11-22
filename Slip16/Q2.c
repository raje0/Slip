// Write a C program which create a child process which catch a signal sighup, sigint and sigquit.
// The Parent process send a sighup or sigint signal after every 3 seconds, at the end of 30 second
// parent send sigquit signal to child and child terminates my displaying message “My DADDY has
// Killed me!!!”.

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
    printf("My DADDY has Killed me!!!\n");
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
        for (int i = 0; i < 10; i++) {
            sleep(3); 
            if (i < 4) {
                if (i % 2 == 0) {
                    kill(child_pid, SIGHUP); 
                } else {
                    kill(child_pid, SIGINT);
            }
        }

        sleep(3); 
        kill(child_pid, SIGQUIT); 

        wait(NULL); 
    }

    return 0;
}



