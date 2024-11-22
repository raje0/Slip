// Write a C program to create n child processes. When all n child processes terminates, Display
// total cumulative time children spent in user and kernel mode

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <time.h>

void child_process(int id) {

    printf("Child %d is running...\n", id);
    for (volatile long i = 0; i < 100000000; i++); 
    printf("Child %d finished.\n", id);
    exit(0);
}

int main() {
    int n;
    printf("Enter the number of child processes: ");
    scanf("%d", &n);

    pid_t pid;
    struct tms tbuf;
    clock_t start, end;
    long total_user_time = 0;
    long total_system_time = 0;

    for (int i = 0; i < n; i++) {
        pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            return 1;
        }
        if (pid == 0) {
            child_process(i);
        }
    }


    for (int i = 0; i < n; i++) {
        wait(&pid);
        
        times(&tbuf);
        total_user_time += tbuf.tms_utime; 
        total_system_time += tbuf.tms_stime;
    }

    printf("Total cumulative time spent by children:\n");
    printf("User Mode: %ld clock ticks\n", total_user_time);
    printf("Kernel Mode: %ld clock ticks\n", total_system_time);

    return 0;
}

