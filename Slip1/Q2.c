// Write a C program to send SIGALRM signal by child process to parent process and parent process
// make a provision to catch the signal and display alarm is fired.(Use Kill, fork, signal and sleep
// system call)

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void signal_handler(int signo) {
    printf("Alarm is fired!\n");
}

int main() {
    pid_t pid;

   
    if (signal(SIGALRM, signal_handler) == SIG_ERR) {
        perror("signal");
        return 1;
    }

   
    pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) { 
        kill(getppid(), SIGALRM);
        printf("Child process sent signal to parent.\n");
    } else { 
        printf("Parent process waiting for signal...\n");
        pause();
    }
    return 0;
}


//  ./a.out 

