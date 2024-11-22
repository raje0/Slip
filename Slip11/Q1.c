// Write a C program to get and set the resource limits such as files, memory associated with a
// process

#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <string.h>

void print_limit(const char *resource_name, int resource) {
    struct rlimit limit;
    if (getrlimit(resource, &limit) == -1) {
        perror("getrlimit");
        exit(EXIT_FAILURE);
    }

    printf("Resource: %s\n", resource_name);
    printf("Soft limit: %lu\n", limit.rlim_cur);
    printf("Hard limit: %lu\n", limit.rlim_max);
}

void set_limit(int resource, rlim_t new_limit) {
    struct rlimit limit;
    if (getrlimit(resource, &limit) == -1) {
        perror("getrlimit");
        exit(EXIT_FAILURE);
    }

    if (new_limit > limit.rlim_max) {
        fprintf(stderr, "New limit exceeds hard limit\n");
        exit(EXIT_FAILURE);
    }

    limit.rlim_cur = new_limit;
    if (setrlimit(resource, &limit) == -1) {
        perror("setrlimit");
        exit(EXIT_FAILURE);
    }
}

int main() {
    print_limit("Number of open files (RLIMIT_NOFILE)", RLIMIT_NOFILE);

 
    print_limit("Virtual memory size (RLIMIT_AS)", RLIMIT_AS);

    rlim_t new_limit = 1024;
    set_limit(RLIMIT_NOFILE, new_limit);
    printf("New limit for open files set to: %lu\n", new_limit);

    print_limit("Number of open files (RLIMIT_NOFILE)", RLIMIT_NOFILE);

    return 0;
}


