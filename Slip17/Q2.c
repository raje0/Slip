// Write a C program to implement the following unix/linux command (use fork, pipe and exec
// system call). Your program should block the signal Ctrl-C and Ctrl-\ signal during the execution.
// i. Ls –l | wc –l


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void block_signals() {
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);  
    sigaddset(&set, SIGQUIT); 
    sigprocmask(SIG_BLOCK, &set, NULL); 
}

void unblock_signals() {
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT); 
    sigaddset(&set, SIGQUIT); 
    sigprocmask(SIG_UNBLOCK, &set, NULL); 
}

int main() {
    int pipefd[2];
    pid_t pid1, pid2;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    block_signals();

    pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) { 
        close(pipefd[1]);

        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]); 

        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) { 
        close(pipefd[0]);

        
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]); 

        execlp("wc", "wc", "-l", NULL);
        perror("execlp"); 
        exit(EXIT_FAILURE);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    unblock_signals();

    return 0;
}


